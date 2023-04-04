#include <iostream>

using namespace std;

int main() {

    int a[] = {0, 3, 4, 5};
    int n = 2;
    int l = -1;
    int r = 4;

    while (r-l > 1) {
        int m = (l + r) / 2;
        if (a[m] >= n) {
            r = m;
        } else {
            l = m;
        }

    cout << l << " " << r << endl;

    }
    return 0;
}