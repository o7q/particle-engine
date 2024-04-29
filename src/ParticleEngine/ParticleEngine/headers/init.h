#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>

#ifndef INIT_H
#define INIT_H

namespace Init {
	sf::Font getBaseFont();
	sf::Text configureText(sf::Font&, std::string, int, sf::Color, sf::Vector2f);
}

#endif