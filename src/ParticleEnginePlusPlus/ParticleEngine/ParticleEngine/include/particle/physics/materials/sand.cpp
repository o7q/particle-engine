#include <iostream>
#include "particle/particle_world.h"
#include "particle/particle_physics.h"

void calculateSand(int row, int col, ParticleWorld* particleWorld)
{
	ParticleWorld::ParticleInstance self = particleWorld->getParticle(row, col);

	if (particleWorld->canUp(row))
	{
		if (particleWorld->getParticle(row - 1, col).materialType == ParticleWorld::MaterialType::Liquid &&
			particleWorld->getParticle(row, col).wetnessMultiplier <= 2.0f)
		{
			self.wetnessMultiplier += 0.1f;
			particleWorld->setParticle(row, col, self);
		}
	}

	if (particleWorld->canLeft(col))
	{
		if (particleWorld->getParticle(row, col - 1).materialType == ParticleWorld::MaterialType::Liquid &&
			particleWorld->getParticle(row, col).wetnessMultiplier <= 1.5f)
		{
			self.wetnessMultiplier += 0.05f;
			particleWorld->setParticle(row, col, self);
		}
	}

	if (particleWorld->canRight(col))
	{
		if (particleWorld->getParticle(row, col + 1).materialType == ParticleWorld::MaterialType::Liquid &&
			particleWorld->getParticle(row, col).wetnessMultiplier <= 1.5f)
		{
			self.wetnessMultiplier += 0.05f;
			particleWorld->setParticle(row, col, self);
		}
	}

	if (particleWorld->canDown(row))
	{
		if (
			(particleWorld->getParticle(row + 1, col).materialType == ParticleWorld::MaterialType::Gas ||
				(particleWorld->getParticle(row + 1, col).material == ParticleWorld::Material::Water) &&
				particleWorld->getParticle(row, col).material == self.material))
		{
			particleWorld->setParticle(row + 1, col, self);
			particleWorld->resetParticle(row, col);
		}
	}

	if (particleWorld->canLeft(col) && particleWorld->canDown(row))
	{
		if (
			(particleWorld->getParticle(row + 1, col - 1).materialType == ParticleWorld::MaterialType::Liquid ||
				particleWorld->getParticle(row + 1, col - 1).materialType == ParticleWorld::MaterialType::Gas) &&
			particleWorld->getParticle(row, col - 1).material == ParticleWorld::Material::Air &&
			particleWorld->getParticle(row, col).material == self.material)
		{
			particleWorld->setParticle(row + 1, col - 1, self);
			particleWorld->resetParticle(row, col);
		}
	}

	if (particleWorld->canRight(col) && particleWorld->canDown(row))
	{
		if (
			(particleWorld->getParticle(row + 1, col + 1).materialType == ParticleWorld::MaterialType::Liquid ||
				particleWorld->getParticle(row + 1, col + 1).materialType == ParticleWorld::MaterialType::Gas) &&
			particleWorld->getParticle(row, col + 1).material == ParticleWorld::Material::Air &&
			particleWorld->getParticle(row, col).material == self.material)
		{
			particleWorld->setParticle(row + 1, col + 1, self);
			particleWorld->resetParticle(row, col);
		}
	}
}