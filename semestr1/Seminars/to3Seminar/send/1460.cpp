#include <iostream>

using namespace std;

int gcd(int a, int b);

int main() {
    int n, k;
    cin >> n;
    int Numbers[n];

    for (int i = 0; i < n; ++i)
    {
        cin >> Numbers[i];
    }

    cin >> k;
    k = ((k%n)+n)%n;

    int ind = 0, end = gcd(n, k);
    int previous = Numbers[0], help;
    int start = 0;

    while (start != end){
        ind = (ind + k) % n;
        swap(Numbers[ind], previous);
        if (ind == start){
            start++;
            previous = Numbers[++ind];
        }
    }


    for (int i = 0; i < n; ++i){
        cout << Numbers[i] << " ";
    }

    return 0;
}

int gcd(int a, int b){
    while (a && b){
        a=a%b;
        swap(a, b);
    }
    return a;
}