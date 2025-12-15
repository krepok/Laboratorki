#pragma once

#include "Get Functions.h"
#include "Laba6.h"
#include "Get Array Functions.h"

std::vector<int> generateArray(int size, int lower, int higher, std::mt19937& gen);
std::vector<double> generateArray(int size, double lower, double higher, std::mt19937& gen);
std::vector<std::string> generateArray(int size, std::string lower, std::string higher, std::mt19937& gen);
std::vector<int> getArrayFromFile(const std::vector<int>&);
std::vector<double> getArrayFromFile(const std::vector<double>&);
std::vector<std::string> getArrayFromFile(const std::vector<std::string>&);
int getSize();

template<typename T>
std::vector<T> getRandomArray()
{
	static std::mt19937 gen(12748273);
	T lower{};
	T higher{};
	getBounds<T>(lower, higher);

	std::cout << "Enter size of array: ";
	int size{ getSize() };

	return generateArray(size, lower, higher, gen);
}