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
	auto add = [](std::string n1, std::string n2)
	{
		std::vector<int> sum(n1.length() + 1);
		for (int i = n1.length() - 1; i >= 0; i--)
		{
			int psum = (n1[i] - '0') + (n2[i] - '0');
			int csum = psum % 10;
			int carry = std::floor((psum + sum[i + 1]) / 10);

			sum[i + 1] = (csum + sum[i + 1]) % 10;
			sum[i] = carry;
		}

		std::vector<std::string> ssum(n1.length() + 1);

		for (int i = 0; i < n1.length() + 1; i++) ssum[i] = std::to_string(sum[i]);

		std::ostringstream os;
		std::copy(ssum.begin() + ((sum[0] == 0) ? 1 : 0), ssum.end(), std::ostream_iterator<std::string>(os));
		std::string fsum = os.str();
		return AInt(fsum.c_str());
	};

	if (this->length() != addend.length())
	{
		std::string smallest = (this->length() < addend.length()) ? this->data : addend.data;
		std::string largest = (this->length() > addend.length()) ? this->data : addend.data;

		smallest = std::string((largest.length() - smallest.length()), '0') + smallest;

		return add(largest, smallest);
	}

	return add(this->data, addend.data);
}

AInt AInt::operator*(AInt factor)
{
	std::vector<std::vector<int>> sum(factor.length());
	for (int i = 0; i < sum.size(); i++)
		for (int j = 0; j < i+1; j++)
			sum[i].push_back(0);

	AInt total = 0;

	for (int i = 0; i < sum.size(); i++)
	{
		for (int j = 0; j < this->length(); j++)
		{
			int mul = (this->data[this->length() - 1 - j] - '0') * (factor.data[sum.size() - 1 - i] - '0') + sum[i][0];
			int pmul = mul % 10;
			int carry = std::floor(mul / 10);

			sum[i][0] = pmul;
			sum[i].insert(sum[i].begin(), carry);
		}
		std::ostringstream os;
		std::copy(sum[i].begin()+1, sum[i].end(), std::ostream_iterator<int>(os));
		total = total + AInt(os.str());
	}

	return AInt(total);
} 

AInt AInt::operator+(int addend)
{
	return (*this + AInt(addend));
}

AInt AInt::operator*(int factor)
{
	return (*this * AInt(factor));
}
