#include <iostream>

using namespace std;

int main() {
    int now, ans=1, k=1, previous;

    cin >> previous;

    while (cin >> now && now != 0)
    {
        if (previous == now)
            k++;
        else
            k = 1;
        if (ans < k)
            ans = k;
        previous = now;
    }

    cout << ans << endl;
    return 0;
}