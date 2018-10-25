#include "ArbitraryInt.h"

void AInt::operator=(const AInt& n)
{
	data = n.data;
	negative = n.negative;
}

void AInt::operator=(const char* n)
{
	if (n[0] == '-')
	{
		data = std::string(n + 1, n + std::strlen(n));
		negative = true;
	}
	else
	{
		data = n;
		negative = false;
	}
}

void AInt::operator=(std::string n)
{
	if (n[0] == '-')
	{
		data = n.substr(1, -1);
		negative = true;
	}
	else
	{
		data = n;
		negative = false;
	}
}

void AInt::operator=(long long int n)
{
	if (n < 0)
	{
		data = std::to_string(n).substr(1, -1);
		negative = true;
	}
	else
	{
		data = n;
		negative = false;
	}
}

AInt AInt::operator+(AInt addend)
{
	if (this->length() < addend.length()) while (this->length() != addend.length()) this->data = "0" + this->data;
	else if(addend.length() < this->length()) while (addend.length() != this->length()) addend.data = "0" + addend.data;

	if (this->negative && addend.negative)
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
	else if (this->negative && !addend.negative)
	{
		this->negative = false;
		addend.negative = false;
		AInt num = addend - *this;
		return num;
	}

	std::string sum;
	int carry = 0;
	for (int i = this->length() - 1; i >= 0; i--)
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

AInt AInt::operator-(AInt subtrahend)
{
	auto sub = [](std::string n1, std::string n2)
	{
		std::vector<int> diff(n1.length() + 1, 0);
		for (int i = n1.length() - 1; i >= 0; i--)
		{
			if ((n1[i] - '0') + diff[i + 1] < (n2[i] - '0'))
			{
				diff[i] -= 1;
				diff[i + 1] += 10;
			}
			diff[i + 1] = (diff[i + 1] + (n1[i] - '0')) - (n2[i] - '0');
		}

		std::vector<std::string> sdiff(n1.length() + 1);

		for (int i = 0; i < n1.length() + 1; i++) sdiff[i] = std::to_string(diff[i]);
		while (sdiff[0] == "0") sdiff.erase(sdiff.begin());

		std::ostringstream os;
		std::copy(sdiff.begin(), sdiff.end(), std::ostream_iterator<std::string>(os));
		std::string fsum = os.str();
		return AInt(fsum.c_str());
	};

	if (*this == subtrahend) return AInt(0);
	else if (*this > subtrahend && !this->negative && !subtrahend.negative)
	{
		while (subtrahend.length() != this->length()) subtrahend.data = "0" + subtrahend.data;
		return sub(this->data, subtrahend.data);
	}
	else if (*this < subtrahend && !this->negative && !subtrahend.negative)
	{
		while (this->length() != subtrahend.length()) this->data = "0" + this->data;
		AInt diff = sub(subtrahend.data, this->data);
		diff.negative = true;
		return diff;
	}
	else if (*this > subtrahend && this->negative && subtrahend.negative)
	{
		while (this->length() != subtrahend.length()) this->data = "0" + this->data;
		subtrahend.negative = false;
		this->negative = false;
		return sub(subtrahend.data, this->data);
	}
	else if (*this < subtrahend && this->negative && subtrahend.negative)
	{
		while (subtrahend.length() != this->length()) subtrahend.data = "0" + subtrahend.data;
		subtrahend.negative = false;
		this->negative = false;
		AInt diff = sub(this->data, subtrahend.data);
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
}

AInt AInt::operator*(AInt factor)
{
	if (this->negative && factor.negative)
	{
		this->negative = false;
		factor.negative = false;
		return *this * factor;
	}
	else if (this->negative != factor.negative)
	{
		this->negative = false;
		factor.negative = false;
		AInt num = *this * factor;
		num.negative = true;
		return num;
	}

	AInt total = 0;

	for (int i = 0; i < factor.length(); i++)
	{
		std::string sum(i, '0');
		int carry = 0;
		for (int j = 0; j < this->length(); j++)
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

AInt AInt::operator+(int addend)
{
	return (*this + AInt(addend));
}

AInt AInt::operator-(int subtrahend)
{
	return (*this - AInt(subtrahend));
}

AInt AInt::operator*(int factor)
{
	return (*this * AInt(factor));
}

AInt AInt::operator-()
{
	this->negative = !this->negative;
	return *this;
}


bool AInt::operator>(AInt comp)
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
	}
}

bool AInt::operator<(AInt comp)
{
	return !(*this > comp);
}

bool AInt::operator>=(AInt comp)
{
	if (*this == comp) return true;
	else if (*this > comp) return true;
	return false;
}

bool AInt::operator<=(AInt comp)
{
	if (*this == comp) return true;
	else if (*this < comp) return true;
	return false;
}

bool AInt::operator==(AInt comp)
{
	if (this->negative != comp.negative) return false;
	else if (this->length() == comp.length())
	{
		for (int i = 0; i < this->length(); i++) if (this->data[i] != comp.data[i]) return false;
		return true;
	}
	else return false;
}

bool AInt::operator!=(AInt comp)
{
	return !(*this == comp);
}