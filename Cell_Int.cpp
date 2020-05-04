#include "Cell_Int.h"

Cell_Int::Cell_Int(char*input)
{
	initial_text = new(std::nothrow) char[strlen(input) + 1];
	if (initial_text != nullptr)
		strcpy(initial_text, input);
	strcpy(type, "int");
	number_i = atoi(input);
}

float Cell_Int::value()
{
	return number_i;
}
