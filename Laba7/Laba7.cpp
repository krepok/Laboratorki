#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

constexpr int c_maxSize{ 300 };

void getStr(char* str)
{
	std::cin.getline(str, c_maxSize);
	if (!std::cin)
	{
		throw std::exception("You entered something wrong!");
	}
	if (std::strlen(str) == 0)
	{
		throw std::exception("You didn't enter anything!");
	}
}

bool isGreaterLex(const char* str)
{
	size_t size{ std::strlen(str) };
	for (int i = 0; i < size - 1; i++)
	{
		if (str[i] > str[i + 1])
		{
			return false;
		}
	}
	return true;
}

void getWords(char* words, char* str, const char* delims)
{
	char* word{ strtok(str, delims) };
	size_t len{ 0 };

	while (word != NULL)
	{
		if (std::strlen(word) == len && isGreaterLex(word))
		{
			strncat(words, " ", 1);
			strncat(words, word, std::strlen(word) + 1);
		}
		else if (std::strlen(word) > len && isGreaterLex(word))
		{
			strncpy(words, word, std::strlen(word) + 1);
			len = std::strlen(word);
		}
		word = std::strtok(NULL, delims);
	}
	if (std::strlen(words) == 0)
	{
		throw std::exception("There are no words letters of which are lexicographically increasing!");
	}
}

int main()
{
	try
	{
		std::cout << "Enter a string: ";
		char str[c_maxSize];
		getStr(str);

		std::cout << "Enter delimiters: ";
		char delims[c_maxSize];
		getStr(delims);

		char words[c_maxSize]{};
		getWords(words, str, delims);
		std::cout << "Words letters of which lexicographically increasing: " << words << '\n';
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << '\n';
	}
	return 0;
}