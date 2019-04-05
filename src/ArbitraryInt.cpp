#include "ArbitraryInt.hpp"

AInt& AInt::operator=(const AInt& n)
{
	data = n.data;
	negative = n.negative;
	return *this;
}

AInt AInt::operator+(AInt addend)
{
	if (this->length() < addend.length()) while (this->length() != addend.length()) this->data = "0" + this->data;
	else if(addend.length() < this->length()) while (addend.length() != this->length()) addend.data = "0" + addend.data;

	
	if (!this->negative && !addend.negative)
	{
		std::string sum;
		int carry = 0;
		for (long long i = this->length() - 1; i >= 0; i--)
		{
			int psum = (this->data[i] - '0') + (addend.data[i] - '0');
			int csum = psum % 10;

			sum.append(std::to_string((csum + carry) % 10));
			carry = std::floor((psum + carry) / 10);
		}

		if (carry != 0) sum.append(std::to_string(carry));

		std::reverse(sum.begin(), sum.end());
		return AInt(sum);
	}
	else if (this->negative && addend.negative)
	{
		this->negative = false;
		addend.negative = false;
		AInt num = *this + addend;
		num.negative = true;
		return num;
	}
	else if (!this->negative && addend.negative)
	{
		this->negative = false;
		addend.negative = false;
		AInt num = *this - addend;
		return num;
	}
	else
	{
		this->negative = false;
		addend.negative = false;
		AInt num = addend - *this;
		return num;
	}
}

AInt AInt::operator-(AInt subtrahend)
{
	if (*this == subtrahend) return AInt(0);
	else if (this->length() > subtrahend.length() && !this->negative && !subtrahend.negative)
	{
		while (subtrahend.length() != this->length()) subtrahend.data = "0" + subtrahend.data;
		return *this - subtrahend;
	}
	else if (*this < subtrahend && !this->negative && !subtrahend.negative)
	{
		while (this->length() != subtrahend.length()) this->data = "0" + this->data;
		AInt diff = subtrahend - *this;
		diff.negative = true;
		return diff;
	}
	else if (*this > subtrahend && this->negative && subtrahend.negative)
	{
		while (this->length() != subtrahend.length()) this->data = "0" + this->data;
		subtrahend.negative = false;
		this->negative = false;
		return subtrahend - *this;
	}
	else if (*this < subtrahend && this->negative && subtrahend.negative)
	{
		while (subtrahend.length() != this->length()) subtrahend.data = "0" + subtrahend.data;
		subtrahend.negative = false;
		this->negative = false;
		AInt diff = *this - subtrahend;
		diff.negative = true;
		return diff;
	}
	else if (this->negative && !subtrahend.negative)
	{
		this->negative = false;
		AInt diff = *this + subtrahend;
		diff.negative = true;
		return diff;
	}
	else if (!this->negative && subtrahend.negative)
	{
		subtrahend.negative = false;
		return *this + subtrahend;
	}
	else
	{ 
		std::string diff;
		int borrow = 0;
		int carry = 0;
		for (long long i = this->length() - 1; i >= 0; i--)
		{
			bool Borrow = (this->data[i] - '0') + borrow < (subtrahend.data[i] - '0');
			if (Borrow) carry = 10;
			else carry = 0;

			diff.append(std::to_string((carry + (this->data[i] - '0') + borrow) - (subtrahend.data[i] - '0')));

			if (Borrow) borrow = -1;
			else borrow = 0;
		}

		std::reverse(diff.begin(), diff.end());
		while (diff[0] == '0') diff.erase(diff.begin());
		return AInt(diff);
	}
}

