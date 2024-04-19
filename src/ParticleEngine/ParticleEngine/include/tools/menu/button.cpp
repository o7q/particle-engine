#include <iostream>
#include "tools/menu/button.h"

sf::Vector2f position, size;
sf::Color color, textColor;
std::string text;
int textSize;

sf::RectangleShape buttonShape;
sf::Text buttonText;

Button::Button(sf::Vector2f position, sf::Vector2f size, sf::Color color, sf::Color textColor, std::string text, int textSize, sf::Font& font)
{
	this->position = position;
	this->size = size;
	this->color = color;
	this->textColor = textColor;
	this->text = text;
	this->textSize = textSize;

	buttonShape.setPosition(position);
	buttonShape.setSize(size);
	buttonShape.setFillColor(color);
	buttonText.setFont(font);
	buttonText.setString(text);
	buttonText.setCharacterSize(textSize);
	buttonText.setFillColor(textColor);

	buttonShape.setSize(sf::Vector2f(buttonText.getGlobalBounds().width, size.y));

	buttonText.setPosition(position.x + size.x / 2 - buttonText.getGlobalBounds().width / 2,
		position.y + size.y / 2 - buttonText.getGlobalBounds().height
	);
}

bool Button::isMouseHover(int mouseX, int mouseY)
{
	return mouseX > position.x && mouseY > position.y && mouseX < size.x + position.x && mouseY < size.y + position.y;
}

bool Button::isMouseHover_highlight(int mouseX, int mouseY, sf::RenderWindow& renderWindow)
{
	if (isMouseHover(mouseX, mouseY))
	{
		highlight(true, renderWindow);
		return true;
	}
	else
	{
		highlight(false, renderWindow);
		return false;
	}
}

void Button::highlight(bool highlight, sf::RenderWindow& renderWindow)
{
	int r = color.r, g = color.g, b = color.b;
	int r_text = textColor.r, g_text = textColor.g, b_text = textColor.b;
	if (highlight)
	{
		r = std::min(r * 1.75, 255.0);
		g = std::min(g * 1.75, 255.0);
		b = std::min(b * 1.75, 255.0);
		buttonShape.setFillColor(sf::Color(r, g, b));

		r_text = std::min(r_text * 1.75, 255.0);
		g_text = std::min(g_text * 1.75, 255.0);
		b_text = std::min(b_text * 1.75, 255.0);
		buttonText.setFillColor(sf::Color(r_text, g_text, b_text));

		sf::Cursor cursor;
		if (cursor.loadFromSystem(sf::Cursor::Hand))
		{
			renderWindow.setMouseCursor(cursor);
		}
	}
	else
	{
		buttonShape.setFillColor(sf::Color(r, g, b));
		buttonText.setFillColor(sf::Color(r_text, g_text, b_text));

		sf::Cursor cursor;
		if (cursor.loadFromSystem(sf::Cursor::Arrow))
		{
			renderWindow.setMouseCursor(cursor);
		}
	}
}

void Button::draw(sf::RenderWindow& renderWindow)
{
	renderWindow.draw(buttonShape);
	renderWindow.draw(buttonText);
}