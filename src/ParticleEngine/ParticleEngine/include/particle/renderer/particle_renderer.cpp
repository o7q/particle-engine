#include <iostream>

#include "particle/particle_world.hpp"
#include "particle/particle_renderer.hpp"

#include "tools/tools.hpp"
#include "tools/random.hpp"

sf::Vector2f operator/(sf::Vector2f a, sf::Vector2f b)
{
	return sf::Vector2f(a.x / b.x, a.y / b.y);
}

sf::Vector2f operator*(sf::Vector2f a, sf::Vector2f b)
{
	return sf::Vector2f(a.x * b.x, a.y * b.y);
}

ParticleRenderer::ParticleRenderer(sf::Vector2u size, ParticleWorld* particleWorld, sf::RenderWindow& renderWindow) : particleWorld(particleWorld), renderWindow(renderWindow)
{
	this->size = size;
	this->zoomLevel = 1.0f;

	if (!shader.loadFromFile("data\\shaders\\particle\\shader.vert", "data\\shaders\\particle\\shader.frag")) {
		std::cerr << "Failed to load shader" << std::endl;
	}

	shader.setUniform("tex", particleWorld->getWorldTexture());
	shader.setUniform("texSize", sf::Vector2f(particleWorld->getColSize(), particleWorld->getRowSize()));
	shader.setUniform("resolution", renderWindow.getView().getSize());

	quad.resize(4);
	quad.setPrimitiveType(sf::Quads);
	quad[0].position = sf::Vector2f(-1, -1);
	quad[1].position = sf::Vector2f(1, -1);
	quad[2].position = sf::Vector2f(1, 1);
	quad[3].position = sf::Vector2f(-1, 1);
	quad[0].texCoords = sf::Vector2f(0, 1);
	quad[1].texCoords = sf::Vector2f(1, 1);
	quad[2].texCoords = sf::Vector2f(1, 0);
	quad[3].texCoords = sf::Vector2f(0, 0);
}

void ParticleRenderer::render()
{
	particleWorld->updatePixels();

	shader.setUniform("translation", translation);
	shader.setUniform("zoom", zoomLevel);

	renderWindow.draw(quad, &shader);
}

void ParticleRenderer::zoom(float zoomAmount)
{
	zoomLevel *= zoomAmount;
}

void ParticleRenderer::setUIOffset(sf::Vector2i uiOffset)
{
	this->uiOffset = uiOffset;
}

sf::Vector2i ParticleRenderer::getUIOffset()
{
	return uiOffset;
}

float ParticleRenderer::getZoom()
{
	return this->zoomLevel;
}

sf::Vector2u ParticleRenderer::getSize()
{
	return this->size;
}

void ParticleRenderer::translate(sf::Vector2f direction)
{
	translation += direction;
}

sf::Vector2f ParticleRenderer::getTranslate()
{
	return this->translation;
}

void ParticleRenderer::setTranslate(sf::Vector2f position)
{
	this->translation = position;
}

sf::Vector2i ParticleRenderer::windowToWorldCoordinates(sf::Vector2i windowPosition)
{
	sf::Vector2f windowSize = sf::Vector2f(renderWindow.getSize());
	sf::Vector2f worldSize = sf::Vector2f(particleWorld->getWorldSize());

	// Map window to [-1, 1]
	sf::Vector2f windowPositionNormalized = (sf::Vector2f(windowPosition) / windowSize) * 2.0f - sf::Vector2f(1, 1);

	windowPositionNormalized /= zoomLevel;
	windowPositionNormalized += translation / windowSize;

	float aspect = (windowSize.x / windowSize.y) * (worldSize.y / worldSize.x);
	if (aspect < 1.0)
	{
		windowPositionNormalized = windowPositionNormalized * sf::Vector2f(1.0, 1.0 / aspect);
	}
	else
	{
		windowPositionNormalized = windowPositionNormalized * sf::Vector2f(aspect, 1.0);
	}

	windowPositionNormalized = (windowPositionNormalized + sf::Vector2f(1, 1)) / 2.0f;

	windowPositionNormalized = windowPositionNormalized * worldSize;

	return sf::Vector2i(windowPositionNormalized);
}