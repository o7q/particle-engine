#include <iostream>

#include "tools/tools.h"

int verify256Range(int value)
{
	return std::min(std::max(value, 0), 255);
}