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
	sf::Font font;
	if (!font.loadFromFile("C:\\Users\\james\\Desktop\\GitHub\\particle-engine\\src\\BUILD\\ParticleEngine\\alagard.ttf"))
	{
		// error...
	}

	Button* testButton = new Button(sf::Vector2f(0 + 10, rowSize * pixelSize + 300), sf::Vector2f(55, 25), sf::Color(255, 0, 0), sf::Color(160, 160, 160), "Stone", 20, font);

	// button declaration
	Button* stoneButton = new Button(sf::Vector2f(0 + 10, rowSize * pixelSize), sf::Vector2f(55, 25), sf::Color(0, 0, 0), sf::Color(160, 160, 160), "Stone", 20, font);
	Button* sandButton = new Button(sf::Vector2f(stoneButton->position.x + stoneButton->size.x, rowSize * pixelSize), sf::Vector2f(50, 25), sf::Color(0, 0, 0), sf::Color(245, 228, 118), "Sand", 20, font);
	Button* dirtButton = new Button(sf::Vector2f(sandButton->position.x + sandButton->size.x, rowSize * pixelSize), sf::Vector2f(40, 25), sf::Color(0, 0, 0), sf::Color(77, 54, 15), "Dirt", 20, font);
	Button* grassButton = new Button(sf::Vector2f(dirtButton->position.x + dirtButton->size.x, rowSize * pixelSize), sf::Vector2f(55, 25), sf::Color(0, 0, 0), sf::Color(60, 110, 33), "Grass", 20, font);
	Button* waterButton = new Button(sf::Vector2f(0 + 10, 25 + rowSize * pixelSize), sf::Vector2f(55, 25), sf::Color(0, 0, 0), sf::Color(72, 136, 240), "Water", 20, font);
	Button* iceButton = new Button(sf::Vector2f(waterButton->position.x + waterButton->size.x, 25 + rowSize * pixelSize), sf::Vector2f(35, 25), sf::Color(0, 0, 0), sf::Color(120, 212, 240), "Ice", 20, font);
	Button* fireButton = new Button(sf::Vector2f(iceButton->position.x + iceButton->size.x, 25 + rowSize * pixelSize), sf::Vector2f(45, 25), sf::Color(0, 0, 0), sf::Color(255, 191, 0), "Fire", 20, font);
	Button* gasolineButton = new Button(sf::Vector2f(fireButton->position.x + fireButton->size.x, 25 + rowSize * pixelSize), sf::Vector2f(80, 25), sf::Color(0, 0, 0), sf::Color(215, 219, 77), "Gasoline", 20, font);
	Button* smokeButton = new Button(sf::Vector2f(0 + 10, 50 + rowSize * pixelSize), sf::Vector2f(60, 25), sf::Color(0, 0, 0), sf::Color(120, 120, 120), "Smoke", 20, font);
	Button* toxicGasButton = new Button(sf::Vector2f(smokeButton->position.x + smokeButton->size.x, 50 + rowSize * pixelSize), sf::Vector2f(95, 25), sf::Color(0, 0, 0), sf::Color(81, 97, 47), "Toxic Gas", 20, font);
	Button* flammableGasButton = new Button(sf::Vector2f(toxicGasButton->position.x + toxicGasButton->size.x, 50 + rowSize * pixelSize), sf::Vector2f(145, 25), sf::Color(0, 0, 0), sf::Color(156, 133, 81), "Flammable Gas", 20, font);
	Button* airButton = new Button(sf::Vector2f(0 + 10, 75 + rowSize * pixelSize), sf::Vector2f(30, 25), sf::Color(0, 0, 0), sf::Color(255, 255, 255), "Air", 20, font);

	ParticleWorld* particleWorld = new ParticleWorld(rowSize, colSize);

	ParticleWorld::ParticleInstance drawingParticle;
	drawingParticle.material = ParticleWorld::Material::Sand;
	drawingParticle.materialType = ParticleWorld::MaterialType::Solid;

	sf::RenderWindow window(sf::VideoMode(1900, 1000), "particle engine");
	sf::RectangleShape rectangle(sf::Vector2f(pixelSize, pixelSize));

	while (window.isOpen())
	{
		sf::Event event;
		sf::Vector2i localMousePos = sf::Mouse::getPosition(window);
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		updateParticleWorld(particleWorld);

		window.clear();
		renderParticles(particleWorld, window, pixelSize);

		// button fx
		{
			bool stoneButton_hover = stoneButton->isMouseHover_highlight(localMousePos.x, localMousePos.y, window);
			bool sandButton_hover = sandButton->isMouseHover_highlight(localMousePos.x, localMousePos.y, window);
			bool dirtButton_hover = dirtButton->isMouseHover_highlight(localMousePos.x, localMousePos.y, window);
			bool grassButton_hover = grassButton->isMouseHover_highlight(localMousePos.x, localMousePos.y, window);
			bool waterButton_hover = waterButton->isMouseHover_highlight(localMousePos.x, localMousePos.y, window);
			bool iceButton_hover = iceButton->isMouseHover_highlight(localMousePos.x, localMousePos.y, window);
			bool fireButton_hover = fireButton->isMouseHover_highlight(localMousePos.x, localMousePos.y, window);
			bool gasolineButton_hover = gasolineButton->isMouseHover_highlight(localMousePos.x, localMousePos.y, window);
			bool smokeButton_hover = smokeButton->isMouseHover_highlight(localMousePos.x, localMousePos.y, window);
			bool toxicGasButton_hover = toxicGasButton->isMouseHover_highlight(localMousePos.x, localMousePos.y, window);
			bool flammableGasButton_hover = flammableGasButton->isMouseHover_highlight(localMousePos.x, localMousePos.y, window);
			bool airButton_hover = airButton->isMouseHover_highlight(localMousePos.x, localMousePos.y, window);

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (stoneButton_hover)
				{
					drawingParticle.material = ParticleWorld::Material::Stone;
					drawingParticle.materialType = ParticleWorld::MaterialType::Solid;
				}
				if (sandButton_hover)
				{
					drawingParticle.material = ParticleWorld::Material::Sand;
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
				if (waterButton_hover)
				{
					drawingParticle.material = ParticleWorld::Material::Water;
					drawingParticle.materialType = ParticleWorld::MaterialType::Liquid;
				}
				if (iceButton_hover)
				{
					drawingParticle.material = ParticleWorld::Material::Ice;
					drawingParticle.materialType = ParticleWorld::MaterialType::Solid;
				}
				if (fireButton_hover)
				{
					drawingParticle.material = ParticleWorld::Material::Fire;
					drawingParticle.materialType = ParticleWorld::MaterialType::Liquid;
				}
				if (gasolineButton_hover)
				{
					drawingParticle.material = ParticleWorld::Material::Gasoline;
					drawingParticle.materialType = ParticleWorld::MaterialType::Liquid;
				}
				if (smokeButton_hover)
				{
					drawingParticle.material = ParticleWorld::Material::Smoke;
					drawingParticle.materialType = ParticleWorld::MaterialType::Gas;
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
				if (airButton_hover)
				{
					drawingParticle.material = ParticleWorld::Material::Air;
					drawingParticle.materialType = ParticleWorld::MaterialType::Gas;
				}

				particleWorld->paintParticles(localMousePos.y / pixelSize, localMousePos.x / pixelSize, 10, drawingParticle);
			}

			stoneButton->draw(window);
			sandButton->draw(window);
			dirtButton->draw(window);
			grassButton->draw(window);
			waterButton->draw(window);
			iceButton->draw(window);
			fireButton->draw(window);
			gasolineButton->draw(window);
			smokeButton->draw(window);
			toxicGasButton->draw(window);
			flammableGasButton->draw(window);
			airButton->draw(window);
		}

		testButton->draw(window);

		window.display();
	}

	delete particleWorld;

	return 0;
}