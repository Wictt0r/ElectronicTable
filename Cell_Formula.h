#pragma once
#include"Cell.h"
#pragma warning(disable:4996)
class Cell_Formula : public Cell
{
public:
	Cell_Formula(char*);
	float value();
private:
};

