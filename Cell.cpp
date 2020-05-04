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
}
void Cell::del()
{
	delete[] initial_text;
}
//cout<<
//cin>>
