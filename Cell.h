#pragma once
#include<iostream>
#include<fstream>
//#include"Cell_Float.h"
//#include"Cell_Int.h"
//#include"Cell_String.h"
//#include"Cell_Formula.h"

class Cell
{
public:
	Cell() :type("empty"), initial_text(nullptr), cell_type(nullptr){};
	Cell(const Cell&);
	~Cell();
	bool Initialize(char*);
	Cell* operator=(const Cell&);
	
	char* get_initial_text() { return initial_text; }
	void copy(const Cell&);
	void del();
	float sum();

protected:
	char type[7];
	char* initial_text;
	Cell* cell_type;
};
//std::ostream& operator << (std::ostream&,Cell*);
//std::istream& operator >> (std::istream&, Cell*);