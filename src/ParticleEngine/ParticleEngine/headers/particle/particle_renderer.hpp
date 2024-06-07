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

	ParticleRenderer(sf::Vector2u, ParticleWorld*, sf::RenderWindow&);

	void render();
	void zoom(float);
	float getZoom();
	void translate(sf::Vector2f);
	sf::Vector2f getTranslate();
	void setTranslate(sf::Vector2f);

	sf::Vector2u getSize();
	void setUIOffset(sf::Vector2i);
	sf::Vector2i getUIOffset();

	sf::Vector2i windowToWorldCoordinates(sf::Vector2i);

private:
	sf::Vector2u size;

	ParticleWorld* particleWorld;
	sf::RenderWindow& renderWindow;

	sf::Shader shader;
	sf::VertexArray quad;

	sf::Vector2i uiOffset;

	sf::Vector2f translation;
	float zoomLevel;
};