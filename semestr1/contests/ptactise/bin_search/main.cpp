#include <iostream>

using namespace std;

int binary_search(int *a, int n, int x) {
    int l = 0;
    int r = n;
    while (r-l > 1) {
        int m = (r+l)/2;
        if (a[m] <= x) {
            l = m;
        }
        else {
            r = m;
        }
    }
    return l;
}

int main() {
    int a[] = {0, 3, 4, 5, 6, 6, 6, 6, 9, 10, 15, 20, 21};

    cout << binary_search(&a[0], 13, 21);
    return 0;
}