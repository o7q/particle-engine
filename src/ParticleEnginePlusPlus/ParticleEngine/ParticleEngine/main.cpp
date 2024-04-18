#include <iostream>

#include <SFML/Graphics.hpp>

#include "particle/particle_world.h"
#include "particle/particle_physics.h"
#include "particle/particle_renderer.h"
#include "headers/tools/menu/button.h"

const unsigned int rowSize = 200;
const unsigned int colSize = 300;

const int pixelSize = 3;

int main()
{
	Button* sandButton = new Button(sf::Vector2f(0, 100 + rowSize * pixelSize), sf::Vector2f(50, 25), sf::Color(245, 228, 118), "Sand", "data\\fonts\\alagard.ttf");
	Button* waterButton = new Button(sf::Vector2f(55, 100 + rowSize * pixelSize), sf::Vector2f(50, 25), sf::Color(72, 136, 240), "Water", "data\\fonts\\alagard.ttf");
	Button* smokeButton = new Button(sf::Vector2f(110, 100 + rowSize * pixelSize), sf::Vector2f(50, 25), sf::Color(120, 120, 120), "Smoke", "data\\fonts\\alagard.ttf");

	ParticleWorld* particleWorld = new ParticleWorld(rowSize, colSize);

	ParticleWorld::ParticleInstance drawingParticle;
	drawingParticle.material = ParticleWorld::Material::Sand;
	drawingParticle.materialType = ParticleWorld::MaterialType::Solid;

	sf::RenderWindow window(sf::VideoMode(1900, 1000), "particle engine");
	sf::RectangleShape rectangle(sf::Vector2f(pixelSize, pixelSize));

	while (window.isOpen())
	{
		sf::Vector2i localPos = sf::Mouse::getPosition(window);
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		bool sandButton_hover = sandButton->isMouseHover(localPos.x, localPos.y);
		sandButton->highlight(sandButton_hover, window);

		bool waterButton_hover = waterButton->isMouseHover(localPos.x, localPos.y);
		waterButton->highlight(waterButton_hover, window);

		bool smokeButton_hover = smokeButton->isMouseHover(localPos.x, localPos.y);
		smokeButton->highlight(smokeButton_hover, window);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (sandButton_hover)
			{
				drawingParticle.material = ParticleWorld::Material::Sand;
				drawingParticle.materialType = ParticleWorld::MaterialType::Solid;
			}
			if (waterButton_hover)
			{
				drawingParticle.material = ParticleWorld::Material::Water;
				drawingParticle.materialType = ParticleWorld::MaterialType::Liquid;
			}
			if (smokeButton_hover)
			{
				drawingParticle.material = ParticleWorld::Material::Smoke;
				drawingParticle.materialType = ParticleWorld::MaterialType::Gas;
			}

			particleWorld->paintParticles(localPos.y / pixelSize, localPos.x / pixelSize, 3, drawingParticle);
		}

		step(particleWorld);

		window.clear();
		renderParticles(particleWorld, window, pixelSize);
		
		window.draw(sandButton->buttonRect);
		window.draw(waterButton->buttonRect);
		window.draw(smokeButton->buttonRect);

		window.display();
	}

	delete particleWorld;

	return 0;
}