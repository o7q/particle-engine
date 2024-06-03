#include <iostream>

#include "particle/particle_world.hpp"
#include "particle/particle_sounds.hpp"

#include "tools/tools.hpp"
#include "tools/random.hpp"

void ParticleWorld::calculate_explosive(int row, int col, Ruleset ruleset)
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

		paintParticles(row - 10, col, 10, smokeExplosion, ParticleWorld::Shape::Circle);

		ParticleWorld::Particle fireExplosion;
		fireExplosion.material = ParticleWorld::Material::Fire;
		fireExplosion.materialType = ParticleWorld::MaterialType::Liquid;
		fireExplosion.physicsType = ParticleWorld::PhysicsType::Fire;

		int randExplosionPattern = Random::genInt(0, explosionPatterns.size() - 1);

		imageToParticles(row, col, explosionPatterns[randExplosionPattern], fireExplosion, false);


		SoundEngine::playSound(SoundEngine::SoundType::DynamiteExplosion, col, getColSize());
		//setShakeCountdown(10);
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