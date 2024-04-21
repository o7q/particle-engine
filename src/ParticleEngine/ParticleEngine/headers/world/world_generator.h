#pragma once

#ifndef WORLD_GENERATOR_H
#define WORLD_GENERATOR_H

#include "particle/particle_world.h"
#include "tools/num2d.h"

enum WorldType {
	Ocean,
	Swamp
};

void generateWorld(ParticleWorld*, WorldType);

void generateOcean(ParticleWorld*);
void generateSwamp(ParticleWorld*);

Int2D* generateNoiseBase(int, int, Double2D*);
int* generateGroundLayer(int, int, int, int, int, double*, int);
double* generate1DKernel(int, double);
Double2D* generate2DKernel(int, int, double);

#endif