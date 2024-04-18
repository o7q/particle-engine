#include "particle/particle_world.h"
#include "particle/particle_physics.h"

void step(ParticleWorld* particleWorld)
{
	for (int row = particleWorld->rowSize - 1; row >= 0; row--)
	{
		for (int col = particleWorld->colSize - 1; col >= 0; col--)
		{
			if (particleWorld->getParticle(row, col).verticalParticleUpdated)
			{
				ParticleWorld::ParticleInstance self = particleWorld->getParticle(row, col);
				self.verticalParticleUpdated = false;
				particleWorld->setParticle(row, col, self);
			}

			switch (particleWorld->getParticle(row, col).material)
			{
			case ParticleWorld::Material::Sand:
				calculateSand(row, col, particleWorld);
				break;
			case ParticleWorld::Material::Water:
				calculateWater(row, col, particleWorld);
				break;
			case ParticleWorld::Material::Smoke:
				calculateSmoke(row, col, particleWorld);
				break;
			}
		}
	}
}