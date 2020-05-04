#include "Cell_Formula.h"

Cell_Formula::Cell_Formula(char* input)
{
	initial_text = new(std::nothrow) char[strlen(input) + 1];
	if(initial_text!=nullptr)
	strcpy(initial_text, input);
	strcpy(type, "formula");
}

float Cell_Formula::value()
{
	return 0.0f;
}
