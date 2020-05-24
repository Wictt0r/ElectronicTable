#include "Cell_Float.h"


Cell_Float::Cell_Float(char* input)
{
	initial_text = new(std::nothrow) char[strlen(input) + 1];
	if (initial_text != nullptr)
		strcpy(initial_text, input);
	strcpy(type, "float");
}

Cell_Float::Cell_Float(const Cell_Float& other)
{
	set_type(other.type);
	set_initial_text(other.initial_text);
}

Cell_Float::Cell_Float() :Cell()
{
}

float Cell_Float::value()
{
	return str_to_float(initial_text);
}

char* Cell_Float::print()
{
	return initial_text;
}

Cell* Cell_Float::copy()
{
	return new(std::nothrow) Cell_Float(*this);
}

void Cell_Float::calculate(Cell***, size_t, size_t*,size_t,size_t)
{
	return;
}

