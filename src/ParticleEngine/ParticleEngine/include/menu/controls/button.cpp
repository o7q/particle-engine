#include <iostream>

#include "menu/controls/button.h"
#include "tools/tools.h"

Button::Button(sf::RenderWindow& renderWindow, sf::Font& textFont) : renderWindow(renderWindow), textFont(textFont)
{
	this->position = sf::Vector2f(0, 0);
	this->size = sf::Vector2f(20, 10);
	this->color = sf::Color(50, 50, 50);

	this->textString = "";
	this->textSize = 3;
	this->textColor = sf::Color(200, 200, 200);
	this->textAlignMode = TextAlignMode::CENTER;
	this->highlightMode = HighlightMode::HIGHLIGHT;

	this->id = "";
	this->type = "";

	this->canClick = false;
	this->enabled = true;

	refresh();
}

void Button::setPosition(sf::Vector2f position)
{
	this->position = position;
	refresh();
}

void Button::setSize(sf::Vector2f size)
{
	this->size = size;
	refresh();
}

void Button::setColor(sf::Color color)
{
	this->color = color;
	refresh();
}

void Button::setTextString(std::string textString)
{
	this->textString = textString;
	refresh();
}

void Button::setTextFont(sf::Font& textFont)
{
	this->textFont = textFont;
	refresh();
}

void Button::setTextSize(int textSize)
{
	this->textSize = textSize;
	refresh();
}

void Button::setTextColor(sf::Color textColor)
{
	this->textColor = textColor;
	refresh();
}

void Button::setTextAlign(TextAlignMode textAlignMode)
{
	this->textAlignMode = textAlignMode;
	refresh();
}

void Button::setHighlightMode(HighlightMode highlightMode)
{
	this->highlightMode = highlightMode;
	refresh();
}

void Button::setId(std::string id)
{
	this->id = id;
}

void Button::setType(std::string type)
{
	this->type = type;
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

std::string Button::getType()
{
	return type;
}

void Button::refresh()
{
	buttonShape.setPosition(position);
	buttonShape.setSize(size);
	buttonShape.setFillColor(color);
	buttonText.setFillColor(textColor);
	buttonText.setString(textString);
	buttonText.setFont(textFont);

	switch (textAlignMode)
	{
	case TextAlignMode::CENTER:
		buttonText.setPosition(position.x + size.x / 2 - buttonText.getGlobalBounds().width / 2,
			position.y + size.y / 2 - buttonText.getGlobalBounds().height
		);
		break;
	}
}

void Button::highlight(bool highlight)
{
	int r = color.r, g = color.g, b = color.b;
	int r_text = textColor.r, g_text = textColor.g, b_text = textColor.b;

	if (!enabled)
	{
		int grayscale = (r + g + b) / 30;
		buttonShape.setFillColor(sf::Color(grayscale, grayscale, grayscale));
		buttonText.setFillColor(sf::Color(grayscale, grayscale, grayscale));
		return;
	}

	if (highlight && highlightMode == HighlightMode::HIGHLIGHT)
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

void Button::draw()
{
	LOCAL_MOUSE_POSITION = sf::Mouse::getPosition(renderWindow);

	highlight(isMouseHover());

	renderWindow.draw(buttonShape);
	renderWindow.draw(buttonText);
}

void Button::enable()
{
	enabled = true;
}

void Button::disable()
{
	enabled = false;
}

bool Button::isMouseHover()
{
	return LOCAL_MOUSE_POSITION.x > position.x && LOCAL_MOUSE_POSITION.y > position.y && LOCAL_MOUSE_POSITION.x < size.x + position.x && LOCAL_MOUSE_POSITION.y < size.y + position.y;
}

bool Button::hasMouseClicked()
{
	if (!enabled)
	{
		return false;
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !isMouseHover())
	{
		canClick = false;
	}
	
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && !canClick)
	{
		canClick = true;
	}
	
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && canClick && isMouseHover())
	{
		canClick = false;
		return true;
	}

	return false;
}