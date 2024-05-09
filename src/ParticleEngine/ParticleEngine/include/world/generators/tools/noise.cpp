#include <iostream>

#include "world/world_generator.h"

#include "tools/num2d.h"
#include "tools/random.h"

Int2D* generateNoiseBase(int rowSize, int colSize, Double2D* kernel, int minBrightness, int maxBrightness)
{
	Int2D* noisyWorld = new Int2D(rowSize, colSize);
	Int2D* convolutedWorld = new Int2D(rowSize, colSize);

	for (int row = 0; row < rowSize; ++row)
	{
		for (int col = 0; col < colSize; ++col)
		{
			// random height value (0 - 255 because it will be used as a color)
			noisyWorld->set(row, col, Random::genInt(0, 255));
		}
	}

	for (int row = 0; row < rowSize; ++row)
	{
		for (int col = 0; col < colSize; ++col)
		{
			int kernel_rowSize = kernel->getRowSize();
			int kernel_colSize = kernel->getColSize();

			double worldSmoothConvolution = 0;
			for (int kernel_row = 0; kernel_row < kernel_rowSize; ++kernel_row)
			{
				for (int kernel_col = 0; kernel_col < kernel_colSize; ++kernel_col)
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

			int pixelValue = std::clamp(static_cast<int>(worldSmoothConvolution) % 255, minBrightness, maxBrightness);
			convolutedWorld->set(row, col, pixelValue);
		}
	}

	delete noisyWorld;

	return convolutedWorld;
}

int* generateGroundLayer(int rowSize, int colSize, int noisyCutStartMin, int noisyCutEndMax, int topOffset, double* kernel, int kernelSize)
{
	int* groundHeights = new int[colSize];
	int* convolutedGroundHeights = new int[colSize];

	for (int col = 0; col < colSize; ++col)
	{
		// create range for ground heights
		groundHeights[col] = Random::genInt(noisyCutStartMin, noisyCutEndMax);
	}

	for (int col = 0; col < colSize; ++col)
	{
		double groundLayerConvolution = 0;

		for (int kernel_col = 0; kernel_col < kernelSize; ++kernel_col)
		{
			int colIndex = std::min(col + kernel_col, colSize - 1);

			groundLayerConvolution += groundHeights[colIndex] * kernel[kernel_col];
		}

		convolutedGroundHeights[col] = std::min(static_cast<int>(groundLayerConvolution) + topOffset, rowSize);
	}

	delete[] groundHeights;

	return convolutedGroundHeights;
}