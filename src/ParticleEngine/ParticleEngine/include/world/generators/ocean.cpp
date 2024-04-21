#include <iostream>
#include <limits>

#include "world/world_generator.h"
#include "particle/particle_world.h"
#include "tools/num2d.h"

void generateOcean(ParticleWorld* particleWorld)
{
	std::random_device rd;
	std::mt19937 gen(rd());

	int rowSize = particleWorld->getRowSize();
	int colSize = particleWorld->getColSize();

	Double2D* kernel = generate2DKernel(15, 15, 0.005);

	Int2D* convolutedWorld = generateNoiseBase(rowSize, colSize, kernel);

	int groundHeightKernelSize = 10;
	double* groundHeightsKernel = generate1DKernel(groundHeightKernelSize, 0.05);

	int* convolutedGroundHeights = generateGroundLayer(rowSize, colSize, 200, rowSize, 100, groundHeightsKernel, groundHeightKernelSize);

	for (int col = 0; col < colSize; col++)
	{
		for (int row = 0; row < convolutedGroundHeights[col]; row++)
		{
			if (row < 120)
			{
				convolutedWorld->set(row, col, 0);
			}
			else
			{
				convolutedWorld->set(row, col, 255);
			}
		}
	}

	int quantizedValueMap[] = { 255, 165, 155, 143, 127, 0 };

	std::uniform_int_distribution<int> colorPatternDist(9, 10);

	ParticleWorld::ParticleInstance temp = particleWorld->getDefaultInstance();
	for (int row = 0; row < rowSize; row++)
	{
		for (int col = 0; col < colSize; col++)
		{
			int closestDistance = std::numeric_limits<int>::max();
			int closestIndex = 0;

			for (int i = 0; i < sizeof(quantizedValueMap) / sizeof(quantizedValueMap[0]); i++)
			{
				double distance = std::sqrt(std::pow(convolutedWorld->get(row, col) - quantizedValueMap[i], 2));

				if (distance < closestDistance)
				{
					closestDistance = distance;
					closestIndex = i;
				}
			}

			switch (quantizedValueMap[closestIndex])
			{
			case 255:
				temp.material = ParticleWorld::Material::Water;
				temp.materialType = ParticleWorld::MaterialType::Liquid;
				break;
			case 143:
				temp.material = ParticleWorld::Material::Sand;
				temp.materialType = ParticleWorld::MaterialType::Solid;
				break;
			case 155:
				temp.material = ParticleWorld::Material::Sandstone;
				temp.materialType = ParticleWorld::MaterialType::Solid;
				break;
			case 127:
				temp.material = ParticleWorld::Material::Dirt;
				temp.materialType = ParticleWorld::MaterialType::Solid;
				break;
			case 0:
				temp.material = ParticleWorld::Material::Air;
				temp.materialType = ParticleWorld::MaterialType::Gas;
				break;
			}
			temp.brightnessMultiplier = colorPatternDist(gen) / 10.f;
			particleWorld->setParticle(row, col, temp);
		}
	}
}