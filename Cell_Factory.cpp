#include "Cell_Factory.h"

Cell* Cell_Factory::Initialize(char* input)
{
	
		Cell* new_cell;
		if (input[0] == '+' || input[0] == '-' || (input[0] >= '0' && input[0] <= '9'))
		{

			size_t dot_counter = 0, i = 0;
			if (input[0] == '+' || input[0] == '-')
				i = 1;
			for (i; i < strlen(input); ++i)
			{
				if (input[i] < '0' || input[i]>'9')
				{
					if (input[i] == '.')dot_counter++;
					else
					{
						std::cout << "Unknown type:" << input;
						return nullptr;
					}
				}
			}
			if (dot_counter == 0)
			{
				new_cell = new Cell_Int(input);
				return new_cell;
			}
			if (dot_counter == 1)
			{
				new_cell = new Cell_Float(input);
				return new_cell;
			}
		}
		else if (input[0] == '\"' && input[strlen(input) - 1] == '\"')
		{
			new_cell = new Cell_String(input);
			return new_cell;
		}
		else if (input[0] == '=')
		{
			new_cell = new Cell_Formula(input);
			return new_cell;
			// is formula correct
		}
		else 
		{
			std::cout << "Unknown type:" << input;
			return nullptr;
		}
	
}
