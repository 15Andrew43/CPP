#include <iostream>
#include <cmath>
using namespace std;

int main() {

    int n, m;
    cin >> n >> m;
    cout << ((abs(n)>=abs(m) && !(n%m)) || (abs(m)>=abs(n) && !(m%n))) << endl;

    return 0;
}