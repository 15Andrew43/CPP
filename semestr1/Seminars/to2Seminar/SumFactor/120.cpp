#include <iostream>

using namespace std;

int main()
{
    int n;
    float s=1, k=1;

    cin >> n;

    for(int i=1; i<=n; ++i)
    {
        k /= i;
        s += k;
    }

    cout << s << endl;
    return 0;
}