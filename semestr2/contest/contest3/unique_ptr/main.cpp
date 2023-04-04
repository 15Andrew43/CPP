#include <iostream>
#include "unique_ptr.h"

using namespace std;

struct A {
    int x;
    double y;

    explicit A(int x = 0, double y = 0.0) : x(x), y(y) {
    }
};


int main() {
    UniquePtr<A> a(new A);
    cout << (a->x == 0) << '\n';
    cout << ((*a).x == 0.0) << '\n';

    return 0;
}