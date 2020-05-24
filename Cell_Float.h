#pragma once
#include"Cell.h"
#include"cstring"
#pragma warning(disable:4996)
class Cell_Float : public Cell
{
public:
	Cell_Float(char*);
	Cell_Float(const Cell_Float&);
	Cell_Float();
	float value();
	char* print();
	Cell* copy();
	
private:
	void calculate(Cell***, size_t, size_t*, size_t, size_t);
};

