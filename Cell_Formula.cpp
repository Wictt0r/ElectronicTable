#include "Cell_Formula.h"
#include<cmath>

Cell_Formula::Cell_Formula(char* input)
{
	initial_text = new(std::nothrow) char[strlen(input) + 1];
	if(initial_text!=nullptr)
	strcpy(initial_text, input);
	strcpy(type, "formula");
	value_of_formula = 0;
	is_correct = true;
}

Cell_Formula::Cell_Formula(const Cell_Formula& other)
{
	set_type(other.type);
	set_initial_text(other.initial_text);
	value_of_formula = other.value_of_formula;
	is_correct = other.is_correct;
}

float Cell_Formula::value()
{
	return value_of_formula;
}

char* Cell_Formula::print()
{
	if (is_correct == true)
	{
		return float_to_str(value_of_formula);
	}
	else 
	{
		static char error[] = "Error";
		return error;
	}

}

Cell* Cell_Formula::copy()
{
	return new(std::nothrow) Cell_Formula(*this);
}

void Cell_Formula::calculate(Cell*** matrix,size_t height,size_t* width,size_t current_height,size_t current_width)
{
	float number1 = 0, number2 = 0;
	char operation;
	size_t next_symbol=1;
	number1 = calculate_first_number(matrix, height, width, next_symbol,current_height,current_width);
	operation = initial_text[next_symbol];
	number2= calculate_second_number(matrix, height, width, next_symbol, current_height, current_width);
	
	if (operation == '+')
	{
		value_of_formula = number1 + number2;
		return;
	}
	if (operation == '-')
	{
		value_of_formula = number1 - number2;
		return;
	}
	if (operation == '*')
	{
		value_of_formula = number1 * number2;
		return;
	}
	if (operation == '/')
	{
		if (number2 != 0)
		{
			value_of_formula = number1 / number2;
			return;
		}
		else is_correct = false;
	}
	if (operation == '^')
	{
		value_of_formula = pow(number1, number2);
	}
	return;
}

float Cell_Formula::calculate_first_number(Cell*** matrix, size_t height, size_t* width,size_t &next_symbol, size_t current_height, size_t current_width)
{
	float number = 0;
	size_t edit_height = 0, edit_width = 0, i = 1,symbol_counter = 0,dot_counter=0;
	bool is_formula = false;
	char word[32];
	while (initial_text[i] != '+' && initial_text[i] != '-' && initial_text[i] != '*' && initial_text[i] != '/' && initial_text[i] != '^')
	{
		if (initial_text[i] == ' ')
		{
			++i;
			continue;
		}
		if (initial_text[i] == '.')
			++dot_counter;
		if ((initial_text[i] < '0' || initial_text[i]>'9')&& initial_text[i]!='.')
			is_formula = true;
		word[symbol_counter] = initial_text[i];
		++symbol_counter;
		++i;
	}
	word[symbol_counter] = '\0';
	if (dot_counter > 1)
	{
		next_symbol = i;
		return 0;
	}
	if (is_formula == true)
	{
		if (detect_cell(word, edit_height, edit_width) == true )
		{ 
			if (edit_height > height || edit_width > width[edit_height] || (current_height == edit_height && current_width == edit_width))
			{
				next_symbol = i;
				return 0;
			}
			if (matrix[edit_height][edit_width] == nullptr)
			{
				next_symbol = i;
				return 0;
			}
				number = matrix[edit_height][edit_width]->value();
		}
	}
	else
		number = str_to_float(word);
	next_symbol = i;
	return number;
}

float Cell_Formula::calculate_second_number(Cell*** matrix, size_t height, size_t* width, size_t& next_symbol, size_t current_height, size_t current_width)
{
	float number = 0;
	size_t  edit_height = 0, edit_width = 0 ,i = next_symbol + 1,symbol_counter=0,dot_counter=0;
	bool is_formula = false;
	char word[32];
	while (initial_text[i] != '\0')
	{
		if (initial_text[i] == ' ')
		{
			++i;
			continue;
		}
		if (initial_text[i] == '.')
			++dot_counter;
		if ((initial_text[i] < '0' || initial_text[i]>'9') && initial_text[i] != '.')
			is_formula = true;
		word[symbol_counter] = initial_text[i];
		++symbol_counter;
		++i;
	}
	word[symbol_counter] = '\0';
	if (dot_counter > 1)
		return 0;
	if (is_formula == true)
	{
		if (detect_cell(word, edit_height, edit_width) == true)
		{
			if (edit_height > height || edit_width > width[edit_height] || (current_height == edit_height && current_width == edit_width))
				return 0;
			if (matrix[edit_height][edit_width] == nullptr)
				return 0;
			number = matrix[edit_height][edit_width]->value();
		}
	}
	else
		number = str_to_float(word);
	return number;
}
