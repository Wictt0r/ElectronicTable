#pragma once
#include"Cell.h"
class Cell_Formula : public Cell
{
public:
	float sum();
private:
	char* formula;
};

