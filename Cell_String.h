#pragma once
#include "Cell.h"
#pragma warning(disable:4996)
class Cell_String :public Cell
{
public:
	Cell_String(const Cell_String&);
	Cell_String(char*);
	Cell_String();
	float value();
	char* print();
	Cell* copy();
private:
	char* remove_quotes();

};
