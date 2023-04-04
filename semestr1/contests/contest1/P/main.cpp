#include <iostream>
#include <algorithm>

using namespace std;

void insertion_sort(int *a, int n);

int main() {
    int n;
    long long int x;
    cin >> n >> x;
    int a, b, c;
    int *array = new int [n];

    for (int i = 0; i < n; ++i){
        cin >> array[i];
    }

    insertion_sort(array, n);

    long long int min = 1000000001;
    for (int i = 0; i < n-1; ++i){
        for (int j = i+1; j < n; ++j){
            int l = -1;
            int r = n;
            int find = x-array[i]-array[j];
      //      cout << find << "------------------"<< endl;
//binresearch
            while (r-l > 1) {
                int m = (l + r) / 2;
                if (array[m] >= find) {
                    r = m;
                } else {
                    l = m;
                }
            }

            for (int k = l - 2; k < l + 3; ++k) {
                if (k >= 0 && k < n && k != i && k != j) {
                    if (abs(array[k] - find) < min) {
                        min = abs(array[k] - find);
                        c = k;
                        a = i;
                        b = j;
                    }
                }
            }
   //         cout << a << " " << b << " " << c << endl;
        }
    }


    cout << array[a] << " " << array[b] << " " << array[c];
    return 0;
}

void insertion_sort(int *a, int n) {

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
}
