#pragma once

class Int2D {
private:
	int* arr;
	int rowSize;
	int colSize;

public:
	Int2D(int, int);
	~Int2D();

	int get(int, int);
	void set(int, int, int);
	int getRowSize();
	int getColSize();
};

class Double2D {
private:
	double* arr;
	int rowSize;
	int colSize;

public:
	Double2D(int, int);
	~Double2D();

	double get(int, int);
	void set(int, int, double);
	int getRowSize();
	int getColSize();
};