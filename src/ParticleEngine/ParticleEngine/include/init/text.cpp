#include <iostream>

#include <SFML/Graphics.hpp>

#include "init.hpp"
#include "tools/logger.hpp"

sf::Font Init::getBaseFont()
{
	sf::Font baseFont;
	if (!baseFont.loadFromFile("data\\fonts\\alagard.ttf"))
	{
		Logger::log(Logger::LogType::ERROR, __func__, __LINE__, "Unable to load baseFont!");
	}
	return baseFont;
}

sf::Text Init::configureText(sf::Font& font, std::string text, int characterSize, sf::Color color, sf::Vector2f position)
{
	sf::Text titleBarText;
	titleBarText.setFont(font);

	titleBarText.setString(text);
	titleBarText.setCharacterSize(characterSize);
	titleBarText.setFillColor(color);
	titleBarText.setPosition(position);

	return titleBarText;
}