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

Cell::Cell(const Cell& other)
{
	copy(other);
}

Cell::~Cell()
{
	del();
}

bool Cell::Initialize(char* input)
{
	if (input[0] == '+' || input[0] == '-' || (input[0]>='0' && input[0]<='9'))
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
			initial_text=new (std::nothrow) char[strlen(input)+1];
			strcpy(initial_text, input);
			return true;
		}
		if (dot_counter == 1)
		{
			strcpy(type, "float");
			cell_type = new Cell_Float;
			initial_text = new (std::nothrow) char[strlen(input) + 1];
			strcpy(initial_text, input);
			return true;
		}
		if (dot_counter>1)
		{
			std::cout << "Unknown type:" << input;
			return false;
		}
	}
	else if (input[0] == '\"' && input[strlen(input)-1] == '\"')
	{
		strcpy(type, "string");
		cell_type = new Cell_String;
		initial_text = new (std::nothrow) char[strlen(input) + 1];
		strcpy(initial_text, input);
		return true;
	}
	else if (input[0] == '=')
	{
		strcpy(type, "formula");
		cell_type = new Cell_Formula;
		initial_text = new (std::nothrow) char[strlen(input) + 1];
		strcpy(initial_text, input);
		return true;
		// is formula correct
	}
	else {
		std::cout << "Unknown type:" << input;
		return false;
	}
}
Cell* Cell::operator=(const Cell& other)
{
	if(this!=&other)
	{ 
	del();
	copy(other);
	}
	return this;
}
void Cell::copy(const Cell& other)
{
	strcpy(type, other.type);
	initial_text = new(std::nothrow)char[strlen(other.initial_text) + 1];
	strcpy(initial_text, other.initial_text);
	cell_type = other.cell_type;
}
void Cell::del()
{
	delete[] initial_text;
	delete cell_type;
}
//cout<<
//cin>>
