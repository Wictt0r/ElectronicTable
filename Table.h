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
	Table(const Table&);
	~Table();
	Table* operator=(const Table&);
	void split_input(char*, size_t);
	

//private:
	char* file_name;
	size_t height;
	size_t* width;
	Cell*** matrix;
	
	void detect_function(char**,size_t);
	char skip_widespace(std::ifstream&,char);
	bool set_Parameters(char*);
	bool set_height(char*);
	bool set_width(char*);
	bool create_matrix(size_t,size_t*);
	char* read_word(std::ifstream&, char&);
	bool open(char*);
	void close();
	void copy(const Table&);
	void save();
	void save_as(char*);
	void print();
	size_t find_max_width();
	size_t* find_setw();
	bool is_default();
	bool resize_line(size_t, size_t);
	bool edit_create_new_word(char**, size_t, char*&);
	void edit_initialize_new_word(char**, size_t, char*&);
	bool edit(char**,size_t);
	
	void del();
	void calculate_formulas();
};

