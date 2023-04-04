#include <iostream>
#include <cstring>

using namespace std;

int main() {
    char a[256];
    int ind;
    bool t = false, T = false;
    cin >> a;
    int L = strlen(a);
    for (int i = 1; i < L; ++i) {
        if (i+1 < L && a[i-1] == a[i+1]) {
            ind = i;
            t = true;
            break;
        }
        else if (a[i] == a[i-1]) {
            ind = i;
            T = true;
            break;
        }
    }

    if (t) {
        cout << a[ind-1] << a[ind] << a[ind+1];
    }
    else if (T) {
        cout << a[ind-1] << a[ind];
    }
    else {
        cout << 0;
    }
    return 0;
}