#include "world/world_generator.hpp"

#include "tools/num2d.hpp"

double* generate1DKernel(int colSize, double value)
{
	double* kernel = new double[colSize];
	for (int col = 0; col < colSize; ++col)
	{
		kernel[col] = value;
	}

	return kernel;
}

Double2D* generate2DKernel(int rowSize, int colSize, double value)
{
	Double2D* kernel = new Double2D(rowSize, colSize);
	for (int row = 0; row < rowSize; ++row)
	{
		for (int col = 0; col < colSize; ++col)
		{
			kernel->set(row, col, value);
		}
	}

	return kernel;
}