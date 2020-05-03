#pragma once
#include<iostream>
#include<fstream>
class Cell
{
public:
	void Initialize(char*);

protected:
	char* type;
};
std::ostream& operator << (std::ostream&,Cell*);
std::istream& operator >> (std::istream&, Cell*);