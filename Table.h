#pragma once
#include<iostream>
#include<iomanip>
#include<fstream>
#include<cstring>
#include "Cell.h"


class Table
{
public:
	Table();
	~Table();
	void split_input(char*, size_t);
	void del();

private:
	char* file_name;
	size_t height;
	size_t* width;
	Cell*** matrix;
	
	void detect_function(char**,size_t);
	char skip_widespace(std::ifstream&,char);
	bool set_Parameters(char*);
	void set_height(char*);
	bool set_width(char*);
	bool create_matrix();
	char* read_word(std::ifstream&, char&);
	bool open(char*);
	void close();
	void save();
	void save_as(char*);
	void print();
	size_t find_max_width();
	size_t* find_setw();
	bool is_default();
};

