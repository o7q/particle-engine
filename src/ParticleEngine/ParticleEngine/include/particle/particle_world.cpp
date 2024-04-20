#include <iostream>
#include <random>

#include "particle/particle_world.h"
#include "tools/tools.h"

unsigned int rowSize;
unsigned int colSize;
ParticleWorld::ParticleInstance* particles;

// configure Mersenne Twister pseudo-random number generator
std::random_device rd;
std::mt19937 gen(rd());
//

ParticleWorld::ParticleWorld(int rowSize, int colSize)
{
	this->rowSize = rowSize;
	this->colSize = colSize;
	particles = new ParticleInstance[rowSize * colSize];

	for (int row = 0; row < rowSize; row++)
	{
		for (int col = 0; col < colSize; col++)
		{
			resetParticle(row, col);
		}
	}
}

ParticleWorld::~ParticleWorld() {
	delete[] particles;
}

void ParticleWorld::setParticle(int row, int col, ParticleWorld::ParticleInstance particleInstance) {
	*(particles + get1DIndex(row, col, colSize)) = particleInstance;
}

ParticleWorld::ParticleInstance ParticleWorld::getParticle(int row, int col) {
	return *(particles + get1DIndex(row, col, colSize));
}

void ParticleWorld::resetParticle(int row, int col) {
	ParticleWorld::ParticleInstance temp;
	temp.material = ParticleWorld::Material::Air;
	temp.materialType = ParticleWorld::MaterialType::Gas;
	temp.wetnessMultiplier = 1.0f;
	temp.brightnessMultiplier = 1.0f;
	temp.intValue = 0;
	temp.physicsFreezeTime = 0;
	setParticle(row, col, temp);
}

void ParticleWorld::paintParticles(int row, int col, int size, ParticleWorld::ParticleInstance particleInstance)
{
	std::uniform_int_distribution<int> dist(9, 10);

	for (int rowIndex = 0; rowIndex < size; rowIndex++)
	{
		for (int colIndex = 0; colIndex < size; colIndex++)
		{
			if (!(row < rowSize && col < colSize && row > 0 && col > 0))
			{
				continue;
			}

			int r = rowIndex - size / 2;
			int c = colIndex - size / 2;

			int r2 = std::max(row + r, 0);
			r2 = std::min(r2, rowSize - 1);
			int c2 = std::max(col + c, 0);
			c2 = std::min(c2, colSize - 1);

			particleInstance.brightnessMultiplier = dist(gen) / 10.f;
			particleInstance.wetnessMultiplier = 1.0f;
			particleInstance.intValue = 0;

			setParticle(r2, c2, particleInstance);
		}
	}
}

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