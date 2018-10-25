#include "ArbitraryInt.h"

#include <iostream>
#include <string>
#include <cstdio>
#include <sstream>
#include <fstream>
#include <chrono>

using namespace std;

// 999999999999999999 : 18 digits long

int main()
{
	//Test calculation to find 100000 fibonnaci number
	auto start = chrono::high_resolution_clock::now();

	AInt n1 = 1;
	AInt n2 = 1;
	AInt n3;
	for (int i = 2; i < 100000; i++)
	{
		n3 = n2 + n1;
		n1 = n2;
		n2 = n3;
	}
	cout << n3 << endl;

	auto stop = chrono::high_resolution_clock::now();
	cout << chrono::duration_cast<chrono::nanoseconds>(stop - start).count() << endl;

	system("PAUSE");

 	return 0;
}