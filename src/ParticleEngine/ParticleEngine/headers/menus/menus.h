#pragma once

#ifndef MENUS_H
#define MENUS_H

#include <SFML/Graphics.hpp>
#include "tools/menu/button.h"
#include "particle/particle_world.h"

#include <SFML/Audio.hpp>

enum Menu {
	Main,
	Sandbox
};

Menu sandboxMenu_run(sf::RenderWindow&, int, ParticleWorld*, std::vector<Button*>, ParticleWorld::ParticleInstance&, sf::Vector2i, sf::Vector2i, int);
std::vector<Button*> sandboxMenu_getButtons(int, int, int, sf::Vector2i, sf::Font&);

Menu mainMenu_run(sf::RenderWindow&, ParticleWorld*, std::vector<sf::Music*>, bool);
std::vector<sf::Music*> mainMenu_getMusic();
std::vector<sf::SoundBuffer*> mainMenu_getSounds();

#endif