#pragma once
#include "LightMath.h"
#include "LightModel.h"
#include "LightRandom.h"

namespace Light
{
	struct Camera
	{
	public:
		virtual Ray GenerateRay(double left, double top, double right, double bottom, Random::RAND_ENGINE *eng = NULL) const = 0;
		/*
		在对应底片矩形区域内生成一个光线
		参数应在[0,1]范围内
		*/
	};
};