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
	virtual float value() = 0;
	virtual char* print() = 0;
	virtual void calculate(Cell***,size_t,size_t*,size_t,size_t) = 0;
	static float str_to_float(char*);
	static bool detect_cell(char*, size_t&, size_t&);
	static char* float_to_str(float);

protected:
	char type[7];
	char* initial_text;
};
//std::ostream& operator << (std::ostream&,Cell*);
//std::istream& operator >> (std::istream&, Cell*);