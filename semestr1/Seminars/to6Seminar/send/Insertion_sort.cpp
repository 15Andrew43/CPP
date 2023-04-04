#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;
    int *a = new int[n];

    for (int i = 0; i < n; i++){
        cin >> a[i];
    }

    for (int i = 0; i < n-1; i++){
        int ind = i+1;
        int l = -1;
        int r = ind;
        int m;

        while (r-l>1){
            m = (l + r)/2;
            if (a[m] >= a[ind]){
                r = m;
            }
            else{
                l = m;
            }
        }

        for (int i = ind; i > r; --i){
            swap(a[i], a[i-1]);
        }

    }

    for(int i = 0; i < n; i++){
        cout << a[i] << ' ';
    }

    delete []a;
    return 0;
}