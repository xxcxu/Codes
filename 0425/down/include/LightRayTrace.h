#pragma once
#include "LightScene.h"

namespace Light
{
    struct Source
    {
        Vector4 pos;
        Vector3 intensity;
    };

    Scene* GetRayTraceScene(Camera * _pcamara, Film * _pfilm, Model * _pmodel, Source * _psource, int nsource, Vector3 ambient = MakeVector3());
}