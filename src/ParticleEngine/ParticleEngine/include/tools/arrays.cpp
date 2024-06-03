#include "tools/tools.hpp"

int get1DIndex(int row, int col, int colSize)
{
	return row * colSize + col;
}