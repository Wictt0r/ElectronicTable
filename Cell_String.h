#pragma once
#include "Cell.h"
class Cell_String :public Cell
{
public:
	float sum();
private:
	char* string;
};