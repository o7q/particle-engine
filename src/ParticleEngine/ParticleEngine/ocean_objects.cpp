#include <iostream>
#include <vector>
#include "SFML/Graphics.hpp"
#include "world/world_generator.h"

std::vector<sf::Image> ocean_getObjects()
{
	std::vector<sf::Image> ocean_objects;
	sf::Image seaweed1;
	if (!seaweed1.loadFromFile("data\\objects\\foliage\\seaweed\\seaweed1.png"))
	{
		// error
	}

	ocean_objects.push_back(seaweed1);
	return ocean_objects;
}