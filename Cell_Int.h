#pragma once
#include "Cell.h"
#pragma warning(disable:4996)
class Cell_Int : public Cell
{
public:
	Cell_Int(const Cell_Int&);
	Cell_Int(char*);
	Cell_Int();
	float value();
	char* print();
	Cell* copy();
private:
	void calculate(Cell***, size_t, size_t*, size_t, size_t);

};

