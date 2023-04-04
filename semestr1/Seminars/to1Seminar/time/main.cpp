#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    int s, m, h;
    cin >> s;
    s=s%(24*60*60);
    h=(s/(60*60));
    m=(s-h*60*60)/60;
    s=s%60;
    cout << h << ":" << setfill('0')  << setw(2) << m << ":" << setfill('0')  << setw(2) << s << endl;

    return 0;
}