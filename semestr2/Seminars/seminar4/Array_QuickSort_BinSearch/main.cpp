#include <iostream>

#include "array.h"

#include "quicksort.h"

int main() {
	Array<int, 3> a;
	a[0] = 1;
	a[1] = 1;
	a[2] = 2;
	Array<int, 3> b;
	b[0] = 0;
	b[1] = 1;
	b[2] = 2;
	std::cout << (a != b) << '\n';
	std::cout << a.Front() << '\n';
	int* ptr = a.Begin();
	std::cout << *(ptr+1) << '\n';
	a.Fill(7);
	std::cout << "sdvwvcwd\n";
	std::cout << a[0] << '\n';
}