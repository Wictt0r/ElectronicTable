#include "Cell_Float.h"


Cell_Float::Cell_Float(char* input)
{
	initial_text = new(std::nothrow) char[strlen(input) + 1];
	if (initial_text != nullptr)
		strcpy(initial_text, input);
	strcpy(type, "float");
	number_f = str_to_float(input);
}

float Cell_Float::value()
{
	return number_f;
}

float Cell_Float::str_to_float(char* number)
{
	float number_temp=0;
	int counter_fraction = 0, counter = 0;
	bool is_negative = false;
	int count_to = 0;
	if (number[0] == '-')
	{
		is_negative = true;
		count_to = 1;
	}
	if (number[0] == '+')
	{
		count_to = 1;
	}
	for (int i = strlen(number) - 1; i >= count_to; --i)
	{
		if (number[i] == '.')
		{
			counter_fraction = counter;
		}
		else
		{
			number_temp += (number[i] - '0') * pow(10, counter);
			counter++;
		}
	}
	number_temp *= pow(0.1, counter_fraction);
	if (is_negative == true)
		number_temp *= -1;
	return number_temp;
}
