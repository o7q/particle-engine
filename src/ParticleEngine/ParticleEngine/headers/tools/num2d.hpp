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
	int getRowSize() const;
	int getColSize() const;
};

class Float2D {
private:
	float* arr;
	int rowSize;
	int colSize;

public:
	Float2D(int, int);
	~Float2D();

	float get(int, int);
	void set(int, int, float);
	int getRowSize() const;
	int getColSize() const;
};