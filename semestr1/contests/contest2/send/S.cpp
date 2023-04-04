#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;
    int *array = new int [n];
    for (int i = 0; i < n; ++i) {
        cin >> array[i];
    }

    int * MaxLen = new int [n];
    int * path = new int [n];
    int * ans = new int [n];

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
/*
    for (int i = 0; i < n; ++i) {
        cout << MaxLen[i] << ' ';
    }
    cout << endl;
    for (int i = 0; i < n; ++i) {
        cout << path[i] << ' ';
    }
*/
    int k = n-1;
    while (path[position] != -1) {
        ans[k--] = array[position];
        position = path[position];
    }
    ans[k] = array[position];

    for (int i = k; i < n; ++i) {
        cout << ans[i] << ' ';
    }
    return 0;
}