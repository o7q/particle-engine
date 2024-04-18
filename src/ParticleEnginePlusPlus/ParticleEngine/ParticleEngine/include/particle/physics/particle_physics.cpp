#include "particle/particle_world.h"
#include "particle/particle_physics.h"
#include "tools/tools.h"

void updateParticles(ParticleWorld* particleWorld)
{
	for (int row = particleWorld->rowSize - 1; row >= 0; row--)
	{
		for (int col = particleWorld->colSize - 1; col >= 0; col--)
		{
			if (particleWorld->getParticle(row, col).verticalParticleUpdated)
			{
				particleWorld->particles[get1DIndex(row, col, particleWorld->colSize)].verticalParticleUpdated = false;
			}

			switch (particleWorld->getParticle(row, col).material)
			{
			case ParticleWorld::Material::Sand:
				calculate_sand(row, col, particleWorld);
				break;
			case ParticleWorld::Material::Water:
				calculate_liquid(row, col, particleWorld);
				break;
			case ParticleWorld::Material::Ice:
				calculate_ice(row, col, particleWorld);
				break;
			case ParticleWorld::Material::Smoke:
				calculate_smoke(row, col, particleWorld);
				break;
			case ParticleWorld::Material::Dirt:
				calculate_dirt(row, col, particleWorld);
				break;
			case ParticleWorld::Material::Grass:
				calculate_grass(row, col, particleWorld);
				break;
			case ParticleWorld::Material::Fire:
				calculate_fire(row, col, particleWorld);
				break;
			case ParticleWorld::Material::Gasoline:
				calculate_liquid(row, col, particleWorld);
				break;
			case ParticleWorld::Material::FlammableGas:
				calculate_smoke(row, col, particleWorld);
				break;
			case ParticleWorld::Material::ToxicGas:
				calculate_smoke(row, col, particleWorld);
				break;
			}
		}
	}
}