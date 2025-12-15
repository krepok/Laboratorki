#include <iostream>

void getBounds(int& lowerBound, int& higherBound);
int getNum();
int findIndex(int index);
bool isArmstrong(int num);
bool isSumEqualProd(int num);
bool isPrime(int num);
void printSumProd(int lowerBound, int higherBound);
void printArmstrong(int num);
void printPrimes(int num);

int main()
{
	try
	{
		std::cout << "Enter a number: ";
		int num{ getNum() };

		try
		{
			printPrimes(num);
		}
		catch (const char* text)
		{
			std::cout << text << '\n';
		}

		std::cout << "Enter a number: ";
		num = getNum();
		printArmstrong(num);

		int lowerBound{};
		int higherBound{};
		getBounds(lowerBound, higherBound);
		printSumProd(lowerBound, higherBound);

		std::cout << "Enter an index of a digit in number series : ";
		int index{ getNum() };
		std::cout << "Digit with index " << index << " is " << findIndex(index);
	}
	catch (const char* text)
	{
		std::cout << text << '\n';
	}

	return 0;
}

void getBounds(int& lowerBound, int& higherBound)
{
	std::cout << "Enter lower and higher bound: ";
	std::cin >> lowerBound >> higherBound;
	if (!std::cin)
	{
		throw "You entered wrong bounds!";
	}
	if (lowerBound < 1 || higherBound < 1)
	{
		throw "Bounds should be greater than 0!";
	}
	if (lowerBound > higherBound)
	{
		std::swap(higherBound, lowerBound);
	}
}

int getNum()
{
	int num{};
	std::cin >> num;
	if (!std::cin)
	{
		throw "You entered non number value!";
	}
	if (num < 1)
	{
		throw "Number should be greater than 0!";
	}
	return num;
}

int findIndex(int index)
{
	int length{ 1 };
	int count{ 9 };
	int start{ 1 };

	while (index > length * count) 
	{
		index -= length * count;
		length++;
		count *= 10;
		start *= 10;
	}

	int number{ start + (index - 1) / length };

	int digitPos{ (index - 1) % length };

	for (int i = 0; i < length - 1 - digitPos; ++i) 
	{
		number /= 10;
	}
	return number % 10;
}

bool isArmstrong(int num)
{
	int temp{ num };
	int sum{};
	int n{ static_cast<int>(log10(num)) + 1 };
	for (int i = 0; i < n; i++)
	{
		sum += pow((temp % 10), n);
		temp /= 10;
	}
	if (sum == num)
	{
		return true;
	}
	return false;
}

bool isSumEqualProd(int num)
{
	int sum{};
	int max{};
	while (num)
	{
		int temp{ num % 10 };
		sum += temp;
		if (temp > max)
		{
			max = temp;
		}
		num /= 10;
	}
	if (sum == max * max)
	{
		return true;
	}
	return false;
}

bool isPrime(int num)
{
	if (num == 2)
	{
		return true;
	}
	if (num % 2 == 0 || num == 1)
	{
		return false;
	}
	int bound{ static_cast<int>(sqrt(num)) };
	for (int i = 3; i <= bound; i += 2)
	{
		if (num % i == 0)
		{
			return false;
		}
	}
	return true;
}

void printSumProd(int lowerBound, int higherBound)
{
	int counter{};
	std::cout << "Numbers with sum of digits equal square of max digit: ";
	while (lowerBound <= higherBound)
	{
		if (isSumEqualProd(lowerBound))
		{
			std::cout << lowerBound << ", ";
			++counter;
		}
		lowerBound++;
	}
	if (counter == 0)
	{
		std::cout << "there are no such numbers in this area :(\n";
	}
	else
	{
		std::cout << "\b \b" << "\b \b" << '\n';
	}
}

void printArmstrong(int num)
{
	std::cout << "Armstrong numbers: ";
	for (int i = 1; i <= num; i++)
	{
		if (isArmstrong(i))
		{
			std::cout << i << ", ";
		}
	}
	std::cout << "\b \b" << "\b \b" << '\n';
}

void printPrimes(int num)
{
	if (num == 1)
	{
		throw "1 doesn't have prime factors!";
	}
	std::cout << "Prime factors is: ";
	int i{ 2 };
	while (num > 1)
	{
		if (isPrime(i))
		{
			while (num % i == 0)
			{
				num /= i;
				std::cout << i << " * ";
			}
		}
		i++;
	}
	std::cout << "\b \b" << "\b \b" << '\n';
}