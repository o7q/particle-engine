#include <iostream>

#include "particle/particle_world.h"
#include "particle/particle_sounds.h"

#include "tools/tools.h"
#include "tools/random.h"

void ParticleWorld::calculate_acid(int row, int col, Ruleset ruleset)
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
			setParticle(row - 1, col, self);
			particles[get1DIndex(row, col, colSize)].material = ParticleWorld::Material::Water;
		}
	}

	int eatChance = Random::genInt(0, 25);

	ParticleWorld::Particle acidSmoke;
	acidSmoke.material = ParticleWorld::Material::AcidGas;
	acidSmoke.materialType = ParticleWorld::MaterialType::Gas;
	acidSmoke.physicsType = ParticleWorld::PhysicsType::AcidSmoke;
	acidSmoke.flammable = true;

	// fell is used to determine if the water should continue to look for a lower value
	// if not defined, the water will move indefinetely, for visual appeal, this value for introduced to freeze the water in place after a certain amount of time
	bool fell = false;

	if (ruleset.canDown)
	{
		// apply gravity (down)
		if (
			getParticle(row + 1, col).materialType == ParticleWorld::MaterialType::Gas &&
			getParticle(row, col).material == self.material)
		{
			self.physicsFreezeTime = 0;
			fell = true;
			self.lastY = row + 1;
			self.isFalling = true;
			setParticle(row + 1, col, self);
			resetParticle(row, col);
		}
		else if (
			eatChance == 0 &&
			getParticle(row + 1, col).material != ParticleWorld::Material::Air &&
			getParticle(row + 1, col).material != self.material
			)
		{
			self.physicsFreezeTime = 0;
			fell = true;
			self.lastY = row + 1;
			self.isFalling = true;
			paintParticles(row - 3, col, 2, acidSmoke, ParticleWorld::Shape::Square);
			setParticle(row + 1, col, self);
			resetParticle(row, col);

			SoundEngine::playSound(SoundEngine::SoundType::Sizzle, col, getColSize());
		}
	}

	if (std::abs(lastY - self.lastY) == 0 && self.isFalling)
	{
		particles[get1DIndex(row, col, getColSize())].isFalling = false;
		self.isFalling = false;
		SoundEngine::playSound(SoundEngine::SoundType::Bubble, col, getColSize());
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
			getParticle(row, col - 1).materialType == ParticleWorld::MaterialType::Gas &&
			self.physicsFreezeTime < getColSize() &&
			getParticle(row, col).material == self.material)
		{
			setParticle(row, col - 1, self);
			resetParticle(row, col);
		}
		else if (
			eatChance == 0 &&
			getParticle(row, col - 1).material != ParticleWorld::Material::Air &&
			getParticle(row, col - 1).material != self.material
			)
		{
			paintParticles(row - 3, col, 2, acidSmoke, ParticleWorld::Shape::Square);
			setParticle(row, col - 1, self);
			resetParticle(row, col);
		}
	}

	if (ruleset.canRight)
	{
		// apply gravity (right)
		if (
			getParticle(row, col + 1).materialType == ParticleWorld::MaterialType::Gas &&
			self.physicsFreezeTime < getColSize() &&
			getParticle(row, col).material == self.material)
		{
			setParticle(row, col + 1, self);
			resetParticle(row, col);
		}
		else if (
			eatChance == 0 &&
			getParticle(row, col + 1).material != ParticleWorld::Material::Air &&
			getParticle(row, col + 1).material != self.material
			)
		{
			paintParticles(row - 3, col, 2, acidSmoke, ParticleWorld::Shape::Square);
			setParticle(row, col + 1, self);
			resetParticle(row, col);
		}
	}
}