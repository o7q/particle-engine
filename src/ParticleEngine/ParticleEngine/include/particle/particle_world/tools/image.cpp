#include "particle/particle_world.h"

#include "tools/random.h"

void ParticleWorld::paintParticles(int row, int col, int size, ParticleWorld::ParticleInstance particleInstance, ParticleWorld::Shape shape)
{
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

				particleInstance.brightnessMultiplier = Random::genDouble(0.9, 1.0);
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

					particleInstance.brightnessMultiplier = Random::genDouble(0.9, 1.0);
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