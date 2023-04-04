#include <iostream>

using namespace std;

int f1() {
    return 11111;
}

int f2() {
    return 22222;
}

int f3() {
    return 33333;
}

int f4() {
    return 44444;
}

int f5() {
    return 55555;
}

int main() {
    cout << "Hello, World!" << endl;

    int (*pf[5])()  = {&f1, &f2, &f3, &f4, &f5};
    for (int i = 0; i < 5; ++i) {
        cout << pf[i]() << ' ';
    }
    return 0;
}