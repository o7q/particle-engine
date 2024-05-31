#include <iostream>

#include "particle/particle_world.h"
#include "particle/particle_sounds.h"

#include "tools/tools.h"
#include "tools/random.h"

void ParticleWorld::calculate_sand(int row, int col, Ruleset ruleset)
{
	// define self, this value is used whenever a pixel moves, it acts as a copy of all the settings for the current pixel
	// selfInital SHOULD NOT CHANGE
	const ParticleWorld::Particle selfInitial = getParticle(row, col);
	ParticleWorld::Particle self = selfInitial;

	if (ruleset.canUp)
	{
		// increment wetness if a liquid is present (up = more wet)
		if (getParticle(row - 1, col).materialType == ParticleWorld::MaterialType::Liquid &&
			self.wetnessMultiplier <= 2.0f)
		{
			self.wetnessMultiplier += 0.1f;
		}
	}

	if (ruleset.canLeft)
	{
		// increment wetness if a liquid is present (left)
		if (getParticle(row, col - 1).materialType == ParticleWorld::MaterialType::Liquid &&
			self.wetnessMultiplier <= 1.5f)
		{
			self.wetnessMultiplier += 0.05f;
		}
	}

	if (ruleset.canRight)
	{
		// increment wetness if a liquid is present (right)
		if (getParticle(row, col + 1).materialType == ParticleWorld::MaterialType::Liquid &&
			self.wetnessMultiplier <= 1.5f)
		{
			self.wetnessMultiplier += 0.05f;
		}
	}

	if (ruleset.canDown)
	{
		// apply gravity (down)
		if (
			(getParticle(row + 1, col).materialType == ParticleWorld::MaterialType::Gas ||
				(getParticle(row + 1, col).materialType == ParticleWorld::MaterialType::Liquid) &&
				getParticle(row, col).material == self.material))
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
			getParticle(row, col - 1).materialType == ParticleWorld::MaterialType::Gas &&
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
			getParticle(row, col + 1).materialType == ParticleWorld::MaterialType::Gas &&
			getParticle(row, col).material == self.material)
		{
			setParticle(row + 1, col + 1, self);
			resetParticle(row, col);
		}
	}
}