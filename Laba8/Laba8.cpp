#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::string getDelimString(std::string str, std::string_view delims);
std::vector<std::string> getWords(std::string& text, const std::string& delims);
std::string getStr();
bool isStrNum(const std::string& word);
std::string getFinalResult(std::string origin, std::string_view delimStr, std::pair<int, int> nums);
std::pair<int, int> getNums(const std::vector<std::string>& words);

int main()
{
	try
	{
		std::string str{ getStr() };
		std::string delims{ " ,;/" };
		std::string delimStr{ getDelimString(str, delims) };

		std::vector<std::string> words{ getWords(str, delims) };

		try
		{
			std::pair<int, int> minMaxNums{ getNums(words) };
			std::string res{ getFinalResult(str, delimStr, minMaxNums) };
			std::cout << res << '\n';
		}
		catch (const std::exception&)
		{
			std::cout << "Not enough numbers in this string!" << '\n';
		}

	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << '\n';
	}
	return 0;
}

std::string getStr()
{
	std::string str{};
	std::cout << "Enter a string (delimiters are 'space', 'comma', 'slash', 'semi-colon': ";
	std::getline(std::cin, str);
	if (str.empty())
	{
		throw std::exception("You didn't enter anything!");
	}
	return str;
}

std::string getDelimString(std::string str, std::string_view delims)
{
	size_t size{ str.size() };
	for (int i = 0; i < size; i++)
	{
		if (delims.find_first_of(str.at(i)) != std::string::npos)
		{
			str.at(i) = delims.at(0);
		}
	}
	return { delims.at(0) + str + delims.at(0) };
}

std::vector<std::string> getWords(std::string& text, const std::string& delims)
{
	char temp{};
	std::string tempString{};
	std::vector<std::string> words{};
	size_t size{ text.size() };

	for (int i = 0; i < size; i++)
	{
		temp = text[i];
		if (delims.find_first_of(temp) == std::string::npos)
		{
			tempString.push_back(temp);
		}
		else
		{
			if (!tempString.empty())
			{
				words.push_back(tempString);
				tempString.clear();
			}
		}
	}
	if (!tempString.empty())
	{
		words.push_back(tempString);
		tempString.clear();
	}
	return words;
}

bool isStrNum(const std::string& word)
{
	for (auto symbol : word)
	{
		if (!std::isdigit(symbol))
		{
			return false;
		}
	}
	return true;
}

std::pair<int, int> getNumsMinMax(const std::vector<int>& nums)
{
	size_t size{ nums.size() };
	int max{};
	int min{};
	for (int i = 0; i < size; i++)
	{
		if (nums[max] < nums[i])
		{
			max = i;
		}
		if (nums[min] > nums[i])
		{
			min = i;
		}
	}
	return { nums[min], nums[max] };
}

std::string getFinalResult(std::string origin, std::string_view delimStr, std::pair<int, int> nums)
{
	std::string minNumText{ delimStr[0] + std::to_string(nums.first) + delimStr[0] };
	std::string maxNumText{ delimStr[0] + std::to_string(nums.second) + delimStr[0] };
	auto min{ delimStr.find(minNumText) };
	auto max{ delimStr.find(maxNumText) };
	if (min < max)
	{
		origin.replace(max, std::to_string(nums.second).size(), std::to_string(nums.first));
		origin.replace(min, std::to_string(nums.first).size(), std::to_string(nums.second));
	}
	else
	{
		origin.replace(min, std::to_string(nums.first).size(), std::to_string(nums.second));
		origin.replace(max, std::to_string(nums.second).size(), std::to_string(nums.first));
	}
	return origin;
}

std::pair<int, int> getNums(const std::vector<std::string>& words)
{
	std::vector<int> nums;
	size_t size{ words.size() };
	for (int i = 0; i < size; i++)
	{
		if (isStrNum(words.at(i)))
		{
			nums.push_back(std::stoi(words[i]));
		}
	}
	if (nums.size() < 2)
	{
		throw std::exception();
	}
	return getNumsMinMax(nums);
}