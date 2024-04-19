#include <iostream>
#include "particle/particle_world.h"
#include "particle/particle_physics.h"
#include "tools/tools.h"

void calculate_ice(int row, int col, ParticleWorld* particleWorld)
{
	ParticleWorld::ParticleInstance self = particleWorld->getParticle(row, col);

    std::uniform_int_distribution<int> dist(0, 3);
    int meltValue = dist(particleWorld->gen);

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

    if (particleWorld->canLeft(col))
    {
        if (particleWorld->getParticle(row, col - 1).material == ParticleWorld::Material::Air)
        {
            particleWorld->particles[get1DIndex(row, col, particleWorld->colSize)].intValue += 3;
        }

        if (particleWorld->getParticle(row, col - 1).material == ParticleWorld::Material::Water)
        {
            particleWorld->particles[get1DIndex(row, col, particleWorld->colSize)].intValue += 2;
        }

        if (particleWorld->getParticle(row, col - 1).material == ParticleWorld::Material::Fire)
        {
            particleWorld->particles[get1DIndex(row, col, particleWorld->colSize)].intValue += 5000;
        }
    }

    if (particleWorld->canRight(col))
    {
        if (particleWorld->getParticle(row, col + 1).material == ParticleWorld::Material::Air)
        {
            particleWorld->particles[get1DIndex(row, col, particleWorld->colSize)].intValue += 3;
        }

        if (particleWorld->getParticle(row, col + 1).material == ParticleWorld::Material::Water)
        {
            particleWorld->particles[get1DIndex(row, col, particleWorld->colSize)].intValue += 2;
        }

        if (particleWorld->getParticle(row, col + 1).material == ParticleWorld::Material::Fire)
        {
            particleWorld->particles[get1DIndex(row, col, particleWorld->colSize)].intValue += 5000;
        }
    }

    if (particleWorld->canUp(row))
    {
        if (particleWorld->getParticle(row - 1, col).material == ParticleWorld::Material::Fire)
        {
            particleWorld->particles[get1DIndex(row, col, particleWorld->colSize)].intValue += 2500;
        }
    }

    if (particleWorld->getParticle(row, col).intValue >= 5000)
    {
        particleWorld->particles[get1DIndex(row, col, particleWorld->colSize)].material = ParticleWorld::Material::Water;
        particleWorld->particles[get1DIndex(row, col, particleWorld->colSize)].materialType = ParticleWorld::MaterialType::Liquid;
    }
    else
    {
        particleWorld->particles[get1DIndex(row, col, particleWorld->colSize)].intValue += meltValue;
    }
}