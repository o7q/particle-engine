#pragma once

#ifndef MENU_BUTTON_H
#define MENU_BUTTON_H

#include <iostream>

#include <SFML/Graphics.hpp>

class Button {
private:
	sf::Vector2f position, size;
	sf::Color color, textColor;
	std::string text, id, type;
	int textSize;
	bool canClick;
	bool enabled;

public:
	sf::RectangleShape buttonShape;
	sf::Text buttonText;

	Button(sf::Vector2f, sf::Vector2f, sf::Color, sf::Color, std::string, int, sf::Font&, std::string, std::string);

	bool isMouseHover(int, int);
	void highlight(bool);
	void draw(sf::RenderWindow&);

	void enable();
	void disable();
	bool isEnabled();

	sf::Vector2f getPos();
	sf::Vector2f getSize();
	std::string getId();
	std::string getType();

	std::string handleClick(int, int);
};

#endif