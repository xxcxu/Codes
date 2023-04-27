#include "LightFilm.h"

namespace Light
{
	
	double clamp01(double x)
	{
		return x < 0 ? 0 : x > 1 ? 1 : x;
	}

	int F64_C8(double x)
	{
		return clamp01(x)*255.0 + 0.5;
	}

	Vector3 Vec42Vec3(Vector4 vec4)
	{
		if(vec4.w < EPS) return MakeVector3();
		return MakeVector3(vec4.x, vec4.y, vec4.z)*(1.0/vec4.w);
	}

	Vector3 clamp01(Vector3 vec)
	{
		return MakeVector3(clamp01(vec.x), clamp01(vec.y), clamp01(vec.z));
	}

	Color Vec2Color(Vector4 vec4)
	{
		return Vec2Color(Vec42Vec3(vec4));
	}

	Color Vec2Color(Vector3 vec3)
	{
		return Color(
			F64_C8(vec3.x),
			F64_C8(vec3.y),
			F64_C8(vec3.z)
		);
	}

	Film::Film()
	{
		pFilm = NULL;
		width = 0;
		height = 0;
	}

	Film::Film(UINT w, UINT h, UINT msaa)
	{
		msaa = std::min(msaa, 16u);
		pFilm = new Vector4[w*h*msaa*msaa];
		width = w;
		height = h;
		MSAA = msaa;
		memset(pFilm, 0, sizeof(Vector4)*w*h*msaa*msaa);
	}

	Film::~Film()
	{
		if(pFilm) delete[] pFilm;
		pFilm = 0;
	}

	UINT Film::GetWidth() const { return width; }
	UINT Film::GetHeight() const { return height; }
	UINT Film::GetMSAA() const { return MSAA; }

	Vector4* Film::GetFilmPtr() { return pFilm; }

	void Film::GetImage(Image * pImg) const
	{
		if (!width || !height) return;
		if (pImg->GetWidth() != width || pImg->GetHeight() != height)
			pImg->Resize(width, height);
		Color * pixels = pImg->GetColorPtr();
		double inv_msaa_sq = 1.0 / (double)(MSAA*MSAA);
		for (UINT p = 0; p < width*height; p++)
		{
			UINT i = p*MSAA*MSAA;
			Vector3 RGB = MakeVector3();
			for (int j = 0; j < MSAA*MSAA; j++)
				RGB = RGB + clamp01(Vec42Vec3(pFilm[i + j]))*inv_msaa_sq;
			pixels[p] = Vec2Color(RGB);
		}
	}
}