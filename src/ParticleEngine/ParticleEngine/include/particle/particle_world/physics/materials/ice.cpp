#include <iostream>

#include "particle/particle_world.hpp"
#include "particle/particle_sounds.hpp"

#include "tools/tools.hpp"
#include "tools/random.hpp"

void ParticleWorld::calculate_ice(int row, int col, Ruleset ruleset)
{
	// define self, this value is used whenever a pixel moves, it acts as a copy of all the settings for the current pixel
	// selfInital SHOULD NOT CHANGE
	const ParticleWorld::Particle selfInitial = getParticle(row, col);
	ParticleWorld::Particle self = selfInitial;;

	// define random melt chance
	int meltValue = Random::genInt(0, 3);

	if (ruleset.canDown)
	{
		// apply gravity (down)
		if (
			(getParticle(row + 1, col).material == ParticleWorld::Material::Air ||
				getParticle(row + 1, col).materialType == ParticleWorld::MaterialType::Gas) &&
			getParticle(row, col).material == self.material)
		{
			setParticle(row + 1, col, self);
			resetParticle(row, col);
		}
	}

	if (ruleset.canLeft)
	{
		// if in contact with steam, increment melt chance by 20 (left)
		if (getParticle(row, col - 1).material == ParticleWorld::Material::Steam)
		{
			particles[get1DIndex(row, col, getColSize())].intValue += 20;
		}

		// if in contact with air, increment melt chance by 3 (left)
		if (getParticle(row, col - 1).material == ParticleWorld::Material::Air)
		{
			particles[get1DIndex(row, col, getColSize())].intValue += 3;
		}

		// if in contact with a liquid, increment melt chance by 2 (left)
		if (getParticle(row, col - 1).material == ParticleWorld::Material::Water)
		{
			particles[get1DIndex(row, col, getColSize())].intValue += 2;
		}

		// if in contact with a fire, increment melt chance by MAX (left)
		if (getParticle(row, col - 1).material == ParticleWorld::Material::Fire)
		{
			particles[get1DIndex(row, col, getColSize())].intValue += 5000;
		}
	}

	if (ruleset.canRight)
	{
		// if in contact with steam, increment melt chance by 20 (right)
		if (getParticle(row, col + 1).material == ParticleWorld::Material::Steam)
		{
			particles[get1DIndex(row, col, getColSize())].intValue += 20;
		}

		// if in contact with air, increment melt chance by 3 (right)
		if (getParticle(row, col + 1).material == ParticleWorld::Material::Air)
		{
			particles[get1DIndex(row, col, getColSize())].intValue += 3;
		}

		// if in contact with a liquid, increment melt chance by 2 (right)
		if (getParticle(row, col + 1).material == ParticleWorld::Material::Water)
		{
			particles[get1DIndex(row, col, getColSize())].intValue += 2;
		}

		// if in contact with a fire, increment melt chance by MAX (right)
		if (getParticle(row, col + 1).material == ParticleWorld::Material::Fire)
		{
			particles[get1DIndex(row, col, getColSize())].intValue += 5000;
		}
	}

	if (ruleset.canUp)
	{
		// if in contact with a fire (up), increment melt chance by 2500 (MAX/2)
		if (getParticle(row - 1, col).material == ParticleWorld::Material::Fire)
		{
			particles[get1DIndex(row, col, getColSize())].intValue += 2500;
		}
	}

	if (getParticle(row, col).intValue >= 5000)
	{
		// if the ice has an intValue (meltValue) of 5000, convert it to water
		resetParticle(row, col);
		particles[get1DIndex(row, col, getColSize())].material = ParticleWorld::Material::Water;
		particles[get1DIndex(row, col, getColSize())].materialType = ParticleWorld::MaterialType::Liquid;
		particles[get1DIndex(row, col, getColSize())].physicsType = ParticleWorld::PhysicsType::Water;
		particles[get1DIndex(row, col, getColSize())].createsSteam = true;
	}
	else
	{
		// increment the meltValue anyways, even if nothing happens
		particles[get1DIndex(row, col, getColSize())].intValue += meltValue;
	}
}