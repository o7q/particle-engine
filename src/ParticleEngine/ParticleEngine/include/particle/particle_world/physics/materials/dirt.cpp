#include <iostream>

#include "particle/particle_world.h"
#include "particle/particle_sounds.h"

#include "tools/tools.h"
#include "tools/random.h"

void ParticleWorld::calculate_dirt(int row, int col, Ruleset ruleset)
{
	// define self, this value is used whenever a pixel moves, it acts as a copy of all the settings for the current pixel
	// selfInital SHOULD NOT CHANGE
	const ParticleWorld::Particle selfInitial = getParticle(row, col);
	ParticleWorld::Particle self = selfInitial;

	if (ruleset.canUp)
	{
		// increment wetness if a liquid is present (up = more wet)
		if (getParticle(row - 1, col).materialType == ParticleWorld::MaterialType::Liquid &&
			getParticle(row, col).wetnessMultiplier <= 1.0f)
		{
			particles[get1DIndex(row, col, getColSize())].wetnessMultiplier += 0.1f;
		}

		// grow grass if water is present
		if (getParticle(row - 1, col).material == ParticleWorld::Material::Water &&
			getParticle(row, col).wetnessMultiplier >= 0.9f)
		{
			particles[get1DIndex(row, col, getColSize())].material = ParticleWorld::Material::Grass;
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
				getParticle(row + 1, col).material == ParticleWorld::Material::Water) &&
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