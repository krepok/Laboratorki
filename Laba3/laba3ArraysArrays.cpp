#include <iostream>
#include <cstdint>
#include <cmath>
#include <vector>
#include <random>
#include <array>
#include <stdexcept>

enum class RandomType
{
	Mersenne,
	Rand,
};

enum class ArrayType
{
	Vector,
	Array,
	CArray,
	DynamicCArray,
};

ArrayType getArrayType()
{
	std::cout <<
		"1. C-style array\n" <<
		"2. C-style dynamic array\n" <<
		"3. std::array\n" <<
		"4. std::vector\n" <<
		"Enter type of array to use: ";
	int arrayType{};
	std::cin >> arrayType;
	switch (arrayType)
	{
	case 1:
		return ArrayType::CArray;
	case 2:
		return ArrayType::DynamicCArray;
	case 3:
		return ArrayType::Array;
	case 4:
		return ArrayType::Vector;
	default:
		throw std::exception("Incorrect number!");
	}
}

size_t getSize()
{
	std::cout << "Enter size of array: ";
	size_t size{};
	std::cin >> size;
	if (!std::cin)
	{
		throw std::exception("You entered non integer value!");
	}
	if (size < 2)
	{
		throw std::exception("Size can't be less than 2!");
	}
	return size;
}

template<typename T>
void getArrayFromUser(T& arr, size_t size)
{
	std::cout << "Enter array: ";
	for (int i = 0; i < size; i++)
	{
		std::cin >> arr[i];
		if (!std::cin)
		{
			throw std::exception("You entered non integer value!");
		}
	}
}

void getBounds(int& lower, int& higher)
{
	std::cout << "Enter bounds of elements: ";
	std::cin >> lower >> higher;
	if (!std::cin)
	{
		throw std::exception("You entered non integer value!");
	}
	if (lower > higher)
	{
		throw std::exception("Lower bound can't be greater than higher!");
	}
}

RandomType getRandomType()
{
	std::cout <<
		"1. Rand()\n" <<
		"2. Mersenne twister\n" <<
		"Enter type of random: ";
	int dataType{};
	std::cin >> dataType;
	switch (dataType)
	{
	case 1:
		return RandomType::Rand;
	case 2:
		return RandomType::Mersenne;
	default:
		throw std::exception("Incorrect number!");
	}
}

template<typename T>
void getMersenneArray(T& arr, size_t size, int lowerBound, int higherBound)
{
	static std::mt19937 gen(123712);
	std::uniform_int_distribution dist(lowerBound, higherBound);
	for (int i = 0; i < size; i++)
	{
		arr[i] = dist(gen);
	}
}

template<typename T>
void getRandArray(T& arr, size_t size, int lowerBound, int higherBound)
{
	srand(time(0));
	for (int i = 0; i < size; i++)
	{
		arr[i] = rand() % (higherBound - lowerBound + 1) + lowerBound;
	}
}
	
template<typename T>
void getRandomArray(T& arr, size_t size)
{

	int lowerBound{};
	int higherBound{};
	getBounds(lowerBound, higherBound);

	RandomType randomType{ getRandomType() };
	switch (randomType)
	{
	case RandomType::Rand:
		getRandArray(arr, size, lowerBound, higherBound);
		break;
	case RandomType::Mersenne:
		getMersenneArray(arr, size, lowerBound, higherBound);
		break;
	}
}

char getWay()
{
	char wayToGetArray{};
	std::cout << "Enter how you want to make an array (r - for random, m - for manually): ";
	std::cin >> wayToGetArray;
	if (!std::cin)
	{
		throw std::exception("You entered non integer value");
	}
	return wayToGetArray;
}

template<typename T>
void getArray(T& arr, size_t size)
{
	char wayToGetArray{ getWay() };
	switch (wayToGetArray)
	{
	case 'r':
	case 'R':
		getRandomArray(arr, size);
		break;
	case 'm':
	case 'M':
		getArrayFromUser(arr, size);
		break;
	default:
		throw std::exception("You entered wrong value!");
	}
}

template<typename T>
void printArray(const T& arr, size_t size)
{
	for (int i = 0; i < size; i++)
	{
		std::cout << arr[i] << ' ';
	}
	std::cout << '\n';
}

template<typename T>
double getMultOfElements(const T& arr, size_t size)
{
	double multOfElements{ 1 };
	for (int i = 0; i < size; i++)
	{
		if (arr[i] == 0)
		{
			if (arr[i + 1] == 0)
			{
				throw std::exception("There are no elements between two zeros!");
			}
			for (int j = i + 1; j < size; j++)
			{
				if (arr[j] == 0)
				{
					return multOfElements;
				}
				multOfElements *= arr[j];
			}
		}
	}
	throw std::exception("There are not enough zeroes in this array!");
}

template<typename T>
int getSignSwitchesRIGHT(const T& arr, size_t size)
{
	bool posSign{ false };
	if (arr[0] >= 0)
	{
		posSign = true;
	}
	int signChanges{ 0 };

	for (int i = 1; i < size; ++i)
	{
		if (arr[i] < 0 && posSign)
		{
			++signChanges;
			posSign = false;
		}
		else if (arr[i] >= 0 && !posSign)
		{
			++signChanges;
			posSign = true;
		}
	}
	return signChanges;
}

template<typename T>
void sortArray(T& arr, size_t size)
{
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = 0; j < size - i - 1; j++)
		{
			if (abs(arr[j] % 2) == 1 && arr[j + 1] % 2 == 0)
			{
				std::swap(arr[j], arr[j + 1]);
			}
		}
	}
}

template<typename T>
void getResult(T& array, size_t size)
{
	getArray(array, size);

	std::cout << "Number of sign switches in this array is " << getSignSwitchesRIGHT(array, size) << '\n';

	try
	{
		double multOfElements{ getMultOfElements(array, size) };
		std::cout << "Product of elements between two zeros is " << multOfElements << '\n';
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << '\n';
	}

	std::cout << "Unsorted array: ";
	printArray(array, size);

	std::cout << "Sorted array: ";
	sortArray(array, size);
	printArray(array, size);
}

template<typename T>
void getResult(T& array, size_t size, size_t maxSize)
{
	if (maxSize < size)
	{
		throw std::exception("Entered size is too big for this array type");
	}

	getArray(array, size);

	std::cout << "Number of sign switches in this array is " << getSignSwitchesRIGHT(array, size) << '\n';

	try
	{
		double multOfElements{ getMultOfElements(array, size) };
		std::cout << "Product of elements between two zeros is " << multOfElements << '\n';
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << '\n';
	}

	std::cout << "Unsorted array: ";
	printArray(array, size);

	std::cout << "Sorted array: ";
	sortArray(array, size);
	printArray(array, size);
}

int main()
{
	constexpr size_t c_maxSize{ 1000 };
	try
	{
		ArrayType arrayType{ getArrayType() };
		size_t size{ getSize() };

		switch (arrayType)
		{
		case ArrayType::CArray:
		{
			int array[c_maxSize];
			getResult(array, size, c_maxSize);
			break;
		}
		case ArrayType::DynamicCArray:
		{
			int* array{ new int[size] };
			getResult(array, size);
			delete[] array;
			break;
		}
		case ArrayType::Vector:
		{
			std::vector<int> array(size);
			getResult(array, size);
			break;
		}
		case ArrayType::Array:
		{
			std::array<int, c_maxSize> array;
			getResult(array, size, c_maxSize);
			break;
		}
		}
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << '\n';
	}
	return 0;
}