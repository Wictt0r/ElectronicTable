#pragma once
#include"Cell.h"
#include"Table.h"
#pragma warning(disable:4996)
class Cell_Formula : public Cell
{
public:
	Cell_Formula(char*);
	float value();
	char* print();
private:
	void calculate(Cell***, size_t, size_t*,size_t,size_t);
	float calculate_first_number(Cell***, size_t, size_t*,size_t&, size_t , size_t );
	float calculate_second_number(Cell***, size_t, size_t*, size_t&, size_t , size_t );
	float value_of_formula;
};

