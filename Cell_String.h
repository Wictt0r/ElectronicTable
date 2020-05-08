#pragma once
#include "Cell.h"
#pragma warning(disable:4996)
class Cell_String :public Cell
{
public:
	Cell_String(char*);
	float value();
	char* print();
private:
	char* remove_quotes();
	void calculate(Cell***, size_t, size_t*, size_t, size_t);

};
