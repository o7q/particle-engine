#pragma once

#include "particle/particle_world.hpp"

#include "tools/num2d.hpp"

enum WorldType {
	Ocean,
	Swamp
};

void generateWorld(ParticleWorld*, WorldType);

void generateOcean(ParticleWorld*);
std::vector<sf::Image> ocean_getObjects();

void generateSwamp(ParticleWorld*);

// noise
Int2D* generateNoiseBase(int, int, Float2D*, int, int);
int* generateGroundLayer(int, int, int, int, int, float*, int);

// kernel
float* generate1DKernel(int, float);
Float2D* generate2DKernel(int, int, float);

// quantize
int quantizeValue(int, int*, int);