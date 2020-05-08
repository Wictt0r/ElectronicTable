#pragma once
#include"Cell.h"
#include"cstring"
#pragma warning(disable:4996)
class Cell_Float : public Cell
{
public:
	Cell_Float(char*);
	float value();
	char* print();
	
private:
	void calculate(Cell***, size_t, size_t*, size_t, size_t);
};

