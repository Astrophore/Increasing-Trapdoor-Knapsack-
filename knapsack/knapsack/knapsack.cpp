// knapsack.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <stdio.h>
#include <cmath>
#include <bitset>
#include <vector>
#include <functional>
#include <sstream>
#include <algorithm>
#include <iterator>

using namespace std;

int gcd(int a1, int a2) {
	int tmp;
	while (a2 != 0) {
		tmp = a1;
		a1 = a2;
		a2 = tmp % a2;
	}
	return a1;
}

int modInverse(int a, int b)
{
	a = a % b;
	for (int x = 1; x < b; x++)
	{
		if ((a*x) % b == 1)
			return x;
	}
}

int main()
{
    std::cout << "Hello World!\n"; 
}

