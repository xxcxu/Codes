#pragma once
#include "LightCamera.h"

namespace Light
{
    class CameraPanorama: public Camera
	{
		Matrix34 coord;
	public:
		CameraPanorama();
		void SetCoordinateSystem(Matrix34 _coord);
		Ray GenerateRay(double left, double top, double right, double bottom, Random::RAND_ENGINE *eng = NULL) const;
		Ray GenerateRay(double x, double y) const;
	};
}