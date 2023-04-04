#include <iostream>

using namespace std;

int main() {
    int n, a;
    cin >> n;
    int Numbers[n];

    for (int i = 0; i < n; ++i)
    {
        cin >> a;
        Numbers[(i+1)%n] = a;
    }

    for (int i = 0; i < n; ++i)
    {
        cout << Numbers[i] << " ";
    }
    return 0;
}