#include <iostream>

#include "world/world_generator.h"
#include "particle/particle_world.h"
#include "tools/num2d.h"

void generateOcean(ParticleWorld* particleWorld)
{
	std::random_device rd;
	std::mt19937 gen(rd());

	int rowSize = particleWorld->getRowSize();
	int colSize = particleWorld->getColSize();

	// LAYER 1
	Double2D* layer1_kernel = generate2DKernel(15, 15, 0.005);
	Int2D* layer1_convolutedWorld = generateNoiseBase(rowSize, colSize, layer1_kernel, 0, 255);

	int layer1_groundHeightKernelSize = 10;
	double* layer1_groundHeightsKernel = generate1DKernel(layer1_groundHeightKernelSize, 0.05);

	int* layer1_convolutedGroundHeights = generateGroundLayer(rowSize, colSize, 200, rowSize, 100, layer1_groundHeightsKernel, layer1_groundHeightKernelSize);

	for (int col = 0; col < colSize; ++col)
	{
		for (int row = 0; row < layer1_convolutedGroundHeights[col]; ++row)
		{
			if (row < 120)
			{
				layer1_convolutedWorld->set(row, col, 0);
			}
			else
			{
				layer1_convolutedWorld->set(row, col, 255);
			}
		}
	}
	//

	int quantizedValueMap[] = { 255, 165, 155, 143, 127, 0 };

	std::vector<sf::Image> ocean_objects = ocean_getObjects();

	std::uniform_int_distribution<int> colorPatternDist(9, 10);

	for (int row = 0; row < rowSize; ++row)
	{
		for (int col = 0; col < colSize; ++col)
		{
			ParticleWorld::ParticleInstance temp;
			int closestIndex = quantizeValue(layer1_convolutedWorld->get(row, col), quantizedValueMap, 6);

			switch (quantizedValueMap[closestIndex])
			{
			case 255:
				temp.material = ParticleWorld::Material::Water;
				temp.materialType = ParticleWorld::MaterialType::Liquid;
				temp.physicsType = ParticleWorld::PhysicsType::Water;
				temp.createsSteam = true;
				break;
			case 143:
				temp.material = ParticleWorld::Material::Sand;
				temp.materialType = ParticleWorld::MaterialType::Solid;
				temp.physicsType = ParticleWorld::PhysicsType::Sand;
				break;
			case 155:
				temp.material = ParticleWorld::Material::Sandstone;
				temp.materialType = ParticleWorld::MaterialType::Solid;
				temp.physicsType = ParticleWorld::PhysicsType::NoGravity;
				break;
			case 127:
				temp.material = ParticleWorld::Material::Dirt;
				temp.materialType = ParticleWorld::MaterialType::Solid;
				temp.physicsType = ParticleWorld::PhysicsType::Dirt;
				break;
			case 0:
				temp.material = ParticleWorld::Material::Air;
				temp.materialType = ParticleWorld::MaterialType::Gas;
				temp.physicsType = ParticleWorld::PhysicsType::NoGravity;
				break;
			}
			temp.brightnessMultiplier = colorPatternDist(gen) / 10.f;
			particleWorld->setParticle(row, col, temp);
		}
	}

	ParticleWorld::ParticleInstance temp2;
	temp2.material = ParticleWorld::Material::Grass;
	temp2.materialType = ParticleWorld::MaterialType::Solid;
	temp2.physicsType = ParticleWorld::PhysicsType::NoGravity;
	for (int i = 0; i < colSize; i++)
	{
		std::uniform_int_distribution<int> genChance(0, 1);

		if (genChance(gen) == 0 && particleWorld->getParticle(layer1_convolutedGroundHeights[i] - 1, i).materialType != ParticleWorld::MaterialType::Gas)
		{
			std::uniform_int_distribution<int> randweed(0, ocean_objects.size() - 1);
			sf::Image randimage(ocean_objects[randweed(gen)]);
			particleWorld->imageToParticles(layer1_convolutedGroundHeights[i] - randimage.getSize().y, i, randimage, temp2, true);
		}
	}

	delete layer1_kernel;
	delete layer1_convolutedWorld;
	delete[] layer1_groundHeightsKernel;
	delete[] layer1_convolutedGroundHeights;
}