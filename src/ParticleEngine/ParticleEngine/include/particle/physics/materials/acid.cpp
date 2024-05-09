#include <iostream>

#include "particle/particle_world.h"
#include "particle/particle_physics.h"
#include "particle/particle_sounds.h"

#include "tools/tools.h"
#include "tools/random.h"

void calculate_acid(int row, int col, ParticleWorld* particleWorld)
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
			particleWorld->setParticle(row - 1, col, self);
			particleWorld->particles[get1DIndex(row, col, particleWorld->getColSize())].material = ParticleWorld::Material::Water;
		}
	}

	int eatChance = Random::genInt(0, 25);

	ParticleWorld::ParticleInstance acidSmoke;
	acidSmoke.material = ParticleWorld::Material::AcidGas;
	acidSmoke.materialType = ParticleWorld::MaterialType::Gas;
	acidSmoke.physicsType = ParticleWorld::PhysicsType::AcidSmoke;
	acidSmoke.flammable = true;

	// fell is used to determine if the water should continue to look for a lower value
	// if not defined, the water will move indefinetely, for visual appeal, this value for introduced to freeze the water in place after a certain amount of time
	bool fell = false;

	if (particleWorld->canDown(row))
	{
		// apply gravity (down)
		if (
			particleWorld->getParticle(row + 1, col).materialType == ParticleWorld::MaterialType::Gas &&
			particleWorld->getParticle(row, col).material == self.material)
		{
			self.physicsFreezeTime = 0;
			fell = true;
			self.lastY = row + 1;
			self.isFalling = true;
			particleWorld->setParticle(row + 1, col, self);
			particleWorld->resetParticle(row, col);
		}
		else if (
			eatChance == 0 &&
			particleWorld->getParticle(row + 1, col).material != ParticleWorld::Material::Air &&
			particleWorld->getParticle(row + 1, col).material != self.material
			)
		{
			self.physicsFreezeTime = 0;
			fell = true;
			self.lastY = row + 1;
			self.isFalling = true;
			particleWorld->paintParticles(row - 3, col, 2, acidSmoke, ParticleWorld::Shape::Square);
			particleWorld->setParticle(row + 1, col, self);
			particleWorld->resetParticle(row, col);

			SoundEngine::playSound(SoundEngine::SoundType::Sizzle, col, particleWorld->getColSize());
		}
	}

	if (std::abs(lastY - self.lastY) == 0 && self.isFalling)
	{
		particleWorld->particles[get1DIndex(row, col, particleWorld->getColSize())].isFalling = false;
		self.isFalling = false;
		SoundEngine::playSound(SoundEngine::SoundType::Bubble, col, particleWorld->getColSize());
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
			particleWorld->getParticle(row, col - 1).materialType == ParticleWorld::MaterialType::Gas &&
			self.physicsFreezeTime < particleWorld->getColSize() &&
			particleWorld->getParticle(row, col).material == self.material)
		{
			particleWorld->setParticle(row, col - 1, self);
			particleWorld->resetParticle(row, col);
		}
		else if (
			eatChance == 0 &&
			particleWorld->getParticle(row, col - 1).material != ParticleWorld::Material::Air &&
			particleWorld->getParticle(row, col - 1).material != self.material
			)
		{
			particleWorld->paintParticles(row - 3, col, 2, acidSmoke, ParticleWorld::Shape::Square);
			particleWorld->setParticle(row, col - 1, self);
			particleWorld->resetParticle(row, col);
		}
	}

	if (particleWorld->canRight(col))
	{
		// apply gravity (right)
		if (
			particleWorld->getParticle(row, col + 1).materialType == ParticleWorld::MaterialType::Gas &&
			self.physicsFreezeTime < particleWorld->getColSize() &&
			particleWorld->getParticle(row, col).material == self.material)
		{
			particleWorld->setParticle(row, col + 1, self);
			particleWorld->resetParticle(row, col);
		}
		else if (
			eatChance == 0 &&
			particleWorld->getParticle(row, col + 1).material != ParticleWorld::Material::Air &&
			particleWorld->getParticle(row, col + 1).material != self.material
			)
		{
			particleWorld->paintParticles(row - 3, col, 2, acidSmoke, ParticleWorld::Shape::Square);
			particleWorld->setParticle(row, col + 1, self);
			particleWorld->resetParticle(row, col);
		}
	}
}