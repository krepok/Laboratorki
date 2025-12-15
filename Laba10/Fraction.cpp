#include "Fraction.h"

int Fraction::nod(int num, int denom) const
{
	num = abs(num);
	while (denom) 
	{
		num %= denom;
		std::swap(num, denom);
	}
	return num;
}

int Fraction::nok(int denom1, int denom2) const
{
	return denom1 * denom2 / nod(denom1, denom2);
}

Fraction::Fraction()
	: num{ 0 }, denom{ 1 }
{
}

Fraction::Fraction(int _num, int _denom)
	: num{ _num }, denom{ _denom }
{
	if (_denom == 0)
	{
		denom = 1;
	}
	if (denom < 0)
	{
		num *= -1;
		denom *= -1;
	}
	if (int n = nod(num, denom); n != 1)
	{
		num /= n;
		denom /= n;
	}
}

Fraction::Fraction(int _num)
	: num{ _num }, denom { 1 }
{
}

Fraction::Fraction(const Fraction& other)
	: num{ other.num }, denom{ other.denom }
{
}

Fraction::Fraction(Fraction&& other) noexcept
	: num{ other.num }, denom{ other.denom }
{
	other.num = 0;
	other.denom = 1;
}

Fraction Fraction::operator+(const Fraction& other) const
{
	if (this->denom == other.denom)
	{
		return { this->num + other.num, this->denom };
	}
	else
	{
		int n{ nok(this->denom, other.denom) };
		return { this->num * other.denom + other.num * this->denom , n};
	}
}

Fraction Fraction::operator-(const Fraction& other) const
{
	if (this->denom == other.denom)
	{
		return { this->num - other.num, this->denom };
	}
	else
	{
		int n{ nok(this->denom, other.denom) };
		return { this->num * other.denom - other.num * this->denom , n };
	}
}

Fraction Fraction::operator*(const Fraction& other) const
{
	return { this->num * other.num, this->denom * other.denom };
}

Fraction Fraction::operator/(const Fraction& other) const
{
	return { this->num * other.denom, this->denom * other.num };
}

Fraction Fraction::operator=(const Fraction& other)
{
	if (this == &other)
	{
		return *this;
	}
	this->num = other.num;
	this->denom = other.denom;
	return *this;
}

Fraction Fraction::operator=(Fraction&& other) noexcept 
{
	this->num = other.num;
	this->denom = other.denom;
	other.num = 0;
	other.denom = 1;
	return *this;
}

Fraction Fraction::operator+=(const Fraction& other)
{
	*this = *this + other;
	return *this;
}

Fraction Fraction::operator-=(const Fraction& other)
{
	*this = *this - other;
	return *this;
}

Fraction Fraction::operator*=(const Fraction& other)
{
	*this = *this * other;
	return *this;
}

Fraction Fraction::operator/=(const Fraction& other)
{
	*this = *this / other;
	return *this;
}

Fraction Fraction::operator!() const
{
	if (this->num == 0)
	{
		return 0;
	}
	return { this->denom, this->num };
}

Fraction Fraction::operator-() const
{
	return *this * -1;
}

bool Fraction::operator==(const Fraction& other) const
{
	if (this->num == other.num && this->denom == other.denom)
	{
		return true;
	}
	return false;
}

bool Fraction::operator!=(const Fraction& other) const
{
	if (this->num == other.num && this->denom == other.denom)
	{
		return false;
	}
	return true;
}

bool Fraction::operator>(const Fraction& other) const
{
	if (to_double(*this) > to_double(other))
	{
		return true;
	}
	return false;
}

bool Fraction::operator<(const Fraction& other) const
{
	if (to_double(*this) < to_double(other))
	{
		return true;
	}
	return false;
}

bool Fraction::operator>=(const Fraction& other) const
{
	if (to_double(*this) >= to_double(other))
	{
		return true;
	}
	return false;
}

bool Fraction::operator<=(const Fraction& other) const
{
	if (to_double(*this) <= to_double(other))
	{
		return true;
	}
	return false;
}

Fraction Fraction::operator++()
{
	this->num += this->denom;
	return *this;
}

Fraction Fraction::operator--()
{
	this->num -= this->denom;
	return *this;
}

Fraction Fraction::operator++(int)
{
	Fraction temp{ *this };
	this->num += this->denom;
	return temp;
}

Fraction Fraction::operator--(int)
{
	Fraction temp{ *this };
	this->num -= this->denom;
	return temp;
}

std::ostream& operator<<(std::ostream& out, const Fraction& fraction)
{
	if (fraction.denom != 1)
	{
		out << fraction.num << '/' << fraction.denom;
	}
	else
	{
		out << fraction.num;
	}
	return out;
}

std::istream& operator>>(std::istream& in, Fraction& fraction)
{
	char slash{};
	int num{};
	int denom{};
	in >> num >> slash >> denom;
	if (!in)
	{
		num = 0;
		denom = 1;
		in.clear();
		in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	Fraction temp{ num, denom };
	fraction = temp;
	return in;
}

double to_double(const Fraction& fraction)
{
	return static_cast<double>(fraction.num) / fraction.denom;
}