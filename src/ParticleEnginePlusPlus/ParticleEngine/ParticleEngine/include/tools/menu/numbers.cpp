#include "tools/tools.h"

int get1DIndex(int row, int col, int colSize)
{
	return row * colSize + col;
}