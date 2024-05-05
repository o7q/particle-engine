#pragma once

#ifndef PARTICLE_RENDERER_H
#define PARTICLE_RENDERER_H

#include <SFML/Graphics.hpp>

#include "particle/particle_world.h"

class ParticleRenderer {
public:

	enum class Direction {
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

	enum class ZoomType {
		ZOOM_IN,
		ZOOM_OUT
	};

	ParticleRenderer(sf::Vector2u);

	void resizeQuadClump();

	int render(ParticleWorld*, sf::RenderWindow&, sf::Vector2i);
	void zoom(float);
	float getZoom();
	void translate(Direction);
	sf::Vector2f getTranslate();
	void setTranslate(sf::Vector2f);

	sf::Vector2u getSize();

private:
	sf::Vector2u size;

	sf::VertexArray quadClump;
	sf::Vector2f position;
	float zoomLevel;

	int pixelSize;
};

//int renderParticleWorld(ParticleWorld*, sf::RenderWindow&, sf::VertexArray&, sf::Vector2i, int, int);

#endif