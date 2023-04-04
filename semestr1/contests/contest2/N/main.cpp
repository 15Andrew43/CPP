#include <iostream>

using namespace std;

int RandomizedPartition(int * a, int l, int r);
void QuickSort(int * a, int l, int r);

int main() {
    int n;
    cin >> n;
    int *array = new int [n];
    for (int i = 0; i < n; i++) {
        cin >> array[i];
    }
    QuickSort(array, 0, n-1);
    for (int i = 0; i < n; i++) {
        cout << array[i] << ' ';
    }
    return 0;
}

int RandomizedPartition(int * a, int l, int r) {
    int i = rand() % (r-l+1) + l;
    swap(a[i], a[r]);
    int x = a[r];
    i = l-1;
    for (int j = l; j < r; ++j) {
        if (a[j] <= x) {
            i++;
            swap(a[i], a[j]);
        }
    }
    swap(a[i+1], a[r]);
    return i+1;
}

void QuickSort(int * a, int l, int r) {
    int pirot;
    if (l < r) {
        pirot = RandomizedPartition(a, l, r);
        QuickSort(a, l, pirot-1);
        QuickSort(a, pirot+1, r);
    }
}