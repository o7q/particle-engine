#include <iostream>

#include <SFML/Graphics.hpp>

#include "init.h"

namespace Init {
	sf::Font getBaseFont()
	{
		sf::Font baseFont;
		if (!baseFont.loadFromFile("data\\fonts\\alagard.ttf"))
		{
			// error
		}
		return baseFont;
	}

	sf::Text configureText(sf::Font& font, std::string text, int characterSize, sf::Color color, sf::Vector2f position)
	{
		sf::Text titleBarText;
		titleBarText.setFont(font);

		titleBarText.setString(text);
		titleBarText.setCharacterSize(characterSize);
		titleBarText.setFillColor(color);
		titleBarText.setPosition(position);

		return titleBarText;
	}
}