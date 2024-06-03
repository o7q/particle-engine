#include <iostream>

#include "particle/particle_world.hpp"
#include "particle/particle_sounds.hpp"

#include "tools/tools.hpp"
#include "tools/random.hpp"

void ParticleWorld::calculate_fire(int row, int col, Ruleset ruleset)
{
	// define randomBurnout value (0, 2), 2 means higher chance to burnout
	int randomBurnout = Random::genInt(0, 2);

	particles[get1DIndex(row, col, getColSize())].intValue += randomBurnout;
	if (getParticle(row, col).intValue > 200)
	{
		resetParticle(row, col);
	}

	// define self, this value is used whenever a pixel moves, it acts as a copy of all the settings for the current pixel
	// define self after randomBurnout, so the value is replicated through adjacent particles, if applicable
	// selfInital SHOULD NOT CHANGE
	ParticleWorld::Particle selfInitial = getParticle(row, col);
	ParticleWorld::Particle self = selfInitial;

	if (ruleset.canUp)
	{
		// ignite flammable materials (up)
		if (
			getParticle(row - 1, col).flammable == true &&
			getParticle(row, col).material == selfInitial.material)
		{
			setParticle(row - 1, col, self);
			SoundEngine::playSound(SoundEngine::SoundType::Fire, col, getColSize());
		}
	}

	if (ruleset.canDown)
	{
		// ignite flammable down
		if (
			getParticle(row + 1, col).flammable == true &&
			getParticle(row, col).material == selfInitial.material)
		{
			setParticle(row + 1, col, self);
			SoundEngine::playSound(SoundEngine::SoundType::Fire, col, getColSize());
		}

		// apply gravity (down
		if (
			getParticle(row + 1, col).materialType == ParticleWorld::MaterialType::Gas &&
			getParticle(row, col).material == selfInitial.material)
		{
			setParticle(row + 1, col, self);
			resetParticle(row, col);
		}

		// create steam if in contact with water
		if (getParticle(row + 1, col).createsSteam == true)
		{
			ParticleWorld::Particle steam;
			steam.material = ParticleWorld::Material::Steam;
			steam.materialType = ParticleWorld::MaterialType::Gas;
			steam.physicsType = ParticleWorld::PhysicsType::Smoke;
			paintParticles(row - 1, col, 5, steam, ParticleWorld::Shape::Square);

			SoundEngine::playSound(SoundEngine::SoundType::Sizzle, col, getColSize());
		}
	}

	if (ruleset.canLeft)
	{
		// ignite flammable (left)
		if (
			getParticle(row, col - 1).flammable == true &&
			getParticle(row, col).material == selfInitial.material)
		{
			setParticle(row, col - 1, self);

			SoundEngine::playSound(SoundEngine::SoundType::Fire, col, getColSize());
		}

		// apply gravity (left)
		if (
			(getParticle(row, col - 1).material == ParticleWorld::Material::Air ||
				getParticle(row, col - 1).materialType == ParticleWorld::MaterialType::Gas) &&
			getParticle(row, col).material == selfInitial.material)
		{
			setParticle(row, col - 1, self);
			resetParticle(row, col);
		}
	}

	if (ruleset.canRight)
	{
		// ignite flammable (right)
		if (
			getParticle(row, col + 1).flammable == true &&
			getParticle(row, col).material == selfInitial.material)
		{
			setParticle(row, col + 1, self);
			SoundEngine::playSound(SoundEngine::SoundType::Fire, col, getColSize());
		}

		// apply gravity (right)
		if (
			(getParticle(row, col + 1).material == ParticleWorld::Material::Air ||
				getParticle(row, col + 1).materialType == ParticleWorld::MaterialType::Gas) &&
			getParticle(row, col).material == selfInitial.material)
		{
			setParticle(row, col + 1, self);
			resetParticle(row, col);
		}
	}
}