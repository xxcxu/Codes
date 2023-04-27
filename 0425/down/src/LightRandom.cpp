#include "LightRandom.h"

namespace Light
{
	namespace Random
	{
		RAND_ENGINE g_random_device;

		void initSeedByTime()
		{
			g_random_device = RAND_ENGINE(time(NULL));
		}

		double randDouble(double _min, double _max)
		{
			return std::uniform_real_distribution<>(_min, _max)(g_random_device);
		}

		int randInt(int _min, int _max)
		{
			return std::uniform_int_distribution<>(_min, _max)(g_random_device);
		}

		double randDouble(RAND_ENGINE *eng, double _min, double _max)
		{
			if(eng)
				return std::uniform_real_distribution<>(_min, _max)(*eng);
			else
				return std::uniform_real_distribution<>(_min, _max)(g_random_device);
		}

		int randInt(RAND_ENGINE *eng, int _min, int _max)
		{
			if(eng)
				return std::uniform_int_distribution<>(_min, _max)(*eng);
			else
				return std::uniform_int_distribution<>(_min, _max)(g_random_device);
		}

		double randDouble(RAND_ENGINE &eng, double _min, double _max)
		{
			return std::uniform_real_distribution<>(_min, _max)(eng);
		}

		int randInt(RAND_ENGINE &eng, int _min, int _max)
		{
			return std::uniform_int_distribution<>(_min, _max)(eng);
		}
	}
};