#include <iostream>

#include "particle/particle_world.hpp"
#include "particle/particle_sounds.hpp"

#include "tools/tools.hpp"
#include "tools/random.hpp"

void ParticleWorld::calculate_grass(int row, int col, Ruleset ruleset)
{
	// define self, this value is used whenever a pixel moves, it acts as a copy of all the settings for the current pixel
	// selfInital SHOULD NOT CHANGE
	const ParticleWorld::Particle selfInitial = getParticle(row, col);
	ParticleWorld::Particle self = selfInitial;

	// generate random int for growing chance of flowers
	int growFlowerChance = Random::genInt(0, 10000000);

	if (ruleset.canUp)
	{
		// increment wetness if a liquid is present (up)
		if (getParticle(row - 1, col).materialType == ParticleWorld::MaterialType::Liquid &&
			getParticle(row, col).wetnessMultiplier <= 1.0f)
		{
			particles[get1DIndex(row, col, getColSize())].wetnessMultiplier += 0.1f;
		}

		if (getParticle(row - 1, col).material == ParticleWorld::Material::Air &&
			getParticle(row, col).wetnessMultiplier >= 0.9f)
		{
			// choose flower to grow, blue being the rarest, pink being the most common
			ParticleWorld::Material flowerToGrow = ParticleWorld::Material::RedFlower;
			bool growFlower = false;
			if (growFlowerChance < 10)
			{
				flowerToGrow = ParticleWorld::Material::BlueFlower;
				growFlower = true;
			}
			else if (growFlowerChance < 50)
			{
				flowerToGrow = ParticleWorld::Material::YellowFlower;
				growFlower = true;
			}
			else if (growFlowerChance < 75)
			{
				flowerToGrow = ParticleWorld::Material::PinkFlower;
				growFlower = true;
			}
			else if (growFlowerChance < 100)
			{
				growFlower = true;
			}

			// grow the flower
			if (growFlower)
			{
				particles[get1DIndex(row - 1, col, getColSize())].material = flowerToGrow;
			}
		}
	}

	if (ruleset.canLeft)
	{
		// increment wetness if a liquid is present (left)
		if (getParticle(row, col - 1).materialType == ParticleWorld::MaterialType::Liquid &&
			getParticle(row, col).wetnessMultiplier <= 0.5f)
		{
			particles[get1DIndex(row, col, getColSize())].wetnessMultiplier += 0.05f;
		}
	}

	if (ruleset.canRight)
	{
		// increment wetness if a liquid is present (right)
		if (getParticle(row, col + 1).materialType == ParticleWorld::MaterialType::Liquid &&
			getParticle(row, col).wetnessMultiplier <= 0.5f)
		{
			particles[get1DIndex(row, col, getColSize())].wetnessMultiplier += 0.05f;
		}
	}

	if (ruleset.canDown)
	{
		// apply gravity (down)
		if (
			(getParticle(row + 1, col).materialType == ParticleWorld::MaterialType::Gas ||
				getParticle(row + 1, col).materialType == ParticleWorld::MaterialType::Liquid) &&
			getParticle(row, col).material == self.material)
		{
			setParticle(row + 1, col, self);
			resetParticle(row, col);
		}
	}

	if (ruleset.canLeft && ruleset.canDown)
	{
		// apply gravity (left)
		if (
			(getParticle(row + 1, col - 1).materialType == ParticleWorld::MaterialType::Liquid ||
				getParticle(row + 1, col - 1).materialType == ParticleWorld::MaterialType::Gas) &&
			getParticle(row, col - 1).material == ParticleWorld::Material::Air &&
			getParticle(row, col).material == self.material)
		{

			setParticle(row + 1, col - 1, self);
			resetParticle(row, col);
		}
	}

	if (ruleset.canRight && ruleset.canDown)
	{
		// apply gravity (right)
		if (
			(getParticle(row + 1, col + 1).materialType == ParticleWorld::MaterialType::Liquid ||
				getParticle(row + 1, col + 1).materialType == ParticleWorld::MaterialType::Gas) &&
			getParticle(row, col + 1).material == ParticleWorld::Material::Air &&
			getParticle(row, col).material == self.material)
		{

			setParticle(row + 1, col + 1, self);
			resetParticle(row, col);
		}
	}
}