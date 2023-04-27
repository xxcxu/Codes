#pragma once
#include <random>
#include <ctime>

namespace Light
{
	namespace Random
	{
		typedef std::mt19937_64 RAND_ENGINE;
		void initSeedByTime();
		double randDouble(double _min = 0.0, double _max = 1.0);
		int randInt(int _min = 0, int _max = 2147483647);

		double randDouble(RAND_ENGINE *eng, double _min = 0.0, double _max = 1.0);
		int randInt(RAND_ENGINE *eng, int _min = 0, int _max = 2147483647);

		double randDouble(RAND_ENGINE &eng, double _min = 0.0, double _max = 1.0);
		int randInt(RAND_ENGINE &eng, int _min = 0, int _max = 2147483647);
	}
};