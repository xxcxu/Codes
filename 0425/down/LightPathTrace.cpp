#include "include/LightPathTrace.h"


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
        nSource = 0;
	}

	ScenePathTrace::ScenePathTrace(Camera * _pcamara, Film * _pfilm, Model * _pmodel, Source * _psource, int nsource)
	{
		pFilm = _pfilm;
		pCam = _pcamara;
		pSource = _psource;
		pModel = _pmodel;
        nSource = nsource;
	}

    Scene* GetPathTraceScene(Camera * _pcamara, Film * _pfilm, Model * _pmodel, Source * _psource, int nsource)
    {
        return new ScenePathTrace(_pcamara, _pfilm, _pmodel, _psource, nsource);
    }

	Vector3 ScenePathTrace::SampleRay(const Ray & ray, Random::RAND_ENGINE *eng)
	{
		/*
		你需要完善这个函数，实现路径追踪的功能
		你可以对这个类添加任意的函数或变量，你也可以通过将数据导出的方式在类外实现功能，只要此函数的返回值满足采样要求即可
		祝一切顺利
		*/
		return MakeVector3();
	}
}