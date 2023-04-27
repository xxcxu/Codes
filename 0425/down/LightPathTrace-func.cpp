#include "LightPathTrace.h"


namespace Light
{
	class ScenePathTrace: public Scene
	{
	public:
        int nSource;
		Source * pSource;
		Model * pModel;
		
		ScenePathTrace();
		ScenePathTrace(Camera * _pcamara, Film * _pfilm, Model * _pmodel, Source * _psource, int nsource);
		virtual Vector3 SampleRay(const Ray & ray, Random::RAND_ENGINE *eng = 0);
	};

	ScenePathTrace::ScenePathTrace()
	{
		pFilm = 0;
		pCam = 0;
		pSource = 0;
		pModel = 0;
	}

	ScenePathTrace::ScenePathTrace(Camera * _pcamara, Film * _pfilm, Model * _pmodel, Source * _psource, int nsource)
	{
		pFilm = _pfilm;
		pCam = _pcamara;
		pSource = _psource;
		pModel = _pmodel;
        nSource = nsource;
	}

    int nSource;
	Source *pSource;
	Model *pModel;
    
    Scene* GetPathTraceScene(Camera * _pcamara, Film * _pfilm, Model * _pmodel, Source * _psource, int nsource)
    {
		pSource = _psource;
		pModel = _pmodel;
        nSource = nsource;
        return new ScenePathTrace(_pcamara, _pfilm, _pmodel, _psource, nsource);
    }

	Vector3 SampleRay(const Ray & ray, Random::RAND_ENGINE *eng);

	Vector3 ScenePathTrace::SampleRay(const Ray & ray, Random::RAND_ENGINE *eng)
	{
		return Light::SampleRay(ray, eng);
	}

    /*
    这个文件帮你进行了一次简单的再封装，
	如果你不清楚类和成员函数是怎么工作的，
	你可以在此文件的基础上通过一些普通函数实现你的功能
    */

	Vector3 SampleRay(const Ray & ray, Random::RAND_ENGINE *eng)
	{
		return MakeVector3();
	}
}