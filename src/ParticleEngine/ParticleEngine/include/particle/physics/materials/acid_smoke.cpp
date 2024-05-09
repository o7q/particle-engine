#include <iostream>

#include "particle/particle_world.h"
#include "particle/particle_physics.h"
#include "particle/particle_sounds.h"

#include "tools/tools.h"
#include "tools/random.h"

void calculate_acidSmoke(int row, int col, ParticleWorld* particleWorld)
{
	// define self, this value is used whenever a pixel moves, it acts as a copy of all the settings for the current pixel
	// selfInital SHOULD NOT CHANGE
	const ParticleWorld::ParticleInstance selfInitial = particleWorld->getParticle(row, col);
	ParticleWorld::ParticleInstance self = selfInitial;

	// define distribution for randomJitter, randomJitter is used to add randomness to unstable materials, such as: gas
	int randomJitter = Random::genInt(0, 1);

	int eatChance = Random::genInt(0, 100);

	if (particleWorld->canUp(row))
	{
		if (
			particleWorld->getParticle(row - 1, col).material == ParticleWorld::Material::Air &&
			particleWorld->getParticle(row, col).material == self.material &&
			particleWorld->getParticle(row, col).intValue > 1)
		{
			particleWorld->setParticle(row - 1, col, self);
			particleWorld->particles[get1DIndex(row - 1, col, particleWorld->getColSize())].intValue = 0;
			if (particleWorld->getParticle(row - 1, col).brightnessMultiplier > 0.4f)
			{
				// deincrement brightness, giving the illusion of dissipation
				particleWorld->particles[get1DIndex(row - 1, col, particleWorld->getColSize())].brightnessMultiplier -= 0.005f;
			}
			particleWorld->resetParticle(row, col);
		}
		else
		{
			if (
				eatChance == 0 &&
				particleWorld->getParticle(row - 1, col).material != ParticleWorld::Material::Air &&
				particleWorld->getParticle(row - 1, col).material != ParticleWorld::Material::Acid &&
				particleWorld->getParticle(row - 1, col).material != self.material
				)
			{
				particleWorld->setParticle(row - 1, col, self);
				particleWorld->resetParticle(row, col);
			}
			particleWorld->particles[get1DIndex(row, col, particleWorld->getColSize())].intValue++;
		}
	}

	if (particleWorld->canLeft(col) && randomJitter == 0)
	{
		// apply gravity (left)
		if (
			particleWorld->getParticle(row, col - 1).material == ParticleWorld::Material::Air &&
			particleWorld->getParticle(row, col).material == self.material)
		{
			particleWorld->setParticle(row, col - 1, self);
			particleWorld->resetParticle(row, col);
		}
		else if (
			eatChance == 0 &&
			particleWorld->getParticle(row, col - 1).material != ParticleWorld::Material::Air &&
			particleWorld->getParticle(row, col - 1).material != ParticleWorld::Material::Acid &&
			particleWorld->getParticle(row, col - 1).material != self.material
			)
		{
			particleWorld->setParticle(row, col - 1, self);
			particleWorld->resetParticle(row, col);
		}
	}

	if (particleWorld->canRight(col) && randomJitter == 1)
	{
		// apply gravity (right)
		if (
			particleWorld->getParticle(row, col + 1).material == ParticleWorld::Material::Air &&
			particleWorld->getParticle(row, col).material == self.material)
		{
			particleWorld->setParticle(row, col + 1, self);
			particleWorld->resetParticle(row, col);
		}
		else if (
			eatChance == 0 &&
			particleWorld->getParticle(row, col + 1).material != ParticleWorld::Material::Air &&
			particleWorld->getParticle(row, col + 1).material != ParticleWorld::Material::Acid &&
			particleWorld->getParticle(row, col + 1).material != self.material
			)
		{
			particleWorld->setParticle(row, col + 1, self);
			particleWorld->resetParticle(row, col);
		}
	}

	particleWorld->particles[get1DIndex(row, col, particleWorld->getColSize())].intValue++;
	if (particleWorld->getParticle(row, col).intValue > 600)
	{
		// eventually kill the particle if it gets to a certain age
		particleWorld->resetParticle(row, col);
	}

	if (particleWorld->getParticle(row, col).intValue % 240 == 0)
	{
		if (particleWorld->getParticle(row, col).brightnessMultiplier > 0.1f)
		{
			// slowly darken the particle as it ages
			particleWorld->particles[get1DIndex(row, col, particleWorld->getColSize())].brightnessMultiplier -= 0.1f;
		}
	}
}