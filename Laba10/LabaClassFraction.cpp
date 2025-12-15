#include <iostream>
#include "Fraction.h"
#include <string>
#include <cmath>

int main()
{
	Fraction fractionStandard{};
	std::cout << "Standard initialization: " << fractionStandard << '\n';

	Fraction fractionCopy{ fractionStandard };
	std::cout << "Copy initialization: " << fractionCopy << '\n';

	Fraction fraction1{ -1, 2 };
	Fraction fraction2{ 1, 3 };

	std::cout << fraction1 << " + " << fraction2 << " = " << fraction1 + fraction2 << '\n';
	std::cout << fraction1 << " - " << fraction2 << " = " << fraction1 - fraction2 << '\n';
	std::cout << fraction1 << " * " << fraction2 << " = " << fraction1 * fraction2 << '\n';
	std::cout << fraction1 << " / " << fraction2 << " = " << fraction1 / fraction2 << '\n';

	Fraction fraction3{};
	std::cout << "Enter a fraction( a/b ): ";
	std::cin >> fraction3;
	std::cout << fraction3 << '\n';

	std::cout << "Fraction " << fraction3 << " to double: " << to_double(fraction3) << '\n';

	std::cout << "Reciprocal fraction of " << fraction3 << " is " << !fraction3 << '\n';

	std::cout << "++" << fraction3 << " is " << ++fraction3 << '\n';
	std::cout << fraction3 << "--" << " is " << fraction3-- << '\n';
	
	std::cout << "After --: " << fraction3 << '\n';

	Fraction fraction4{};
	Fraction fraction5{};
	std::cout << "Enter 2 fractions: ";
	std::cin >> fraction4 >> fraction5;

	if (fraction4 == fraction5)
	{
		std::cout << fraction4 << " = " << fraction5 << '\n';
	}
	else if (fraction4 > fraction5)
	{
		std::cout << fraction4 << " > " << fraction5 << '\n';
	}
	else if (fraction4 < fraction5)
	{
		std::cout << fraction4 << " < " << fraction5 << '\n';
	}

	return 0;
}