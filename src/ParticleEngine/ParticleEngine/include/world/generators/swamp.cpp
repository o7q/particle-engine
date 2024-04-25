#include <iostream>

#include "world/world_generator.h"
#include "particle/particle_world.h"
#include "tools/num2d.h"

void generateSwamp(ParticleWorld* particleWorld)
{
	std::random_device rd;
	std::mt19937 gen(rd());

	int rowSize = particleWorld->getRowSize();
	int colSize = particleWorld->getColSize();

	// LAYER 3
	Double2D* layer3_kernel = generate2DKernel(15, 15, 0.01);
	Int2D* layer3_convolutedWorld = generateNoiseBase(rowSize, colSize, layer3_kernel, 0, 255);

	int layer3_groundHeightKernelSize = 40;
	double* layer3_groundHeightsKernel = generate1DKernel(layer3_groundHeightKernelSize, 0.05);

	int* layer3_convolutedGroundHeights = generateGroundLayer(rowSize, colSize, 200, rowSize, -220, layer3_groundHeightsKernel, layer3_groundHeightKernelSize);

	for (int col = 0; col < colSize; ++col)
	{
		for (int row = 0; row < layer3_convolutedGroundHeights[col]; ++row)
		{
			layer3_convolutedWorld->set(row, col, 0);
		}
	}
	//

	// LAYER 2
	Double2D* layer2_kernel = generate2DKernel(20, 20, 0.01);
	Int2D* layer2_convolutedWorld = generateNoiseBase(rowSize, colSize, layer2_kernel, 0, 240);

	int layer2_groundHeightKernelSize = 40;
	double* layer2_groundHeightsKernel = generate1DKernel(layer2_groundHeightKernelSize, 0.05);

	int* layer2_convolutedGroundHeights = generateGroundLayer(rowSize, colSize, 200, rowSize, -300, layer2_groundHeightsKernel, layer2_groundHeightKernelSize);

	for (int col = 0; col < colSize; ++col)
	{
		for (int row = 0; row < layer2_convolutedGroundHeights[col]; ++row)
		{
			layer2_convolutedWorld->set(row, col, 0);
		}
	}
	//

	// LAYER 1
	Double2D* layer1_kernel = generate2DKernel(20, 20, 0.01);
	Int2D* layer1_convolutedWorld = generateNoiseBase(rowSize, colSize, layer1_kernel, 0, 200);

	int layer1_groundHeightKernelSize = 40;
	double* layer1_groundHeightsKernel = generate1DKernel(layer1_groundHeightKernelSize, 0.05);

	int* layer1_convolutedGroundHeights = generateGroundLayer(rowSize, colSize, 200, rowSize, -320, layer1_groundHeightsKernel, layer1_groundHeightKernelSize);

	for (int col = 0; col < colSize; ++col)
	{
		for (int row = 0; row < layer1_convolutedGroundHeights[col]; ++row)
		{
			if (row < 170)
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

	Int2D* convolutedWorld = new Int2D(rowSize, colSize);

	for (int row = 0; row < rowSize; ++row)
	{
		for (int col = 0; col < colSize; ++col)
		{
			int layer1_int = layer1_convolutedWorld->get(row, col);
			convolutedWorld->set(row, col, layer1_int);
		}
	}

	for (int row = 0; row < rowSize; ++row)
	{
		for (int col = 0; col < colSize; ++col)
		{
			int layer2_int = layer2_convolutedWorld->get(row, col);
			if (layer2_int != 0)
			{
				convolutedWorld->set(row, col, layer2_int);
			}
		}
	}

	for (int row = 0; row < rowSize; ++row)
	{
		for (int col = 0; col < colSize; ++col)
		{
			int layer3_int = layer3_convolutedWorld->get(row, col);
			if (layer3_int != 0)
			{
				convolutedWorld->set(row, col, layer3_int);
			}
		}
	}

	//std::uniform_int_distribution<int> asd(9, 100);
	//for (int i = 0; i < 10; i++)
	//{
	//	int test = asd(gen);
	//	particleWorld->imageToParticles(asd, col, sf::Image & image, ParticleWorld::ParticleInstance particleInstance, bool useImageColors);
	//}

	// debug draw
	//for (int row = 0; row < rowSize; ++row)
	//{
	//	for (int col = 0; col < colSize; ++col)
	//	{
	//		int rand = convolutedWorld->get(row, col);
	//		ParticleWorld::ParticleInstance temp = particleWorld->getDefaultInstance();
	//		temp.material = ParticleWorld::Material::Stone;
	//		temp.materialType = ParticleWorld::MaterialType::Solid;
	//		temp.color = sf::Color(rand, rand, rand);
	//		temp.overrideColor = true;
	//		particleWorld->setParticle(row, col, temp);
	//	}
	//}

	int quantizedValueMap[] = { 255, 200, 240, 3, 69, 0 };

	std::uniform_int_distribution<int> colorPatternDist(9, 10);
	for (int row = 0; row < rowSize; ++row)
	{
		for (int col = 0; col < colSize; ++col)
		{
			ParticleWorld::ParticleInstance temp;
			int closestIndex = quantizeValue(convolutedWorld->get(row, col), quantizedValueMap, 7);

			switch (quantizedValueMap[closestIndex])
			{
			case 255:
				temp.material = ParticleWorld::Material::SwampWater;
				temp.materialType = ParticleWorld::MaterialType::Liquid;
				temp.physicsType = ParticleWorld::PhysicsType::Water;
				temp.createsSteam = true;
				break;
			case 200:
				temp.material = ParticleWorld::Material::Grass;
				temp.materialType = ParticleWorld::MaterialType::Solid;
				temp.physicsType = ParticleWorld::PhysicsType::Grass;
				break;
			case 240:
				temp.material = ParticleWorld::Material::DarkDirt;
				temp.materialType = ParticleWorld::MaterialType::Solid;
				temp.physicsType = ParticleWorld::PhysicsType::Dirt;
				break;
			case 3:
				temp.material = ParticleWorld::Material::Dirt;
				temp.materialType = ParticleWorld::MaterialType::Solid;
				temp.physicsType = ParticleWorld::PhysicsType::Dirt;
				break;
			case 69:
				temp.material = ParticleWorld::Material::Stone;
				temp.materialType = ParticleWorld::MaterialType::Solid;
				temp.physicsType = ParticleWorld::PhysicsType::NoGravity;
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

	sf::Image bushImage;
	if (!bushImage.loadFromFile("data\\objects\\foliage\\swamp_tree.png"))
	{
		// error
	}

	ParticleWorld::ParticleInstance temp2;
	temp2.material = ParticleWorld::Material::Grass;
	temp2.materialType = ParticleWorld::MaterialType::Solid;
	temp2.physicsType = ParticleWorld::PhysicsType::NoGravity;
	for (int i = 0; i < colSize; i++)
	{
		std::uniform_int_distribution<int> genChance(0, 10);

		if (genChance(gen) == 0 && particleWorld->getParticle(layer1_convolutedGroundHeights[i] - 1, i).materialType != ParticleWorld::MaterialType::Liquid)
		{
			particleWorld->imageToParticles(layer1_convolutedGroundHeights[i] - bushImage.getSize().y, i, bushImage, temp2, true);
		}
	}

	delete layer1_kernel;
	delete layer1_convolutedWorld;
	delete[] layer1_groundHeightsKernel;
	delete[] layer1_convolutedGroundHeights;

	delete layer2_kernel;
	delete layer2_convolutedWorld;
	delete[] layer2_groundHeightsKernel;
	delete[] layer2_convolutedGroundHeights;

	delete layer3_kernel;
	delete layer3_convolutedWorld;
	delete[] layer3_groundHeightsKernel;
	delete[] layer3_convolutedGroundHeights;

	delete convolutedWorld;
}