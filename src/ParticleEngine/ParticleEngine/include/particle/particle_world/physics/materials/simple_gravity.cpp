#include <iostream>

#include "particle/particle_world.hpp"
#include "particle/particle_sounds.hpp"

#include "tools/tools.hpp"
#include "tools/random.hpp"

void ParticleWorld::calculate_simpleGravity(int row, int col, Ruleset ruleset)
{
	// define self, this value is used whenever a pixel moves, it acts as a copy of all the settings for the current pixel
	// selfInital SHOULD NOT CHANGE
	const ParticleWorld::Particle selfInitial = getParticle(row, col);
	ParticleWorld::Particle self = selfInitial;

	if (ruleset.canDown)
	{
		// apply downwards gravity
		if (
			(getParticle(row + 1, col).materialType == ParticleWorld::MaterialType::Gas/* ||
				getParticle(row + 1, col).materialType == ParticleWorld::MaterialType::Liquid*/) &&
			getParticle(row, col).material == self.material)
		{
			setParticle(row + 1, col, self);
			resetParticle(row, col);
		}
	}
}