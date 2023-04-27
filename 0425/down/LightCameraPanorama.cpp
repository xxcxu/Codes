#include "include/LightCameraPanorama.h"

namespace Light
{

    CameraPanorama::CameraPanorama()
    {
        coord = Matrix34();
    }

    void CameraPanorama::SetCoordinateSystem(Matrix34 _coord)
    {
        coord = _coord;
    }

    Ray CameraPanorama::GenerateRay(double left, double top, double right, double bottom, Random::RAND_ENGINE *eng) const
    {
        double
        x = Random::randDouble(eng, left, right),
        y = Random::randDouble(eng, top, bottom);
        return GenerateRay(x, y);
    }

    Ray CameraPanorama::GenerateRay(double x, double y) const
    {
        return Ray();
    }
}