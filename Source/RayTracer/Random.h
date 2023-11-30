#pragma once
#include <cstdlib>
#include <ctime>
#include <algorithm>

inline void seedRandom(unsigned int seed)
{
	std::srand(seed);
}

inline float random01()
{
	return ((float)(rand() / (float)RAND_MAX));
}

inline float random(float min, float max)
{
	//<if (min > max) swap values 
	if (min > max)	std::swap(min, max);
	return min + (random01()*(max - min));
}