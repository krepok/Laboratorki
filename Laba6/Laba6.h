#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
#include <vector>
#include <stdexcept>
#include <string>
#include <concepts>

std::vector<int> getArrayFromFile(const std::vector<int>&);
std::vector<double> getArrayFromFile(const std::vector<double>&);
std::vector<std::string> getArrayFromFile(const std::vector<std::string>&);

enum class Way
{
	FileToFile,
	RandomToFile,
	FileToConsole,
};

enum class DataType
{
	Int,
	Double,
	String,
};

template<typename T>
void writeResultFile(const std::vector<T>& info, std::ofstream& fout)
{
	if (fout.is_open())
	{
		fout << "Number of unique elements is " << getNumOfUniques<T>(info);
		fout.close();
		std::cout << "Done!";
	}
	else
	{
		throw std::exception("Couldn't open a file!");
	}
}

template<typename T>
void printResultConsole(const std::vector<T>& info)
{
	std::cout << "Number of unique elements is " << getNumOfUniques<T>(info) << '\n';
}

template<typename T>
int getNumOfUniques(std::vector<T> info)
{
	std::sort(info.begin(), info.end());
	auto toErase{ std::unique(info.begin(), info.end()) };
	info.erase(toErase, info.end());
	return info.size();
}

template<typename T>
void writeArrayFile(std::vector<T> info, std::ofstream& fout)
{
	fout << "Generated array: ";
	for (T i : info)
	{
		fout << i << ' ';
	}
	fout << '\n';
}

template<typename T>
void getAndOutputArray(std::vector<T>& info, Way way)
{
	switch (way)
	{
	case Way::FileToFile:
	{
		info = getArrayFromFile(info);
		std::ofstream fout("out.txt");
		writeResultFile(info, fout);
		fout.close();
	}
		break;
	case Way::RandomToFile:
	{
		info = getRandomArray<T>();
		std::ofstream fout("out.txt");
		writeArrayFile(info, fout);
		writeResultFile(info, fout);
		fout.close();
	}
		break;
	case Way::FileToConsole:
	{
		info = getArrayFromFile(info);
		printResultConsole(info);
		break;
	}
	}
}