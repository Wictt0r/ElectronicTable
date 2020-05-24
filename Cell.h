#pragma once
#include<iostream>
#include<fstream>

class Cell
{
public:
	Cell() :type("empty"), initial_text(nullptr){};
	Cell(char*);
	~Cell();
	
	char* get_initial_text() { return initial_text; }
	char* get_type() { return type; }
	virtual Cell* copy()=0;
	void del();
	virtual float value() = 0;
	virtual char* print() = 0;
	virtual void calculate(Cell***,size_t,size_t*,size_t,size_t) = 0;
	void set_type(const char*);
	void set_initial_text(const char*);
	static float str_to_float(char*);
	static bool detect_cell(char*, size_t&, size_t&);
	static char* float_to_str(float);

protected:
	char type[7];
	char* initial_text;
};