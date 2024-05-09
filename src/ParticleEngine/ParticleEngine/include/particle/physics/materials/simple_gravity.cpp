#include <iostream>

#include "particle/particle_world.h"
#include "particle/particle_physics.h"
#include "particle/particle_sounds.h"

#include "tools/tools.h"
#include "tools/random.h"

void calculate_simpleGravity(int row, int col, ParticleWorld* particleWorld)
{
	// define self, this value is used whenever a pixel moves, it acts as a copy of all the settings for the current pixel
	// selfInital SHOULD NOT CHANGE
	const ParticleWorld::ParticleInstance selfInitial = particleWorld->getParticle(row, col);
	ParticleWorld::ParticleInstance self = selfInitial;

	if (particleWorld->canDown(row))
	{
		// apply downwards gravity
		if (
			(particleWorld->getParticle(row + 1, col).materialType == ParticleWorld::MaterialType::Gas/* ||
				particleWorld->getParticle(row + 1, col).materialType == ParticleWorld::MaterialType::Liquid*/) &&
			particleWorld->getParticle(row, col).material == self.material)
		{
			particleWorld->setParticle(row + 1, col, self);
			particleWorld->resetParticle(row, col);
		}
	}
}