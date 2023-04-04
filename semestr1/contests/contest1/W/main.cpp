#include <iostream>

using namespace std;

void hanoi(int n, int from, int to, int additional);

int main() {
    int n;
    cin >> n;
    hanoi(n,1,2,3);
    return 0;
}

void hanoi(int n, int from, int to, int additional) {
    if (n == 0) {
        return;
    }
    hanoi(n-1, from, additional, to);
    cout << from << " " << to << endl;
    hanoi(n-1, additional, to, from);
}