#include <iostream>

using namespace std;

int main() {
    int r, c;
    int d;
    int inconvenience;
    int ans = 0;
    cin >> r >> c;
    int start, end;
    int n = r*c;
    int *a = new int[n];

    for(int i = 0; i < n; ++i){
        cin >> a[i];
    }

    for (int i = 0; i < n-1; i++){
        bool check = true;
        start = ( (i % 2 == 0) ? (i/2) : (n-i/2-2) );
        end = ( (i % 2 == 0) ? (n - i/2 - 1) : (i/2) );
        d = ( (i % 2 == 0) ? (1) : (-1) );

        for (int j = start; ((i%2==0) ? (j < end) : (j >= end)); j += d){
            if (a[j] > a[j+1]){
                swap(a[j], a[j+1]);
                check = false;
            }
        }

        if (check)
            break;
    }

    for (int i = 0; i < n; i+=c){
        inconvenience = a[i+c-1] - a[i];
        if (ans < inconvenience){
            ans = inconvenience;
        }
    }
    cout << ans;
    delete []a;
    return 0;
}