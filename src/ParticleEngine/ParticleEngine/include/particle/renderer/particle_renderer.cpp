#include <iostream>

#include "particle/particle_world.h"
#include "particle/particle_renderer.h"

#include "tools/tools.h"

ParticleRenderer::ParticleRenderer(sf::Vector2u size)
{
	this->size = size;
	this->zoomLevel = 1;
	quadClump = sf::VertexArray(sf::Quads);
	resizeQuadClump();
}

void ParticleRenderer::zoom(float zoomAmount)
{
	zoomLevel += zoomAmount;
	zoomLevel = std::max(zoomLevel, 1.0f);

	resizeQuadClump();
}

float ParticleRenderer::getZoom()
{
	return this->zoomLevel;
}

sf::Vector2u ParticleRenderer::getSize()
{
	return this->size;
}

void ParticleRenderer::translate(Direction direction)
{
	switch (direction)
	{
	case Direction::UP:
		position.y -= 5.0f / this->zoomLevel;
		break;
	case Direction::DOWN:
		position.y += 5.0f / this->zoomLevel;
		break;
	case Direction::RIGHT:
		position.x += 5.0f / this->zoomLevel;
		break;
	case Direction::LEFT:
		position.x -= 5.0f / this->zoomLevel;
		break;
	}
}

sf::Vector2f ParticleRenderer::getTranslate()
{
	return this->position;
}

void ParticleRenderer::setTranslate(sf::Vector2f position)
{
	this->position = position;
}

void ParticleRenderer::resizeQuadClump()
{
	quadClump.clear();
	quadClump.resize(((size.x * size.y) / zoomLevel) * 4);
}

