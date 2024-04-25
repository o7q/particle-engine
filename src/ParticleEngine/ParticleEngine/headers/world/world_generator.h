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
std::vector<sf::Image> ocean_getObjects();

void generateSwamp(ParticleWorld*);

// noise
Int2D* generateNoiseBase(int, int, Double2D*, int, int);
int* generateGroundLayer(int, int, int, int, int, double*, int);

// kernel
double* generate1DKernel(int, double);
Double2D* generate2DKernel(int, int, double);

// quantize
int quantizeValue(int, int*, int);

#endif