#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;
    int *array = new int[n];
    int *IncreasingSequence = new int [n];

    for (int i = 0; i < n; ++i) {
        cin >> array[i];
        IncreasingSequence[i] = 1;
    }

    int amount = 1;
    for (int i = 1; i < n; ++i) {
        for (int j = i-1; j >= 0; --j) {
            if (array[j] < array[i]) {
                IncreasingSequence[i] += IncreasingSequence[j];
                IncreasingSequence[i] %= 1000000;
            }
        }
        amount += IncreasingSequence[i];
        amount %= 1000000;
    }

    cout << amount;

    delete []array;
    delete []IncreasingSequence;
    return 0;
}