#pragma once
#include <random>

#ifndef PARTICLE_WORLD_H
#define PARTICLE_WORLD_H

#include <SFML/Graphics.hpp>

class ParticleWorld {
private:
	bool frozen = false;
	int rowSize;
	int colSize;

public:
	enum Material {
		Air,

		Stone,
		Sand,
		Sandstone,
		Dirt,
		Grass,
		RedFlower,
		PinkFlower,
		YellowFlower,
		BlueFlower,

		Water,
		Gasoline,
		Fire,
		Ice,

		Smoke,
		Steam,
		ToxicGas,
		FlammableGas
	};

	enum MaterialType {
		Solid,
		Liquid,
		Gas
	};

	struct ParticleInstance {
		Material material;
		MaterialType materialType;
		sf::Color color;
		bool overrideColor;
		float wetnessMultiplier;
		float brightnessMultiplier;
		int intValue;
		int physicsFreezeTime;
	};

	std::random_device rd;
	std::mt19937 gen;

	ParticleInstance* particles;

	ParticleWorld(int, int);
	~ParticleWorld();

	void freeze();
	void unfreeze();
	bool isFrozen();

	int getRowSize();
	int getColSize();

	ParticleInstance getParticle(int, int);
	void setParticle(int, int, ParticleInstance);

	void resetParticle(int, int);

	void paintParticles(int, int, int, ParticleInstance);

	void imageToParticles(int, int, sf::Image&, ParticleWorld::ParticleInstance, bool);

	ParticleInstance getDefaultInstance();

	bool canLeft(int);
	bool canRight(int);
	bool canUp(int);
	bool canDown(int);
};

#endif