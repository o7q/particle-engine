#include <iostream>

#include "particle/particle_world.h"
#include "world/world_generator.h"

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