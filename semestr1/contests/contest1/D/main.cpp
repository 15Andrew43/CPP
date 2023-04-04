#include <iostream>

using namespace std;

int main() {
    long int x, y;
    cin >> x >> y;
    long int p = x*y;

    while (y!=0){
        x = x%y;
        swap(x, y);
    }
    cout << x << endl;
    cout << p/x;

    return 0;
}