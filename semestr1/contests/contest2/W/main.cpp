#include <iostream>
#include <cstring>

using namespace std;

int main() {
    char str1[1001];
    char str2[1001];
    cin >> str1 >> str2;
    int a = strlen(str1);
    int b = strlen(str2);

    int **array = new int* [a+1];
    for (int i = 0; i < a+1; ++i) {
        array[i] = new int [b+1];
        array[i][0] = i;
    }
    for (int i = 0; i < b+1; ++i) {
        array[0][i] = i;
    }


    for (int i = 1; i < a+1; ++i) {
        for (int j = 1; j < b+1; ++j) {
            if (str1[i-1] == str2[j-1]) {
                array[i][j] = min(min(array[i-1][j]+1, array[i][j-1]+1), array[i-1][j-1]);
            }
            else {
                array[i][j] = min(min(array[i-1][j]+1, array[i][j-1]+1), array[i-1][j-1]+1);
            }
        }
    }

    cout << array[a][b];

    for (int i = 0; i < a+1; ++i) {
        delete []array[i];
    }
    delete []array;
    return 0;
}