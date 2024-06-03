#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>

namespace Init {
	sf::Font getBaseFont();
	sf::Text configureText(sf::Font&, std::string, int, sf::Color, sf::Vector2f);
}