#pragma once

#ifndef MENU_BUTTON_H
#define MENU_BUTTON_H

#include <iostream>
#include <SFML/Graphics.hpp>

class Button {
public:
	sf::Vector2f position, size;
	sf::Color color;
	std::string text, font;

	sf::RectangleShape buttonRect;

	Button(sf::Vector2f, sf::Vector2f, sf::Color, std::string, std::string);

	bool isMouseHover(int, int);
	void highlight(bool, sf::RenderWindow&);
};

#endif