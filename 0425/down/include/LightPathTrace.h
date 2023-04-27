#pragma once
#include "LightScene.h"
#include "LightModel.h"

namespace Light
{
    struct Source
    {
        Triangle triangle;
        Vector3 luminance;
    };

    Scene* GetPathTraceScene(Camera * _pcamara, Film * _pfilm, Model * _pmodel, Source * _psource, int nsource);
}