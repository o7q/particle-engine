#pragma once

#ifndef PARTICLE_PHYSICS_H
#define PARTICLE_PHYSICS_H

#include "particle/particle_world.h"

void updateParticleWorld(ParticleWorld*);
void updateParticle(ParticleWorld*, int, int);

void calculate_sand(int, int, ParticleWorld*);
void calculate_liquid(int, int, ParticleWorld*);
void calculate_smoke(int, int, ParticleWorld*);
void calculate_acid(int, int, ParticleWorld*);
void calculate_acidSmoke(int, int, ParticleWorld*);
void calculate_ice(int, int, ParticleWorld*);
void calculate_simpleGravity(int, int, ParticleWorld*);
void calculate_dirt(int, int, ParticleWorld*);
void calculate_grass(int, int, ParticleWorld*);
void calculate_fire(int, int, ParticleWorld*);
void calculate_explosive(int, int, ParticleWorld*);

#endif