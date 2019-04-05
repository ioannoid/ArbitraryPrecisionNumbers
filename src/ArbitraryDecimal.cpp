#include "ArbitraryDecimal.hpp"

ADecimal::ADecimal(Literal, const char* num) {
	std::string temp = num;
	size_t dplace = temp.find('.');

	if (dplace == 0)
	{
		dplace = 1;
		if (temp[0] == '-')
		{
			temp[0] = '0';
			temp = '-' + temp;
		}
		else temp = '0' + temp;
	}

	if (dplace != std::string::npos)
	{
		temp.erase(temp.begin() + dplace);
		dplace -= (temp[0] == '-') ? 1 : 0;

		data = (temp[0] == '-') ? temp.substr(1) : temp;
		negative = temp[0] == '-';
		decimalplace = (int)dplace;
		precision = getLength() - (int)dplace;
	}
	else
	{
		data = (temp[0] == '-') ? temp.substr(1) : temp;
		negative = temp[0] == '-';
		decimalplace = (int)temp.length();
		if (temp[0] == '-') decimalplace--;
		precision = 0;
	}
}

ADecimal& ADecimal::operator=(const ADecimal& n) {
	data = n.data;
	negative = n.negative;
	decimalplace = n.decimalplace;
	precision = n.precision;
	return *this;
}

ADecimal ADecimal::operator+(const ADecimal& addend){
	ADecimal addend1 = *this;	
	ADecimal addend2 = addend;

	if (addend1.negative && !addend2.negative)
	{
		addend1.negative = false;
		return addend2 - addend1;
	}
	else if (!addend1.negative && addend2.negative)
	{
		addend2.negative = false;
		return addend1 - addend2;
	}
	else
	{
		int precision = (addend1.precision > addend2.precision) ? addend2.precision : addend1.precision;
		addend1.setPrecision(precision);
		addend2.setPrecision(precision);
		int dplace;

		if (addend1.getDecimalLength() < addend2.getDecimalLength()) addend1.data += std::string(addend2.getDecimalLength() - addend1.getDecimalLength(), '0');
		else addend2.data += std::string(addend1.getDecimalLength() - addend2.getDecimalLength(), '0');

		if (addend1.decimalplace < addend2.decimalplace)
		{
			dplace = addend2.decimalplace;
			addend1.data = std::string(addend2.decimalplace - addend1.decimalplace, '0') + addend1.data;
		}
		else
		{
			dplace = addend1.decimalplace;
			addend2.data = std::string(addend1.decimalplace - addend2.decimalplace, '0') + addend2.data;
		}

		std::string sum;
		int carry = 0;
		for (long long i = addend1.getLength() - 1; i >= 0; i--)
		{
			int psum = (addend1.data[i] - '0') + (addend2.data[i] - '0');
			int csum = psum % 10;

			sum.append(std::to_string((csum + carry) % 10));
			carry = std::floor((psum + carry) / 10);
		}

		if (carry != 0)
		{
			sum.append(std::to_string(carry));
			dplace++;
		}

		std::reverse(sum.begin(), sum.end());
		sum.insert(sum.begin() + dplace, '.');

		ADecimal fsum(toADecimal(sum)(precision));
		fsum.negative = addend1.negative;

		return fsum;
	}
}

ADecimal ADecimal::operator-(const ADecimal& rsubtrahend) {
	ADecimal minuend = *this;
	ADecimal subtrahend = rsubtrahend;

	if (minuend == subtrahend) return ADecimal(0_ad(precision));
	else if (minuend == subtrahend && minuend.negative != subtrahend.negative)
	{
		minuend.negative = false;
		ADecimal fdiff = minuend + minuend;
		fdiff.negative = minuend.negative;
		return fdiff;
	}
	else if (minuend.negative != subtrahend.negative)
	{
		bool sign = minuend.negative;
		minuend.negative = false;
		subtrahend.negative = false;
		ADecimal fdiff = minuend + subtrahend;
		fdiff.negative = sign;
		return fdiff;
	}
	else if (minuend > subtrahend && minuend.negative)
	{
		minuend.negative = false;
		subtrahend.negative = false;
		ADecimal fdiff = subtrahend - minuend;
		return fdiff;
	}
	else if (minuend < subtrahend && minuend.negative)
	{
		minuend.negative = false;
		subtrahend.negative = false;
		ADecimal fdiff = minuend - subtrahend;
		fdiff.negative = true;
		return fdiff;
	}
	else if (minuend < subtrahend && !minuend.negative)
	{
		ADecimal fdiff = subtrahend - minuend;
		fdiff.negative = true;
		return fdiff;
	}
	else
	{
		int precision = (minuend.precision > subtrahend.precision) ? subtrahend.precision : minuend.precision;
		minuend.setPrecision(precision);
		subtrahend.setPrecision(precision);
		int dplace;

		if (minuend.getDecimalLength() < subtrahend.getDecimalLength()) minuend.data += std::string(subtrahend.getDecimalLength() - minuend.getDecimalLength(), '0');
		else subtrahend.data += std::string(minuend.getDecimalLength() - subtrahend.getDecimalLength(), '0');

		if (minuend.decimalplace < subtrahend.decimalplace)
		{
			dplace = subtrahend.decimalplace;
			minuend.data = std::string(subtrahend.decimalplace - minuend.decimalplace, '0') + minuend.data;
		}
		else
		{
			dplace = minuend.decimalplace;
			subtrahend.data = std::string(minuend.decimalplace - subtrahend.decimalplace, '0') + subtrahend.data;
		}

		std::string diff;
		int borrow = 0;
		int carry = 0;
		for (long long i = minuend.getLength() - 1; i >= 0; i--)
		{
			bool Borrow = (minuend.data[i] - '0') + borrow < (subtrahend.data[i] - '0');
			if (Borrow) carry = 10;
			else carry = 0;

			diff.append(std::to_string((carry + (minuend. data[i] - '0') + borrow) - (subtrahend.data[i] - '0')));

			if (Borrow) borrow = -1;
			else borrow = 0;
		}

		std::reverse(diff.begin(), diff.end());
		diff.insert(diff.begin() + dplace, '.');
		while (diff[0] == '0') diff.erase(diff.begin());
		return ADecimal(toADecimal(diff)(precision));
	}
}

