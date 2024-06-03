#pragma once

#include <SFML/Graphics.hpp>

#include "particle/particle_world.hpp"

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
	void translate(Direction, float);
	sf::Vector2f getTranslate();
	void setTranslate(sf::Vector2f);

	sf::Vector2u getSize();
	void setUIOffset(sf::Vector2i);
	sf::Vector2i getUIOffset();

	sf::Vector2f windowToRenderCoordinates(sf::Vector2f);
	sf::Vector2f renderToWorldCoordinates(sf::Vector2f);
	sf::Vector2f windowToWorldCoordinates(sf::Vector2i);
	sf::Vector2f staticWorldToWorldCoordinates(sf::Vector2i);

private:
	sf::Vector2u size;

	sf::RenderWindow& renderWindow;

	sf::Vector2i uiOffset;

	sf::Vector2f position;
	float zoomLevel;
};