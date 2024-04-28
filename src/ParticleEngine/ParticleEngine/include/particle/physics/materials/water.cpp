#include <iostream>

#include "particle/particle_world.h"
#include "particle/particle_physics.h"
#include "particle/particle_sounds.h"

#include "tools/tools.h"

void calculate_liquid(int row, int col, ParticleWorld* particleWorld)
{
	// define self, this value is used whenever a pixel moves, it acts as a copy of all the settings for the current pixel
	// selfInital SHOULD NOT CHANGE
	const ParticleWorld::ParticleInstance selfInitial = particleWorld->getParticle(row, col);
	ParticleWorld::ParticleInstance self = selfInitial;

	int lastY = selfInitial.lastY;

	if (particleWorld->canUp(row))
	{
		// if the current liquid is gasoline, ensure that it is on top of water
		if (
			particleWorld->getParticle(row, col).material == ParticleWorld::Material::Gasoline &&
			particleWorld->getParticle(row - 1, col).material == ParticleWorld::Material::Water)
		{
			particleWorld->setParticle(row - 1, col, selfInitial);
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
			(/*particleWorld->getParticle(row + 1, col).material == ParticleWorld::Material::Air ||*/
				particleWorld->getParticle(row + 1, col).materialType == ParticleWorld::MaterialType::Gas ||
				particleWorld->getParticle(row + 1, col).material == ParticleWorld::Material::Fire) &&
			particleWorld->getParticle(row, col).material == selfInitial.material)
		{
			fell = true;

			self.lastY = row + 1;
			self.isFalling = true;

			self.physicsFreezeTime = 0;

			particleWorld->setParticle(row + 1, col, self);
			particleWorld->resetParticle(row, col);
		}
	}

	if (std::abs(lastY - self.lastY) == 0 && self.isFalling)
	{
		self.isFalling = false;
		particleWorld->particles[get1DIndex(row, col, particleWorld->getColSize())].isFalling = false;
		SoundEngine::playSound(SoundEngine::SoundType::LiquidDrip, col, particleWorld->getColSize());
	}

	// if the water didn't fall, increment the physicsFreezeTime
	if (!fell)
	{
		self.physicsFreezeTime++;
	}

	if (particleWorld->canDown(row) && particleWorld->canLeft(col))
	{
		// if the water is able to fall (left) next time, reset physicsFreezeTime
		if (particleWorld->getParticle(row + 1, col - 1).materialType == ParticleWorld::MaterialType::Gas)
		{
			self.physicsFreezeTime = 0;
		}
	}

	if (particleWorld->canDown(row) && particleWorld->canRight(col))
	{
		// if the water is able to fall (right) next time, reset physicsFreezeTime
		if (particleWorld->getParticle(row + 1, col + 1).materialType == ParticleWorld::MaterialType::Gas)
		{
			self.physicsFreezeTime = 0;
		}
	}

	if (particleWorld->canLeft(col))
	{
		// apply gravity (left)
		if (
			(particleWorld->getParticle(row, col - 1).materialType == ParticleWorld::MaterialType::Gas ||
				particleWorld->getParticle(row, col - 1).material == ParticleWorld::Material::Fire) &&
			self.physicsFreezeTime < particleWorld->getColSize() &&
			particleWorld->getParticle(row, col).material == selfInitial.material)
		{
			particleWorld->setParticle(row, col - 1, self);
			particleWorld->resetParticle(row, col);
		}
	}

	if (particleWorld->canRight(col))
	{
		// apply gravity (right)
		if (
			(particleWorld->getParticle(row, col + 1).materialType == ParticleWorld::MaterialType::Gas ||
				particleWorld->getParticle(row, col + 1).material == ParticleWorld::Material::Fire) &&
			self.physicsFreezeTime < particleWorld->getColSize() &&
			particleWorld->getParticle(row, col).material == selfInitial.material)
		{
			particleWorld->setParticle(row, col + 1, self);
			particleWorld->resetParticle(row, col);
		}
	}
}