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
		return Cell::str_to_float(remove_quotes());
	}
	if (dot_counter == 0)
	{
		return atoi(remove_quotes());
	}
}

char* Cell_String::print()
{
	return remove_quotes();
}

void Cell_String::calculate(Cell***, size_t, size_t*,size_t,size_t)
{
	return;
}

char* Cell_String::remove_quotes()
{
	size_t word_lenght = strlen(initial_text) - 1;
	for (size_t i = 1; i < strlen(initial_text) - 1; ++i)
	{
		if (initial_text[i] == '\\')
		{
			word_lenght--;
		}
	}
	char* new_word = new(std::nothrow)char[word_lenght];
	if (new_word == nullptr)
		return initial_text;
	size_t symbol_counter = 0;
	for (size_t i = 1; i < strlen(initial_text) - 1; ++i)
	{
		if (initial_text[i] == '\\')
		{
			continue;
		}
		new_word[symbol_counter] = initial_text[i];
		symbol_counter++;
	}
	new_word[symbol_counter] = '\0';

	return new_word;
}
