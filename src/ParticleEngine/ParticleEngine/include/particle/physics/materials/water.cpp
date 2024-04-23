#include <iostream>

#include "particle/particle_world.h"
#include "particle/particle_physics.h"
#include "tools/tools.h"
#include "particle/particle_sounds.h"

void calculate_liquid(int row, int col, ParticleWorld* particleWorld)
{
	// define self, this value is used whenever a pixel moves, it acts as a copy of all the settings for the current pixel
	ParticleWorld::ParticleInstance self = particleWorld->getParticle(row, col);

	if (particleWorld->canUp(row))
	{
		// if the current liquid is gasoline, ensure that it is on top of water
		if (
			particleWorld->getParticle(row, col).material == ParticleWorld::Material::Gasoline &&
			particleWorld->getParticle(row - 1, col).material == ParticleWorld::Material::Water)
		{
			particleWorld->setParticle(row - 1, col, self);
			particleWorld->particles[get1DIndex(row, col, particleWorld->getColSize())].material = ParticleWorld::Material::Water;
		}
	}

	// fell is used to determine if the water should continue to look for a lower value
	// if not defined, the water will move indefinetely, for visual appeal, this value for introduced to freeze the water in place after a certain amount of time
	bool fell = false;

	if (particleWorld->canDown(row))
	{
		// apply gravity (down)
		if (
			(particleWorld->getParticle(row + 1, col).material == ParticleWorld::Material::Air ||
				particleWorld->getParticle(row + 1, col).materialType == ParticleWorld::MaterialType::Gas ||
				particleWorld->getParticle(row + 1, col).material == ParticleWorld::Material::Fire) &&
			particleWorld->getParticle(row, col).material == self.material)
		{
			self.physicsFreezeTime = 0;
			fell = true;
			particleWorld->setParticle(row + 1, col, self);
			particleWorld->resetParticle(row, col);
		}
	}

	// if the water didn't fall, increment the physicsFreezeTime
	if (!fell)
	{
		self.physicsFreezeTime++;
	}

	if (particleWorld->canDown(row) && particleWorld->canLeft(col))
	{
		// if the water is able to fall (left) next time, reset physicsFreezeTime
		if (particleWorld->getParticle(row + 1, col - 1).materialType == ParticleWorld::MaterialType::Gas ||
			particleWorld->getParticle(row + 1, col - 1).material == ParticleWorld::Material::Air)
		{
			self.physicsFreezeTime = 0;
		}
	}

	if (particleWorld->canDown(row) && particleWorld->canRight(col))
	{
		// if the water is able to fall (right) next time, reset physicsFreezeTime
		if (particleWorld->getParticle(row + 1, col + 1).materialType == ParticleWorld::MaterialType::Gas ||
			particleWorld->getParticle(row + 1, col + 1).material == ParticleWorld::Material::Air)
		{
			self.physicsFreezeTime = 0;
		}
	}

	if (particleWorld->canLeft(col))
	{
		// apply gravity (left)
		if (
			(particleWorld->getParticle(row, col - 1).material == ParticleWorld::Material::Air ||
				particleWorld->getParticle(row, col - 1).materialType == ParticleWorld::MaterialType::Gas ||
				particleWorld->getParticle(row, col - 1).material == ParticleWorld::Material::Fire) && self.physicsFreezeTime < particleWorld->getColSize() &&
			particleWorld->getParticle(row, col).material == self.material)
		{
			particleWorld->setParticle(row, col - 1, self);
			particleWorld->resetParticle(row, col);
		}
	}

	if (particleWorld->canRight(col))
	{
		// apply gravity (right)
		if (
			(particleWorld->getParticle(row, col + 1).material == ParticleWorld::Material::Air ||
				particleWorld->getParticle(row, col + 1).materialType == ParticleWorld::MaterialType::Gas ||
				particleWorld->getParticle(row, col + 1).material == ParticleWorld::Material::Fire) && self.physicsFreezeTime < particleWorld->getColSize() &&
			particleWorld->getParticle(row, col).material == self.material)
		{
			particleWorld->setParticle(row, col + 1, self);
			particleWorld->resetParticle(row, col);
		}
	}
}