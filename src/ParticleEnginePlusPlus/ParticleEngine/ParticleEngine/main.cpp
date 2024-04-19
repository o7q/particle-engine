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
	Button* iceButton = new Button(sf::Vector2f(165, 100 + rowSize * pixelSize), sf::Vector2f(50, 25), sf::Color(120, 212, 240), "Smoke", "data\\fonts\\alagard.ttf");
	Button* stoneButton = new Button(sf::Vector2f(220, 100 + rowSize * pixelSize), sf::Vector2f(50, 25), sf::Color(160, 160, 160), "Smoke", "data\\fonts\\alagard.ttf");
	Button* dirtButton = new Button(sf::Vector2f(275, 100 + rowSize * pixelSize), sf::Vector2f(50, 25), sf::Color(77, 54, 15), "Smoke", "data\\fonts\\alagard.ttf");
	Button* grassButton = new Button(sf::Vector2f(330, 100 + rowSize * pixelSize), sf::Vector2f(50, 25), sf::Color(60, 110, 33), "Smoke", "data\\fonts\\alagard.ttf");
	Button* fireButton = new Button(sf::Vector2f(385, 100 + rowSize * pixelSize), sf::Vector2f(50, 25), sf::Color(255, 191, 0), "Smoke", "data\\fonts\\alagard.ttf");
	Button* toxicGasButton = new Button(sf::Vector2f(440, 100 + rowSize * pixelSize), sf::Vector2f(50, 25), sf::Color(81, 97, 47), "Smoke", "data\\fonts\\alagard.ttf");
	Button* flammableGasButton = new Button(sf::Vector2f(495, 100 + rowSize * pixelSize), sf::Vector2f(50, 25), sf::Color(156, 133, 81), "Smoke", "data\\fonts\\alagard.ttf");
	Button* gasolineButton = new Button(sf::Vector2f(550, 100 + rowSize * pixelSize), sf::Vector2f(50, 25), sf::Color(215, 219, 77), "Smoke", "data\\fonts\\alagard.ttf");
	Button* airButton = new Button(sf::Vector2f(605, 100 + rowSize * pixelSize), sf::Vector2f(50, 25), sf::Color(255, 255, 255), "Smoke", "data\\fonts\\alagard.ttf");

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

		bool iceButton_hover = iceButton->isMouseHover(localPos.x, localPos.y);
		iceButton->highlight(iceButton_hover, window);

		bool stoneButton_hover = stoneButton->isMouseHover(localPos.x, localPos.y);
		stoneButton->highlight(stoneButton_hover, window);

		bool dirtButton_hover = dirtButton->isMouseHover(localPos.x, localPos.y);
		dirtButton->highlight(dirtButton_hover, window);

		bool grassButton_hover = grassButton->isMouseHover(localPos.x, localPos.y);
		grassButton->highlight(grassButton_hover, window);

		bool fireButton_hover = fireButton->isMouseHover(localPos.x, localPos.y);
		fireButton->highlight(fireButton_hover, window);

		bool toxicGasButton_hover = toxicGasButton->isMouseHover(localPos.x, localPos.y);
		toxicGasButton->highlight(toxicGasButton_hover, window);

		bool flammableGasButton_hover = flammableGasButton->isMouseHover(localPos.x, localPos.y);
		flammableGasButton->highlight(flammableGasButton_hover, window);

		bool gasolineButton_hover = gasolineButton->isMouseHover(localPos.x, localPos.y);
		gasolineButton->highlight(gasolineButton_hover, window);

		bool airButton_hover = airButton->isMouseHover(localPos.x, localPos.y);
		airButton->highlight(airButton_hover, window);

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
			if (iceButton_hover)
			{
				drawingParticle.material = ParticleWorld::Material::Ice;
				drawingParticle.materialType = ParticleWorld::MaterialType::Solid;
			}
			if (stoneButton_hover)
			{
				drawingParticle.material = ParticleWorld::Material::Stone;
				drawingParticle.materialType = ParticleWorld::MaterialType::Solid;
			}
			if (dirtButton_hover)
			{
				drawingParticle.material = ParticleWorld::Material::Dirt;
				drawingParticle.materialType = ParticleWorld::MaterialType::Solid;
			}
			if (grassButton_hover)
			{
				drawingParticle.material = ParticleWorld::Material::Grass;
				drawingParticle.materialType = ParticleWorld::MaterialType::Solid;
			}
			if (fireButton_hover)
			{
				drawingParticle.material = ParticleWorld::Material::Fire;
				drawingParticle.materialType = ParticleWorld::MaterialType::Liquid;
			}
			if (toxicGasButton_hover)
			{
				drawingParticle.material = ParticleWorld::Material::ToxicGas;
				drawingParticle.materialType = ParticleWorld::MaterialType::Gas;
			}
			if (flammableGasButton_hover)
			{
				drawingParticle.material = ParticleWorld::Material::FlammableGas;
				drawingParticle.materialType = ParticleWorld::MaterialType::Gas;
			}
			if (gasolineButton_hover)
			{
				drawingParticle.material = ParticleWorld::Material::Gasoline;
				drawingParticle.materialType = ParticleWorld::MaterialType::Liquid;
			}
			if (airButton_hover)
			{
				drawingParticle.material = ParticleWorld::Material::Air;
				drawingParticle.materialType = ParticleWorld::MaterialType::Gas;
			}

			particleWorld->paintParticles(localPos.y / pixelSize, localPos.x / pixelSize, 5, drawingParticle);
		}

		updateParticles(particleWorld);

		window.clear();
		renderParticles(particleWorld, window, pixelSize);
		
		window.draw(sandButton->buttonRect);
		window.draw(waterButton->buttonRect);
		window.draw(smokeButton->buttonRect);
		window.draw(iceButton->buttonRect);
		window.draw(stoneButton->buttonRect);
		window.draw(dirtButton->buttonRect);
		window.draw(grassButton->buttonRect);
		window.draw(fireButton->buttonRect);
		window.draw(toxicGasButton->buttonRect);
		window.draw(flammableGasButton->buttonRect);
		window.draw(gasolineButton->buttonRect);
		window.draw(airButton->buttonRect);

		window.display();
	}

	delete particleWorld;

	return 0;
}