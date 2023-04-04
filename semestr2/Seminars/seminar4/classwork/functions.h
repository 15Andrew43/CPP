#ifndef F_H
#define F_H
#include <iostream>

template <class T>
T Max(T lhs, T rhs) {
	std::cout << "Max(T, T)\n";
	return (lhs > rhs) ? lhs : rhs;
}

template <typename U>
U Min(U lhs, U rhs) {
	(lhs < rhs) ? lhs : rhs;
}

template <class T>
int Abs(T x) {
	return (x > 0) ? x : -x;
}

int Max(int lhs, int rhs);
int Min(int lhs, int rhs);
int Abs(int x);

#endif