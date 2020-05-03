#include "Cell.h"
#include"Cell_Float.h"
#include"Cell_Int.h"
#include"Cell_String.h"
#include"Cell_Formula.h"
#pragma warning(disable:4996)

//std::ostream& operator<<(std::ostream& out , Cell* cell)
//{
//	// TODO: insert return statement here
//	//out << cell->content;
//	return out;
//}

//std::istream& operator>>(std::istream& in, Cell* cell)
//{
//	in >> cell->get_content();
//	return in;
//}

bool Cell::Initialize(char* input)
{
	if (input[0] == '+' || input[0] == '-' || (input[0]>=0 && input[0]<=9))
	{
	
		size_t dot_counter = 0,i=0;
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
					return false;
				}
			}
		}
		if (dot_counter == 0)
		{
			strcpy(type, "int");
			cell_type = new Cell_Int;
			return true;
		}
		if (dot_counter == 1)
		{
			strcpy(type, "float");
			cell_type = new Cell_Float;
			return true;
		}
	}
	if (input[0] == '"' && input[strlen(input)] == '"')
	{
		strcpy(type, "string");
		cell_type = new Cell_String;
		return true;
	}
	if (input[0] == '=')
	{
		strcpy(type, "formula");
		cell_type = new Cell_Formula;
		return true;
		// is formula correct
	}
}
//cout<<
//cin>>
