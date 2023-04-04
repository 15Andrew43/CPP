#include <iostream>
#include <cmath>

using namespace std;

bool IsBeaut(int x, int y, int m, int *X, int *Y){
    for (int i = 0; i < m; ++i){
        X[i] = x % 2;
        x /= 2;
        Y[i] = y % 2;
        y /= 2;
        if (i > 0 && X[i] == X[i - 1] && X[i] == Y[i] && Y[i] == Y[i - 1]){
            return true;
        }
    }
    return false;
}

int main(){
    int m, n;
    cin >> m >> n;

    if (m > n) {
        swap(n, m);
    }

    int *X = new int[30];
    int *Y = new int[30];

    long long res[40][200];
    int maxSize = pow(2, m);
    for (int i = 0; i < maxSize; ++i) {
        res[1][i] = 1;
    }

    for (int i = 2; i < n + 1; ++i) {
        for (int j = 0; j < maxSize; ++j) {
            for (int y = 0; y < maxSize; ++y) {
                if (!IsBeaut(j, y, m, X, Y)) {
                    res[i][y] = res[i][y] + res[i - 1][j];
                }
            }
        }
    }

    long long result = 0;
    for (int i = 0; i < maxSize; ++i) {
        result += res[n][i];
    }

    cout << result;

    delete[] X;
    delete[] Y;
    return 0;
}