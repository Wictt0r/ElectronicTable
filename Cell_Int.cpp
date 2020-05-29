#include "Cell_Int.h"

Cell_Int::Cell_Int(const Cell_Int& other)
{
	set_type(other.type);
	set_initial_text(other.initial_text);
}

Cell_Int::Cell_Int(char*input)
{
	initial_text = new(std::nothrow) char[strlen(input) + 1];
	if (initial_text != nullptr)
		strcpy(initial_text, input);
	strcpy(type, "int");
}

Cell_Int::Cell_Int():Cell()
{
}

float Cell_Int::value()
{
	return str_to_float(initial_text);
}

char* Cell_Int::print()
{
	return initial_text;
}

Cell* Cell_Int::copy()
{
	return new (std::nothrow) Cell_Int(*this);
}

