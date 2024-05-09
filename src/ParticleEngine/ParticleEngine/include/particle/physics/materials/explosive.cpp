#include <iostream>

#include "particle/particle_world.h"
#include "particle/particle_physics.h"
#include "particle/particle_sounds.h"

#include "tools/tools.h"
#include "tools/random.h"

void calculate_explosive(int row, int col, ParticleWorld* particleWorld)
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

	// 50, chance to explode from ignition
	if (explode && Random::genInt(0, 50) == 0)
	{
		ParticleWorld::ParticleInstance smokeExplosion;
		smokeExplosion.material = ParticleWorld::Material::Smoke;
		smokeExplosion.materialType = ParticleWorld::MaterialType::Gas;
		smokeExplosion.physicsType = ParticleWorld::PhysicsType::Smoke;

		particleWorld->paintParticles(row - 10, col, 10, smokeExplosion, ParticleWorld::Shape::Circle);

		ParticleWorld::ParticleInstance fireExplosion;
		fireExplosion.material = ParticleWorld::Material::Fire;
		fireExplosion.materialType = ParticleWorld::MaterialType::Liquid;
		fireExplosion.physicsType = ParticleWorld::PhysicsType::Fire;

		int randExplosionPattern = Random::genInt(0, particleWorld->explosionPatterns.size() - 1);

		particleWorld->imageToParticles(row, col, particleWorld->explosionPatterns[randExplosionPattern], fireExplosion, false);


		SoundEngine::playSound(SoundEngine::SoundType::DynamiteExplosion, col, particleWorld->getColSize());
		particleWorld->setShakeCountdown(10);
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