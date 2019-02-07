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
	auto start = chrono::high_resolution_clock::now();
	
	cout << 14_ai % 5 << endl;

	auto stop = chrono::high_resolution_clock::now();
	cout << chrono::duration_cast<chrono::milliseconds>(stop - start).count() << endl;

	system("PAUSE");
 	return 0;
}