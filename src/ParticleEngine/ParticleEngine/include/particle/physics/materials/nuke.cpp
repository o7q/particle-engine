#include <iostream>

#include "particle/particle_world.h"
#include "particle/particle_physics.h"
#include "particle/particle_sounds.h"

#include "tools/tools.h"

void calculate_nuke(int row, int col, ParticleWorld* particleWorld)
{
	// define self, this value is used whenever a pixel moves, it acts as a copy of all the settings for the current pixel
	// selfInital SHOULD NOT CHANGE
	const ParticleWorld::ParticleInstance selfInitial = particleWorld->getParticle(row, col);
	ParticleWorld::ParticleInstance self = selfInitial;

	bool explode = false;

	if (particleWorld->canUp(row))
	{
		if (
			(particleWorld->getParticle(row - 1, col).material == ParticleWorld::Material::Fire) &&
			particleWorld->getParticle(row, col).material == self.material)
		{
			explode = true;
		}
	}

	if (particleWorld->canDown(row))
	{
		if (
			(particleWorld->getParticle(row + 1, col).material == ParticleWorld::Material::Fire) &&
			particleWorld->getParticle(row, col).material == self.material)
		{
			explode = true;
		}
	}

	if (particleWorld->canLeft(col))
	{
		if (
			(particleWorld->getParticle(row, col - 1).material == ParticleWorld::Material::Fire) &&
			particleWorld->getParticle(row, col).material == self.material)
		{
			explode = true;
		}
	}

	if (particleWorld->canRight(col))
	{
		if (
			(particleWorld->getParticle(row, col + 1).material == ParticleWorld::Material::Fire) &&
			particleWorld->getParticle(row, col).material == self.material)
		{
			explode = true;
		}
	}

	std::uniform_int_distribution<int> explosionChanceDist(0, 50);
	if (explode && explosionChanceDist(particleWorld->gen) == 0)
	{
		ParticleWorld::ParticleInstance smokeExplosion;
		smokeExplosion.material = ParticleWorld::Material::Smoke;
		smokeExplosion.materialType = ParticleWorld::MaterialType::Gas;
		smokeExplosion.physicsType = ParticleWorld::PhysicsType::Smoke;

		std::uniform_int_distribution<int> nukeMushroomCloudDist(0, 1);
		particleWorld->imageToParticles(row - 100, col, particleWorld->nukeMushroomCloudPatterns[nukeMushroomCloudDist(particleWorld->gen)], smokeExplosion, false);

		ParticleWorld::ParticleInstance nukeExplosion;
		nukeExplosion.material = ParticleWorld::Material::Fire;
		nukeExplosion.materialType = ParticleWorld::MaterialType::Liquid;
		nukeExplosion.physicsType = ParticleWorld::PhysicsType::Fire;

		std::uniform_int_distribution<int> nukeExplosionPatternDist(0, 2);
		particleWorld->imageToParticles(row, col, particleWorld->nukeExplosionPatterns[nukeExplosionPatternDist(particleWorld->gen)], nukeExplosion, false);


		SoundEngine::playSound(SoundEngine::SoundType::NukeExplosion, col, particleWorld->getColSize());
		particleWorld->setShakeCountdown(50);
	}

	if (particleWorld->canDown(row))
	{
		// apply downwards gravity
		if (
			(particleWorld->getParticle(row + 1, col).materialType == ParticleWorld::MaterialType::Gas ||
				particleWorld->getParticle(row + 1, col).materialType == ParticleWorld::MaterialType::Liquid) &&
			particleWorld->getParticle(row, col).material == self.material)
		{
			particleWorld->setParticle(row + 1, col, self);
			particleWorld->resetParticle(row, col);
		}
	}
}