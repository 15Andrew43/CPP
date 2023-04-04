#include <iostream>

using namespace std;

int main() {
    unsigned int x;
    unsigned int y;
    unsigned int p;
    unsigned int ans;
    int deg_now = 1;
    int deg_plus = 1;
    int mnosh = 1;

    cin >> x >> y >> p;
    x %= p;
    ans = x;

    while (deg_now < y){
        if (y >= deg_now + deg_plus) {
            ans *= mnosh;
            mnosh *= 2;
            deg_plus *= 2;
        }
        else {
            mnosh /= 2;
        }
        ans %= p;
    }

    cout << ans;

    return 0;
}