ADecimal ADecimal::operator*(const ADecimal& factor) {
	ADecimal factor1 = *this;
	ADecimal factor2 = factor;

	if (factor1.negative != factor2.negative)
	{
		factor1.negative = false;
		factor2.negative = false;
		ADecimal fprod = factor1 * factor2;
		fprod.negative = true;
		return fprod;
	}
	else
	{
		int precision = (factor1.precision > factor2.precision) ? factor2.precision : factor1.precision;
		int dplace = factor1.getDecimalLength() + factor2.getDecimalLength();

		AInt total = 0;

		for (long long i = 0; i < factor2.getLength(); i++)
		{
			std::string sum(i, '0');
			int carry = 0;

			for (long long j = 0; j < factor1.getLength(); j++)
			{
				int mul = (factor1.data[factor1.getLength() - 1 - j] - '0') * (factor2.data[factor2.getLength() - 1 - i] - '0') + carry;
				int pmul = mul % 10;

				sum.append(std::to_string(pmul));
				carry = std::floor(mul / 10);
			}

			if (carry != 0) sum.append(std::to_string(carry));

			std::reverse(sum.begin(), sum.end());
			total = total + AInt(sum);
		}
		
		std::string strfprod = total.getString();
		while ((int) strfprod.length() - (int) dplace <= 0) strfprod = '0' + strfprod;
		ADecimal fprod = toADecimal(strfprod);
		fprod.decimalplace = strfprod.length() - dplace;
		fprod.setPrecision(precision);

		return fprod;
	}
}

ADecimal ADecimal::operator/(const ADecimal& divisor) {
	return ADecimal();
}

ADecimal& ADecimal::operator-() {
	this->negative = !this->negative;
	return *this;
}

ADecimal& ADecimal::operator()(int p) {
	this->setPrecision(p);
	return *this;
}

bool ADecimal::operator>(const ADecimal& comp) {
	if (!negative && comp.negative) return true;
	else if (decimalplace < comp.decimalplace && !negative) return false;
	else if (decimalplace < comp.decimalplace && negative) return true;
	else if (decimalplace > comp.decimalplace && negative) return false;
	else if (decimalplace > comp.decimalplace && !negative) return true;
	else if(negative && comp.negative) for (unsigned int i = 0; i < getLength(); i++) if ((data[i] - '0') < (comp.data[i] - '0')) return true;
	for (unsigned int i = 0; i < getLength(); i++) if ((data[i] - '0') > (comp.data[i] - '0')) return true;
	return false;
}

bool ADecimal::operator<(const ADecimal& comp) {
	return !(*this > comp);
}

bool ADecimal::operator>=(const ADecimal& comp) {
	return *this > comp || *this == comp;
}

bool ADecimal::operator<=(const ADecimal& comp) {
	return *this < comp || *this == comp;
}

bool ADecimal::operator==(const ADecimal& comp) {
	if (negative != comp.negative) return false;
	else if (decimalplace != comp.decimalplace) return false;
	else if (getLength() != comp.getLength()) return false;
	else if (data != comp.data) return false;
	return true;
}

bool ADecimal::operator!=(const ADecimal& comp) {
	return !(*this > comp);
}

void ADecimal::setPrecision(const unsigned& precision) {
	if (this->precision < precision) {
		while (getDecimalLength() > precision) data.resize(data.length() - 1);
		this->precision = precision;
	}
	else {
		data.resize(precision + decimalplace);
		this->precision = precision;
	}
}

unsigned ADecimal::getLength() const { 
	return data.length(); 
}

unsigned ADecimal::getDecimalLength() const { 
	return getLength() - decimalplace; 
}

std::string ADecimal::getString() { 
	return data; 
}

std::string ADecimal::getFString() {
	std::string snum = data;
	while (snum[snum.length() - 1] == '0' && snum.length() > decimalplace) snum.resize(snum.length() - 1);
	if (decimalplace != getLength()) snum.insert(snum.begin() + decimalplace, '.');
	return ((negative) ? "-" : "") + snum;
}

ADecimal ADecimal::toADecimal(const char* num) {
	return ADecimal(ADecimal::Literal{}, num);
}

ADecimal ADecimal::toADecimal(std::string num) {
	return ADecimal(ADecimal::Literal{}, num.c_str());
}