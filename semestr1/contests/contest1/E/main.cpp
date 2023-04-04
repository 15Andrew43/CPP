#include <iostream>

using namespace std;

int main() {
    int now;
    int previous;
    int count = 0;
    bool help = false;
    cin >> previous;

    while (cin >> now, now != 0){
        if (now > previous){
            help = true;
        }
        else {
            if (help && now != previous){
                count++;
            }
            help = false;
        }
        previous = now;
    }

    cout << count;
    return 0;
}