#include <iostream>

#include "particle/particle_world.hpp"

#include "world/world_generator.hpp"

void generateWorld(ParticleWorld* particleWorld, WorldType worldType)
{
	switch (worldType)
	{
	case WorldType::Ocean:
		generateOcean(particleWorld);
		break;
	case WorldType::Swamp:
		generateSwamp(particleWorld);
		break;
	}
}