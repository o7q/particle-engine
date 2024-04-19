#include "particle/particle_world.h"
#include "particle/particle_physics.h"
#include "tools/tools.h"

void updateParticleWorld(ParticleWorld* particleWorld)
{
	std::uniform_int_distribution<int> dist(0, 1);

	for (int row = particleWorld->rowSize - 1; row >= 0; row--)
	{
		int updateDirection = dist(particleWorld->gen);

		if (updateDirection == 0)
		{
			for (int col = particleWorld->colSize - 1; col >= 0; col--)
			{
				updateParticle(particleWorld, row, col);
			}
		}
		else
		{
			for (int col = 0; col < particleWorld->colSize; col++)
			{
				updateParticle(particleWorld, row, col);
			}
		}
	}
}

void updateParticle(ParticleWorld* particleWorld, int row, int col)
{
	switch (particleWorld->getParticle(row, col).material)
	{
	case ParticleWorld::Material::Sand:
		calculate_sand(row, col, particleWorld);
		break;
	case ParticleWorld::Material::Dirt:
		calculate_dirt(row, col, particleWorld);
		break;
	case ParticleWorld::Material::Grass:
		calculate_grass(row, col, particleWorld);
		break;
	case ParticleWorld::Material::Water:
	case ParticleWorld::Material::Gasoline:
		calculate_liquid(row, col, particleWorld);
		break;
	case ParticleWorld::Material::Fire:
		calculate_fire(row, col, particleWorld);
		break;
	case ParticleWorld::Material::Ice:
		calculate_ice(row, col, particleWorld);
		break;
	case ParticleWorld::Material::Smoke:
	case ParticleWorld::Material::Steam:
	case ParticleWorld::Material::FlammableGas:
	case ParticleWorld::Material::ToxicGas:
		calculate_smoke(row, col, particleWorld);
		break;
	case ParticleWorld::Material::RedFlower:
	case ParticleWorld::Material::PinkFlower:
	case ParticleWorld::Material::YellowFlower:
	case ParticleWorld::Material::BlueFlower:
		calculate_simpleGravity(row, col, particleWorld);
		break;
	}
}