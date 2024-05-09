#include <iostream>
#include <random>

#include <SFML/Graphics.hpp>

#include "particle/particle_world.h"
#include "tools/tools.h"
#include "tools/logger.h"

ParticleWorld::ParticleWorld(int rowSize, int colSize)
{
	this->rowSize = rowSize;
	this->colSize = colSize;
	particles = new ParticleInstance[rowSize * colSize];

	for (int row = 0; row < rowSize; ++row)
	{
		for (int col = 0; col < colSize; ++col)
		{
			resetParticle(row, col);
		}
	}

	sf::Image temp;

	const std::string explosionPatternPaths[] = {
		"data\\objects\\patterns\\explosion\\explosion1.png",
		"data\\objects\\patterns\\explosion\\explosion2.png",
		"data\\objects\\patterns\\explosion\\explosion3.png",
		"data\\objects\\patterns\\explosion\\explosion4.png",
		"data\\objects\\patterns\\explosion\\explosion5.png",
		"data\\objects\\patterns\\explosion\\explosion6.png",
		"data\\objects\\patterns\\explosion\\explosion7.png",
		"data\\objects\\patterns\\explosion\\explosion8.png",
		"data\\objects\\patterns\\explosion\\explosion9.png",
		"data\\objects\\patterns\\explosion\\explosion10.png",
		"data\\objects\\patterns\\explosion\\explosion11.png",
		"data\\objects\\patterns\\explosion\\explosion12.png"
	};
	for (int i = 0; i < 12; i++)
	{
		if (!temp.loadFromFile(explosionPatternPaths[i]))
		{
			Logger::log(Logger::LogType::ERROR, __func__, __LINE__, "Unable to load explosionPatterns!");
		}
		explosionPatterns.push_back(temp);
	}

	const std::string nukeExplosionPatternPaths[] = {
		"data\\objects\\patterns\\nuke_explosion\\nuke_explosion1.png",
		"data\\objects\\patterns\\nuke_explosion\\nuke_explosion2.png",
		"data\\objects\\patterns\\nuke_explosion\\nuke_explosion3.png"
	};
	for (int i = 0; i < 3; i++)
	{
		if (!temp.loadFromFile(nukeExplosionPatternPaths[i]))
		{
			Logger::log(Logger::LogType::ERROR, __func__, __LINE__, "Unable to load nukeExplosionPatterns!");
		}
		nukeExplosionPatterns.push_back(temp);
	}

	const std::string nukeMushroomCloudPaths[] = {
		"data\\objects\\patterns\\nuke_explosion\\mushroom_cloud\\mushroom_cloud1.png"
	};
	for (int i = 0; i < 1; i++)
	{
		if (!temp.loadFromFile(nukeMushroomCloudPaths[i]))
		{
			Logger::log(Logger::LogType::ERROR, __func__, __LINE__, "Unable to load mushroomCloudPatterns!");
		}
		nukeMushroomCloudPatterns.push_back(temp);
	}
}

ParticleWorld::~ParticleWorld()
{
	delete[] particles;
}

void ParticleWorld::freeze()
{
	frozen = true;
}

void ParticleWorld::unfreeze()
{
	frozen = false;
}

bool ParticleWorld::isFrozen()
{
	return frozen;
}

int ParticleWorld::getRowSize()
{
	return rowSize;
}

int ParticleWorld::getColSize()
{
	return colSize;
}

ParticleWorld::ParticleInstance ParticleWorld::getParticle(int row, int col)
{
	if (row >= 0 && row < rowSize && col >= 0 && col < colSize)
	{
		return *(particles + get1DIndex(row, col, colSize));
	}
	else
	{
		return ParticleInstance();
	}
}

void ParticleWorld::setParticle(int row, int col, ParticleWorld::ParticleInstance particleInstance)
{
	*(particles + get1DIndex(row, col, colSize)) = particleInstance;
}

void ParticleWorld::setShakeCountdown(int value)
{
	shakeCountdown = value;
}

int ParticleWorld::getShakeCountdown()
{
	return shakeCountdown;
}

void ParticleWorld::resetParticle(int row, int col)
{
	setParticle(row, col, getDefaultInstance());
}

ParticleWorld::ParticleInstance ParticleWorld::getDefaultInstance()
{
	ParticleInstance temp;
	return temp;
}