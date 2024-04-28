#include "particle/particle_world.h"

bool ParticleWorld::canLeft(int col)
{
	return col > 0;
}

bool ParticleWorld::canRight(int col)
{
	return col < colSize - 1;
}

bool ParticleWorld::canUp(int row)
{
	return row > 0;
}

bool ParticleWorld::canDown(int row)
{
	return row < rowSize - 1;
}