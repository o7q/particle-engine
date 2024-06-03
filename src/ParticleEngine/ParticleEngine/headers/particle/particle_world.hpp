#pragma once

#include <random>

#include <SFML/Graphics.hpp>

class ParticleWorld {

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
		FlammableGas,
		Dynamite,
		Nuke
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
		NoGravity,
		Explosive,
		Nuke
	};

	enum class MaterialType {
		Solid,
		Liquid,
		Gas
	};

	enum class Shape {
		Square,
		Circle
	};

	class Particle {
	public:
		Material material = Material::Air;
		MaterialType materialType = MaterialType::Gas;
		PhysicsType physicsType = PhysicsType::NoGravity;
		bool flammable = false;
		bool createsSteam = false;
		bool overrideColor = false;
		sf::Color overriddenColor = sf::Color(0, 0, 0);
		float wetnessMultiplier = 1.0f;
		float brightnessMultiplier = 1.0f;

		int intValue = 0;
		int physicsFreezeTime = 0;
		int lastY = 0;
		bool isFalling = false;
	};

	std::vector<sf::Image> explosionPatterns;
	std::vector<sf::Image> nukeExplosionPatterns;
	std::vector<sf::Image> nukeMushroomCloudPatterns;

	struct DrawingParticle {
		Particle particle;
		std::string toolMode = "draw";
		int brushSize = 5;
	};

	Particle* particles;

	ParticleWorld(int, int);
	~ParticleWorld();

	void freeze();
	void unfreeze();
	bool isFrozen();

	int getRowSize();
	int getColSize();

	Particle getParticle(int, int);
	void setParticle(int, int, Particle);

	void resetParticle(int, int);

	void paintParticles(int, int, int, Particle, Shape);

	void imageToParticles(int, int, sf::Image&, Particle, bool);

	void update();

private:
	bool frozen = false;
	int rowSize;
	int colSize;

	struct Ruleset {
		bool canUp = false;
		bool canDown = false;
		bool canLeft = false;
		bool canRight = false;
	};

	void updateParticleRuleset(int, int);
	void updateParticle(int, int, Ruleset);

	void calculate_sand(int, int, Ruleset);
	void calculate_liquid(int, int, Ruleset);
	void calculate_smoke(int, int, Ruleset);
	void calculate_acid(int, int, Ruleset);
	void calculate_acidSmoke(int, int, Ruleset);
	void calculate_ice(int, int, Ruleset);
	void calculate_simpleGravity(int, int, Ruleset);
	void calculate_dirt(int, int, Ruleset);
	void calculate_grass(int, int, Ruleset);
	void calculate_fire(int, int, Ruleset);
	void calculate_explosive(int, int, Ruleset);
	void calculate_nuke(int, int, Ruleset);
};