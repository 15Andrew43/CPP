#include <iostream>

int Max(int lhs, int rhs) {
	std::cout << "Max(int, int)\n";
	return (lhs > rhs) ? lhs : rhs;
}
int Min(int lhs, int rhs) {
	return (lhs < rhs) ? lhs : rhs;
}
int Abs(int x);