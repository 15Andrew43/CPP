#include <iostream>

using namespace std;

int BinSystem(int , char *);

int main() {
    int x;
    int y;
    int p;
    int ans;
    int deg_now = 1;
    int values[1000];
    int count = 1;
    char number[1000];

    cin >> x >> y >> p;
    x %= p;
    ans = 1;
    values[0] = ans;
    int i = 1;
    while (count * 2 < y){
        values[i] = (values[i-1]*values[i-1])%p;
        i++;
        count *= 2;
    }

    BinSystem(y, number);
    int L = strlen(number);

    for (int i = 0; i < L; ++i){
        if (number[i] == '1'){
            ans *= values[i];
            ans %= p;
        }
    }
    cout << ans;

    return 0;
}

void BinSystem(int y, char *number) {
    int i = 0;
    while (y != 0) {
        int z = y % 2;
        y /= 2;
        number[i] = (char)(z+48);
        i++;
    }
    number[i] = '\0';
    int L=i;
    for (int i = 0; i < L; ++i){
        cout << number[i];
    }

}