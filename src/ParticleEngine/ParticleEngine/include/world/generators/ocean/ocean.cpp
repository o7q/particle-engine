#include <iostream>

#include "world/world_generator.h"

#include "particle/particle_world.h"

#include "tools/num2d.h"
#include "tools/random.h"

#include "tools/logger.h"

void generateOcean(ParticleWorld* particleWorld)
{
	int rowSize = particleWorld->getRowSize();
	int colSize = particleWorld->getColSize();

	// LAYER 1
	Logger::log(Logger::LogType::INFO, __func__, __LINE__, "Generating LAYER 1 noise");
	Double2D* layer1_kernel = generate2DKernel(15, 15, 0.005);
	Int2D* layer1_convolutedWorld = generateNoiseBase(rowSize, colSize, layer1_kernel, 0, 255);

	Logger::log(Logger::LogType::INFO, __func__, __LINE__, "Generating LAYER 1 noise (convolution)");
	int layer1_groundHeightKernelSize = 10;
	double* layer1_groundHeightsKernel = generate1DKernel(layer1_groundHeightKernelSize, 0.05);

	// 1.575f is derived from 315/200 (315 is the height of pixelSize 2, 200 is what the height value should be for pixelSize 2, doing this division guarentees no invalid numbers are generated)
	// 3.15f is derived from 315/100 (same applies for this, but instead its for topOffset)
	Logger::log(Logger::LogType::INFO, __func__, __LINE__, "Generating LAYER 1 ground layer");
	int* layer1_convolutedGroundHeights = generateGroundLayer(rowSize, colSize, rowSize / 1.575f, rowSize, rowSize / 3.15f, layer1_groundHeightsKernel, layer1_groundHeightKernelSize);

	for (int col = 0; col < colSize; ++col)
	{
		for (int row = 0; row < layer1_convolutedGroundHeights[col]; ++row)
		{
			// 2.625f is derived from 315/120 (guarentees ocean level does not generate invalid values, read above comments for context)
			if (row < rowSize / 2.625f)
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

	// values for quantized map, each value corresponds to a material
	int quantizedValueMap[] = { 255, 165, 155, 143, 127, 0 };

	std::vector<sf::Image> ocean_objects = ocean_getObjects();

	Logger::log(Logger::LogType::INFO, __func__, __LINE__, "Painting world");
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
			temp.brightnessMultiplier = Random::genDouble(0.9, 1.0);
			particleWorld->setParticle(row, col, temp);
		}
	}

	// place random seaweed
	Logger::log(Logger::LogType::INFO, __func__, __LINE__, "Populating world (foliage)");
	ParticleWorld::ParticleInstance seaweedMaterial;
	seaweedMaterial.material = ParticleWorld::Material::Grass;
	seaweedMaterial.materialType = ParticleWorld::MaterialType::Solid;
	seaweedMaterial.physicsType = ParticleWorld::PhysicsType::SimpleGravity;
	for (int i = 0; i < colSize; i++)
	{
		std::uniform_int_distribution<int> genChance(0, 1);

		if (Random::genInt(0, 1) == 0 && particleWorld->getParticle(layer1_convolutedGroundHeights[i] - 1, i).materialType != ParticleWorld::MaterialType::Gas)
		{
			sf::Image randimage(ocean_objects[Random::genInt(0, ocean_objects.size() - 1)]);
			particleWorld->imageToParticles(layer1_convolutedGroundHeights[i] - randimage.getSize().y, i, randimage, seaweedMaterial, true);
		}
	}

	delete layer1_kernel;
	delete layer1_convolutedWorld;
	delete[] layer1_groundHeightsKernel;
	delete[] layer1_convolutedGroundHeights;

	Logger::log(Logger::LogType::SUCCESS, __func__, __LINE__, "Ocean generation finished!");
}