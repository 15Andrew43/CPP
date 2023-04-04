#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;
    int *x = new int [n+1];
    x[0] = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> x[i];
    }

    int m;
    cin >> m;
    int *y = new int [m+1];
    y[0] = 0;
    for (int i = 1; i <= m; ++i) {
        cin >> y[i];
    }


    int **array = new int * [n+1];
    for (int i = 0; i <= n; ++i) {
        array[i] = new int [m+1];
    }

    for (int i = 0; i <= n; ++i) {
        array[i][0] = 0;
    }
    for (int i = 0; i <=m; ++i) {
        array[0][i] = 0;
    }


    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (x[i] == y[j]) {
                array[i][j] = array[i-1][j-1] + 1;
            }
            else {
                array[i][j] = max(array[i-1][j], array[i][j-1]);
            }
        }
    }
/*
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <=m; ++j) {
            cout << array[i][j]  << ' ';
        }
        cout << endl;
    }
*/
    int *path = new int [n];
    int i = n;
    int j = m;
    int k = 0;

    while (i != 0 && j != 0) {
        if (x[i] == y[j]) {
            path[k++] = x[i];
            i--;
            j--;
        }
        else if (array[i][j] == array[i-1][j]) {
            i--;
        }
        else if (array[i][j] == array[i][j-1]) {
            j--;
        }
    }

    for (int i = k-1; i >= 0; --i) {
        cout << path[i] << ' ';
    }

    return 0;
}