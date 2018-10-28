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

	/*AInt n1 = 1;
	AInt n2 = 1;
	AInt n3;
	for (int i = 2; i < 10000; i++)
	{
		n3 = n2 + n1;
		n1 = n2;
		n2 = n3;
	}
	cout << n3 << endl;*/

	cout << 13908178903981290898023178902789310789213789_ai + 78392183093768128739810237293219_ai << endl;

	auto stop = chrono::high_resolution_clock::now();
	cout << chrono::duration_cast<chrono::milliseconds>(stop - start).count() << endl;

 	return 0;
}