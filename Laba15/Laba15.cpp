#include "QuickSort.h"
#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include <sstream>

struct Student
{
	std::string name{};
	int course{};
	int group{};
	std::vector<int> grades{};

	bool operator==(const Student& other) const
	{
		return this->course == other.course && this->group == other.group && this->name == other.name;
	}

	bool operator>(const Student& other) const
	{
		if (this->course != other.course)
		{
			return this->course > other.course;
		}
		if (this->group != other.group)
		{
			return this->group > other.group;
		}
		if (this->name != other.name)
		{
			return this->name > other.name;
		}
		return false;
	}

	bool operator<(const Student& other) const
	{
		if (this->course != other.course)
		{
			return this->course < other.course;
		}
		if (this->group != other.group)
		{
			return this->group < other.group;
		}
		if (this->name != other.name)
		{
			return this->name < other.name;
		}
		return false;
	}

	bool operator>=(const Student& other) const
	{
		return *this > other || *this == other;
	}

	bool operator<=(const Student& other) const
	{
		return *this < other || *this == other;
	}

	friend std::ostream& operator<<(std::ostream& out, const Student& other)
	{
		out << "Course: " << other.course << " group: " << other.group << '\n' <<
			"Name: " << other.name << "\nGrades:";

		for (const auto& grade : other.grades)
		{
			out << grade << ' ';
		}
		out << '\n';
		return out;
	}
};

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
	Char,
	String,
	Student,
};

int getInfo()
{
	int temp{};
	if (!(std::cin >> temp))
	{
		throw std::invalid_argument("You entered invalid value!");
	}
	return temp;
}

DataType getDataType()
{
	std::cout <<
		"1. Int\n" <<
		"2. Double\n" <<
		"3. Char\n" <<
		"4. String\n" <<
		"5. Student\n" <<
		"Enter type of information: ";
	switch (int dataType{ getInfo() }; dataType)
	{
	case 1:
		return DataType::Int;
	case 2:
		return DataType::Double;
	case 3:
		return DataType::Char;
	case 4:
		return DataType::String;
	case 5:
		return DataType::Student;
	default:
		throw std::invalid_argument("Incorrect number!");
	}
}

Way getWay()
{
	std::cout <<
		"1. Get array from a file and output in another file\n" <<
		"2. Generate random array and output in another file\n" <<
		"3. Get array from a file and output in console\n" <<
		"Enter way to input and output information: ";
	switch (int way{ getInfo() }; way)
	{
	case 1:
		return Way::FileToFile;
	case 2:
		return Way::RandomToFile;
	case 3:
		return Way::FileToConsole;
	default:
		throw std::invalid_argument("Incorrect number!");
	}
}

int getSize()
{
	int num{};
	if (!(std::cin >> num))
	{
		throw std::invalid_argument("You entered something wrong!");
	}
	if (num < 1)
	{
		throw std::invalid_argument("Number of elements must be greater than 0!");
	}
	return num;
}

void checkFile(std::ifstream& fin)
{
	if (!fin.is_open())
	{
		throw std::invalid_argument("Couldn't open a file!");
	}
	if (fin.peek() == EOF)
	{
		throw std::invalid_argument("File is empty!");
	}
}

char getDelimiter()
{
	char temp;
	if (!(std::cin >> temp))
	{
		throw std::invalid_argument("You entered something wrong");
	}
	return temp;
}

std::vector<std::string> getVectorInfo(std::string& info, const char ch)
{
	std::vector<std::string> infoStr{};

	for (auto place = info.find(ch); place != std::string::npos; place = info.find(ch))
	{
		infoStr.push_back(info.substr(0, place));
		info.erase(0, place + 1);
		place = info.find(ch);
	}
	infoStr.push_back(info);

	return infoStr;
}

std::vector<int> getVectorGrades(std::string& info, const char ch)
{
	std::vector<int> infoStr{};

	for (auto place = info.find(ch); place != std::string::npos; place = info.find(ch))
	{
		infoStr.push_back(stoi(info.substr(0, place)));
		info.erase(0, place + 1);
		place = info.find(ch);
	}
	infoStr.push_back(stoi(info));

	return infoStr;
}

template<typename T>
std::vector<T> getArrayFromFile(std::ifstream& fin)
{
	checkFile(fin);
	std::vector<T> infoStr{};
	T temp{};

	while (fin >> temp)
	{
		infoStr.push_back(temp);
	}
	return infoStr;
}

template<>
std::vector<Student> getArrayFromFile(std::ifstream& fin)
{
	checkFile(fin);
	std::string info{};
	std::vector<Student> infoVector{};

	std::cout << "Enter delimiter: ";
	const char ch1{ getDelimiter() };

	std::cout << "Enter delimiter for grades: ";
	const char ch2{ getDelimiter() };

	while (std::getline(fin, info))
	{
		std::vector<std::string> tempStr{ getVectorInfo(info, ch1) };
		infoVector.push_back(Student{ tempStr.at(0), stoi(tempStr.at(1)), stoi(tempStr.at(2)), getVectorGrades(tempStr.at(3), ch2) });
	}

	return infoVector;
}

template<typename T>
void printArray(std::vector<T> info)
{
	std::cout << "Your array is:\n";
	for (const auto& el : info)
	{
		std::cout << el << ' ';
	}
	std::cout << '\n';
}

