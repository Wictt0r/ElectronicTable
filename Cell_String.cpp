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
	float number;
	size_t dot_counter = 0;
	for (size_t i = 1; i < strlen(initial_text)-1; ++i)
	{
		if ((initial_text[i] < '0' || initial_text[i]>'9') && initial_text[i] != '.')
			return 0;
		if (initial_text[i] == '.')
			dot_counter++;
	}
	if (dot_counter > 1)
		return 0;
	if (dot_counter == 1)
	{

	}
	if (dot_counter == 0)
	{

	}
	return 0.0f;
}
