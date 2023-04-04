#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    int xa, ya, xb, yb;
    long double ans;
    cin >> xa >> ya >> xb >> yb;

    if (xa != xb) {
        yb = -yb;
        long double k = (long double)(yb - ya) / (xb - xa);
        long double b = ya - k * xa;
        ans = (long double)(-b) / k;
    }
    else {
        ans = xa;
    }

    cout << fixed << setprecision(9) << ans << endl;
    return 0;
}