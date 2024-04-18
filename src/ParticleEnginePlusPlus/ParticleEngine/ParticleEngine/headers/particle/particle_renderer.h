#pragma once

#ifndef PARTICLE_RENDERER
#define PARTICLE_RENDERER

#include <SFML/Graphics.hpp>
#include "particle/particle_world.h"

void renderParticles(ParticleWorld*, sf::RenderWindow&, int);

#endif