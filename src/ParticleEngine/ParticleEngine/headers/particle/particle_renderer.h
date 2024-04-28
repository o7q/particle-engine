#pragma once

#ifndef PARTICLE_RENDERER_H
#define PARTICLE_RENDERER_H

#include <SFML/Graphics.hpp>
#include "particle/particle_world.h"

int renderParticleWorld(ParticleWorld*, sf::RenderWindow&, sf::VertexArray&, sf::Vector2i, int, int);

#endif