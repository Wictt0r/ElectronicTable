#include "Cell_String.h"

Cell_String::Cell_String(char* input)
{
	initial_text = new(std::nothrow) char[strlen(input) + 1];
	if (initial_text != nullptr)
		strcpy(initial_text, input);
	strcpy(type, "string");
}

float Cell_String::value()
{
	
	return 0.0f;
}
