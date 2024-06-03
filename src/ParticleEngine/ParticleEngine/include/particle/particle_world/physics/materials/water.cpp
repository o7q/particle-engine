#include <iostream>

#include "particle/particle_world.hpp"
#include "particle/particle_sounds.hpp"

#include "tools/tools.hpp"
#include "tools/random.hpp"

void ParticleWorld::calculate_liquid(int row, int col, Ruleset ruleset)
{
	// define self, this value is used whenever a pixel moves, it acts as a copy of all the settings for the current pixel
	// selfInital SHOULD NOT CHANGE
	const ParticleWorld::Particle selfInitial = getParticle(row, col);
	ParticleWorld::Particle self = selfInitial;

	int lastY = selfInitial.lastY;

	if (ruleset.canUp)
	{
		// if the current liquid is gasoline, ensure that it is on top of water
		if (
			getParticle(row, col).material == ParticleWorld::Material::Gasoline &&
			getParticle(row - 1, col).material == ParticleWorld::Material::Water)
		{
			setParticle(row - 1, col, selfInitial);
			particles[get1DIndex(row, col, getColSize())].material = ParticleWorld::Material::Water;
		}
	}

	// fell is used to determine if the water should continue to look for a lower value
	// if not defined, the water will move indefinetely, for visual appeal, this value for introduced to freeze the water in place after a certain amount of time
	bool fell = false;

	if (ruleset.canDown)
	{
		// apply gravity (down)
		if (
			(/*getParticle(row + 1, col).material == ParticleWorld::Material::Air ||*/
				getParticle(row + 1, col).materialType == ParticleWorld::MaterialType::Gas ||
				getParticle(row + 1, col).material == ParticleWorld::Material::Fire) &&
			getParticle(row, col).material == selfInitial.material)
		{
			fell = true;

			self.lastY = row + 1;
			self.isFalling = true;

			self.physicsFreezeTime = 0;

			setParticle(row + 1, col, self);
			resetParticle(row, col);
		}
	}

	if (std::abs(lastY - self.lastY) == 0 && self.isFalling)
	{
		self.isFalling = false;
		particles[get1DIndex(row, col, getColSize())].isFalling = false;
		SoundEngine::playSound(SoundEngine::SoundType::LiquidDrip, col, getColSize());
	}

	// if the water didn't fall, increment the physicsFreezeTime
	if (!fell)
	{
		self.physicsFreezeTime++;
	}

	if (ruleset.canDown && ruleset.canLeft)
	{
		// if the water is able to fall (left) next time, reset physicsFreezeTime
		if (getParticle(row + 1, col - 1).materialType == ParticleWorld::MaterialType::Gas)
		{
			self.physicsFreezeTime = 0;
		}
	}

	if (ruleset.canDown && ruleset.canRight)
	{
		// if the water is able to fall (right) next time, reset physicsFreezeTime
		if (getParticle(row + 1, col + 1).materialType == ParticleWorld::MaterialType::Gas)
		{
			self.physicsFreezeTime = 0;
		}
	}

	if (ruleset.canLeft)
	{
		// apply gravity (left)
		if (
			(getParticle(row, col - 1).materialType == ParticleWorld::MaterialType::Gas ||
				getParticle(row, col - 1).material == ParticleWorld::Material::Fire) &&
			self.physicsFreezeTime < getColSize() &&
			getParticle(row, col).material == selfInitial.material)
		{
			setParticle(row, col - 1, self);
			resetParticle(row, col);
		}
	}

	if (ruleset.canRight)
	{
		// apply gravity (right)
		if (
			(getParticle(row, col + 1).materialType == ParticleWorld::MaterialType::Gas ||
				getParticle(row, col + 1).material == ParticleWorld::Material::Fire) &&
			self.physicsFreezeTime < getColSize() &&
			getParticle(row, col).material == selfInitial.material)
		{
			setParticle(row, col + 1, self);
			resetParticle(row, col);
		}
	}
}