#pragma once
#include<iostream>
#include<fstream>

class Cell
{
public:
	Cell() :type("empty"), initial_text(nullptr){};
	Cell(char*);
	Cell(const Cell&);
	~Cell();
	//bool Initialize(char*);
	Cell* operator=(const Cell&);
	
	char* get_initial_text() { return initial_text; }
	char* get_type() { return type; }
	void copy(const Cell&);
	void del();
	virtual float value()=0;

protected:
	char type[7];
	char* initial_text;
};
//std::ostream& operator << (std::ostream&,Cell*);
//std::istream& operator >> (std::istream&, Cell*);