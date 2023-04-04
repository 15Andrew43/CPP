#include <iostream>

using namespace std;

int main() {
    int n;
    int max1 = -30001, max2 = -30001, max3 = -30001;
    int min1 = 30001, min2 = 30001;
    cin >> n;
    int *a = new int [n];

    for(int i = 0;  i < n; ++i){
        cin >> a[i];
    }

    for (int i = 0; i < n; ++i){
        if (a[i] >= max3){
            if (a[i] >= max1) {
                max3 = max2;
                max2 = max1;
                max1 = a[i];
            }
            else if (a[i] >= max2){
                max3 = max2;
                max2 = a[i];
            }
            else {
                max3 = a[i];
            }
        }
        if (a[i] <= min2){
            if (a[i] <= min1) {
                min2 = min1;
                min1 = a[i];
            }
            else {
                min2 = a[i];
            }
        }
        cout << max1 << " " << max2 << " " << max3 << endl;
        cout << min1  << " " << min2 << endl << endl;
    }

    if (min1*min2*max1 > max2*max3*max1){
        cout << min1 << " " << min2 << " " << max1;
    }
    else {
        cout << max3 << " " << max2 << " " << max1;
    }

    delete []a;
    return 0;
}