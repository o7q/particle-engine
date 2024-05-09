#include <iostream>

#include "tools/random.h"
#include "tools/logger.h"

// configure Mersenne Twister pseudo-random number generator
std::random_device Random::rd;
std::mt19937 Random::gen(Random::rd());
//

void Random::init()
{
	Logger::log(Logger::LogType::INFO, __func__, __LINE__, "Initializing global random");
	reseed();
}

void Random::reseed()
{
	Logger::log(Logger::LogType::INFO, __func__, __LINE__, "Reseeding global random");
	gen.seed(rd());
}

int Random::genInt(int min, int max)
{
	std::uniform_int_distribution<int> dist(min, max);
	return dist(gen);
}

double Random::genDouble(double min, double max)
{
	std::uniform_real_distribution<double> dist(min, max);
	return dist(gen);
}