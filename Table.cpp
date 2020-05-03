#pragma warning(disable:4996)
#include "Table.h"

Table::Table():width(0),height(0),matrix(nullptr){}

Table::~Table()
{
	for (size_t i = 0; i < height; ++i)
		delete[] matrix[i];
	delete[] matrix;
	delete[] file_name;
}

void Table::split_input(char*input, size_t lenght)
{

	size_t counter = 1;
	for (size_t i = 0; i < lenght; ++i)
	{
		if (input[i] == ' ')
		{
			counter++;
			while (input[i] == ' ')
				i++;
		}
	}
	char** split_input = new (std::nothrow) char* [counter];
	if (split_input == nullptr)
	{
		std::cout << "Error with memory allocation" << std::endl;
		return;
	}
	size_t split_input_counter = 0;
	char* token = strtok(input, " ");
	split_input[split_input_counter] = new(std::nothrow) char[strlen(token) + 1];
	if (split_input[split_input_counter] == nullptr)
	{
		std::cout << "Error\n";
	}
	strcpy(split_input[split_input_counter], token);
	++split_input_counter;
	while (token != nullptr)
	{
		token = strtok(nullptr, " ");
		if (token != nullptr)
		{
			split_input[split_input_counter] = new(std::nothrow) char[strlen(token) + 1];
			if (split_input[split_input_counter] == nullptr)
			{
				std::cout << "Error";
				delete[] token;
				for (size_t i = 0; i <= split_input_counter; ++i)
					delete[] split_input[i];
				delete split_input;
				return;
			}
			strcpy(split_input[split_input_counter], token);
			++split_input_counter;
		}
	}
	detect_function(split_input, counter);
	delete[] token;
	for (size_t i = 0; i < split_input_counter; ++i)
		delete[] split_input[i];
	delete[] split_input;
	return;
}

void Table::detect_function(char** split_input, size_t lenght)
{
	if (strcmp(split_input[0],"open")==0)
	{
		if (open(split_input[1]) == true)
		{
			std::cout << "Table added successfully\n";
			return;
		}
		else
		{
			std::cout << "Error table did not load\n";
		}
	}
	if (strcmp(split_input[0], "close") == 0)
	{
		//????
	}
	if (strcmp(split_input[0], "print") == 0)
	{
		print();
	}
	if (strcmp(split_input[0], "edit") == 0)
	{

	}
	if (strcmp(split_input[0], "save") == 0 && strcmp(split_input[1],"as")==0 && lenght==3)
	{

	}
	if (strcmp(split_input[0], "save") == 0 && lenght==1)
	{

	}
	if (strcmp(split_input[0], "help") == 0)
	{

	}
	if (strcmp(split_input[0], "exit") != 0 || lenght > 1)
		std::cout << "Invalid input\n";
}

bool Table::open(char* _file)
{
	file_name = new(std::nothrow)char[strlen(_file) + 1];
	if (file_name == nullptr)
		return false;
	strcpy(file_name, _file);
	std::ifstream file;
	file.open(_file);
	size_t height = 0,width_counter=0;
	width = 0;
	file.seekg(0);
	while (file.good())
	{ 
		char character;
		file.get(character);
		if (character == ',')
			width_counter++;
		if (width < width_counter && character == '\n')
		{
			width = width_counter;
			width_counter;
		}
		if (character == '\n')
			height++;
	}
	matrix = new(std::nothrow)  Cell*[height];
	if (matrix == nullptr)
	{
		file.close();
		return false;
	}
	for (size_t i = 0; i < height; ++i)
	{
		matrix[i] = new(std::nothrow) Cell[width];
		if (matrix[i] == nullptr)
		{
			for (size_t p = 0; p < i; ++p)
				delete[] matrix[p];
			delete[] matrix;
			file.close();
			return false;
		}
	}
	size_t current_width = 0, current_height = 0;
	file.seekg(0);
	while (file.good())
	{
		
	}
}

void Table::save()
{
	save_as(file_name);
	return;
}

void Table::save_as(char* _file)
{
	std::ofstream file;
	file.open(_file,std::ios::trunc);
	for (size_t i = 0; i < height && file.good(); ++i)
	{
		for (size_t j = 0; j < width &&file.good(); ++j)
		{
			file << matrix[i][j];
		}
		file << '\n';
	}
	file.close();
}

void Table::print()
{
	size_t max_lenght = 0;
	/*for (size_t i = 0; i <width ; ++i)
	{
		for (size_t j = 0; j < height; ++j)
		{

		}
	}*/
	for (size_t i = 0; i < height; ++i)
	{
		
		for (size_t j = 0; j < width; ++j)
		{
			//std::cout << std::setw(max_lenght)<<matrix[i][j];
			if (i != height - 1)
				std::cout << "|";
		}
		std::cout << std::endl;
	}
}
