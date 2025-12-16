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

void Fraction::reduce()
{
	if (int n = nod(num, denom); n != 1)
	{
		num /= n;
		denom /= n;
	}
}

Fraction::Fraction(int _num, int _denom)
	: num{ _num }, denom{ _denom }
{
	if (_denom == 0)
	{
		throw std::invalid_argument("You entered 0 as a denom!");
	}
	if (denom < 0)
	{
		num *= -1;
		denom *= -1;
	}
	reduce();
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
		return Fraction{ this->num + other.num, this->denom };
	}
	else
	{
		int n{ nok(this->denom, other.denom) };
		return Fraction{ this->num * other.denom + other.num * this->denom , n};
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

Fraction& Fraction::operator=(const Fraction& other)
{
	if (this != &other)
	{
		this->num = other.num;
		this->denom = other.denom;
	}
	return *this;
}

Fraction& Fraction::operator=(Fraction&& other) noexcept 
{
	if (this != &other)
	{
		this->num = other.num;
		this->denom = other.denom;
		other.num = 0;
		other.denom = 1;
	}
	return *this;
}

Fraction& Fraction::operator+=(const Fraction& other)
{
	*this = *this + other;
	return *this;
}

Fraction& Fraction::operator-=(const Fraction& other)
{
	*this = *this - other;
	return *this;
}

Fraction& Fraction::operator*=(const Fraction& other)
{
	*this = *this * other;
	return *this;
}

Fraction& Fraction::operator/=(const Fraction& other)
{
	if (other == 0)
	{
		throw std::invalid_argument("Can't divide by 0!");
	}
	*this = *this / other;
	return *this;
}

Fraction Fraction::operator!() const
{
	if (this->num == 0)
	{
		throw std::invalid_argument("Can't get reciprocal fraction of 0!");
	}
	return { this->denom, this->num };
}

Fraction Fraction::operator-() const
{
	Fraction temp{ *this * -1 };
	return temp;
}

bool Fraction::operator==(const Fraction& other) const
{
	return this->num == other.num && this->denom == other.denom;
}

bool Fraction::operator!=(const Fraction& other) const
{
	return !(*this == other);
}

bool Fraction::operator>(const Fraction& other) const
{
	return to_double(*this) > to_double(other);
}

bool Fraction::operator<(const Fraction& other) const
{
	return to_double(*this) < to_double(other);

}

bool Fraction::operator>=(const Fraction& other) const
{
	return *this > other || *this == other;
}

bool Fraction::operator<=(const Fraction& other) const
{
	return *this < other || *this == other;
}

Fraction& Fraction::operator++()
{
	this->num += this->denom;
	return *this;
}

Fraction& Fraction::operator--()
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

Fraction operator+(int num, const Fraction& fraction)
{
	return fraction + num;
}

Fraction operator-(int num, const Fraction& fraction)
{
	return Fraction{ num } - fraction;
}

Fraction operator*(int num, const Fraction& fraction)
{
	return fraction * num;
}

Fraction operator/(int num, const Fraction& fraction)
{
	return Fraction{ num } / fraction;
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
		in.clear();
		in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		throw std::invalid_argument("You entered invalid fraction!");
	}
	Fraction temp{ num, denom };
	fraction = temp;
	return in;
}

double to_double(const Fraction& fraction)
{
	return static_cast<double>(fraction.num) / fraction.denom;
}