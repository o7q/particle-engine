#include "particle/particle_world.h"
#include "particle/particle_physics.h"
#include "particle/particle_renderer.h"

#include "tools/tools.h"
#include "tools/random.h"

void updateParticleWorld(ParticleWorld* particleWorld, ParticleRenderer* particleRenderer)
{
	int xPadding = 20;
	int yPadding = 200;

	sf::Vector2i particleRendererPosition = particleRenderer->getUIOffset();
	sf::Vector2u particleRendererSize = particleRenderer->getSize();
	float zoomLevel = particleRenderer->getZoom();

	for (int row = particleRendererSize.y / zoomLevel + yPadding; row >= -1 - yPadding; --row)
	{
		int updateDirection = Random::genInt(0, 1);

		switch (updateDirection)
		{
		case 0:
			for (int col = particleRendererSize.x / zoomLevel + xPadding; col >= -1 - xPadding; --col)
			{
				sf::Vector2i worldCoord(particleRenderer->staticWorldToWorldCoordinates(sf::Vector2i(col, row)));
				updateParticle(particleWorld, worldCoord.y, worldCoord.x);
			}
			break;
		case 1:
			for (int col = 0 - xPadding; col < particleRendererSize.x / zoomLevel + xPadding; ++col)
			{
				sf::Vector2i worldCoord(particleRenderer->staticWorldToWorldCoordinates(sf::Vector2i(col, row)));
				updateParticle(particleWorld, worldCoord.y, worldCoord.x);
			}
			break;
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
	case ParticleWorld::PhysicsType::Explosive:
		calculate_explosive(row, col, particleWorld);
		break;
	case ParticleWorld::PhysicsType::Nuke:
		calculate_nuke(row, col, particleWorld);
		break;
	}
}