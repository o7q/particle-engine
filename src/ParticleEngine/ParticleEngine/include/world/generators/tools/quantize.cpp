#include <iostream>
#include <limits>

#include "world/world_generator.hpp"

int quantizeValue(int input, int* values, int valuesSize)
{
	float closestDistance = std::numeric_limits<float>::max();
	int closestIndex = 0;

	for (int i = 0; i < valuesSize; ++i)
	{
		float distance = std::sqrt(std::pow(input - values[i], 2));

		if (distance < closestDistance)
		{
			closestDistance = distance;
			closestIndex = i;
		}
	}

	return closestIndex;
}