template<>
void printArray(std::vector<Student> info)
{
	std::cout << "Your array is:\n";
	for (const auto& el : info)
	{
		std::cout << "------------------\n";
		std::cout << el;
	}
	std::cout << '\n';
}

template<typename T>
void writeArrayToFile(std::ofstream& fout, std::vector<T> info)
{
	if (!fout.is_open())
	{
		throw std::invalid_argument("Couldn't open a file!");
	}
	for (const auto& el : info)
	{
		fout << el << ' ';
	}
	fout << '\n';
}

template<>
void writeArrayToFile(std::ofstream& fout, std::vector<Student> info)
{
	if (!fout.is_open())
	{
		throw std::invalid_argument("Couldn't open a file!");
	}
	for (const auto& el : info)
	{
		fout << "------------------\n";
		fout << el;
	}
	fout << '\n';
}

template<typename T>
void getBounds(T& lower, T& higher)
{
	std::cout << "Enter bounds of distribution: ";
	if (!(std::cin >> lower >> higher))
	{
		throw std::invalid_argument("You entered something wrong!");
	}
	if (lower > higher)
	{
		std::swap(lower, higher);
	}
}

template<>
void getBounds(Student& lower, Student& higher) { ; }

std::vector<int> generateArray(int size, std::mt19937& gen, int lower, int higher)
{
	std::vector<int> info;
	std::uniform_int_distribution<int> dist(lower, higher);
	for (int i = 0; i < size; i++)
	{
		info.push_back(dist(gen));
	}
	return info;
}

std::vector<double> generateArray(int size, std::mt19937& gen, double lower, double higher)
{
	std::vector<double> info;
	std::uniform_real_distribution<double> dist(lower, higher);
	for (int i = 0; i < size; i++)
	{
		info.push_back(dist(gen));
	}
	return info;
}

std::vector<char> generateArray(int size, std::mt19937& gen)
{
	std::vector<char> info;
	std::uniform_int_distribution<int> dist(33, 126);
	for (int i = 0; i < size; i++)
	{
		info.push_back(static_cast<char>(dist(gen)));
	}
	return info;
}


std::vector<std::string> generateArray(int size, std::mt19937& gen, std::string lower, std::string higher)
{
	throw std::invalid_argument("You can't generate random array of strings!");
}

std::vector<Student> generateArray(int size, std::mt19937& gen, Student lower, Student higher)
{
	throw std::invalid_argument("You can't generate random array of students!");
}

template<typename T>
std::vector<T> getRandomArray()
{
	static std::mt19937 gen(12748273);
	T lower{};
	T higher{};
	getBounds<T>(lower, higher);

	std::cout << "Enter size of array: ";
	int size{ getSize() };

	return generateArray(size, gen, lower, higher);
}

template<>
std::vector<char> getRandomArray()
{
	static std::mt19937 gen(12748273);
	std::cout << "Enter size of array: ";
	int size{ getSize() };

	return generateArray(size, gen);
}

template<typename T>
void getAndOutputArray(std::vector<T>& info, Way way)
{
	switch (way)
	{
	case Way::FileToFile:
	{
		std::ifstream fin("in.txt");
		std::ofstream fout("out.txt");

		info = getArrayFromFile<T>(fin);
		quickSort(info, 0, info.size() - 1);
		fout << "Your array is:\n";
		writeArrayToFile(fout, info);
		std::cout << "Done!\n";

		fin.close();
		fout.close();
		break;
	}
	case Way::RandomToFile:
	{
		std::ofstream fout("out.txt");

		info = getRandomArray<T>();
		fout << "Your unsorted array is:\n";
		writeArrayToFile(fout, info);
		quickSort(info, 0, info.size() - 1);
		fout << "Your sorted array is:\n";
		writeArrayToFile(fout, info);
		std::cout << "Done!\n";

		fout.close();
		break;
	}
	case Way::FileToConsole:
	{
		std::ifstream fin("in.txt");

		info = getArrayFromFile<T>(fin);
		quickSort(info, 0, info.size() - 1);
		printArray(info);

		fin.close();
		break;
	}
	}
}

int main()
{
	try
	{
		Way way{ getWay() };
		DataType type{ getDataType() };
		if (way == Way::RandomToFile && (type == DataType::String || type == DataType::Student))
		{
			throw std::invalid_argument("You can't generate random array of strings!");
		}

		switch (type)
		{
		case DataType::Int:
		{
			std::vector<int> infoInt;
			getAndOutputArray(infoInt, way);
			break;
		}
		case DataType::Double:
		{
			std::vector<double> infoDouble;
			getAndOutputArray(infoDouble, way);
			break;
		}
		case DataType::Char:
		{
			std::vector<char> infoChar;
			getAndOutputArray(infoChar, way);
			break;
		}
		case DataType::String:
		{
			std::vector<std::string> infoString;
			getAndOutputArray(infoString, way);
			break;
		}
		case DataType::Student:
		{
			std::vector<Student> infoStudent;
			getAndOutputArray(infoStudent, way);
			break;
		}
		}
	}
	catch (const std::invalid_argument& e)
	{
		std::cout << e.what() << '\n';
	}
	
	return 0;
}