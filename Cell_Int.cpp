#include "Cell_Int.h"

Cell_Int::Cell_Int(char*input)
{
	initial_text = new(std::nothrow) char[strlen(input) + 1];
	if (initial_text != nullptr)
		strcpy(initial_text, input);
	strcpy(type, "int");
}

float Cell_Int::value()
{
	return atoi(initial_text);
}

char* Cell_Int::print()
{
	return initial_text;
}

void Cell_Int::calculate(Cell***, size_t, size_t*,size_t,size_t)
{
	return;
}
