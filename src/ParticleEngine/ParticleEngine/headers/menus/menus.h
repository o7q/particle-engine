#pragma once

#ifndef MENUS_H
#define MENUS_H

#include <unordered_set>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "particle/particle_world.h"

#include "tools/menu/button.h"

enum Menu {
	Main,
	Sandbox
};

Menu sandboxMenu_run(sf::RenderWindow&, int, ParticleWorld*, std::vector<Button*>, ParticleWorld::DrawingParticle&, sf::Vector2i, sf::Vector2i, int, std::unordered_set<std::string>&);
std::vector<Button*> sandboxMenu_getButtons(int, int, int, sf::Vector2i, sf::Font&);

Menu mainMenu_run(sf::RenderWindow&, ParticleWorld*, std::vector<sf::Music*>, bool);
std::vector<sf::Music*> mainMenu_getMusic();

#endif