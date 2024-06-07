#include "tools/num2d.hpp"
#include "tools/tools.hpp"

Float2D::Float2D(int rowSize, int colSize)
{
	arr = new float[rowSize * colSize];

	this->rowSize = rowSize;
	this->colSize = colSize;
}

Float2D::~Float2D()
{
	delete[] arr;
}

float Float2D::get(int row, int col)
{
	return *(arr + get1DIndex(row, col, colSize));
}

void Float2D::set(int row, int col, float value)
{
	*(arr + get1DIndex(row, col, colSize)) = value;
}

int Float2D::getRowSize() const
{
	return rowSize;
}

int Float2D::getColSize() const
{
	return colSize;
}