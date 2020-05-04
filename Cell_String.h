#pragma once
#include "Cell.h"
#pragma warning(disable:4996)
class Cell_String :public Cell
{
public:
	Cell_String(char*);
	float value();
private:
};
