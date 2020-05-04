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
				delete []split_input;
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

void Table::del()
{
	delete[] file_name;
	for (size_t i = 0; i < height; ++i)
		delete[] matrix[i];
	delete[] matrix;
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
			return;
		}
	}
	if (strcmp(split_input[0], "close") == 0)
	{
		//????
	}
	if (strcmp(split_input[0], "print") == 0)
	{
		print();
		return;
	}
	if (strcmp(split_input[0], "edit") == 0)
	{

	}
	if (strcmp(split_input[0], "save") == 0 && strcmp(split_input[1],"as")==0 && lenght==3)
	{
		save_as(split_input[2]);
		return;
	}
	if (strcmp(split_input[0], "save") == 0 && lenght==1)
	{
		save();
		return;
	}
	if (strcmp(split_input[0], "help") == 0)
	{

	}
	if (strcmp(split_input[0], "exit") != 0 || lenght > 1)
		std::cout << "Invalid input\n";
}

char Table::skip_widespace(std::ifstream& file,char symbol)
{
	while (symbol == ' ' || symbol == '\t')
	{
		file.get(symbol);
	}
	return symbol;
}
bool Table::set_Parameters(char* _file)
{
	file_name = new(std::nothrow)char[strlen(_file) + 1];
	if (file_name == nullptr)
		return false;
	strcpy(file_name, _file);
	std::ifstream file;
	file.open(_file);
	size_t width_counter = 1;
	height = 0;
	width = 1;
	while (file.good())
	{
		char character;
		file.get(character);
		if (character == ',' && file.eof()==false)
			width_counter++;
		if (character == '\n' || file.eof() == true)
		{
			height++;
			if (width < width_counter)
				width = width_counter;
			width_counter = 1;
		}
	}
	matrix = new(std::nothrow)  Cell * [height];
	if (matrix == nullptr)
	{
		file.close();
		del();
		return false;
	}
	for (size_t i = 0; i < height; ++i)
	{
		matrix[i] = new(std::nothrow) Cell[width];
		if (matrix[i] == nullptr)
		{
			del();
			file.close();
			return false;
		}
	}
	std::cout << "width:" << width << " height:" << height << std::endl;
	file.close();
	return true;
}

char* Table::read_word(std::ifstream& file, char &symbol)
{
	char word[128],character;
	file.get(character);
	character = skip_widespace(file, character);
	size_t symbol_counter = 0;
	while (character != ',' && character != '\n' && file.good())
	{
		if ((character == ' ' || character == '\t') && ((file.peek() == ' ' || file.peek() == '\t') || file.peek() == ','))
		{
			break;
		}
		word[symbol_counter] = character;
		symbol_counter++;
		file.get(character);
	}
	word[symbol_counter] = '\0';
	symbol = character;
	return word;
}

bool Table::open(char* _file)
{
	if (set_Parameters(_file) == false)
		return false;
	size_t current_width = 0, current_height = 0;
	std::ifstream file;
	file.open(_file);
	
	while (file.good())
	{
		char symbol, word[128];
		strcpy(word, read_word(file, symbol));
		if (strlen(word) == 0 )
		{
			current_width = 0;
			current_height++;
			continue;
		}
		if (matrix[current_height][current_width].Initialize(word) == false)
		{
			std::cout << "Column:" << current_width +1<< " Line:" << current_height+1; 
			del();
			return false;
		}
		std::cout << "current_height:" << current_height << " current_width:" << current_width<<" ";
		std::cout <<"word:" <<word << " " << std::endl;
		symbol = skip_widespace(file, symbol);
		if (symbol == ',')
		{
			current_width++;
		}
		symbol = skip_widespace(file, symbol);
		if (symbol == '\n')
		{
			current_height++;
			current_width = 0;
		}

	}
	file.close();
	return true;
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
			if(matrix[i][j].get_initial_text()!=nullptr)
			file << matrix[i][j].get_initial_text();
			if (j != width - 1)
				file << ',';
		}
		file << '\n';
	}
	file.close();
}

void Table::print()
{
	//size_t max_lenght = 0;
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
			if (matrix[i][j].get_initial_text() != nullptr)
				std::cout << std::setw(10) << matrix[i][j].get_initial_text();
			else
				std::cout << " ";
			if (i != width - 1)
				std::cout << "|";
		}
		std::cout << std::endl;
	}
	return;
}
