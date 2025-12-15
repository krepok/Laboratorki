#include "Laba6.h"
#include "Get Functions.h"
#include "Get Array Functions.h"

Way getWay()
{
	std::cout <<
		"1. Get array from a file and output in another file\n" <<
		"2. Generate random array and output in another file\n" <<
		"3. Get array from a file and output in console\n" <<
		"Enter way to input and output information: ";
	int way{};
	std::cin >> way;

	switch (way)
	{
	case 1:
		return Way::FileToFile;
	case 2:
		return Way::RandomToFile;
	case 3:
		return Way::FileToConsole;
	default:
		throw std::exception("Incorrect number!");
	}
}

DataType getDataType()
{
	std::cout <<
		"1. Int\n" <<
		"2. Double\n" <<
		"3. String\n" <<
		"Enter type of information: ";
	int dataType{};
	std::cin >> dataType;
	switch (dataType)
	{
	case 1:
		return DataType::Int;
	case 2:
		return DataType::Double;
	case 3:
		return DataType::String;
	default:
		throw std::exception("Incorrect number!");
	}
}

void FileCheck(std::ifstream& fin)
{
	if (!fin.is_open())
	{
		throw std::exception("Couldn't open the file!");
	}
	if (fin.peek() == EOF)
	{
		throw std::exception("File is empty!");
	}
}

int getSize()
{
	int num{};
	std::cin >> num;
	if (!std::cin)
	{
		throw std::exception("You entered something wrong!");
	}
	if (num < 1)
	{
		throw std::exception("Number of elements must be greater than 0!");
	}
	return num;
}