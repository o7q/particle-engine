#pragma once

#include "tools/num2d.h"
#include "tools/tools.h"

#include <iostream>
#include <algorithm>

Int2D::Int2D(int rowSize, int colSize)
{
	arr = new int[rowSize * colSize];

	this->rowSize = rowSize;
	this->colSize = colSize;
}

Int2D::~Int2D()
{
	delete[] arr;
}

int Int2D::get(int row, int col)
{
	return *(arr + get1DIndex(row, col, colSize));
}

void Int2D::set(int row, int col, int value)
{
	*(arr + get1DIndex(row, col, colSize)) = value;
}

int Int2D::getRowSize()
{
	return rowSize;
}

int Int2D::getColSize()
{
	return colSize;
}