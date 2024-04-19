#include <iostream>

#include "particle/particle_world.h"
#include "particle/particle_physics.h"
#include "tools/tools.h"

void calculate_grass(int row, int col, ParticleWorld* particleWorld)
{
	// define self, this value is used whenever a pixel moves, it acts as a copy of all the settings for the current pixel
	ParticleWorld::ParticleInstance self = particleWorld->getParticle(row, col);

	// generate random int for growing chance of floweres
	std::uniform_int_distribution<int> dist(0, 10000000);
	int growFlowerChance = dist(particleWorld->gen);

	if (particleWorld->canUp(row))
	{
		// increment wetness if a liquid is present (up)
		if (particleWorld->getParticle(row - 1, col).materialType == ParticleWorld::MaterialType::Liquid &&
			particleWorld->getParticle(row, col).wetnessMultiplier <= 1.0f)
		{
			particleWorld->particles[get1DIndex(row, col, particleWorld->colSize)].wetnessMultiplier += 0.1f;
		}

		if (particleWorld->getParticle(row - 1, col).material == ParticleWorld::Material::Air &&
			particleWorld->getParticle(row, col).wetnessMultiplier >= 0.9f)
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
				particleWorld->particles[get1DIndex(row - 1, col, particleWorld->colSize)].material = flowerToGrow;
			}
		}
	}

	if (particleWorld->canLeft(col))
	{
		// increment wetness if a liquid is present (left)
		if (particleWorld->getParticle(row, col - 1).materialType == ParticleWorld::MaterialType::Liquid &&
			particleWorld->getParticle(row, col).wetnessMultiplier <= 0.5f)
		{
			particleWorld->particles[get1DIndex(row, col, particleWorld->colSize)].wetnessMultiplier += 0.05f;
		}
	}

	if (particleWorld->canRight(col))
	{
		// increment wetness if a liquid is present (right)
		if (particleWorld->getParticle(row, col + 1).materialType == ParticleWorld::MaterialType::Liquid &&
			particleWorld->getParticle(row, col).wetnessMultiplier <= 0.5f)
		{
			particleWorld->particles[get1DIndex(row, col, particleWorld->colSize)].wetnessMultiplier += 0.05f;
		}
	}

	if (particleWorld->canDown(row))
	{
		// apply gravity (down)
		if (
			(particleWorld->getParticle(row + 1, col).materialType == ParticleWorld::MaterialType::Gas ||
				particleWorld->getParticle(row + 1, col).materialType == ParticleWorld::MaterialType::Liquid) &&
			particleWorld->getParticle(row, col).material == self.material)
		{
			particleWorld->setParticle(row + 1, col, self);
			particleWorld->resetParticle(row, col);
		}
	}

	if (particleWorld->canLeft(col) && particleWorld->canDown(row))
	{
		// apply gravity (left)
		if (
			(particleWorld->getParticle(row + 1, col - 1).materialType == ParticleWorld::MaterialType::Liquid ||
				particleWorld->getParticle(row + 1, col - 1).materialType == ParticleWorld::MaterialType::Gas) &&
			particleWorld->getParticle(row, col - 1).material == ParticleWorld::Material::Air &&
			particleWorld->getParticle(row, col).material == self.material)
		{

			particleWorld->setParticle(row + 1, col - 1, self);
			particleWorld->resetParticle(row, col);
		}
	}

	if (particleWorld->canRight(col) && particleWorld->canDown(row))
	{
		// apply gravity (right)
		if (
			(particleWorld->getParticle(row + 1, col + 1).materialType == ParticleWorld::MaterialType::Liquid ||
				particleWorld->getParticle(row + 1, col + 1).materialType == ParticleWorld::MaterialType::Gas) &&
			particleWorld->getParticle(row, col + 1).material == ParticleWorld::Material::Air &&
			particleWorld->getParticle(row, col).material == self.material)
		{

			particleWorld->setParticle(row + 1, col + 1, self);
			particleWorld->resetParticle(row, col);
		}
	}
}