#include "ArbitraryInt.hpp"
#include "ArbitraryDecimal.hpp"

#include <iostream>
#include <string>
#include <cstdio>
#include <sstream>
#include <fstream>
#include <chrono>

using namespace std;

int main() {
	auto start = chrono::high_resolution_clock::now();

	ADecimal r = 31.38802_ad(10);
	ADecimal m = -65.43219_ad(4);
	ADecimal n = -8.432498899_ad;

	cout << r << ":" << m << ":" << n << endl;

	ADecimal t = m * n;

	cout << t << endl;

	auto stop = chrono::high_resolution_clock::now();
	cout << chrono::duration_cast<chrono::milliseconds>(stop - start).count() << endl;

 	return 0;
};