#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    int column, j = 31;
    cin >> column;

    for (int i = 32; i < 31 + 96/column; ++i){
        for (int j = i; j < 128; j = j + 96/column){
            cout << setw(3) << j << " -" << setw(2) << char(j) << "    ";
        }
        cout << endl;
    }

    return 0;
}