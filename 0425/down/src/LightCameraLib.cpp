#include "LightCameraLib.h"

namespace Light
{
	Matrix34 Matrix34Camera(double pitch, double yaw, double roll, Vector4 origin)
	{
		return Matrix34Translate(origin)*Matrix34Rotation(pitch, yaw, roll);
	}

	Matrix34 Matrix34CameraLookAt(Vector4 from, Vector4 look_at)
	{
		from.w = 1;
		if(look_at.iscoord()) look_at = look_at - from;
		look_at = look_at / look_at.len();
		return Matrix34Camera(asin(look_at.y), atan2(look_at.x, look_at.z), 0, from);
	}

	CameraNormal::CameraNormal()
	{
		coord = Matrix34Identical();
		width = 4.0;
		height = 3.0;
	}

	void CameraNormal::SetCoordinateSystem(Matrix34 _coord)
	{
		coord = _coord;
	}

	void CameraNormal::SetVisualField(double _width, double _height)
	{
		width = _width;
		height = _height;
	}

	Ray CameraNormal::GenerateRay(double left, double top, double right, double bottom, Random::RAND_ENGINE *eng) const
	{
		Ray ray;
		ray.o = MakePos(0, 0, 0);
		if(eng)
			ray.d = MakeVec((Random::randDouble(*eng, left, right) - 0.5) * width, (0.5 - Random::randDouble(*eng, top, bottom)) * height, 1);
		else
			ray.d = MakeVec((Random::randDouble(left, right) - 0.5) * width, (0.5 - Random::randDouble(top, bottom)) * height, 1);
		ray.d = ray.d / ray.d.len();
		ray.o = coord*ray.o;
		ray.d = coord*ray.d;
		return ray;
	}
}