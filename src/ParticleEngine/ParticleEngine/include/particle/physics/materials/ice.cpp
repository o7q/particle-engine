#include <iostream>

#include "particle/particle_world.h"
#include "particle/particle_physics.h"
#include "tools/tools.h"

void calculate_ice(int row, int col, ParticleWorld* particleWorld)
{
	// define self, this value is used whenever a pixel moves, it acts as a copy of all the settings for the current pixel
	ParticleWorld::ParticleInstance self = particleWorld->getParticle(row, col);

	// define random melt chance
	std::uniform_int_distribution<int> dist(0, 3);
	int meltValue = dist(particleWorld->gen);

	if (particleWorld->canDown(row))
	{
		// apply gravity (down)
		if (
			(particleWorld->getParticle(row + 1, col).material == ParticleWorld::Material::Air ||
				particleWorld->getParticle(row + 1, col).materialType == ParticleWorld::MaterialType::Gas) &&
			particleWorld->getParticle(row, col).material == self.material)
		{
			particleWorld->setParticle(row + 1, col, self);
			particleWorld->resetParticle(row, col);
		}
	}

	if (particleWorld->canLeft(col))
	{
		// if in contact with steam, increment melt chance by 20 (left)
		if (particleWorld->getParticle(row, col - 1).materialType == ParticleWorld::Material::Steam)
		{
			particleWorld->particles[get1DIndex(row, col, particleWorld->colSize)].intValue += 20;
		}

		// if in contact with air, increment melt chance by 3 (left)
		if (particleWorld->getParticle(row, col - 1).material == ParticleWorld::Material::Air)
		{
			particleWorld->particles[get1DIndex(row, col, particleWorld->colSize)].intValue += 3;
		}

		// if in contact with a liquid, increment melt chance by 2 (left)
		if (particleWorld->getParticle(row, col - 1).materialType == ParticleWorld::Material::Water)
		{
			particleWorld->particles[get1DIndex(row, col, particleWorld->colSize)].intValue += 2;
		}

		// if in contact with a fire, increment melt chance by MAX (left)
		if (particleWorld->getParticle(row, col - 1).material == ParticleWorld::Material::Fire)
		{
			particleWorld->particles[get1DIndex(row, col, particleWorld->colSize)].intValue += 5000;
		}
	}

	if (particleWorld->canRight(col))
	{
		// if in contact with steam, increment melt chance by 20 (right)
		if (particleWorld->getParticle(row, col + 1).materialType == ParticleWorld::Material::Steam)
		{
			particleWorld->particles[get1DIndex(row, col, particleWorld->colSize)].intValue += 20;
		}

		// if in contact with air, increment melt chance by 3 (right)
		if (particleWorld->getParticle(row, col + 1).material == ParticleWorld::Material::Air)
		{
			particleWorld->particles[get1DIndex(row, col, particleWorld->colSize)].intValue += 3;
		}

		// if in contact with a liquid, increment melt chance by 2 (right)
		if (particleWorld->getParticle(row, col + 1).material == ParticleWorld::Material::Water)
		{
			particleWorld->particles[get1DIndex(row, col, particleWorld->colSize)].intValue += 2;
		}

		// if in contact with a fire, increment melt chance by MAX (right)
		if (particleWorld->getParticle(row, col + 1).material == ParticleWorld::Material::Fire)
		{
			particleWorld->particles[get1DIndex(row, col, particleWorld->colSize)].intValue += 5000;
		}
	}

	if (particleWorld->canUp(row))
	{
		// if in contact with a fire (up), increment melt chance by 2500 (MAX/2)
		if (particleWorld->getParticle(row - 1, col).material == ParticleWorld::Material::Fire)
		{
			particleWorld->particles[get1DIndex(row, col, particleWorld->colSize)].intValue += 2500;
		}
	}

	if (particleWorld->getParticle(row, col).intValue >= 5000)
	{
		// if the ice has an intValue (meltValue) of 5000, convert it to water
		particleWorld->resetParticle(row, col);
		particleWorld->particles[get1DIndex(row, col, particleWorld->colSize)].material = ParticleWorld::Material::Water;
		particleWorld->particles[get1DIndex(row, col, particleWorld->colSize)].materialType = ParticleWorld::MaterialType::Liquid;
	}
	else
	{
		// increment the meltValue anyways, even if nothing happens
		particleWorld->particles[get1DIndex(row, col, particleWorld->colSize)].intValue += meltValue;
	}
}