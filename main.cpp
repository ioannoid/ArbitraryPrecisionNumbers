#include "ArbitraryInt.h"

#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

int main()
{
	AInt a = 111111111111_ai;
	AInt b = 111111111111_ai;

	cout << a << "," << b <<endl;

	AInt c  = a * b;
	cout << c << endl;

 	return 0;
}