#include "Flowerbed.h"
#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <string>

void checkFile(std::ifstream& fin)
{
	if (!fin.is_open())
	{
		throw std::exception("Couldn't open a file!");
	}
	if (fin.peek() == EOF)
	{
		throw std::exception("File is empty!");
	}
}

std::list<std::string> getListInfo(std::string& info, const char ch)
{
	std::list<std::string> infoStr{};

	for (auto place = info.find(ch); place != std::string::npos; place = info.find(ch))
	{
		infoStr.push_back(info.substr(0, place));
		info.erase(0, place + 1);
		place = info.find(ch);
	}
	infoStr.push_back(info);

	return infoStr;
}

Ridge getInfo(std::ifstream& fin)
{
	checkFile(fin);
	std::string info{};
	Ridge ridge{};

	while (std::getline(fin, info))
	{
		std::list<std::string> tempStr{ getListInfo(info, ';') };
		ridge.add({ stoi(tempStr.front()), *std::next(tempStr.begin(), 1), getListInfo(tempStr.back(), ',') });
	}

	return ridge;
}

template<typename T>
void printContainer(T vector)
{
	if (vector.empty())
	{
		std::cout << "There are no such elements!\n";
		return;
	}
	for (auto el : vector)
	{
		std::cout << el << ", ";
	}
	std::cout << "\b \b" << "\b \b";
	std::cout << '\n';
}

template<>
void printContainer(Ridge ridge)
{
	if (ridge.empty())
	{
		std::cout << "There are no such Flowerbeds!\n";
		return;
	}
	std::vector<Flowerbed> flowerbeds{ ridge.getFlowerbeds() };
	for (auto flowerbed : flowerbeds)
	{
		std::cout << "----------\n";
		std::cout << flowerbed;
	}
	std::cout << '\n';
}

void replaceSomeFlower(Ridge& ridge)
{
	std::cout << "Do you want to replace some flower with other(y/n)?: ";
	char ans{};
	std::cin >> ans;

	switch (ans)
	{
	case 'y':
	case 'Y':
	{
		std::string toReplace{};
		std::string replace{};

		std::cout << "Enter which flower to replace and with what to replace:\n";
		std::cin >> toReplace >> replace;

		ridge.replaceFlower(toReplace, replace);
		std::cout << "Done, the new container is:\n";
		printContainer(ridge);

		break;
	}
	case 'n':
	case 'N':
		std::cout << "Ok!\n\n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		break;
	default:
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "You entered something wrong!\n\n";
		break;
	}
}

int getSize()
{
	int size{};
	std::cin >> size;
	if (size < 1)
	{
		throw std::exception("You entered invalid size!");
	}
	return size;
}

int main()
{
	try
	{
		std::ifstream fin("data.txt");

		Ridge ridge{ getInfo(fin) };

		std::cout << "Unsorted flowerbeds:\n";
		printContainer(ridge);

		std::cout << "Sorted flowerbeds(shape -> id):\n";
		sort(ridge);
		printContainer(ridge);

		std::cout << "All flowers:\n";
		printContainer(ridge.getSetAllFlowers());
		std::cout << '\n';

		replaceSomeFlower(ridge);

		std::cout << "Common flowers:\n";
		printContainer(ridge.getSetCommonFlowers());
		std::cout << '\n';

		std::cout << "Enter number of unique flowers: ";
		int size{ getSize() };
		printContainer(ridge.getRidgeWithNumber(size));
		std::cout << '\n';

		std::cout << "Enter a flower to find flowerbeds without it: ";
		std::string flower{};
		std::cin >> flower;
		printContainer(ridge.getRidgeWithoutFlower(flower));
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << '\n';
	}
	return 0;
}