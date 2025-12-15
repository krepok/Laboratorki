#include "Laba6.h"
#include "Get Functions.h"
#include "Get Array Functions.h"

std::vector<int> generateArray(int size, int lower, int higher, std::mt19937& gen)
{
	std::vector<int> info;
	std::uniform_int_distribution<int> dist(lower, higher);
	for (int i = 0; i < size; i++)
	{
		info.push_back(dist(gen));
	}
	return info;
}

std::vector<double> generateArray(int size, double lower, double higher, std::mt19937& gen)
{
	std::vector<double> info;
	std::uniform_real_distribution<double> dist(lower, higher);
	for (int i = 0; i < size; i++)
	{
		info.push_back(dist(gen));
	}
	return info;
}

std::vector<std::string> generateArray(int size, std::string lower, std::string higher, std::mt19937& gen)
{
	throw std::exception("You can't generate random array of strings!");
}

std::vector<int> getArrayFromFile(const std::vector<int>&) 
{
	std::vector<int> info;
	int temp;
	std::string check;
	std::ifstream fin("in.txt");
	FileCheck(fin);

	if (fin.is_open())
	{
		while (fin >> check)
		{
			std::istringstream str(check); // для проверки на правильность данных в файле
			str >> temp;
			if (check == std::to_string(temp))
			{
				info.push_back(temp);
			}
			else
			{
				throw std::exception("There are element/elements of other types!");
			}
		}
		fin.close();
	}
	else
	{
		throw std::exception("Couldn't open a file!");
	}
	if (info.empty())
	{
		throw std::exception("There are no elements in this file!");
	}
	return info;
}

std::vector<double> getArrayFromFile(const std::vector<double>&)
{
	std::vector<double> info;
	double temp;
	std::string check;
	std::ifstream fin("in.txt");
	FileCheck(fin);

	if (fin.is_open())
	{
		while (fin >> check)
		{
			size_t size{ check.size() };
			std::istringstream str(check);
			str >> temp;
			if (check == std::to_string(temp).substr(0, size))
			{
				info.push_back(temp);
			}
			else
			{
				throw std::exception("There are element/elements of other types!");
			}
		}
		fin.close();
	}
	else
	{
		throw std::exception("Couldn't open a file!");
	}
	if (info.empty())
	{
		throw std::exception("There are no elements in this file!");
	}
	return info;
}

std::vector<std::string> getArrayFromFile(const std::vector<std::string>&)
{
	std::vector<std::string> info;
	std::string temp;
	std::ifstream fin("in.txt");
	FileCheck(fin);

	if (fin.is_open())
	{
		while (fin >> temp)
		{
			info.push_back(temp);
		}
		fin.close();
	}
	else
	{
		throw std::exception("Couldn't open a file!");
	}
	if (info.empty())
	{
		throw std::exception("There are no elements in this file!");
	}
	return info;
}
