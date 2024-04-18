#include <iostream>
#include "particle/particle_world.h"
#include "particle/particle_physics.h"
#include "tools/tools.h"

void calculate_fire(int row, int col, ParticleWorld* particleWorld)
{
	ParticleWorld::ParticleInstance self = particleWorld->getParticle(row, col);

	if (particleWorld->canUp(row))
	{
		if (
			(particleWorld->getParticle(row - 1, col).material == ParticleWorld::Material::FlammableGas ||
				particleWorld->getParticle(row - 1, col).material == ParticleWorld::Material::Gasoline) &&
			particleWorld->getParticle(row, col).material == self.material)
		{
			particleWorld->setParticle(row - 1, col, self);
		}
	}

	if (particleWorld->canDown(row))
	{
		if (
			(particleWorld->getParticle(row + 1, col).material == ParticleWorld::Material::FlammableGas ||
				particleWorld->getParticle(row + 1, col).material == ParticleWorld::Material::Gasoline) &&
			particleWorld->getParticle(row, col).material == self.material)
		{
			particleWorld->setParticle(row + 1, col, self);
		}

		if (
			(particleWorld->getParticle(row + 1, col).material == ParticleWorld::Material::Air ||
				particleWorld->getParticle(row + 1, col).materialType == ParticleWorld::MaterialType::Gas) &&
			particleWorld->getParticle(row, col).material == self.material)
		{
			particleWorld->setParticle(row + 1, col, self);
			particleWorld->resetParticle(row, col);
		}
	}

	if (particleWorld->canLeft(col))
	{
		if (
			(particleWorld->getParticle(row, col - 1).material == ParticleWorld::Material::FlammableGas ||
				particleWorld->getParticle(row, col - 1).material == ParticleWorld::Material::Gasoline) &&
			particleWorld->getParticle(row, col).material == self.material)
		{
			particleWorld->setParticle(row, col - 1, self);
		}

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
		if (
			(particleWorld->getParticle(row, col + 1).material == ParticleWorld::Material::FlammableGas ||
				particleWorld->getParticle(row, col + 1).material == ParticleWorld::Material::Gasoline) &&
			particleWorld->getParticle(row, col).material == self.material)
		{
			particleWorld->setParticle(row, col + 1, self);
		}

		if (
			(particleWorld->getParticle(row, col + 1).material == ParticleWorld::Material::Air ||
				particleWorld->getParticle(row, col + 1).materialType == ParticleWorld::MaterialType::Gas) &&
			particleWorld->getParticle(row, col).material == self.material)
		{
			particleWorld->setParticle(row, col + 1, self);
			particleWorld->resetParticle(row, col);
		}
	}

	particleWorld->particles[get1DIndex(row, col, particleWorld->colSize)].intValue++;
	if (particleWorld->getParticle(row, col).intValue > 10)
	{
		particleWorld->resetParticle(row, col);
	}
}