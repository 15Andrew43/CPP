#include <iostream>

using namespace std;

int NOP(int * x, int * y, int * path, int n, int m) {

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

    for (int i = 0; i < k/2; ++i) {
        swap(path[i], path[k-i-1]);
    }

    for (int i = 0; i < k; ++i) {
        cout << path[i] << ' ';
    }

    for (int i = 0; i < n+1; ++i) {
        delete []array[i];
    }
    return k;
}

void NVP(int * array, int n, int *ans) {

    int * MaxLen = new int [n];
    int * path = new int [n];


    for (int i = 0; i < n; ++i) {
        MaxLen[i] = 1;
        path[i] = -1;
    }

    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (array[i] > array[j]) {
                if (MaxLen[i] <= MaxLen[j]) {
                    MaxLen[i] = MaxLen[j]+1;
                    path[i] = j;
                }
            }
        }
    }

    int maxlen = MaxLen[0];
    int position = n-1;
    for (int i = 0; i < n; ++i) {
        if (MaxLen[i] > maxlen) {
            maxlen = MaxLen[i];
            position = i;
        }
    }

    int k = 0;
    while (path[position] != -1) {
        ans[k++] = array[position];
        position = path[position];
    }
    ans[k] = array[position];

    for (int i = 0; i < k/2; ++i) {
        swap(ans[i], ans[k-i-1]);
    }

    for (int i = 0; i < k; ++i) {
        cout << ans[i] << ' ';
    }

    delete []MaxLen;
    delete []path;
}

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

    int *path = new int [n];
    int k = NOP(x, y, path, n, m);

    cout << endl;

    int * ans = new int [n];
    NVP(path, k, ans);

    cout <<  endl << k << endl;

    for (int i = 0; i < k; ++i) {
        cout << ans[i] << ' ';
    }
    return 0;
}