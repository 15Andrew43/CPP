#include <iostream>
#include <cmath>

using namespace std;


int main() {

    int X, Y, x, y;

    cin >> X >> Y >> x >> y;

    if (abs(X-x)<=1 && abs(Y-y)<=1)
    {
        if (X==x && Y==y)
            cout << "NO" << endl;
        else
            cout << "YES" << endl;
    }
    else
    {
        cout << "NO" << endl;
    }

    return 0;
}