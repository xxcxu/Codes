#pragma once
#include "LightCamera.h"

namespace Light
{

	Matrix34 Matrix34Camera(double pitch, double yaw, double roll, Vector4 origin);

	Matrix34 Matrix34CameraLookAt(Vector4 from, Vector4 look_at);

	class CameraNormal: public Camera
	{
		Matrix34 coord;
		double width, height;
	public:
		CameraNormal();
		void SetCoordinateSystem(Matrix34 _coord);
		void SetVisualField(double _width, double _height);
		Ray GenerateRay(double left, double top, double right, double bottom, Random::RAND_ENGINE *eng = NULL) const;
	};//*/
}