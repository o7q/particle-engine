#pragma once

#ifndef PHYSICS_MANAGER
#define PHYSICS_MANAGER

#include "particle/particle_world.h"

void step(ParticleWorld*);

void calculateSand(int, int, ParticleWorld*);
void calculateWater(int, int, ParticleWorld*);
void calculateSmoke(int, int, ParticleWorld*);

#endif