#include <iostream>
#include <vector>
#include <random>
#include <iomanip>

size_t getSize()
{
	size_t size{};
	if (!(std::cin >> size))
	{
		throw std::exception("You entered non integer value!");
	}
	if (size < 2)
	{
		throw std::exception("Size can't be less than 2!");
	}
	return size;
}

void getBounds(int& lowerBound, int& higherBound)
{
	std::cout << "Enter bounds of elements: ";
	if (!(std::cin >> lowerBound >> higherBound))
	{
		throw std::exception("You entered ivalid bounds!");
	}
	if (higherBound < lowerBound)
	{
		std::swap(higherBound, lowerBound);
	}
}

void getRandomArray(std::vector<std::vector<int>>& arr, int lowerBound, int higherBound)
{
	static std::mt19937 gen(283274);
	std::uniform_int_distribution dist(lowerBound, higherBound);
	for (auto& vector : arr)
	{
		for (auto& el : vector)
		{
			el = dist(gen);
		}
	}
}

std::vector<std::vector<int>> getArray()
{
	std::cout << "Enter number of rows in matrix: ";
	size_t rows{ getSize() };
	std::cout << "Enter number of cols in matrix: ";
	size_t cols{ getSize() };
	std::vector<std::vector<int>> arr(rows, std::vector<int>(cols, 0));

	int lowerBound{};
	int higherBound{};
	getBounds(lowerBound, higherBound);

	getRandomArray(arr, lowerBound, higherBound);

	return arr;
}

void deleteMaxRowCol(std::vector<std::vector<int>>& arr)
{
	auto iMax{ arr.begin() };
	auto jMax{ (arr.at(0)).begin() };
	int jMaxCounter{};

	for (auto i = arr.begin(); i != arr.end(); ++i)
	{
		int counter{};
		for (auto j = i->begin(); j != i->end(); ++j)
		{
			if (*j > *jMax)
			{
				iMax = i;
				jMax = j;
				jMaxCounter = counter;
			}
			counter++;
		}
	}

	arr.erase(iMax);
	for (auto& row : arr)
	{
		row.erase(row.begin() + jMaxCounter);
	}
}

void printMatrix(const std::vector<std::vector<int>>& arr)
{
	for (const auto& row : arr)
	{
		for (const auto& el : row)
		{
			std::cout << std::setw(5) << el << ' ';
		}
		std::cout << '\n';
	}
}

int getRowSum(const std::vector<int>& row)
{
	int sum{};
	for (int num : row)
	{
		sum += num;
	}
	return sum;
}

void sortMatrix(std::vector<std::vector<int>>& arr)
{
	std::vector<int> sums{};

	for (const auto& row : arr)
	{
		sums.push_back(getRowSum(row));
	}

	size_t size{ arr.size() };
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = 0; j < size - 1 - i; j++)
		{
			if (sums.at(j) > sums.at(j + 1))
			{
				std::swap(arr.at(j), arr.at(j + 1));
				std::swap(sums.at(j), sums.at(j + 1));
			}
		}
	}
}

int main()
{
	try
	{
		std::vector<std::vector<int>> temp{ getArray() };
		std::cout << "Matrix:\n";
		printMatrix(temp);

		std::cout << "Matrix with deleted row and col:\n";
		deleteMaxRowCol(temp);
		printMatrix(temp);
		std::cout << '\n';

		std::cout << "Sorted matrix:\n";
		sortMatrix(temp);
		printMatrix(temp);

	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << '\n';
	}
	return 0;
}