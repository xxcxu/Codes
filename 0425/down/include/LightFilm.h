#pragma once
#include "LightImage.h"
#include "LightMath.h"

namespace Light
{

	double clamp01(double x);
	int F64_C8(double x);

	Color Vec2Color(Vector4 vec4);
	Color Vec2Color(Vector3 vec3);
	Vector3 Vec42Vec3(Vector4 vec4);
	Vector3 clamp01(Vector3 vec);

	class Film
	{
		Vector4 *pFilm;
		UINT width, height, MSAA;
	public:
		Film();
		~Film();
		Film(UINT w, UINT h, UINT msaa = 2);
		Vector4* GetFilmPtr();
		UINT GetWidth() const;
		UINT GetHeight() const;
		UINT GetMSAA() const;
		void GetImage(Image *pImg) const;
	};
}