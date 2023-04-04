#include <iostream>
using namespace std;

int main() {

    int a, b, c, d;
    int xz;
    float xf;
    cin >> a >> b >> c >> d;

    if (a==0)
    {
        if (b == 0 && (d != 0 || c != 0))
            cout << "INF" << endl;
        else
            cout << "NO" << endl;
    }
    else
    {
        xz=-b/a;
        xf=float(-b)/a;

        if (xf==float(-d)/c)
            cout << "NO" << endl;
        else
        {
            if (xf==xz)
                cout << xz << endl;
            else
                cout << "NO" << endl;
        }
    }

    return 0;
}