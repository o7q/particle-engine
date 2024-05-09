#pragma once

#include <random>

#ifndef RANDOM_H
#define RANDOM_H

class Random {
public:
	static std::random_device rd;
	static std::mt19937 gen;

	static void init();
	static void reseed();
	static int genInt(int, int);
	static double genDouble(double, double);
};

#endif