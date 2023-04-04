#include <iostream>

using namespace std;


int main() {
    int a, max = -1, Max=-1;

    while (cin >> a && a != 0)
    {
        if (max < a) {
            if (Max < a) {
                max = Max;
                Max = a;
            }
            else
                max = a;

        }
    }

    cout << max << endl;
    return 0;
}