#include <iostream>

using namespace std;

int main() {
    int a;
    int sum = 0;
    cin >> a;

    sum += a%10;
    a /= 10;
    sum += a%10;
    a /= 10;
    sum += a%10;

    cout<< sum<< endl;
    return 0;
}