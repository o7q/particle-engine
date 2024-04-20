#pragma once

#ifndef PARTICLE_RENDERER_H
#define PARTICLE_RENDERER_H

#include <SFML/Graphics.hpp>
#include "particle/particle_world.h"

void renderParticleWorld(ParticleWorld*, sf::RenderWindow&, int, int, int);

#endif