#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <string_view>

void fileCheck(std::ifstream& fin);
int findMaxSubstring(std::string_view str);
void printStrings(const std::vector<std::string>& strings, int maxSubstr);
std::vector<std::string> findStrings(std::ifstream& fin, int& maxSubstr);

int main()
{
	try
	{
		std::ifstream fin("input.txt");
		fileCheck(fin);

		int maxSubstr{ 1 };
		std::vector<std::string> strings{ findStrings(fin, maxSubstr) };

		printStrings(strings, maxSubstr);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << '\n';
	}
	return 0;
}

void fileCheck(std::ifstream& fin)
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

int findMaxSubstring(std::string_view str)
{
	size_t size{ str.size() };
	int maxSubstr{ 1 };
	int counter = 1;

	for (int i = 0; i < size - 1; i++)
	{
		if (str.at(i) < str.at(i + 1))
		{
			++counter;
		}
		else
		{
			if (counter > maxSubstr)
			{
				maxSubstr = counter;
			}
			counter = 1;
		}
	}

	if (counter > maxSubstr)
	{
		maxSubstr = counter;
	}
	return maxSubstr;
}

void printStrings(const std::vector<std::string>& strings, int maxSubstr)
{
	std::cout << "Strings with max substring size of " << maxSubstr << ":\n";
	for (int i = 0; i < 10 && i < strings.size(); i++)
	{
		std::cout << strings[i] << '\n';
	}
}

std::vector<std::string> findStrings(std::ifstream& fin, int& maxSubstr)
{
	std::vector<std::string> strings{};
	std::string str{};
	while (std::getline(fin, str))
	{
		int sizeSubstr{ findMaxSubstring(str) };
		if (sizeSubstr == maxSubstr)
		{
			strings.push_back(str);
		}
		else if (sizeSubstr > maxSubstr)
		{
			strings.clear();
			strings.push_back(str);
			maxSubstr = sizeSubstr;
		}
	}
	return strings;
}