AInt AInt::operator*(AInt factor)
{
	if (!this->negative && !factor.negative)
	{
		AInt total = 0;

		for (long long i = 0; i < factor.length(); i++)
		{
			std::string sum(i, '0');
			int carry = 0;
			for (long long j = 0; j < this->length(); j++)
			{
				int mul = (this->data[this->length() - 1 - j] - '0') * (factor.data[factor.length() - 1 - i] - '0') + carry;
				int pmul = mul % 10;

				sum.append(std::to_string(pmul));
				carry = std::floor(mul / 10);
			}

			if (carry != 0) sum.append(std::to_string(carry));

			std::reverse(sum.begin(), sum.end());
			total = total + AInt(sum);
		}

		return AInt(total);
	}
	else if (this->negative && factor.negative)
	{
		this->negative = false;
		factor.negative = false;
		return *this * factor;
	}
	else
	{
		this->negative = false;
		factor.negative = false;
		AInt num = *this * factor;
		num.negative = true;
		return num;
	}
}

AInt AInt::operator/(AInt divisor)
{
	if (*this < divisor) return 0_ai;

	AInt temp = *this;

	AInt quotient = 0;
	while (temp >= divisor)
	{
		temp -= divisor;
		quotient += 1;
	}

	return quotient;
}

AInt AInt::operator%(AInt divisor)
{
	AInt temp = *this;

	while (temp >= divisor)
	{
		temp -= divisor;
	}

	return temp;
}

AInt AInt::pow(AInt exp)
{
	AInt num = 1;
	while (exp != 0)
	{
		num *= *this;
		exp--;
	}
	return num;
}

AInt AInt::pow(AInt base, AInt exp)
{
	AInt num = 1;
	while (exp != 0)
	{
		num *= base;
		exp -= 1;
	}
	return num;
}

void AInt::operator+=(const AInt& addend)
{
	*this = *this + addend;
}

void AInt::operator-=(const AInt& subtrahend)
{
	*this = *this - subtrahend;
}

void AInt::operator*=(const AInt& factor)
{
	*this = *this * factor;
}

void AInt::operator/=(const AInt & divisor)
{
	*this = *this / divisor;
}

void AInt::operator%=(const AInt & divisor)
{
	*this = *this % divisor;
}

AInt AInt::operator++()
{
	*this += 1;
	return *this;
}

AInt AInt::operator--()
{
	*this -= 1;
	return *this;
}

AInt AInt::operator++(int)
{
	AInt temp = *this;
	*this += 1;
	return temp;
}

AInt AInt::operator--(int)
{
	AInt temp = *this;
	*this -= 1;
	return temp;
}

AInt AInt::operator-()
{
	this->negative = !this->negative;
	return *this;
}

bool AInt::operator>(const AInt& comp)
{
	if (this->length() > comp.length())
	{
		if (this->negative && !comp.negative) return false;
		else if (this->negative && comp.negative) return false;
		else return true;
	}
	else if (this->length() < comp.length())
	{
		if (this->negative && !comp.negative) return false;
		else if (this->negative && comp.negative) return true;
		else return false;
	}
	else
	{
		if (this->negative && !comp.negative) return false;
		else if (!this->negative && comp.negative) return true;
		else if (!this->negative && !comp.negative)
		{
			for (int i = 0; i < this->length(); i++) if ((this->data[i] - '0') > (comp.data[i] - '0')) return true;
			return false;
		}
		else if (this->negative && comp.negative)
		{
			for (int i = 0; i < this->length(); i++) if ((this->data[i] - '0') < (comp.data[i] - '0')) return true;
			return false;
		}
		else return false;
	}
}

bool AInt::operator<(const AInt& comp)
{
	return !(*this > comp);
}

bool AInt::operator>=(const AInt& comp)
{
	if (*this == comp) return true;
	else if (*this > comp) return true;
	return false;
}

bool AInt::operator<=(const AInt& comp)
{
	if (*this == comp) return true;
	else if (*this < comp) return true;
	return false;
}

bool AInt::operator==(const AInt& comp)
{
	if (this->negative != comp.negative) return false;
	else if (this->length() != comp.length()) return false;
	else if (this->data == comp.data) return true;
	else return false;
}

bool AInt::operator!=(const AInt& comp)
{
	return !(*this == comp);
}