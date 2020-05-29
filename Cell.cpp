#include "Cell.h"
#include"Cell_Float.h"
#include"Cell_Int.h"
#include"Cell_String.h"
#include"Cell_Formula.h"
#pragma warning(disable:4996)

Cell::~Cell()
{
	del();
}

void Cell::del()
{
	delete[] initial_text;
}
void Cell::calculate(Cell***, size_t, size_t*, size_t, size_t)
{
	return;
}
void Cell::set_type(const char* _type)
{
	strcpy(type, _type);
}
void Cell::set_initial_text(const char* _initial_text)
{
	initial_text = new(std::nothrow) char[strlen(_initial_text) + 1];
	if (initial_text == nullptr)
		return;
	strcpy(initial_text, _initial_text);
}
float Cell::str_to_float(char* number)
{
	float number_temp = 0;
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

bool Cell::detect_cell(char* _cell, size_t& _height, size_t& _width)
{
	if (_cell[0] != 'R' && _cell[0] != 'r')
		return false;
	bool flag = false;
	size_t symbol_counter = strlen(_cell) - 1, counter = 0, number_temp = 0;
	while (symbol_counter > 0)
	{
		if (_cell[symbol_counter] == 'C' || _cell[symbol_counter] == 'c')
		{

			_width = number_temp - 1;
			counter = 0;
			number_temp = 0;
			flag = true;
			symbol_counter--;
			continue;
		}
		if (_cell[symbol_counter] < '0' || _cell[symbol_counter] > '9')
		{
			_width = 0;
			flag = false;
			break;
		}
		number_temp += (_cell[symbol_counter] - '0') * pow(10, counter);
		symbol_counter--;
		counter++;
	}
	if (flag == true)
		_height = number_temp - 1;
	return flag;
}

char* Cell::float_to_str(float number)
{
	static char word[32];
	_gcvt(number, 30, word);
	if (word[strlen(word)-1] == '.')word[strlen(word)-1] = '\0';
	return word;
}
