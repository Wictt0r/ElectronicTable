#pragma once
#include "Cell.h"
#pragma warning(disable:4996)
class Cell_Int : public Cell
{
public:
	Cell_Int(char*);
	float value();
private:
	int number_i;
};

