#pragma once

#include <iostream>
#include <string>
#include <string_view>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <math.h>
#include <sstream>
#include <iterator>

#include "ArbitraryInt.hpp"

//yoo bitch wassup cutie

class ADecimal
{
private:
	class Literal {};
public:
	ADecimal() {}
	ADecimal(const ADecimal& n) : data(n.data), negative(n.negative), decimalplace(n.decimalplace), precision(n.precision) {}
	ADecimal(Literal, std::string_view num);

	ADecimal& operator=(const ADecimal& n);

	ADecimal operator+(const ADecimal& addend);
	ADecimal operator-(const ADecimal& rsubtrahend);
	ADecimal operator*(const ADecimal& factor);
	ADecimal operator/(const ADecimal& divisor);

	ADecimal operator-();
	ADecimal& operator()(int p);

	bool operator>(const ADecimal& comp);
	bool operator<(const ADecimal& comp);
	bool operator>=(const ADecimal& comp);
	bool operator<=(const ADecimal& comp);
	bool operator==(const ADecimal& comp);
	bool operator!=(const ADecimal& comp);

	void setPrecision(const unsigned& precision);

	unsigned getLength() const;
	unsigned getDecimalLength() const;
	std::string getString();
	std::string getFString();

	static ADecimal toADecimal(const char* num);
	static ADecimal toADecimal(std::string num);

	friend inline std::ostream& operator<<(std::ostream& os, const ADecimal& num);
	friend inline ADecimal operator""_ad(const char* lit);

private:
	std::string data;
	bool negative = false;
	unsigned int decimalplace;
	unsigned int precision;
};

std::ostream& operator<<(std::ostream& os, const ADecimal& num) {
	std::string snum = num.data;
	while (snum[snum.length() - 1] == '0' && snum.length() > num.decimalplace) snum.resize(snum.length() - 1);
	if(num.decimalplace != num.getLength()) snum.insert(snum.begin() + num.decimalplace, '.');
	os << ((num.negative) ? "-" : "") << snum;
	return os;
}

ADecimal operator""_ad(const char* lit) {
	return ADecimal(ADecimal::Literal{}, lit);
}
