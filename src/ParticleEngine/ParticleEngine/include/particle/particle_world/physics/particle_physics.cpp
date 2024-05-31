#include "particle/particle_world.h"
#include "particle/particle_renderer.h"

#include "tools/tools.h"
#include "tools/random.h"

void ParticleWorld::update(/*ParticleWorld* particleWorld, ParticleRenderer* particleRenderer*/)
{
	for (int row = rowSize - 1; row >= 0; --row)
	{
		int updateDirection = Random::genInt(0, 1);

		switch (updateDirection)
		{
		case 0:
			for (int col = colSize - 1; col >= 0; --col)
			{
				updateParticleRuleset(row, col);
			}
			break;
		case 1:
			for (int col = 0; col < colSize; ++col)
			{
				updateParticleRuleset(row, col);
			}
			break;
		}
	}

	//int xPadding = 20;
	//int yPadding = 200;

	//sf::Vector2i particleRendererPosition = particleRenderer->getUIOffset();
	//sf::Vector2u particleRendererSize = particleRenderer->getSize();
	//float zoomLevel = particleRenderer->getZoom();

	//for (int row = particleRendererSize.y / zoomLevel + yPadding; row >= -1 - yPadding; --row)
	//{
	//	int updateDirection = Random::genInt(0, 1);

	//	switch (updateDirection)
	//	{
	//	case 0:
	//		for (int col = particleRendererSize.x / zoomLevel + xPadding; col >= -1 - xPadding; --col)
	//		{
	//			updateParticle(particleWorld, particleRenderer, row, col);
	//		}
	//		break;
	//	case 1:
	//		for (int col = 0 - xPadding; col < particleRendererSize.x / zoomLevel + xPadding; ++col)
	//		{
	//			updateParticle(particleWorld, particleRenderer, row, col);
	//		}
	//		break;
	//	}
	//}
}

void ParticleWorld::updateParticleRuleset(int row, int col)
{
	Ruleset ruleset;

	ruleset.canUp = row > 0;
	ruleset.canDown = row < rowSize - 1;
	ruleset.canLeft = col > 0;
	ruleset.canRight = col < colSize - 1;

	updateParticle(row, col, ruleset);
}

void ParticleWorld::updateParticle(int row, int col, Ruleset ruleset)
{
	switch (getParticle(row, col).physicsType)
	{
	case ParticleWorld::PhysicsType::Sand:
		calculate_sand(row, col, ruleset);
		break;
	case ParticleWorld::PhysicsType::Acid:
		calculate_acid(row, col, ruleset);
		break;
	case ParticleWorld::PhysicsType::AcidSmoke:
		calculate_acidSmoke(row, col, ruleset);
		break;
	case ParticleWorld::PhysicsType::Water:
		calculate_liquid(row, col, ruleset);
		break;
	case ParticleWorld::PhysicsType::Smoke:
		calculate_smoke(row, col, ruleset);
		break;
	case ParticleWorld::PhysicsType::Ice:
		calculate_ice(row, col, ruleset);
		break;
	case ParticleWorld::PhysicsType::SimpleGravity:
		calculate_simpleGravity(row, col, ruleset);
		break;
	case ParticleWorld::PhysicsType::Dirt:
		calculate_dirt(row, col, ruleset);
		break;
	case ParticleWorld::PhysicsType::Grass:
		calculate_grass(row, col, ruleset);
		break;
	case ParticleWorld::PhysicsType::Fire:
		calculate_fire(row, col, ruleset);
		break;
	case ParticleWorld::PhysicsType::Explosive:
		calculate_explosive(row, col, ruleset);
		break;
	case ParticleWorld::PhysicsType::Nuke:
		calculate_nuke(row, col, ruleset);
		break;
	}
}