#include <iostream>
#include <cmath>
using namespace std;


int main() {

    int X, Y, x, y;

    cin >> X >> Y >> x >> y;

    if (X==x || Y==y || abs(X-x)==abs(Y-y))
    {
        cout << "YES" << endl;
    }
    else
    {
        cout << "NO" << endl;
    }

    return 0;
}