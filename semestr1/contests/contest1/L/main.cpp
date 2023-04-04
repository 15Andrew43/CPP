#include <iostream>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    // birth arr
    int **p = new int *[n+1];
    for (int i = 0; i < n+1; ++i){
        p[i] = new int [m+1];
    }

// ввод вмассива + окруж5не сверху и справа нулями
    for (int i = 0; i < m+1; ++i){
        p[0][i] = 0;
    }
    for (int i = 1; i < n+1; ++i){
        p[i][0] = 0;
        for (int j = 1; j < m+1; ++j){
            cin >> p[i][j];
        }
    }


// обработка
    for (int i = 1; i < n+1; ++i){
        for (int j = 1; j < m+1; ++j){
            p[i][j] = p[i][j] + (p[i-1][j] + p[i][j-1] - p[i-1][j-1]);
        }
    }

//вывод
    for (int i = 1; i < n+1; ++i){
        for (int j = 1; j < m+1; ++j){
            cout << p[i][j] << ' ';
        }
        cout << endl;
    }
// удаление массива
    for (int i = 0; i < n+1; ++i){
        delete []p[i];
    }
    return 0;
}