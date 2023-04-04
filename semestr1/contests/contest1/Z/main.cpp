#include <iostream>
#include <iomanip>

using namespace std;

int lf(int A, int B, int C, int D, int NatureL);
int rf(int A, int B, int C, int D, int NatureR);

int main() {
    int A, B, C, D;
    long double m = 1;
    cin >> A >> B >> C >> D;

    long double L, R;
    if (A > 0 && D > 0) {
        R = 0;
        L = lf(A, B, C, D, 0);
    }
    else if (A < 0 && D < 0) {
        R = 0;
        L = lf(A, B, C, D, 1);
    }
    else if (A > 0 && D < 0) {
        L = 0;
        R = rf(A, B, C, D, 1);
    }
    else if  (A < 0 && D > 0) {
        L = 0;
        R = rf(A, B, C, D, 0);
    }
    else {
        m = 0;
    }
    if (m != 0) {
        for (int i = 0; i < 100; ++i) {
            m = (L + R) / 2;
            if (A * m * m * m + B * m * m + C * m + D > 0) {
                if (A > 0) {
                    R = m;
                } else {
                    L = m;
                }
            }
            if (A * m * m * m + B * m * m + C * m + D < 0) {
                if (A > 0) {
                    L = m;
                } else {
                    R = m;
                }
            }
        }
        m = (L + R) / 2;
    }
    cout << fixed << setprecision(10) << m;
    return 0;
}

int lf(int A, int B, int C, int D, int NatureL) {
    int L = -10;
    int ans;
    int m = L;
    if (NatureL) {
        while (A*m*m*m + B*m*m + C*m + D < 0) {
            m *= 2;
        }
        ans = m;
    }
    else {
        while (A*m*m*m + B*m*m + C*m + D > 0) {
            m *= 2;
        }
        ans = m;
    }
    return ans;
}

int rf(int A, int B, int C, int D, int NatureR) {
    int R = 10;
    int ans;
    int m = R;
    if (NatureR) {
        while (A*m*m*m + B*m*m + C*m + D < 0) {
            m *= 2;
        }
        ans = m;
    }
    else {
        while (A*m*m*m + B*m*m + C*m + D > 0) {
            m *= 2;
        }
        ans = m;
    }
    return ans;
}