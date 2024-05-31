#include <iostream>

#include "particle/particle_world.h"
#include "particle/particle_sounds.h"

#include "tools/tools.h"
#include "tools/random.h"

void ParticleWorld::calculate_smoke(int row, int col, Ruleset ruleset)
{
	// define self, this value is used whenever a pixel moves, it acts as a copy of all the settings for the current pixel
	// selfInital SHOULD NOT CHANGE
	const ParticleWorld::Particle selfInitial = getParticle(row, col);
	ParticleWorld::Particle self = selfInitial;

	// define distribution for randomJitter, randomJitter is used to add randomness to unstable materials, such as: gas
	int randomJitter = Random::genInt(0, 1);

	if (ruleset.canUp)
	{
		if (
			getParticle(row - 1, col).material == ParticleWorld::Material::Air &&
			getParticle(row, col).material == self.material &&
			getParticle(row, col).intValue > 1)
		{
			setParticle(row - 1, col, self);
			particles[get1DIndex(row - 1, col, getColSize())].intValue = 0;
			if (getParticle(row - 1, col).brightnessMultiplier > 0.1f)
			{
				// deincrement brightness, giving the illusion of dissipation
				particles[get1DIndex(row - 1, col, getColSize())].brightnessMultiplier -= 0.005f;
			}
			resetParticle(row, col);
		}
		else
		{
			particles[get1DIndex(row, col, getColSize())].intValue++;
		}
	}

	if (ruleset.canLeft && randomJitter == 0)
	{
		// apply gravity (left)
		if (
			getParticle(row, col - 1).material == ParticleWorld::Material::Air &&
			getParticle(row, col).material == self.material)
		{
			setParticle(row, col - 1, self);
			resetParticle(row, col);
		}
	}

	if (ruleset.canRight && randomJitter == 1)
	{
		// apply gravity (right)
		if (
			getParticle(row, col + 1).material == ParticleWorld::Material::Air &&
			getParticle(row, col).material == self.material)
		{
			setParticle(row, col + 1, self);
			resetParticle(row, col);
		}
	}

	particles[get1DIndex(row, col, getColSize())].intValue++;
	if (getParticle(row, col).intValue > 150)
	{
		// eventually kill the particle if it gets to a certain age
		resetParticle(row, col);
	}

	if (getParticle(row, col).intValue % 60 == 0)
	{
		if (getParticle(row, col).brightnessMultiplier > 0.1f)
		{
			// slowly darken the particle as it ages
			particles[get1DIndex(row, col, getColSize())].brightnessMultiplier -= 0.1f;
		}
	}
}