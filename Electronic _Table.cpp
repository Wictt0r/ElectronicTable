#include<iostream>
#include"Cell.h"
#include"Table.h"

int main()
{
	Table table;
	char input[100];
	do
	{
		std::cout << '>';
		std::cin.getline(input, 100);
		table.split_input(input, strlen(input));
	} while (strcmp(input, "exit") != 0);
}