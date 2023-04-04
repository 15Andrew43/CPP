#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;
    int *array = new int [n];
    array[0] = 0;
    int a, b, c;
    for (int i = 1; i < n; ++i) {
        a = 1000001;
        b = 1000001;
        c = 1000001;

        if ((i+1) % 2 == 0) {
            a = array[(i+1) / 2 -1];
        }
        if ((i+1) % 3 == 0) {
            b = array[(i+1) / 3 -1];
        }
        c = array[i-1];

        array[i] = min(min(a, b), c)+1;
    }

    cout << array[n-1];
            return 0;
}