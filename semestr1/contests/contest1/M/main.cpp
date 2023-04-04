#include <iostream>

using namespace std;

void f(unsigned long long int **p, unsigned long long int **q, int n);

int main() {
    int n;
    unsigned long long int d;
    cin >> n >> d;
    unsigned long long int **M = new unsigned long long int*[n];
    unsigned long long int **ans = new unsigned long long int *[n];
    unsigned long long int **m = new unsigned long long int *[n];
    for (int i = 0; i < n; ++i) {
        M[i] = new unsigned long long int[n];
        ans[i] = new unsigned long long int[n];
        ans[i][i] = 1;
        m[i] = new unsigned long long int[n];
    }


    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> M[i][j];
            m[i][j] = M[i][j];
        }
    }


    while (d) {
        short int z = d%2;
        d /= 2;
        if (z == 1) {
            //ans *= m;
            f(ans, m, n);
        }
        //m *= m;
        f(m, m, n);
    }

    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            cout << ans[i][j] << ' ';
        }
        cout << endl;
    }

    for (int i = 0; i < n; ++i){
        delete []M[i];
        delete []ans[i];
        delete []m[i];
    }
    delete[]M;
    delete[]ans;
    delete[]m;
    return 0;
}

void f(unsigned long long int **p, unsigned long long int **q, int n) {
    if (p != q) {
        unsigned long long int *str = new unsigned long long int[n];

        for (int k = 0; k < n; ++k) {
            for (int i = 0; i < n; ++i) {
                unsigned long long int s = 0;
                for (int j = 0; j < n; ++j) {
                    s += (p[k][j] * q[j][i]);
                }
                str[i] = s;
            }
            for (int i = 0; i < n; ++i){
                p[k][i] = str[i];
            }
        }
        delete []str;
    }
    else {
        unsigned long long int **m_m = new unsigned long long int*[n];
        for (int i = 0; i < n; ++i){
            m_m[i] = new unsigned long long int[n];
        }

        for (int k = 0; k < n; ++k) {
            for (int i = 0; i < n; ++i) {
                unsigned long long int s = 0;
                for (int j = 0; j < n; ++j) {
                    s += (p[k][j] * q[j][i]);
                }
                m_m[k][i] = s;
            }
        }

        for (int i = 0; i < n; ++i){
            for (int j = 0; j < n; ++j){
                p[i][j] = m_m[i][j];
            }
        }

        for (int i = 0; i < n; ++i){
            delete []m_m[i];
        }
        delete []m_m;
    }
}