#include <iostream>

#include "particle/particle_world.h"
#include "particle/particle_physics.h"
#include "tools/tools.h"
#include "particle/particle_sounds.h"

void calculate_fire(int row, int col, ParticleWorld* particleWorld)
{
	// define randomBurnout value (0, 2), 2 means higher chance to burnout
	std::uniform_int_distribution<int> dist(0, 2);
	int randomBurnout = dist(particleWorld->gen);

	particleWorld->particles[get1DIndex(row, col, particleWorld->getColSize())].intValue += randomBurnout;
	if (particleWorld->getParticle(row, col).intValue > 500)
	{
		particleWorld->resetParticle(row, col);
	}

	// define self, this value is used whenever a pixel moves, it acts as a copy of all the settings for the current pixel
	// define self after randomBurnout, so the value is replicated through adjacent particles, if applicable
	ParticleWorld::ParticleInstance self = particleWorld->getParticle(row, col);

	if (particleWorld->canUp(row))
	{
		// ignite flammable materials (up)
		if (
			particleWorld->getParticle(row - 1, col).flammable == true &&
			particleWorld->getParticle(row, col).material == self.material)
		{
			particleWorld->setParticle(row - 1, col, self);
			SoundEngine::playSound(SoundEngine::SoundType::Fire, col, particleWorld->getColSize());
		}
	}

	if (particleWorld->canDown(row))
	{
		// ignite flammable down
		if (
			particleWorld->getParticle(row + 1, col).flammable == true &&
			particleWorld->getParticle(row, col).material == self.material)
		{
			particleWorld->setParticle(row + 1, col, self);
			SoundEngine::playSound(SoundEngine::SoundType::Fire, col, particleWorld->getColSize());
		}

		// apply gravity (down
		if (
			particleWorld->getParticle(row + 1, col).materialType == ParticleWorld::MaterialType::Gas &&
			particleWorld->getParticle(row, col).material == self.material)
		{
			particleWorld->setParticle(row + 1, col, self);
			particleWorld->resetParticle(row, col);
		}

		// create steam if in contact with water
		if (particleWorld->getParticle(row + 1, col).createsSteam == true)
		{
			ParticleWorld::ParticleInstance steam;
			steam.material = ParticleWorld::Material::Steam;
			steam.materialType = ParticleWorld::MaterialType::Gas;
			steam.physicsType = ParticleWorld::PhysicsType::Smoke;
			particleWorld->paintParticles(row - 1, col, 5, steam);
			SoundEngine::playSound(SoundEngine::SoundType::Sizzle, col, particleWorld->getColSize());
		}
	}

	if (particleWorld->canLeft(col))
	{
		// ignite flammable (left)
		if (
			particleWorld->getParticle(row, col - 1).flammable == true &&
			particleWorld->getParticle(row, col).material == self.material)
		{
			particleWorld->setParticle(row, col - 1, self);
			SoundEngine::playSound(SoundEngine::SoundType::Fire, col, particleWorld->getColSize());
		}

		// apply gravity (left)
		if (
			(particleWorld->getParticle(row, col - 1).material == ParticleWorld::Material::Air ||
				particleWorld->getParticle(row, col - 1).materialType == ParticleWorld::MaterialType::Gas) &&
			particleWorld->getParticle(row, col).material == self.material)
		{
			particleWorld->setParticle(row, col - 1, self);
			particleWorld->resetParticle(row, col);
		}
	}

	if (particleWorld->canRight(col))
	{
		// ignite flammable (right)
		if (
			particleWorld->getParticle(row, col + 1).flammable == true &&
			particleWorld->getParticle(row, col).material == self.material)
		{
			particleWorld->setParticle(row, col + 1, self);
			SoundEngine::playSound(SoundEngine::SoundType::Fire, col, particleWorld->getColSize());
		}

		// apply gravity (right)
		if (
			(particleWorld->getParticle(row, col + 1).material == ParticleWorld::Material::Air ||
				particleWorld->getParticle(row, col + 1).materialType == ParticleWorld::MaterialType::Gas) &&
			particleWorld->getParticle(row, col).material == self.material)
		{
			particleWorld->setParticle(row, col + 1, self);
			particleWorld->resetParticle(row, col);
		}
	}
}