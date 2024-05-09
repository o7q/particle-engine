#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>

#include "world/world_generator.h"

#include "tools/logger.h"

std::vector<sf::Image> ocean_getObjects()
{
	Logger::log(Logger::LogType::INFO, __func__, __LINE__, "Loading ocean objects");

	std::vector<sf::Image> ocean_objects;

	sf::Image temp;

	const std::string oceanObjectPaths[] = {
		"data\\objects\\foliage\\seaweed\\seaweed1.png",
		"data\\objects\\foliage\\seaweed\\seaweed2.png",
		"data\\objects\\foliage\\seaweed\\seaweed3.png",
		"data\\objects\\foliage\\seaweed\\seaweed4.png",
		"data\\objects\\foliage\\seaweed\\seaweed5.png",
		"data\\objects\\foliage\\seaweed\\seaweed6.png",
		"data\\objects\\foliage\\seaweed\\seaweed7.png",
		"data\\objects\\foliage\\seaweed\\seaweed8.png",
		"data\\objects\\foliage\\seaweed\\seaweed9.png",
		"data\\objects\\foliage\\seaweed\\seaweed10.png",
		"data\\objects\\foliage\\seaweed\\seaweed11.png",
		"data\\objects\\foliage\\seaweed\\seaweed12.png",
		"data\\objects\\foliage\\seaweed\\seaweed13.png",
		"data\\objects\\foliage\\seaweed\\seaweed14.png",
		"data\\objects\\foliage\\seaweed\\seaweed15.png"
	};
	for (int i = 0; i < 15; i++)
	{
		if (!temp.loadFromFile(oceanObjectPaths[i]))
		{
			Logger::log(Logger::LogType::ERROR, __func__, __LINE__, "Unable to load oceanObjects!");
		}
		ocean_objects.push_back(temp);
	}

	return ocean_objects;
}