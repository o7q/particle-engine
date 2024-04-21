#include <iostream>
#include <vector>

#include "tools/menu/button.h"

std::vector<Button*> sandboxMenu_getButtons(int rowSize, int pixelSize, int offsetX, int offsetY, sf::Font& font)
{
	std::vector<Button*> sandbox_buttons;

	Button* stoneButton = new Button(
		sf::Vector2f(0 + offsetX, rowSize * pixelSize + offsetY), sf::Vector2f(25, 25), sf::Color(160, 160, 160),
		sf::Color(0, 0, 0), "", 0, font,
		"stoneButton"
	);
	Button* sandButton = new Button(
		sf::Vector2f(stoneButton->position.x + stoneButton->size.x, rowSize * pixelSize + offsetY), sf::Vector2f(25, 25), sf::Color(245, 228, 118),
		sf::Color(0, 0, 0), "", 0, font,
		"sandButton"
	);
	Button* dirtButton = new Button(
		sf::Vector2f(sandButton->position.x + sandButton->size.x, rowSize * pixelSize + offsetY), sf::Vector2f(25, 25), sf::Color(77, 54, 15),
		sf::Color(0, 0, 0), "", 0, font,
		"dirtButton"
	);
	Button* grassButton = new Button(
		sf::Vector2f(dirtButton->position.x + dirtButton->size.x, rowSize * pixelSize + offsetY), sf::Vector2f(25, 25), sf::Color(60, 110, 33),
		sf::Color(0, 0, 0), "", 0, font,
		"grassButton"
	);
	Button* waterButton = new Button(
		sf::Vector2f(grassButton->position.x + grassButton->size.x, rowSize * pixelSize + offsetY), sf::Vector2f(25, 25), sf::Color(72, 136, 240),
		sf::Color(0, 0, 0), "", 0, font,
		"waterButton"
	);
	Button* iceButton = new Button(
		sf::Vector2f(waterButton->position.x + waterButton->size.x, rowSize * pixelSize + offsetY), sf::Vector2f(25, 25), sf::Color(120, 212, 240),
		sf::Color(0, 0, 0), "", 0, font,
		"iceButton"
	);
	Button* fireButton = new Button(
		sf::Vector2f(iceButton->position.x + iceButton->size.x, rowSize * pixelSize + offsetY), sf::Vector2f(25, 25), sf::Color(255, 191, 0),
		sf::Color(0, 0, 0), "", 0, font,
		"fireButton"
	);
	Button* gasolineButton = new Button(
		sf::Vector2f(fireButton->position.x + fireButton->size.x, rowSize * pixelSize + offsetY), sf::Vector2f(25, 25), sf::Color(215, 219, 77),
		sf::Color(0, 0, 0), "", 0, font,
		"gasolineButton"
	);
	Button* smokeButton = new Button(
		sf::Vector2f(gasolineButton->position.x + gasolineButton->size.x, rowSize * pixelSize + offsetY), sf::Vector2f(25, 25), sf::Color(120, 120, 120),
		sf::Color(0, 0, 0), "", 0, font,
		"smokeButton"
	);
	Button* toxicGasButton = new Button(
		sf::Vector2f(smokeButton->position.x + smokeButton->size.x, rowSize * pixelSize + offsetY), sf::Vector2f(25, 25), sf::Color(81, 97, 47),
		sf::Color(0, 0, 0), "", 0, font,
		"toxicGasButton"
	);
	Button* flammableGasButton = new Button(
		sf::Vector2f(toxicGasButton->position.x + toxicGasButton->size.x, rowSize * pixelSize + offsetY), sf::Vector2f(25, 25), sf::Color(156, 133, 81),
		sf::Color(0, 0, 0), "", 0, font,
		"flammableGasButton"
	);
	Button* airButton = new Button(
		sf::Vector2f(flammableGasButton->position.x + flammableGasButton->size.x, rowSize * pixelSize + offsetY), sf::Vector2f(25, 25), sf::Color(255, 255, 255),
		sf::Color(0, 0, 0), "", 0, font,
		"airButton"
	);

	Button* pauseButton = new Button(
		sf::Vector2f(400, rowSize * pixelSize + offsetY), sf::Vector2f(120, 25), sf::Color(0, 0, 0),
		sf::Color(240, 100, 50), "Pause Simulation", 15, font,
		"pauseButton"
	);

	sandbox_buttons.push_back(stoneButton);
	sandbox_buttons.push_back(sandButton);
	sandbox_buttons.push_back(dirtButton);
	sandbox_buttons.push_back(grassButton);
	sandbox_buttons.push_back(waterButton);
	sandbox_buttons.push_back(iceButton);
	sandbox_buttons.push_back(fireButton);
	sandbox_buttons.push_back(gasolineButton);
	sandbox_buttons.push_back(smokeButton);
	sandbox_buttons.push_back(toxicGasButton);
	sandbox_buttons.push_back(flammableGasButton);
	sandbox_buttons.push_back(airButton);
	sandbox_buttons.push_back(pauseButton);

	return sandbox_buttons;
}