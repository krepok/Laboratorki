#pragma once

#include "Laba6.h"
#include "Get Functions.h"
#include "Get Array Functions.h"

int getSize();
Way getWay();
DataType getDataType();
void FileCheck(std::ifstream& fin);

template<typename T>
void getBounds(T& lower, T& higher)
{
	std::cout << "Enter bounds of distribution: ";
	std::cin >> lower >> higher;
	if (!std::cin)
	{
		throw std::exception("You entered something wrong!");
	}
	if (lower > higher)
	{
		throw std::exception("Lower bound can't be greater than higher bound!");
	}
}