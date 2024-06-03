#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>

#include "particle/particle_world.hpp"

class Button {

public:
	enum class TextAlignMode {
		CENTER
	};

	enum class HighlightMode {
		HIGHLIGHT,
		NONE
	};

	Button(sf::RenderWindow&, sf::Font&);

	void setPosition(sf::Vector2f);
	void setSize(sf::Vector2f);
	void setColor(sf::Color);

	void setTextString(std::string);
	void setTextFont(sf::Font&);
	void setTextSize(int);
	void setTextColor(sf::Color);
	void setTextAlign(TextAlignMode);
	void setHighlightMode(HighlightMode);
	void setId(std::string);
	void setType(std::string);

	sf::Vector2f getPos();
	sf::Vector2f getSize();
	std::string getId();
	std::string getType();

	void refresh();

	void draw();

	void enable();
	void disable();

	bool isMouseHover();
	bool hasMouseClicked();

private:
	sf::RenderWindow& renderWindow;
	sf::Font& textFont;

	sf::Vector2i LOCAL_MOUSE_POSITION;

	sf::RectangleShape buttonShape;
	sf::Text buttonText;

	sf::Vector2f position, size;
	sf::Color color, textColor;
	std::string textString;
	int textSize;
	TextAlignMode textAlignMode;
	HighlightMode highlightMode;
	std::string id, type;

	bool canClick;
	bool enabled;

	void highlight(bool);
};