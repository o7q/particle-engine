#include "particle/particle_world.h"
#include "particle/particle_physics.h"
#include "tools/tools.h"

void updateParticleWorld(ParticleWorld* particleWorld)
{
	std::uniform_int_distribution<int> dist(0, 1);

	for (int row = particleWorld->getRowSize() - 1; row >= 0; --row)
	{
		int updateDirection = dist(particleWorld->gen);

		if (updateDirection == 0)
		{
			for (int col = particleWorld->getColSize() - 1; col >= 0; --col)
			{
				updateParticle(particleWorld, row, col);
			}
		}
		else
		{
			for (int col = 0; col < particleWorld->getColSize(); ++col)
			{
				updateParticle(particleWorld, row, col);
			}
		}
	}
}

void updateParticle(ParticleWorld* particleWorld, int row, int col)
{
	switch (particleWorld->getParticle(row, col).physicsType)
	{
	case ParticleWorld::PhysicsType::Sand:
		calculate_sand(row, col, particleWorld);
		break;
	case ParticleWorld::PhysicsType::Acid:
		calculate_acid(row, col, particleWorld);
		break;
	case ParticleWorld::PhysicsType::AcidSmoke:
		calculate_acidSmoke(row, col, particleWorld);
		break;
	case ParticleWorld::PhysicsType::Water:
		calculate_liquid(row, col, particleWorld);
		break;
	case ParticleWorld::PhysicsType::Smoke:
		calculate_smoke(row, col, particleWorld);
		break;
	case ParticleWorld::PhysicsType::Ice:
		calculate_ice(row, col, particleWorld);
		break;
	case ParticleWorld::PhysicsType::SimpleGravity:
		calculate_simpleGravity(row, col, particleWorld);
		break;
	case ParticleWorld::PhysicsType::Dirt:
		calculate_dirt(row, col, particleWorld);
		break;
	case ParticleWorld::PhysicsType::Grass:
		calculate_grass(row, col, particleWorld);
		break;
	case ParticleWorld::PhysicsType::Fire:
		calculate_fire(row, col, particleWorld);
		break;
	}
}