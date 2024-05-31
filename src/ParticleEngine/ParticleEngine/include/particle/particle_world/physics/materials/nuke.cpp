#include <iostream>

#include "particle/particle_world.h"
#include "particle/particle_sounds.h"

#include "tools/tools.h"
#include "tools/random.h"

void ParticleWorld::calculate_nuke(int row, int col, Ruleset ruleset)
{
	// define self, this value is used whenever a pixel moves, it acts as a copy of all the settings for the current pixel
	// selfInital SHOULD NOT CHANGE
	const ParticleWorld::Particle selfInitial = getParticle(row, col);
	ParticleWorld::Particle self = selfInitial;

	bool explode = false;

	if (ruleset.canUp)
	{
		if (
			(getParticle(row - 1, col).material == ParticleWorld::Material::Fire) &&
			getParticle(row, col).material == self.material)
		{
			explode = true;
		}
	}

	if (ruleset.canDown)
	{
		if (
			(getParticle(row + 1, col).material == ParticleWorld::Material::Fire) &&
			getParticle(row, col).material == self.material)
		{
			explode = true;
		}
	}

	if (ruleset.canLeft)
	{
		if (
			(getParticle(row, col - 1).material == ParticleWorld::Material::Fire) &&
			getParticle(row, col).material == self.material)
		{
			explode = true;
		}
	}

	if (ruleset.canRight)
	{
		if (
			(getParticle(row, col + 1).material == ParticleWorld::Material::Fire) &&
			getParticle(row, col).material == self.material)
		{
			explode = true;
		}
	}

	// 50, chance to explode from ignition
	if (explode && Random::genInt(0, 50) == 0)
	{
		ParticleWorld::Particle smokeExplosion;
		smokeExplosion.material = ParticleWorld::Material::Smoke;
		smokeExplosion.materialType = ParticleWorld::MaterialType::Gas;
		smokeExplosion.physicsType = ParticleWorld::PhysicsType::Smoke;

		int randNukeMushroomCloud = Random::genInt(0, nukeMushroomCloudPatterns.size() - 1);
		imageToParticles(row - 100, col, nukeMushroomCloudPatterns[randNukeMushroomCloud], smokeExplosion, false);

		ParticleWorld::Particle nukeExplosion;
		nukeExplosion.material = ParticleWorld::Material::Fire;
		nukeExplosion.materialType = ParticleWorld::MaterialType::Liquid;
		nukeExplosion.physicsType = ParticleWorld::PhysicsType::Fire;

		int randNukeExplosion = Random::genInt(0, nukeExplosionPatterns.size() - 1);
		imageToParticles(row, col, nukeExplosionPatterns[randNukeExplosion], nukeExplosion, false);


		SoundEngine::playSound(SoundEngine::SoundType::NukeExplosion, col, getColSize());
		//setShakeCountdown(50);
	}

	if (ruleset.canDown)
	{
		// apply downwards gravity
		if (
			(getParticle(row + 1, col).materialType == ParticleWorld::MaterialType::Gas ||
				getParticle(row + 1, col).materialType == ParticleWorld::MaterialType::Liquid) &&
			getParticle(row, col).material == self.material)
		{
			setParticle(row + 1, col, self);
			resetParticle(row, col);
		}
	}
}