#include <iostream>
#include "particle/particle_world.h"
#include "particle/particle_physics.h"
#include "tools/tools.h"

void calculate_ice(int row, int col, ParticleWorld* particleWorld)
{
	ParticleWorld::ParticleInstance self = particleWorld->getParticle(row, col);

    if (particleWorld->canDown(row))
    {
        if (
            (particleWorld->getParticle(row + 1, col).material == ParticleWorld::Material::Air ||
                particleWorld->getParticle(row + 1, col).materialType == ParticleWorld::MaterialType::Gas) &&
            particleWorld->getParticle(row, col).material == self.material)
        {
            particleWorld->setParticle(row + 1, col, self);
            particleWorld->resetParticle(row, col);
        }
    }

    if (particleWorld->getParticle(row, col).intValue > 1000)
    {
        particleWorld->particles[get1DIndex(row, col, particleWorld->colSize)].material = ParticleWorld::Material::Water;
        particleWorld->particles[get1DIndex(row, col, particleWorld->colSize)].materialType = ParticleWorld::MaterialType::Liquid;
    }
    else
    {
        particleWorld->particles[get1DIndex(row, col, particleWorld->colSize)].intValue++;
        return;
    }

    if (particleWorld->canLeft(row))
    {
        if (
            (particleWorld->getParticle(row, col - 1).material == ParticleWorld::Material::Air ||
                particleWorld->getParticle(row, col - 1).materialType == ParticleWorld::MaterialType::Gas) &&
            particleWorld->getParticle(row, col).material == self.material)
        {
            particleWorld->setParticle(row, col - 1, self);
            particleWorld->resetParticle(row, col);
        }
    }

    if (particleWorld->canRight(row))
    {
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