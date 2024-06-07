#include "world/world_generator.hpp"

#include "tools/num2d.hpp"

float* generate1DKernel(int colSize, float value)
{
	float* kernel = new float[colSize];
	for (int col = 0; col < colSize; ++col)
	{
		kernel[col] = value;
	}

	return kernel;
}

Float2D* generate2DKernel(int rowSize, int colSize, float value)
{
	Float2D* kernel = new Float2D(rowSize, colSize);
	for (int row = 0; row < rowSize; ++row)
	{
		for (int col = 0; col < colSize; ++col)
		{
			kernel->set(row, col, value);
		}
	}

	return kernel;
}