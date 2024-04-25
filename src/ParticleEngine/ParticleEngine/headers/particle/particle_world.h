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
	enum class Material {
		Air,

		Stone,
		Sand,
		Sandstone,
		Dirt,
		DarkDirt,
		Grass,
		RedFlower,
		PinkFlower,
		YellowFlower,
		BlueFlower,

		Water,
		SwampWater,
		Gasoline,
		Fire,
		Ice,
		Acid,

		Smoke,
		Steam,
		AcidGas,
		FlammableGas
	};

	enum class PhysicsType {
		Sand,
		Water,
		Smoke,
		Acid,
		AcidSmoke,
		Ice,
		SimpleGravity,
		Dirt,
		Grass,
		Fire,
		NoGravity
	};

	enum class MaterialType {
		Solid,
		Liquid,
		Gas
	};

	struct ParticleInstance {
		Material material = Material::Air;
		MaterialType materialType = MaterialType::Gas;
		PhysicsType physicsType = PhysicsType::NoGravity;
		bool flammable = false;
		bool createsSteam = false;
		sf::Color color = sf::Color(0, 0, 0);
		bool overrideColor = false;
		float wetnessMultiplier = 1.0f;
		float brightnessMultiplier = 1.0f;

		int intValue = 0;
		int physicsFreezeTime = 0;
		int lastY = 0;
		bool isFalling = false;
	};

	static std::random_device rd;
	static std::mt19937 gen;

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

	ParticleInstance getDefaultInstance();

	void resetParticle(int, int);

	void paintParticles(int, int, int, ParticleInstance);

	void imageToParticles(int, int, sf::Image&, ParticleWorld::ParticleInstance, bool);

	bool canLeft(int);
	bool canRight(int);
	bool canUp(int);
	bool canDown(int);
};

#endif