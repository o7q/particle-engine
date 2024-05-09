#include <vector>

#include <SFML/Graphics.hpp>

#include "menu/menu.h"

Menu::Menu(sf::RenderWindow& renderWindow) : renderWindow(renderWindow)
{

}

Menu::~Menu()
{
	for (Button* button : buttons)
	{
		delete button;
	}
}

bool Menu::init()
{
	bool init = doInit;
	doInit = false;
	return init;
}

bool Menu::update()
{
	LOCAL_MOUSE_POSITION = sf::Mouse::getPosition(renderWindow);
	MOUSE_DOWN = sf::Mouse::isButtonPressed(sf::Mouse::Left);

	for (Button* button : buttons)
	{
		button->draw();
	}

	return true;
}

MenuType Menu::tick()
{
	return MenuType::MAIN_MENU;
}

void Menu::setButtons(std::vector<Button*> buttons)
{
	this->buttons = buttons;
}

std::vector<Button*> Menu::getDefaultButtons(sf::RenderWindow&, sf::Font&, sf::Vector2i, sf::Vector2u)
{
	std::vector<Button*> defaults;
	return defaults;
}