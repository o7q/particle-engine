#pragma once

#ifndef MENU_BUTTON_H
#define MENU_BUTTON_H

#include <iostream>
#include <SFML/Graphics.hpp>

class Button {
public:
	sf::Vector2f position, size;
	sf::Color color, textColor;
	std::string text, id;
	int textSize;

	sf::RectangleShape buttonShape;
	sf::Text buttonText;

	Button(sf::Vector2f, sf::Vector2f, sf::Color, sf::Color, std::string, int, sf::Font&, std::string);

	bool isMouseHover(int, int);
	void highlight(bool);
	void draw(sf::RenderWindow&);
};

#endif