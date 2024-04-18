#pragma once
#include <random>

#ifndef PARTICLE_WORLD
#define PARTICLE_WORLD

class ParticleWorld {
public:
	enum Material {
		Air,
		Sand,
		Water,
		Smoke
	};

	enum MaterialType {
		Solid,
		Liquid,
		Gas
	};

	struct ParticleInstance {
		Material material;
		MaterialType materialType;
		float wetnessMultiplier;
		float brightnessMultiplier;
		int intValue;
		bool verticalParticleUpdated;
	};

	int rowSize;
	int colSize;
	ParticleInstance* particles;

	std::random_device rd;
	std::mt19937 gen;

	ParticleWorld(int, int);
	~ParticleWorld();

	void setParticle(int, int, ParticleInstance);
	ParticleInstance getParticle(int, int);

	void resetParticle(int, int);

	void paintParticles(int, int, int, ParticleInstance);

	bool canLeft(int);
	bool canRight(int);
	bool canUp(int);
	bool canDown(int);
};

#endif