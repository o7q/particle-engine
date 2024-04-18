#include <iostream>
#include "particle/particle_world.h"
#include "particle/particle_physics.h"

void calculate_liquid(int row, int col, ParticleWorld* particleWorld)
{
	ParticleWorld::ParticleInstance self = particleWorld->getParticle(row, col);

	if (particleWorld->canDown(row))
	{
		if (
			(particleWorld->getParticle(row + 1, col).material == ParticleWorld::Material::Air ||
				particleWorld->getParticle(row + 1, col).materialType == ParticleWorld::MaterialType::Gas ||
				particleWorld->getParticle(row + 1, col).material == ParticleWorld::Material::Fire) &&
			particleWorld->getParticle(row, col).material == self.material)
		{
			particleWorld->setParticle(row + 1, col, self);
			particleWorld->resetParticle(row, col);
		}
	}

	if (particleWorld->canLeft(col))
	{
		if (
			(particleWorld->getParticle(row, col - 1).material == ParticleWorld::Material::Air ||
				particleWorld->getParticle(row, col - 1).materialType == ParticleWorld::MaterialType::Gas ||
				particleWorld->getParticle(row, col - 1).material == ParticleWorld::Material::Fire) &&
			particleWorld->getParticle(row, col).material == self.material)
		{
			particleWorld->setParticle(row, col - 1, self);
			particleWorld->resetParticle(row, col);
		}
	}

	if (particleWorld->canRight(col))
	{
		if (
			(particleWorld->getParticle(row, col + 1).material == ParticleWorld::Material::Air ||
				particleWorld->getParticle(row, col + 1).materialType == ParticleWorld::MaterialType::Gas ||
				particleWorld->getParticle(row, col + 1).material == ParticleWorld::Material::Fire) &&
			particleWorld->getParticle(row, col).material == self.material)
		{
			particleWorld->setParticle(row, col + 1, self);
			particleWorld->resetParticle(row, col);
		}
	}
}