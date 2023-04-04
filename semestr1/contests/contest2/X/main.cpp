#include <iostream>

using namespace std;

int main() {
    char S[100];
    char T[100];
    int lenS = strlen(S);
    int lenT = strlen(T);
    cin >> S >> T;
    char ***F = new char** [lenS+1];
    for (int i = 0; i < lenS; ++i) {
        F[i] = new char * [lenT+1];
        for (int j = 0; j < lenT; ++j) {
            F[i][j] = new char[80];
        }
    }

    for (int i = 1; i < lenS; ++i) {
        if (F[0][1] > 'a'  )
        F[i][0]
    }

    return 0;
}