#include <iostream>

#include "tools/menu/button.h"
#include "tools/tools.h"

Button::Button(sf::Vector2f position, sf::Vector2f size, sf::Color color, sf::Color textColor, std::string text, int textSize, sf::Font& font, std::string id)
{
	this->position = position;
	this->size = size;
	this->color = color;
	this->textColor = textColor;
	this->text = text;
	this->textSize = textSize;
	this->id = id;
	this->canClick = false;

	buttonShape.setPosition(position);
	buttonShape.setSize(size);
	buttonShape.setFillColor(color);
	buttonText.setFont(font);
	buttonText.setString(text);
	buttonText.setCharacterSize(textSize);
	buttonText.setFillColor(textColor);

	buttonText.setPosition(position.x + size.x / 2 - buttonText.getGlobalBounds().width / 2,
		position.y + size.y / 2 - buttonText.getGlobalBounds().height
	);
}

bool Button::isMouseHover(int mouseX, int mouseY)
{
	return mouseX > position.x && mouseY > position.y && mouseX < size.x + position.x && mouseY < size.y + position.y;
}

void Button::highlight(bool highlight)
{
	int r = color.r, g = color.g, b = color.b;
	int r_text = textColor.r, g_text = textColor.g, b_text = textColor.b;
	if (highlight)
	{
		r = verify256Range(r * 1.75);
		g = verify256Range(g * 1.75);
		b = verify256Range(b * 1.75);
		buttonShape.setFillColor(sf::Color(r, g, b));

		r_text = verify256Range(r_text * 1.75);
		g_text = verify256Range(g_text * 1.75);
		b_text = verify256Range(b_text * 1.75);
		buttonText.setFillColor(sf::Color(r_text, g_text, b_text));
	}
	else
	{
		buttonShape.setFillColor(sf::Color(r, g, b));
		buttonText.setFillColor(sf::Color(r_text, g_text, b_text));
	}
}

void Button::draw(sf::RenderWindow& renderWindow)
{
	renderWindow.draw(buttonShape);
	renderWindow.draw(buttonText);
}

sf::Vector2f Button::getPos()
{
	return position;
}
sf::Vector2f Button::getSize()
{
	return size;
}

std::string Button::getId()
{
	return id;
}

std::string Button::handleClick(int mouseX, int mouseY)
{
	highlight(isMouseHover(mouseX, mouseY));

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !isMouseHover(mouseX, mouseY))
	{
		canClick = false;
	}
	
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && !canClick)
	{
		canClick = true;
	}
	
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && canClick && isMouseHover(mouseX, mouseY))
	{
		canClick = false;
		return id;
	}

	return "";
}