#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    int n, m;
    cin >> n;
    int **p = new int *[2*n+1];
    for (int i = 0; i < 2*n+1; ++i){
        p[i] = new int [2*n+1];
    }
    p[n][n] = 0;
    p[n-1][n] = 1;
    int L = 1;
    int count = 0;
    int x = n, y = n, k = -1;

    while (L < 2*n+1){
        for(int i = 0; i < L; ++i){
            p[x][y] = count++;
            x += k;
        }
        for(int i = 0; i < L; ++i){
            p[x][y] = count++;
            y += k;
        }
        k *= (-1);
        L++;
    }
    for (int y = 2*n; y >=0; --y){
        p[y][2*n]=count++;
    }

    for (int i = 0; i < 2*n+1; i++){
        for (int j = 0; j < 2*n+1; ++j){
            cout <<  setw(3) <<p[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}