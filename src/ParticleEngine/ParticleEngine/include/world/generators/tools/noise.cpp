#include <iostream>

#include "tools/num2d.h"
#include "world/world_generator.h"

Int2D* generateNoiseBase(int rowSize, int colSize, Double2D* kernel)
{
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_int_distribution<int> dist(0, 255);

	Int2D* noisyWorld = new Int2D(rowSize, colSize);
	Int2D* convolutedWorld = new Int2D(rowSize, colSize);

	for (int row = 0; row < rowSize; row++)
	{
		for (int col = 0; col < colSize; col++)
		{
			noisyWorld->set(row, col, dist(gen));
		}
	}

	for (int row = 0; row < rowSize; row++)
	{
		for (int col = 0; col < colSize; col++)
		{
			int kernel_rowSize = kernel->getRowSize();
			int kernel_colSize = kernel->getColSize();

			double worldSmoothConvolution = 0;
			for (int kernel_row = 0; kernel_row < kernel_rowSize; kernel_row++)
			{
				for (int kernel_col = 0; kernel_col < kernel_colSize; kernel_col++)
				{
					int rowIndex = std::min(
						std::max(row + kernel_row - kernel_rowSize / 2, 0),
						rowSize - 1
					);
					int colIndex = std::min(
						std::max(col + kernel_col - kernel_colSize / 2, 0),
						colSize - 1
					);
					worldSmoothConvolution += noisyWorld->get(rowIndex, colIndex) * kernel->get(kernel_row, kernel_col);
				}
			}

			convolutedWorld->set(row, col, (int)worldSmoothConvolution);
		}
	}

	delete noisyWorld;

	return convolutedWorld;
}

int* generateGroundLayer(int rowSize, int colSize, int noisyCutStartMin, int noisyCutEndMax, int topOffset, double* kernel, int kernelSize)
{
	std::random_device rd;
	std::mt19937 gen(rd());

	int* groundHeights = new int[colSize];
	int* convolutedGroundHeights = new int[colSize];

	std::uniform_int_distribution<int> groundHeightRange(noisyCutStartMin, noisyCutEndMax);
	for (int col = 0; col < colSize; col++)
	{
		groundHeights[col] = groundHeightRange(gen);
	}

	for (int col = 0; col < colSize; col++)
	{
		double groundLayerConvolution = 0;

		for (int kernel_col = 0; kernel_col < kernelSize; kernel_col++)
		{
			int colIndex = std::min(col + kernel_col, colSize - 1);

			groundLayerConvolution += groundHeights[colIndex] * kernel[kernel_col];
		}

		convolutedGroundHeights[col] = std::min((int)groundLayerConvolution + topOffset, rowSize);
	}

	delete[] groundHeights;

	return convolutedGroundHeights;
}

double* generate1DKernel(int colSize, double value)
{
	double* kernel = new double[colSize];
	for (int col = 0; col < colSize; col++)
	{
		kernel[col] = value;
	}

	return kernel;
}

Double2D* generate2DKernel(int rowSize, int colSize, double value)
{
	Double2D* kernel = new Double2D(rowSize, colSize);
	for (int row = 0; row < rowSize; row++)
	{
		for (int col = 0; col < colSize; col++)
		{
			kernel->set(row, col, value);
		}
	}

	return kernel;
}