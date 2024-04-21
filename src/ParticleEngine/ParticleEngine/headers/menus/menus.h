#pragma once

#ifndef MENUS_H
#define MENUS_H

#include <SFML/Graphics.hpp>
#include "tools/menu/button.h"
#include "particle/particle_world.h"

#include <SFML/Audio.hpp>

enum Menu {
	MainIntro,
	Sandbox
};

Menu sandboxMenu_run(sf::RenderWindow&, int, ParticleWorld*, std::vector<Button*>, ParticleWorld::ParticleInstance&, sf::Vector2i, sf::Vector2u);
std::vector<Button*> sandboxMenu_getButtons(int, int, int, int, sf::Font&);

Menu mainMenuIntro_run(sf::RenderWindow&, ParticleWorld*, std::vector<sf::Music*>, bool);
std::vector<sf::Music*> mainMenuIntro_getMusic();

#endif