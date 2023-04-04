#include <iostream>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    int * weight = new int [n+1];
    int * price = new int [n+1];
    for (int i = 1; i <= n; ++i) {
        cin >> weight[i];
    }
    for (int i = 1; i <= n; ++i) {
        cin >> price[i];
    }

    int* *d = new int* [n+1];
    for (int i = 0; i <= n; ++i) {
        d[i] = new int [m+1];
        d[i][0] = 0;
    }

    for (int i = 0; i <= m; ++i) {
        d[0][i] = 0;
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (j-weight[i] >= 0)
                d[i][j] = max(d[i-1][j], price[i] + d[i-1][j-weight[i]]);
            else
                d[i][j] = d[i-1][j];
        }
    }

    /*
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            cout << d[i][j] << ' ';
        }
        cout << endl;
    }
    */
    int *path = new int [n+1];
    int position = 0;
    int i = n;
    int j = m;
    while (i && j) {
        if (d[i][j] != d[i-1][j]) {
            path[position++] = i;
            j -= weight[i];
        }
        i--;
    }
    position--;
    for (int i = position; i >= 0; --i) {
        cout << path[i] << ' ';
    }
    return 0;
}