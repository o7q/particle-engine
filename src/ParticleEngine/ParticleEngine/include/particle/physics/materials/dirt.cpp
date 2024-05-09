#include <iostream>

#include "particle/particle_world.h"
#include "particle/particle_physics.h"
#include "particle/particle_sounds.h"

#include "tools/tools.h"
#include "tools/random.h"

void calculate_dirt(int row, int col, ParticleWorld* particleWorld)
{
	// define self, this value is used whenever a pixel moves, it acts as a copy of all the settings for the current pixel
	// selfInital SHOULD NOT CHANGE
	const ParticleWorld::ParticleInstance selfInitial = particleWorld->getParticle(row, col);
	ParticleWorld::ParticleInstance self = selfInitial;

	if (particleWorld->canUp(row))
	{
		// increment wetness if a liquid is present (up = more wet)
		if (particleWorld->getParticle(row - 1, col).materialType == ParticleWorld::MaterialType::Liquid &&
			particleWorld->getParticle(row, col).wetnessMultiplier <= 1.0f)
		{
			particleWorld->particles[get1DIndex(row, col, particleWorld->getColSize())].wetnessMultiplier += 0.1f;
		}

		// grow grass if water is present
		if (particleWorld->getParticle(row - 1, col).material == ParticleWorld::Material::Water &&
			particleWorld->getParticle(row, col).wetnessMultiplier >= 0.9f)
		{
			particleWorld->particles[get1DIndex(row, col, particleWorld->getColSize())].material = ParticleWorld::Material::Grass;
		}
	}

	if (particleWorld->canLeft(col))
	{
		// increment wetness if a liquid is present (left)
		if (particleWorld->getParticle(row, col - 1).materialType == ParticleWorld::MaterialType::Liquid &&
			particleWorld->getParticle(row, col).wetnessMultiplier <= 0.5f)
		{
			particleWorld->particles[get1DIndex(row, col, particleWorld->getColSize())].wetnessMultiplier += 0.05f;
		}
	}

	if (particleWorld->canRight(col))
	{
		// increment wetness if a liquid is present (right)
		if (particleWorld->getParticle(row, col + 1).materialType == ParticleWorld::MaterialType::Liquid &&
			particleWorld->getParticle(row, col).wetnessMultiplier <= 0.5f)
		{
			particleWorld->particles[get1DIndex(row, col, particleWorld->getColSize())].wetnessMultiplier += 0.05f;
		}
	}

	if (particleWorld->canDown(row))
	{
		// apply gravity (down)
		if (
			(particleWorld->getParticle(row + 1, col).materialType == ParticleWorld::MaterialType::Gas ||
				particleWorld->getParticle(row + 1, col).material == ParticleWorld::Material::Water) &&
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
			particleWorld->getParticle(row, col - 1).materialType == ParticleWorld::MaterialType::Gas &&
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
			particleWorld->getParticle(row, col + 1).materialType == ParticleWorld::MaterialType::Gas &&
			particleWorld->getParticle(row, col).material == self.material)
		{

			particleWorld->setParticle(row + 1, col + 1, self);
			particleWorld->resetParticle(row, col);
		}
	}
}