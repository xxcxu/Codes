#include "LightScene.h"

namespace Light
{	
	Vector3 Scene::SampleRay(const Ray & ray, Random::RAND_ENGINE *eng)
	{
		return MakeVector3();
	}

	Scene::Scene()
	{
		pCam = 0;
		pFilm = 0;
	}

	Scene::Scene(Camera * _pcamara, Film * _pfilm)
	{
		pCam = _pcamara;
		pFilm = _pfilm;
	}

	void RenderThread(Scene * scene, int tid, bool derandom = false)
	{
		Random::RAND_ENGINE rd(tid);
		UINT w = scene->pFilm->GetWidth(), h = scene->pFilm->GetHeight();
		UINT MSAA = scene->pFilm->GetMSAA();
		double inv_w = 1.0 / (double)w, inv_h = 1.0 / (double)h;
		double inv_w_msaa = inv_w / (double) MSAA, inv_h_msaa = inv_h / (double) MSAA;
		RenderTask task[32];
		RenderResult task_result[32];
		int task_recved = 0;
		bool done = false;
		while(!done)
		{
			scene->task_mtx.lock();
			for (int i = 0; i < 32; i++)
			{
				if (!scene->q_task.empty())
				{
					task[i] = scene->q_task.front();
					if (!task[i].spp)
					{
						done = 1;
						break;
					}
					task_recved++;
					scene->q_task.pop();
				}
				else
				 	break;
			}
			scene->task_mtx.unlock();

			for (int t = 0; t < task_recved; t++)
			{
				task_result[t].x = task[t].x;
				task_result[t].y = task[t].y;
				for (UINT spid = 0; spid < MSAA*MSAA; spid++)
					task_result[t].sampl[spid] = MakeVector4();
				UINT spsp = task[t].spp / (MSAA*MSAA);
				for(UINT spid = 0; spid < MSAA*MSAA; spid++)
				{
					UINT spx = spid % MSAA, spy = spid / MSAA;
					double left = task[t].x * inv_w  + spx * inv_w_msaa, right = task[t].x * inv_w + (spx + 1) * inv_w_msaa;
					double top = task[t].y * inv_h + spy * inv_h_msaa, bottom = task[t].y * inv_h + (spy + 1) * inv_h_msaa;
					if (derandom)
						left = right = (left + right) * 0.5,
						top = bottom = (top + bottom) * 0.5;
					for(UINT samp = 0; samp < spsp; samp++)
					{
						Ray ray = scene->pCam->GenerateRay(left, top, right, bottom, &rd);
						Vector4 sampl_color = MakeVector4(scene->SampleRay(ray, &rd), 1);
						task_result[t].sampl[spid] = task_result[t].sampl[spid] + sampl_color;
					}
				}
			}
			if (task_recved)
			{
				scene->res_mtx.lock();
				for (int t = 0; t < task_recved; t++)
					scene->q_res.push(task_result[t]);
				task_recved = 0;
				scene->res_mtx.unlock();
			}
			//std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
	}

	void Scene::Render(const char * task_name, int spp_per_round, int nthread, bool display, int round)
	{

		UINT w = pFilm->GetWidth(), h = pFilm->GetHeight();
		UINT MSAA = pFilm->GetMSAA();
		char cmd[1024];
#ifdef _WIN32

		sprintf(cmd, "mkdir image_output\\%s", task_name);
#else
		sprintf(cmd, "mkdir -p image_output/%s", task_name);
#endif
		int ignore_warning_ret_system;
		ignore_warning_ret_system = system("mkdir -p image_output");
		ignore_warning_ret_system = system(cmd);
		Random::RAND_ENGINE rd(time(NULL));
		if (!nthread) nthread = std::thread::hardware_concurrency()-2;
		std::thread *render_threads;
		render_threads = new std::thread[nthread];
		spp_per_round = ((spp_per_round - 1) / (MSAA*MSAA) + 1) * (MSAA*MSAA);
		for (int i = 0; i < nthread; i++)
			render_threads[i] = std::thread(RenderThread, this, Random::randInt(rd), (spp_per_round == MSAA*MSAA) && (round == 1));
		printf("Light Rendering...\nTask: %s\nSPP per round: %d\nThreads: %d\n", task_name, spp_per_round, nthread);
		double inv_w = 1.0 / (double)w, inv_h = 1.0 / (double)h;
		double inv_wh = inv_w * inv_h;


		Vector4 *res_buffer = pFilm->GetFilmPtr();
		
		int total_spp = 0;
		int last_recved = 0, new_recved = 0;
		int result_recved = 0, result_total = 0;
		double recv_rate = 0.0;
		bool task_finished = true;
		std::vector<std::pair<UINT, UINT>> vec_pos;
		for (UINT y = 0; y < h; y++)
			for (UINT x = 0; x < w; x++)
				vec_pos.push_back(std::make_pair(x, y));
		Image img;
		int finished_round = 0;
		while(true)
		{
			if (task_finished)
			{
				task_mtx.lock();
				for (UINT p = 0; p < w * h; p++)
					std::swap(vec_pos[p], vec_pos[Random::randInt(rd, 0, w * h - 1)]);
				result_total = 0;
				for (UINT p = 0; p < w * h; p++)
				{
					UINT x, y;
					x = vec_pos[p].first;
					y = vec_pos[p].second;
					int i = (y*w + x)*MSAA*MSAA;
					int super_sample_scale = 1;
					Vector3 sum_sq = MakeVector3(), sum = MakeVector3();
					double sigma[3] = {};
					for (int j = 0; j < MSAA*MSAA; j++)
					{
						Vector3 rgb = clamp01(Vec42Vec3(res_buffer[i+j]));
						sum_sq = sum_sq + rgb*rgb;
						sum = sum + rgb;
					}
					for (int c = 0; c < 3; c++)
						sigma[c] = sum_sq._[c] / (double)(MSAA*MSAA) - (sum._[c]*sum._[c]) / (double)(MSAA*MSAA*MSAA*MSAA);
					double max_sigma = std::max(sigma[0], std::max(sigma[1], sigma[2]));
					super_sample_scale = std::max(1, std::min((int)(max_sigma * 4 * 64), 16));
					for (int _ = 0; _ < super_sample_scale; _++)
						q_task.push(RenderTask({x,y,(UINT)spp_per_round}));
					result_total += super_sample_scale;
				}
				task_mtx.unlock();
				task_finished = false;
			}
			recv_rate = (double)result_recved / (double)result_total;
			new_recved = result_recved - last_recved;
			if (new_recved < 0)new_recved = 0;
			printf("progress: %.2lf%%, recv: %d, total: %d  %.0lfK sample/sec\n", recv_rate * 100.0, result_recved, result_total, (double)(new_recved * spp_per_round)*(double)0.001);
			last_recved = result_recved;
			res_mtx.lock();
			while(!q_res.empty())
			{
				RenderResult res = q_res.front(); q_res.pop();
				for (UINT spid = 0; spid < MSAA*MSAA; spid++)
					res_buffer[(res.y*w + res.x)*MSAA*MSAA + spid] = res_buffer[(res.y*w + res.x)*MSAA*MSAA+spid] + res.sampl[spid];
				result_recved++;
			}
			res_mtx.unlock();
			pFilm->GetImage(&img);

			if(result_recved == result_total)
			{
				task_finished = true;
				result_recved = 0;
				char save_name[1024];
				total_spp += spp_per_round;
				printf("%d spp finished.\n", total_spp);

				time_t tt = time(NULL);
				tm* lt = localtime(&tt);

#ifdef _WIN32
				sprintf(save_name, "image_output\\%s\\%dspp_%d_%02d_%02d_%02d_%02d_%02d.bmp",
#else
				sprintf(save_name, "image_output/%s/%dspp_%d_%02d_%02d_%02d_%02d_%02d.bmp",
#endif
				task_name,
				total_spp,
				lt->tm_year + 1900,
				lt->tm_mon + 1,
				lt->tm_mday,
				lt->tm_hour,
				lt->tm_min,
				lt->tm_sec);
				img.SaveBitmapToFile(save_name);
#ifdef _WIN32
				sprintf(save_name, "image_output\\%s\\%dspp_%d_%02d_%02d_%02d_%02d_%02d.image",
#else
				sprintf(save_name, "image_output/%s/%dspp_%d_%02d_%02d_%02d_%02d_%02d.image",
#endif
				task_name,
				total_spp,
				lt->tm_year + 1900,
				lt->tm_mon + 1,
				lt->tm_mday,
				lt->tm_hour,
				lt->tm_min,
				lt->tm_sec);
				img.SaveToFile(save_name);
				finished_round++;
				if (finished_round == round) break;
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		}
		task_mtx.lock();
		q_task.push(RenderTask({-1u, -1u, 0u}));
		task_mtx.unlock();
		for (int i = 0; i < nthread; i++)
			if (render_threads[i].joinable())
				render_threads[i].join();
	}

}