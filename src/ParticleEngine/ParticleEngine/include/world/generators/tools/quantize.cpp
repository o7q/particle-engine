#include <iostream>
#include <limits>

#include "world/world_generator.h"

int quantizeValue(int input, int* values, int valuesSize)
{
	double closestDistance = std::numeric_limits<double>::max();
	int closestIndex = 0;

	for (int i = 0; i < valuesSize; ++i)
	{
		double distance = std::sqrt(std::pow(input - values[i], 2));

		if (distance < closestDistance)
		{
			closestDistance = distance;
			closestIndex = i;
		}
	}

	return closestIndex;
}