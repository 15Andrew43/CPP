#include <iostream>
using namespace std;

struct Point
{
    int x, y;
} p1 = {1,2}, p2, p3, *pp = &p2, a[10] = {p1, p2, p3};

struct A {
	char c;
	int x;
	double d;
};

int main() {
	cout << sizeof(A::c) +
	        sizeof(A::x) +
	        sizeof(A::d)
	     << endl; // 13
	cout << sizeof(A) << endl; // 16

}

