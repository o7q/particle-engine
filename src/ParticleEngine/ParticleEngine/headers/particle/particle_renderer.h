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

	ParticleRenderer(sf::Vector2u, sf::RenderWindow&);

	int render(ParticleWorld*);
	void zoom(float);
	float getZoom();
	void translate(Direction);
	sf::Vector2f getTranslate();
	void setTranslate(sf::Vector2f);

	sf::Vector2u getSize();
	void setUIOffset(sf::Vector2i);

	sf::Vector2f windowToRenderCoordinates(sf::Vector2f);
	sf::Vector2f renderToWorldCoordinates(sf::Vector2f);
	sf::Vector2f mouseToWorldCoordinates(sf::Vector2i);

private:
	sf::Vector2u size;

	sf::RenderWindow& renderWindow;

	sf::Vector2i uiOffset;

	sf::Vector2f position;
	float zoomLevel;
};

#endif