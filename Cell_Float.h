#pragma once
#include"Cell.h"
#include"cstring"
#pragma warning(disable:4996)
class Cell_Float : public Cell
{
public:
	Cell_Float(char*);
	float value();
private:
	float number_f;

	float str_to_float(char*);
};

