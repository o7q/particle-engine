#include "tools/num2d.hpp"
#include "tools/tools.hpp"

Double2D::Double2D(int rowSize, int colSize)
{
	arr = new double[rowSize * colSize];

	this->rowSize = rowSize;
	this->colSize = colSize;
}

Double2D::~Double2D()
{
	delete[] arr;
}

double Double2D::get(int row, int col)
{
	return *(arr + get1DIndex(row, col, colSize));
}

void Double2D::set(int row, int col, double value)
{
	*(arr + get1DIndex(row, col, colSize)) = value;
}

int Double2D::getRowSize()
{
	return rowSize;
}

int Double2D::getColSize()
{
	return colSize;
}