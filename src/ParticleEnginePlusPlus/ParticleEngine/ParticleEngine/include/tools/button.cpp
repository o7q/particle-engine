#include <iostream>
#include "tools/menu/button.h"

sf::Vector2f position, size;
sf::Color color;
std::string text, font;

sf::RectangleShape buttonRect;

Button::Button(sf::Vector2f position, sf::Vector2f size, sf::Color color, std::string text, std::string font)
{
	this->position = position;
	this->size = size;
	this->color = color;
	this->text = text;
	this->font = font;

	buttonRect.setPosition(position);
	buttonRect.setSize(size);
	buttonRect.setFillColor(color);
}

bool Button::isMouseHover(int mouseX, int mouseY)
{
	return mouseX > position.x && mouseY > position.y && mouseX < size.x + position.x && mouseY < size.y + position.y;
}

void Button::highlight(bool highlight, sf::RenderWindow& renderWindow)
{
	int r = color.r, g = color.g, b = color.b;
	if (highlight)
	{
		r = std::min(r * 1.75, 255.0);
		g = std::min(g * 1.75, 255.0);
		b = std::min(b * 1.75, 255.0);
		buttonRect.setFillColor(sf::Color(r, g, b));

		sf::Cursor cursor;
		if (cursor.loadFromSystem(sf::Cursor::Hand))
		{
			renderWindow.setMouseCursor(cursor);
		}
	}
	else
	{
		buttonRect.setFillColor(sf::Color(r, g, b));

		sf::Cursor cursor;
		if (cursor.loadFromSystem(sf::Cursor::Arrow))
		{
			renderWindow.setMouseCursor(cursor);
		}
	}
}