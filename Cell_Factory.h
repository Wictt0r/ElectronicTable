#pragma once
#include"Cell_Float.h"
#include"Cell_Int.h"
#include"Cell_String.h"
#include"Cell_Formula.h"
#include"Cell.h"
class Cell_Factory
{
public:
	static Cell* Initialize(char* input);
};

