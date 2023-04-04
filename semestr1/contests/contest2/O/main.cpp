#include <iostream>

using namespace std;

int main() {
    long long int n, k, a_0, a_1;
    cin >> n >> k >> a_0 >> a_1;
    long long int a_2;
    int count = 0;

    long long int *A = new long long int[10000000+4321];
    for (int i = 0; i < 10000000+4321; ++i) {
        A[i] = 0;
    }
    A[a_0] = 1;
    A[a_1] = 1;


    for (int i = 2; i < n; ++i) {
        a_2 = (a_1*123 + a_0*45)%(10000000+4321);
        a_0 = a_1;
        a_1 = a_2;
        A[a_2]++;
    }

    for (int i = 0; i < 10000000+4321; ++i) {
        if (A[i]) {
            count += A[i];
            if (count >= k) {
                cout << i;
                break;
            }
        }
    }

    delete []A;
    return 0;
}