int ParticleRenderer::render(ParticleWorld* particleWorld, sf::RenderWindow& renderWindow, sf::Vector2i uiOffset)
{
	int particleCount = 0;
	int quadClumpIndex = 0;


	int minRow = size.y / 2 - size.y / 2 / zoomLevel;
	int maxRow = size.y / 2 + size.y / 2 / zoomLevel;

	int minCol = size.x / 2 - size.x / 2 / zoomLevel;
	int maxCol = size.x / 2 + size.x / 2 / zoomLevel;

	int nRows = maxRow - minRow;
	int nCols = maxCol - minCol;

	//for (int row = 0; row < size.y / zoomLevel; ++row)
	for (int row = minRow; row < maxRow; ++row)
	{
		//for (int col = 0; col < size.x / zoomLevel; ++col)
		for (int col = minCol; col < maxCol; ++col)
		{
			int newRow = row + position.y;
			int newCol = col + position.x;

			ParticleWorld::ParticleInstance currentParticle = particleWorld->getParticle(newRow, newCol);

			float brightnessColor = currentParticle.brightnessMultiplier;
			float brightnessColor2 = brightnessColor == 1 ? 1 : 0.99f;
			float wetnessColor = currentParticle.wetnessMultiplier;
			bool overrideColor = currentParticle.overrideColor;

			sf::Color pixelColor(currentParticle.color);

			if (!overrideColor)
			{
				switch (currentParticle.material)
				{
				case ParticleWorld::Material::Stone: {
					pixelColor.r = static_cast<sf::Uint8>(160 * brightnessColor);
					pixelColor.g = static_cast<sf::Uint8>(160 * brightnessColor);
					pixelColor.b = static_cast<sf::Uint8>(160 * brightnessColor);
					pixelColor.a = 255;

					particleCount++;
					break;
				}
				case ParticleWorld::Material::Sand: {
					pixelColor.r = static_cast<sf::Uint8>(245 / wetnessColor * brightnessColor);
					pixelColor.g = static_cast<sf::Uint8>(228 / wetnessColor * brightnessColor);
					pixelColor.b = static_cast<sf::Uint8>(118 / wetnessColor * brightnessColor);
					pixelColor.a = 255;

					particleCount++;
					break;
				}
				case ParticleWorld::Material::Sandstone: {
					pixelColor.r = static_cast<sf::Uint8>(189 / wetnessColor * brightnessColor);
					pixelColor.g = static_cast<sf::Uint8>(176 / wetnessColor * brightnessColor);
					pixelColor.b = static_cast<sf::Uint8>(91 / wetnessColor * brightnessColor);
					pixelColor.a = 255;

					particleCount++;
					break;
				}
				case ParticleWorld::Material::Dirt: {
					pixelColor.r = static_cast<sf::Uint8>(77 / wetnessColor * brightnessColor);
					pixelColor.g = static_cast<sf::Uint8>(54 / wetnessColor * brightnessColor);
					pixelColor.b = static_cast<sf::Uint8>(15 / wetnessColor * brightnessColor);
					pixelColor.a = 255;

					particleCount++;
					break;
				}
				case ParticleWorld::Material::DarkDirt: {
					pixelColor.r = static_cast<sf::Uint8>(38 / wetnessColor * brightnessColor);
					pixelColor.g = static_cast<sf::Uint8>(27 / wetnessColor * brightnessColor);
					pixelColor.b = static_cast<sf::Uint8>(7 / wetnessColor * brightnessColor);
					pixelColor.a = 255;

					particleCount++;
					break;
				}
				case ParticleWorld::Material::Grass: {
					pixelColor.r = static_cast<sf::Uint8>(60 * brightnessColor);
					pixelColor.g = static_cast<sf::Uint8>(110 * brightnessColor);
					pixelColor.b = static_cast<sf::Uint8>(33 * brightnessColor);
					pixelColor.a = 255;

					particleCount++;
					break;
				}
				case ParticleWorld::Material::RedFlower: {
					pixelColor.r = static_cast<sf::Uint8>(255 * brightnessColor);
					pixelColor.g = static_cast<sf::Uint8>(59 * brightnessColor);
					pixelColor.b = static_cast<sf::Uint8>(59 * brightnessColor);
					pixelColor.a = 255;

					particleCount++;
					break;
				}
				case ParticleWorld::Material::PinkFlower: {
					pixelColor.r = static_cast<sf::Uint8>(246 * brightnessColor);
					pixelColor.g = static_cast<sf::Uint8>(122 * brightnessColor);
					pixelColor.b = static_cast<sf::Uint8>(255 * brightnessColor);
					pixelColor.a = 255;

					particleCount++;
					break;
				}
				case ParticleWorld::Material::YellowFlower: {
					pixelColor.r = static_cast<sf::Uint8>(255 * brightnessColor);
					pixelColor.g = static_cast<sf::Uint8>(222 * brightnessColor);
					pixelColor.b = static_cast<sf::Uint8>(92 * brightnessColor);
					pixelColor.a = 255;

					particleCount++;
					break;
				}
				case ParticleWorld::Material::BlueFlower: {
					pixelColor.r = static_cast<sf::Uint8>(84 * brightnessColor);
					pixelColor.g = static_cast<sf::Uint8>(178 * brightnessColor);
					pixelColor.b = static_cast<sf::Uint8>(255 * brightnessColor);
					pixelColor.a = 255;

					particleCount++;
					break;
				}
				case ParticleWorld::Material::Water: {
					pixelColor.r = static_cast<sf::Uint8>(34 * brightnessColor2);
					pixelColor.g = static_cast<sf::Uint8>(152 * brightnessColor2);
					pixelColor.b = static_cast<sf::Uint8>(218 * brightnessColor2);
					pixelColor.a = 200;

					particleCount++;
					break;
				}
				case ParticleWorld::Material::SwampWater: {
					pixelColor.r = static_cast<sf::Uint8>(85 * brightnessColor);
					pixelColor.g = static_cast<sf::Uint8>(92 * brightnessColor);
					pixelColor.b = static_cast<sf::Uint8>(69 * brightnessColor);
					pixelColor.a = 220;

					particleCount++;
					break;
				}
				case ParticleWorld::Material::Gasoline: {
					pixelColor.r = 215;
					pixelColor.g = 219;
					pixelColor.b = 77;
					pixelColor.a = static_cast<sf::Uint8>(230 * brightnessColor);

					particleCount++;
					break;
				}
				case ParticleWorld::Material::Fire: {
					std::uniform_int_distribution<int> dist(0, 2);
					double fireFlicker = dist(particleWorld->gen) / 2.0;
					pixelColor.r = 255;
					pixelColor.g = static_cast<sf::Uint8>(191 * fireFlicker);
					pixelColor.b = 0;
					pixelColor.a = static_cast<sf::Uint8>(255 * fireFlicker);

					particleCount++;
					break;
				}
				case ParticleWorld::Material::Ice: {
					pixelColor.r = static_cast<sf::Uint8>(120 * brightnessColor);
					pixelColor.g = static_cast<sf::Uint8>(212 * brightnessColor);
					pixelColor.b = static_cast<sf::Uint8>(240 * brightnessColor);
					pixelColor.a = 240;

					particleCount++;
					break;
				}
				case ParticleWorld::Material::Smoke: {
					pixelColor.r = 120;
					pixelColor.g = 120;
					pixelColor.b = 120;
					pixelColor.a = static_cast<sf::Uint8>(240 * brightnessColor);

					particleCount++;
					break;
				}
				case ParticleWorld::Material::Steam: {
					pixelColor.r = 220;
					pixelColor.g = 220;
					pixelColor.b = 220;
					pixelColor.a = static_cast<sf::Uint8>(220 * brightnessColor);

					particleCount++;
					break;
				}
				case ParticleWorld::Material::AcidGas: {
					pixelColor.r = 81;
					pixelColor.g = 97;
					pixelColor.b = 47;
					pixelColor.a = static_cast<sf::Uint8>(235 * brightnessColor);

					particleCount++;
					break;
				}
				case ParticleWorld::Material::FlammableGas: {
					pixelColor.r = 156;
					pixelColor.g = 133;
					pixelColor.b = 81;
					pixelColor.a = static_cast<sf::Uint8>(235 * brightnessColor);

					particleCount++;
					break;
				}
				case ParticleWorld::Material::Acid: {
					pixelColor.r = static_cast<sf::Uint8>(225 * brightnessColor2);
					pixelColor.g = static_cast<sf::Uint8>(255 * brightnessColor2);
					pixelColor.b = static_cast<sf::Uint8>(125 * brightnessColor2);
					pixelColor.a = 200;

					particleCount++;
					break;
				}
				case ParticleWorld::Material::Dynamite: {
					pixelColor.r = static_cast<sf::Uint8>(110 * brightnessColor2);
					pixelColor.g = static_cast<sf::Uint8>(33 * brightnessColor2);
					pixelColor.b = static_cast<sf::Uint8>(29 * brightnessColor2);
					pixelColor.a = 255;

					particleCount++;
					break;
				}
				case ParticleWorld::Material::Nuke: {
					pixelColor.r = static_cast<sf::Uint8>(63 * brightnessColor2);
					pixelColor.g = static_cast<sf::Uint8>(107 * brightnessColor2);
					pixelColor.b = static_cast<sf::Uint8>(49 * brightnessColor2);
					pixelColor.a = 255;

					particleCount++;
					break;
				}
				}
			}

			quadClump[quadClumpIndex].position = sf::Vector2f(
				(col - nCols / 2 - minCol) * zoomLevel + uiOffset.x + size.x / 2,
				(row - nRows / 2 - minRow) * zoomLevel + uiOffset.y + size.y / 2
			);

			quadClump[quadClumpIndex + 1].position = sf::Vector2f(
				std::min(((col - nCols / 2 - minCol) + 1) * zoomLevel + uiOffset.x + size.x / 2, static_cast<float>(size.x)),
				(row - nRows / 2 - minRow) * zoomLevel + uiOffset.y + size.y / 2
			);

			quadClump[quadClumpIndex + 2].position = sf::Vector2f(
				std::min(((col - nCols / 2 - minCol) + 1) * zoomLevel + uiOffset.x + size.x / 2, static_cast<float>(size.x)),
				std::min(((row - nRows / 2 - minRow) + 1) * zoomLevel + uiOffset.y + size.y / 2, static_cast<float>(size.y))
			);

			quadClump[quadClumpIndex + 3].position = sf::Vector2f(
				(col - nCols / 2 - minCol) * zoomLevel + uiOffset.x + size.x / 2,
				std::min(((row - nRows / 2 - minRow) + 1) * zoomLevel + uiOffset.y + size.y / 2, static_cast<float>(size.y))
			);

			for (int i = 0; i < 4; i++)
			{
				quadClump[quadClumpIndex + i].color = pixelColor;
			}

			quadClumpIndex += 4;
		}
	}

	renderWindow.draw(quadClump);

	return particleCount;
}