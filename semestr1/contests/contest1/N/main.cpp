#include <iostream>

using namespace std;

int main() {
    int n;
    int count = 0;
    cin >> n;
    int *a = new int [n];
    for (int i = 0; i < n; ++i){
        cin >> a[i];
    }

    for (int i = 0; i < n-1; i++){
        bool check = true;
        for (int j = 0; j < n-i-1 ; j++){
            if (a[j] > a[j+1]){
                swap(a[j], a[j+1]);
                count++;
                check = false;
            }
        }
        if (check)
            break;
    }

    cout << count;

    delete []a;
    return 0;
}