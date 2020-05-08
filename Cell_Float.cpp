#include "Cell_Float.h"


Cell_Float::Cell_Float(char* input)
{
	initial_text = new(std::nothrow) char[strlen(input) + 1];
	if (initial_text != nullptr)
		strcpy(initial_text, input);
	strcpy(type, "float");
}

float Cell_Float::value()
{
	return str_to_float(initial_text);
}

char* Cell_Float::print()
{
	return initial_text;
}

void Cell_Float::calculate(Cell***, size_t, size_t*,size_t,size_t)
{
	return;
}

