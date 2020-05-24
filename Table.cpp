#pragma warning(disable:4996)
#include "Table.h"
#include"Cell.h"
#include"Cell_Factory.h"

Table::Table():width(nullptr),height(0),matrix(nullptr),file_name(nullptr){}

Table::Table(const Table& other)
{
	copy(other);
}

Table::~Table()
{
	del();
}

Table* Table::operator=(const Table& other)
{
	if (this == &other)
		return this;
	copy(other);
	return this;
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
	{
		for (size_t j = 0; j < width[i]; ++j)
		{
			
			delete matrix[i][j];
		}
	}
	for (size_t i = 0; i < height; ++i)
		delete[] matrix[i];
	delete[] matrix;
	delete[] width;
}

void Table::calculate_formulas()
{
	for (size_t i = 0; i < height; ++i)
		for (size_t j = 0; j < width[i]; ++j)
		{ 
			if(matrix[i][j]!=nullptr)
			matrix[i][j]->calculate(matrix, height, width,i,j);
		}
	return;
}

void Table::detect_function(char** split_input, size_t lenght)
{
	if (strcmp(split_input[0],"open")==0)
	{
		if (is_default() == false)
		{
			std::cout << "Error\nClose current table first\n";
			return;
		}
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
		if (is_default() == false)
		{
			std::cout << "Closing current table\n";
			close();
		}
		else
			std::cout << "No active table\n";
		
		return;
	}
	if (strcmp(split_input[0], "print") == 0)
	{
		print();
		return;
	}
	if (strcmp(split_input[0], "edit") == 0)
	{
		if (is_default() == true)
		{
			std::cout << "No active table\n";
			return;
		}
		if (edit(split_input,lenght) == true)
		{
			std::cout << "Cell edited successfully\n";
		}
		else
			std::cout << "Cell not edited\n";
		return;
	}
	if (lenght==3 && strcmp(split_input[0], "save") == 0 && strcmp(split_input[1],"as")==0)
	{
		save_as(split_input[2]);
		std::cout << "Table saved as:" << split_input[2] << std::endl;
		return;
	}
	if (strcmp(split_input[0], "save") == 0 && lenght==1)
	{
		save();
		std::cout << "Table saved\n";
		return;
	}
	if (strcmp(split_input[0], "help") == 0)
	{
		help();
		return;
	}
	if (strcmp(split_input[0], "exit") != 0 || lenght > 1)
		std::cout << "Invalid input\n";
	return;
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
	if (set_height(_file) == false || set_width(_file) == false)
		return false;
	file_name = new(std::nothrow)char[strlen(_file) + 1];
	if (file_name == nullptr)
		return false;
	strcpy(file_name, _file);
	return true;
}

bool Table::set_height(char* _file)
{
	height = 0;
	std::ifstream file;
	file.open(_file);
	if (file.is_open() == false)
		return false;
	while (file.good())
	{
		char character;
		file.get(character);
		if (character == '\n' || file.eof() == true)
		{
			height++;
		}
	}
	file.close();
	return true;
}

bool Table::set_width(char* _file)
{
	size_t width_counter = 0,line_counter=0;
	std::ifstream file;
	file.open(_file);
	if (file.is_open() == false)
		return false;
	width = new(std::nothrow) size_t[height];
	if (width == nullptr)
		return false;
	while (file.good())
	{
		char character;
		file.get(character);
		if (character == ',' && file.eof() == false)
			width_counter++;
		if (character == '\n' || file.eof() == true)
		{
			width_counter++;
			width[line_counter] = width_counter;
			line_counter++;
			width_counter = 0;
		}
	}
	return true;
}

bool Table::create_matrix(size_t _height,size_t* _width)
{

	matrix = new(std::nothrow)  Cell **[_height];
	if (matrix == nullptr)
	{
		del();
		return false;
	}
	for (size_t i = 0; i < _height; ++i)
	{
		matrix[i] = new(std::nothrow) Cell * [_width[i]];
		if (matrix[i] == nullptr)
		{
			del();
			return false;
		}
	}
	for (size_t i = 0; i < _height; ++i)
	{
		for (size_t j = 0; j < _width[i]; ++j)
		{
			matrix[i][j] = nullptr;
		}
	}
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
	character = skip_widespace(file, character);
	symbol = character;
	return word;
}

