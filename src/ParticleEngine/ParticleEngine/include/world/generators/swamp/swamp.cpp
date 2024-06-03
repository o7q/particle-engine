#include <iostream>

#include "world/world_generator.hpp"

#include "particle/particle_world.hpp"

#include "tools/num2d.hpp"
#include "tools/random.hpp"
#include "tools/logger.hpp"

void generateSwamp(ParticleWorld* particleWorld)
{
	int rowSize = particleWorld->getRowSize();
	int colSize = particleWorld->getColSize();

	// LAYER 3
	Logger::log(Logger::LogType::INFO, __func__, __LINE__, "Generating LAYER 3 noise");
	Double2D* layer3_kernel = generate2DKernel(15, 15, 0.01);
	Int2D* layer3_convolutedWorld = generateNoiseBase(rowSize, colSize, layer3_kernel, 0, 255);

	Logger::log(Logger::LogType::INFO, __func__, __LINE__, "Generating LAYER 3 noise (convolution)");
	int layer3_groundHeightKernelSize = 40;
	double* layer3_groundHeightsKernel = generate1DKernel(layer3_groundHeightKernelSize, 0.05);

	// 1.575f is derived from 315/200 (315 is the height of pixelSize 2, 200 is what the height value should be for pixelSize 2, doing this division guarentees no invalid numbers are generated)
	// -1.40625f is derived from 315/-224 (same applies for this, but instead its for topOffset)
	Logger::log(Logger::LogType::INFO, __func__, __LINE__, "Generating LAYER 3 ground layer");
	int* layer3_convolutedGroundHeights = generateGroundLayer(rowSize, colSize, rowSize / 1.575f, rowSize, rowSize / -1.40625f, layer3_groundHeightsKernel, layer3_groundHeightKernelSize);

	for (int col = 0; col < colSize; ++col)
	{
		for (int row = 0; row < layer3_convolutedGroundHeights[col]; ++row)
		{
			layer3_convolutedWorld->set(row, col, 0);
		}
	}
	//

	// LAYER 2
	Logger::log(Logger::LogType::INFO, __func__, __LINE__, "Generating LAYER 2 noise");
	Double2D* layer2_kernel = generate2DKernel(20, 20, 0.01);
	Int2D* layer2_convolutedWorld = generateNoiseBase(rowSize, colSize, layer2_kernel, 0, 240);

	Logger::log(Logger::LogType::INFO, __func__, __LINE__, "Generating LAYER 2 noise (convolution)");
	int layer2_groundHeightKernelSize = 40;
	double* layer2_groundHeightsKernel = generate1DKernel(layer2_groundHeightKernelSize, 0.05);

	// 1.575f is derived from 315/200 (guarentees swamp level does not generate invalid values, read above comments for context)
	// -1.05f is derived from 315/-300 (guarentees swamp level does not generate invalid values, read above comments for context)
	Logger::log(Logger::LogType::INFO, __func__, __LINE__, "Generating LAYER 2 ground layer");
	int* layer2_convolutedGroundHeights = generateGroundLayer(rowSize, colSize, rowSize / 1.575f, rowSize, rowSize / -1.05, layer2_groundHeightsKernel, layer2_groundHeightKernelSize);

	for (int col = 0; col < colSize; ++col)
	{
		for (int row = 0; row < layer2_convolutedGroundHeights[col]; ++row)
		{
			layer2_convolutedWorld->set(row, col, 0);
		}
	}
	//

	// LAYER 1
	Logger::log(Logger::LogType::INFO, __func__, __LINE__, "Generating LAYER 1 noise");
	Double2D* layer1_kernel = generate2DKernel(20, 20, 0.01);
	Int2D* layer1_convolutedWorld = generateNoiseBase(rowSize, colSize, layer1_kernel, 0, 200);

	Logger::log(Logger::LogType::INFO, __func__, __LINE__, "Generating LAYER 1 noise (convolution)");
	int layer1_groundHeightKernelSize = 40;
	double* layer1_groundHeightsKernel = generate1DKernel(layer1_groundHeightKernelSize, 0.05);

	// 1.575f is derived from 315/200 (guarentees swamp level does not generate invalid values, read above comments for context)
	// -0.984375f is derived from 315/-320 (guarentees swamp level does not generate invalid values, read above comments for context)
	Logger::log(Logger::LogType::INFO, __func__, __LINE__, "Generating LAYER 1 ground layer");
	int* layer1_convolutedGroundHeights = generateGroundLayer(rowSize, colSize, rowSize / 1.575f, rowSize, rowSize / -0.984375f, layer1_groundHeightsKernel, layer1_groundHeightKernelSize);

	for (int col = 0; col < colSize; ++col)
	{
		for (int row = 0; row < layer1_convolutedGroundHeights[col]; ++row)
		{
			// 1.875f is derived from 315/168 (guarentees water level does not generate invalid values, read above comments for context)
			if (row < rowSize / 1.875f)
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

	// cut each ground layer
	Logger::log(Logger::LogType::INFO, __func__, __LINE__, "Cutting LAYER 3 ground layer");
	for (int row = 0; row < rowSize; ++row)
	{
		for (int col = 0; col < colSize; ++col)
		{
			int layer1_int = layer1_convolutedWorld->get(row, col);
			convolutedWorld->set(row, col, layer1_int);
		}
	}

	// cut each ground layer
	Logger::log(Logger::LogType::INFO, __func__, __LINE__, "Cutting LAYER 2 ground layer");
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

	// cut each ground layer
	Logger::log(Logger::LogType::INFO, __func__, __LINE__, "Cutting LAYER 1 ground layer");
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

	// values for quantized map, each value corresponds to a material
	int quantizedValueMap[] = { 255, 200, 240, 3, 69, 0 };

	// random dist for brightness
	std::uniform_int_distribution<int> colorPatternDist(9, 10);

	Logger::log(Logger::LogType::INFO, __func__, __LINE__, "Painting world");
	for (int row = 0; row < rowSize; ++row)
	{
		for (int col = 0; col < colSize; ++col)
		{
			ParticleWorld::Particle temp;
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
			temp.brightnessMultiplier = Random::genDouble(0.9, 1.0);
			particleWorld->setParticle(row, col, temp);
		}
	}

	sf::Image bushImage;
	if (!bushImage.loadFromFile("data\\objects\\foliage\\swamp_tree\\swamp_tree1.png"))
	{
		Logger::log(Logger::LogType::ERROR, __func__, __LINE__, "Unable to load swamp_tree1.png!");
	}

	Logger::log(Logger::LogType::INFO, __func__, __LINE__, "Populating world (foliage)");
	ParticleWorld::Particle grass_instance;
	grass_instance.material = ParticleWorld::Material::Grass;
	grass_instance.materialType = ParticleWorld::MaterialType::Solid;
	grass_instance.physicsType = ParticleWorld::PhysicsType::NoGravity;
	for (int i = 0; i < colSize; i++)
	{
		if (Random::genInt(0, 1) == 0 && particleWorld->getParticle(layer1_convolutedGroundHeights[i] - 1, i).materialType != ParticleWorld::MaterialType::Liquid)
		{
			particleWorld->imageToParticles(layer1_convolutedGroundHeights[i] - bushImage.getSize().y, i, bushImage, grass_instance, true);
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

	Logger::log(Logger::LogType::SUCCESS, __func__, __LINE__, "Swamp generation finished!");
}