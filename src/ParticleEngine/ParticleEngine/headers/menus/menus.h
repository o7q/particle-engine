#pragma once

#ifndef MENUS_H
#define MENUS_H

#include <SFML/Graphics.hpp>
#include "tools/menu/button.h"
#include "particle/particle_world.h"

enum Menu {
	Sandbox
};

Menu sandbox_run(sf::RenderWindow&, int, ParticleWorld*, std::vector<Button*>, ParticleWorld::ParticleInstance&, sf::Vector2i, sf::Vector2u);
std::vector<Button*> sandbox_getButtons(int, int, int, int, sf::Font&);

#endif