bool Table::open(char* _file)
{
	if (set_Parameters(_file) == false)
		return false;
	if (create_matrix(height, width) == false)
		return false;
	size_t current_width = 0, current_height = 0;
	std::ifstream file;
	file.open(_file);
	if (file.is_open() == false)
		return false;
	
	while (file.good())
	{
		char symbol, word[128];
		strcpy(word, read_word(file, symbol));
		if (strlen(word) == 0 && symbol=='\n')
		{
			current_width = 0;
			current_height++;
			continue;
		}
		if (strlen(word) == 0)
		{
			current_width++;
			continue;
		}
		matrix[current_height][current_width] = Cell_Factory::Initialize(word);
		if(matrix[current_height][current_width]==nullptr)
		{
			std::cout << " Column:" << current_width +1<< " Line:" << current_height+1; 
			del();
			return false;
		}
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

void Table::close()
{
	del();
	file_name = nullptr;
	matrix = nullptr;
	width = nullptr;
	height = 0;
}

void Table::copy(const Table& other)
{
	file_name = new(std::nothrow) char[strlen(other.file_name) + 1];
	if (file_name == nullptr)
		return;
	strcpy(file_name, other.file_name);
	if (create_matrix(other.height, other.width) == false)
		return;
	height = other.height;
	width = new(std::nothrow)size_t[height];
	if (width == nullptr)
	{
		del();
		return;
	}
	for (size_t i = 0; i < height; ++i)
		width[i] = other.width[i];
	for (size_t i = 0; i < height; ++i)
		for (size_t j = 0; j < width[i]; ++j)
			if(other.matrix[i][j]!=nullptr)
			matrix[i][j] = other.matrix[i][j]->copy();
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
		for (size_t j = 0; j < width[i] &&file.good(); ++j)
		{
			if(matrix[i][j]!=nullptr)
			file << matrix[i][j]->get_initial_text();
			if (j != width[i] - 1)
				file << ',';
		}
		file << '\n';
	}
	file.close();
}

void Table::print()
{
	calculate_formulas();
	size_t max_width = find_max_width();
	size_t* max_lenght =find_setw();
	if (max_lenght == nullptr)
	{
		std::cout << "Error\n";
		return;
	}
	
	for (size_t i = 0; i < height; ++i)
	{
		std::cout << "|";
		for (size_t j = 0; j < max_width; ++j)
		{
			if (matrix[i][j] != nullptr && j<width[i])
				std::cout << std::setw(max_lenght[j]) << matrix[i][j]->print();
			else
				std::cout << std::setw(max_lenght[j])<<" ";
				std::cout << "|";
		}
		std::cout << std::endl;
	}
	delete[] max_lenght;
	return;
}

size_t Table::find_max_width()
{
	size_t max_width_temp = 0;
	for (size_t i = 0; i < height; ++i)
		if (width[i] > max_width_temp)max_width_temp = width[i];
	return max_width_temp;
}

size_t* Table::find_setw()
{
	size_t* max_lenght_temp = new(std::nothrow)size_t[find_max_width()];
	if (max_lenght_temp == nullptr)
		return nullptr;
	for (size_t i = 0; i < height; ++i)
	{
		for (size_t j = 0; j < width[i]; ++j)
		{

			max_lenght_temp[j] = 1;
		}

	}
	for (size_t i = 0; i < height; ++i)
	{
		for (size_t j = 0; j < width[i]; ++j)
		{
			
			if (matrix[i][j]!=nullptr && max_lenght_temp[j] < strlen(matrix[i][j]->print()))
				max_lenght_temp[j] = strlen(matrix[i][j]->print());
		}

	}
	return max_lenght_temp;
}

bool Table::is_default()
{
	if (file_name == nullptr && matrix == nullptr && width == nullptr && height == 0)
		return true;
	return false;
}
bool Table::resize_line(size_t edit_height, size_t edit_width)
{
	Cell** line_temp = new(std::nothrow) Cell * [edit_width + 1];
	if (line_temp == nullptr)
		return false;
	for (size_t i = 0; i < edit_width + 1; ++i)
		line_temp[i] = nullptr;
	for (size_t i = 0; i < width[edit_height]; ++i)
	{
		line_temp[i] = matrix[edit_height][i];

	}
	for (size_t i = width[edit_height]; i < edit_width; ++i)
		line_temp[i] = nullptr;
	delete[] matrix[edit_height];
	width[edit_height] = edit_width + 1;
	matrix[edit_height] = line_temp;

	
	return true;

}
bool Table::edit_create_new_word(char**split_input,size_t lenght,char*& new_cell)
{
	size_t symbol_counter = 0;
	for (size_t i = 2; i < lenght; ++i)
	{
		symbol_counter += strlen(split_input[i]) + 1;
	}
	new_cell = new(std::nothrow) char[symbol_counter];
	if (new_cell == nullptr)
		return false;
	return true;
}
void Table::edit_initialize_new_word(char** split_input, size_t lenght, char*& new_cell)
{
	strcpy(new_cell, split_input[2]);
	if (lenght > 3)
		strcat(new_cell, " ");
	for (size_t i = 3; i < lenght; ++i)
	{
		strcat(new_cell, split_input[i]);
		if (i != lenght - 1)
		{
			strcat(new_cell, " ");
		}
	}
	return;
}
bool Table::edit(char** split_input,size_t lenght)
{
	size_t edit_height = 0, edit_width = 0;
	char* new_cell;
	if (lenght<3 || Cell::detect_cell(split_input[1], edit_height, edit_width) == false || edit_create_new_word(split_input, lenght, new_cell) == false)
		return false;
	if (edit_height >= height || edit_width >= find_max_width())
	{
		std::cout << "Cell otside table\n";
		return false;
	}
	if (edit_width >= width[edit_height])
	{
		resize_line(edit_height, edit_width);
	}
	edit_initialize_new_word(split_input, lenght, new_cell);
	if(matrix[edit_height][edit_width]!=nullptr)
	delete matrix[edit_height][edit_width];
	matrix[edit_height][edit_width] = Cell_Factory::Initialize(new_cell);
	if (matrix[edit_height][edit_width] == nullptr)
	{
		std::cout << "Previous Cell data lost\n";
		return false;
	}
	return true;
}

void Table::help()
{
	std::cout << "The following commands are supported:\n";
	std::cout << "open <file>: opens <file>\n";
	std::cout << "close: closes currently opened file\n";
	std::cout << "save: saves the current file\n";
	std::cout << "save as <name>: saves current file as <name>\n";
	std::cout << "help: prints this information\n";
	std::cout << "print: prints the current table\n";
	std::cout << "edit <Cell(R<line>C<column>)> <new text>: changes the given cell to <new text>\n";
}


