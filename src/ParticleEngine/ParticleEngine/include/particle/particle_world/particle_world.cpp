#include <iostream>
#include <random>

#include <SFML/Graphics.hpp>

#include "particle/particle_world.h"
#include "tools/tools.h"

// configure Mersenne Twister pseudo-random number generator
std::random_device ParticleWorld::rd;
std::mt19937 ParticleWorld::gen(ParticleWorld::rd());
//

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

	sf::Image image;

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
		if (!image.loadFromFile(explosionPatternPaths[i]))
		{
			// error
		}
		explosionPatterns.push_back(image);
	}
}

ParticleWorld::~ParticleWorld() {
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
	return *(particles + get1DIndex(row, col, colSize));
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

void ParticleWorld::paintParticles(int row, int col, int size, ParticleWorld::ParticleInstance particleInstance, ParticleWorld::Shape shape)
{
	std::uniform_int_distribution<int> dist(9, 10);

	switch (shape)
	{
	case ParticleWorld::Shape::Square:
		for (int rowIndex = 0; rowIndex < size; ++rowIndex)
		{
			for (int colIndex = 0; colIndex < size; ++colIndex)
			{
				if (!(row < rowSize && col < colSize && row > 0 && col > 0))
				{
					continue;
				}

				int r = rowIndex - size / 2;
				int c = colIndex - size / 2;

				int r2 = std::min(
					std::max(row + r, 0),
					rowSize - 1
				);
				int c2 = std::min(
					std::max(col + c, 0),
					colSize - 1
				);

				particleInstance.brightnessMultiplier = dist(gen) / 10.f;
				particleInstance.wetnessMultiplier = 1.0f;
				particleInstance.intValue = 0;

				setParticle(r2, c2, particleInstance);
			}
		}
		break;
	case ParticleWorld::Shape::Circle:
		for (int y = row - size; y <= row + size; ++y)
		{
			for (int x = col - size; x <= col + size; ++x)
			{
				if ((x - col) * (x - col) + (y - row) * (y - row) <= size * size)
				{
					if (!(row < rowSize && col < colSize && row > 0 && col > 0))
					{
						continue;
					}

					int r = std::min(
						std::max(y, 0),
						rowSize - 1
					);
					int c = std::min(
						std::max(x, 0),
						colSize - 1
					);

					particleInstance.brightnessMultiplier = dist(gen) / 10.f;
					particleInstance.wetnessMultiplier = 1.0f;
					particleInstance.intValue = 0;

					setParticle(r, c, particleInstance);
				}
			}
		}
		break;
	}
}

void ParticleWorld::imageToParticles(int row, int col, sf::Image& image, ParticleWorld::ParticleInstance particleInstance, bool useImageColors)
{
	sf::Vector2u imageSize = image.getSize();
	for (int rowIndex = 0; rowIndex < imageSize.y; ++rowIndex)
	{
		for (int colIndex = 0; colIndex < imageSize.x; ++colIndex)
		{
			sf::Color pixelColor = image.getPixel(colIndex, rowIndex);

			if (static_cast<int>(pixelColor.a) != 0)
			{
				if (useImageColors)
				{
					particleInstance.color = pixelColor;
					particleInstance.overrideColor = true;
				}

				int r = std::min(
					std::max(rowIndex + row - static_cast<int>(imageSize.y) / 2, 0),
					rowSize - 1
				);
				int c = std::min(
					std::max(colIndex + col - static_cast<int>(imageSize.x) / 2, 0),
					colSize - 1
				);

				setParticle(r, c, particleInstance);
			}
		}
	}
}