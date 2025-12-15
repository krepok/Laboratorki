#pragma once
#include <stdexcept>
#include <fstream>
#include <iostream>

class Fraction
{
private:
	int num{};
	int denom{};

	int nod(int, int) const;
	int nok(int, int) const;
public:
	Fraction();
	Fraction(int, int);
	Fraction(int);
	Fraction(const Fraction& other);
	Fraction(Fraction&& other) noexcept;

	Fraction operator+(const Fraction&) const;
	Fraction operator-(const Fraction&) const;
	Fraction operator*(const Fraction&) const;
	Fraction operator/(const Fraction&) const;

	Fraction operator=(const Fraction& other);
	Fraction operator=(Fraction&& other) noexcept;

	Fraction operator+=(const Fraction&);
	Fraction operator-=(const Fraction&);
	Fraction operator*=(const Fraction&);
	Fraction operator/=(const Fraction&);

	Fraction operator!() const;
	Fraction operator-() const;

	bool operator==(const Fraction&) const;
	bool operator!=(const Fraction&) const;
	bool operator>(const Fraction&) const;
	bool operator<(const Fraction&) const;
	bool operator>=(const Fraction&) const;
	bool operator<=(const Fraction&) const;

	Fraction operator++();
	Fraction operator--();
	Fraction operator++(int);
	Fraction operator--(int);

	friend std::ostream& operator<<(std::ostream& out, const Fraction& fraction);
	friend std::istream& operator>>(std::istream& in, Fraction& fraction);

	friend double to_double(const Fraction&);
};