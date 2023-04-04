#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    int **p = new int *[n];
    for (int i = 0; i <n; ++i){
        p[i] = new int [m+1];
    }

    int start = 0, end = m-1;
    int k = 1;
    int count = 0;
    for (int i = 0; i < n; ++i){
        for (int j = start; (start == 0 ? j <= end : j >= end); j += k){
            p[i][j] = count++;
        }
        if (start != end) {
            k *= (-1);
            swap(start, end);
        }
    }

    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j){
            cout << setw(3) << p[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}