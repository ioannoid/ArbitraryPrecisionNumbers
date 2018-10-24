#ifndef ARBITRARYINT_H
#define ARBITRARYINT_H

#pragma once

#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <math.h>
#include <sstream>
#include <iterator>

class AInt
{
public:
	AInt() {}
	AInt(const AInt& n) : data(n.data), negative(n.negative) {}
	AInt(const char* n) : data((n[0] == '0') ? std::string(n + 1, n + std::strlen(n)) : n), negative((n[0] == '0') ? true : false) {}
	AInt(std::string n) : data((n[0] == '0') ? n.substr(1,-1) : n), negative((n[0] == '0') ? true : false) {}
	AInt(int n) : data(std::to_string(n).substr((n < 0) ? 1 : 0, -1)), negative((n < 0) ? true : false) {}
	AInt(long long int n) : data(std::to_string(n).substr((n < 0) ? 1 : 0, -1)), negative((n < 0) ? true : false) {}

	void operator=(const AInt& n);
	void operator=(const char* n);
	void operator=(std::string n);
	void operator=(long long int n);

	AInt operator+(AInt addend);
	AInt operator-(AInt subtrahend);
	AInt operator*(AInt factor);

	AInt operator+(int addend);
	AInt operator-(int subtrahend);
	AInt operator*(int factor);

	AInt operator-();

	bool operator>(AInt comp);
	bool operator<(AInt comp);
	bool operator>=(AInt comp);
	bool operator<=(AInt comp);
	bool operator==(AInt comp);
	bool operator!=(AInt comp);

	friend inline std::ostream& operator<<(std::ostream& os, const AInt& num);

	friend inline AInt operator""_ai(const char* lit);
	friend inline AInt operator""_ani(const char* lit);

	std::string getString() { return data; }
	int length() { return data.length(); }
private:
	std::string data;
	bool negative = false;
};

#endif // !ARBITRARYINT_H

inline std::ostream& operator<<(std::ostream& os, const AInt& num)
{
	os << ((num.negative) ? "-" : "") << num.data;
	return os;
}

inline AInt operator""_ai(const char* lit)
{
	return AInt(lit);
}
inline AInt operator""_ani(const char* lit)
{
	AInt n = lit;
	n.negative = true;
	return n;
}
