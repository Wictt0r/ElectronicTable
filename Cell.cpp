#include "Cell.h"

std::ostream& operator<<(std::ostream& out , Cell* cell)
{
	// TODO: insert return statement here
	std::cout << "test\n";
	return out;
}

std::istream& operator>>(std::istream& in, Cell* cell)
{
	// TODO: insert return statement here
	return in;
}

void Cell::Initialize(char* input)
{
}
