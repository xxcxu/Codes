#pragma once

#include "LightCameraLib.h"
#include "LightFilm.h"
#include <thread>
#include <mutex>
#include <queue>
#include <sstream>
#include <cstdlib>

namespace Light
{
	struct RenderTask
	{
		UINT x, y, spp;
	};

	struct RenderResult
	{
		UINT x, y;
		Vector4 sampl[256];
	};

	class Scene
	{
	public:
		Camera * pCam;
		Film * pFilm;
		std::mutex task_mtx;
		std::mutex res_mtx;
		std::queue<RenderTask> q_task;
		std::queue<RenderResult> q_res;
		virtual Vector3 SampleRay(const Ray & ray, Random::RAND_ENGINE *eng = 0);
		Scene();
		Scene(Camera * _pcamara, Film * _pfilm);
		void Render(const char* task_name, int spp_per_round, int nthread = 0, bool display = false, int round = 0);
	};
}

