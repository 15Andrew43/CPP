#include <iostream>

using namespace std;

int main() {
    int n, a, b, k=1;
    cin >> n;
    int Numbers[n];

    for (int i = 0; i < n/2*2; ++i)
    {
        cin >> a;
        Numbers[i+k] = a;
        k *= -1;
    }

    if (n % 2 == 1)
    {
        cin >> a;
        Numbers[n-1] = a;
    }

    for (int i = 0; i < n; ++i)
    {
        cout << Numbers[i] << " ";
    }
    return 0;
}