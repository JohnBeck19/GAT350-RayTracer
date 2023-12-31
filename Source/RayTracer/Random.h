#pragma once
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>

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
inline glm::vec3 random(const glm::vec3& min, const glm::vec3& max)
{
	return glm::vec3(random(min.x, max.x), random(min.y, max.y), random(min.z, max.z));

}
inline glm::vec3 randomInUnitSphere()
{
	glm::vec3 v;
	// generate random vectors between -1 <-> +1, return vector if length is less than 1
	do
	{
		v = random(glm::vec3(-1, -1, -1), glm::vec3(1, 1, 1));
	} while (glm::length2(v) >= 1.0f);

		return v;
}