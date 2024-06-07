#include <iostream>
#include <random>

#include <SFML/Graphics.hpp>

#include "particle/particle_world.hpp"
#include "tools/tools.hpp"
#include "tools/logger.hpp"

ParticleWorld::ParticleWorld(int rowSize, int colSize)
{
	this->rowSize = rowSize;
	this->colSize = colSize;
	particles = new Particle[rowSize * colSize];
	worldPixels = new sf::Uint8[rowSize * colSize * 4];
	worldTexture.create(colSize, rowSize);

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

ParticleWorld::Particle ParticleWorld::getParticle(int row, int col)
{
	if (row >= 0 && row < rowSize && col >= 0 && col < colSize)
	{
		return *(particles + get1DIndex(row, col, colSize));
	}
	else
	{
		return Particle();
	}
}

void ParticleWorld::setParticle(int row, int col, ParticleWorld::Particle particle)
{
	*(particles + get1DIndex(row, col, colSize)) = particle;

	int index = get1DIndex(row, col, colSize) * 4;
	sf::Color particleColor = determineParticleColor(particle);

	worldPixels[index + 0] = particleColor.r;
	worldPixels[index + 1] = particleColor.g;
	worldPixels[index + 2] = particleColor.b;
	worldPixels[index + 3] = particleColor.a;
}

void ParticleWorld::resetParticle(int row, int col)
{
	setParticle(row, col, Particle());
}

sf::Uint8* ParticleWorld::getWorldPixels()
{
	return worldPixels;
}

sf::Texture& ParticleWorld::getWorldTexture()
{
	return worldTexture;
}

sf::Vector2u ParticleWorld::getWorldSize()
{
	return sf::Vector2u(colSize, rowSize);
}

void ParticleWorld::updatePixels()
{
	worldTexture.update(worldPixels);
}

sf::Color ParticleWorld::determineParticleColor(Particle particle)
{
	if (particle.overrideColor)
	{
		return particle.overriddenColor;
	}

	sf::Color c(0, 0, 0, 255);

	switch (particle.material)
	{
	case ParticleWorld::Material::Stone: {
		c = sf::Color(160, 160, 160, 255);
		break;
	}
	case ParticleWorld::Material::Sand: {
		c = sf::Color(245, 228, 118, 255);
		break;
	}
	case ParticleWorld::Material::Sandstone: {
		c = sf::Color(189, 176, 91, 255);
		break;
	}
	case ParticleWorld::Material::Dirt: {
		c = sf::Color(77, 54, 15, 255);
		break;
	}
	case ParticleWorld::Material::DarkDirt: {
		c = sf::Color(38, 27, 7, 255);
		break;
	}
	case ParticleWorld::Material::Grass: {
		c = sf::Color(60, 110, 33, 255);
		break;
	}
	case ParticleWorld::Material::RedFlower: {
		c = sf::Color(255, 59, 59, 255);
		break;
	}
	case ParticleWorld::Material::PinkFlower: {
		c = sf::Color(246, 122, 255, 255);
		break;
	}
	case ParticleWorld::Material::YellowFlower: {
		c = sf::Color(255, 222, 92, 255);
		break;
	}
	case ParticleWorld::Material::BlueFlower: {
		c = sf::Color(84, 178, 255, 255);
		break;
	}
	case ParticleWorld::Material::Water: {
		c = sf::Color(34, 152, 218, 200);
		break;
	}
	case ParticleWorld::Material::SwampWater: {
		c = sf::Color(85, 92, 69, 220);
		break;
	}
	case ParticleWorld::Material::Gasoline: {
		c = sf::Color(215, 219, 77, 230);
		break;
	}
	case ParticleWorld::Material::Fire: {
		c = sf::Color(255, 191, 0, 255);
		break;
	}
	case ParticleWorld::Material::Ice: {
		c = sf::Color(120, 212, 240, 240);
		break;
	}
	case ParticleWorld::Material::Smoke: {
		c = sf::Color(120, 120, 120, 240);
		break;
	}
	case ParticleWorld::Material::Steam: {
		c = sf::Color(220, 220, 220, 220);
		break;
	}
	case ParticleWorld::Material::AcidGas: {
		c = sf::Color(81, 97, 47, 235);
		break;
	}
	case ParticleWorld::Material::FlammableGas: {
		c = sf::Color(156, 133, 81, 235);
		break;
	}
	case ParticleWorld::Material::Acid: {
		c = sf::Color(225, 255, 125, 200);
		break;
	}
	case ParticleWorld::Material::Dynamite: {
		c = sf::Color(110, 33, 29, 255);
		break;
	}
	case ParticleWorld::Material::Nuke: {
		c = sf::Color(63, 107, 49, 255);
		break;
	}
	}

	c.r /= particle.wetnessMultiplier;
	c.r *= particle.brightnessMultiplier;

	c.g /= particle.wetnessMultiplier;
	c.g *= particle.brightnessMultiplier;

	c.b /= particle.wetnessMultiplier;
	c.b *= particle.brightnessMultiplier;

	return c;
}