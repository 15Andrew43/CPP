#include <iostream>

using namespace std;

int Partition(int *a, int l, int r) {
    int i = (r-l)/2;
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

void quick_sort(int *a, int l, int r) {
    int pirot;
    if (l<r) {
        pirot = Partition(a, l, r);
        quick_sort(a, l, pirot-1);
        quick_sort(a, pirot+1, r);
    }
}

int main() {

    return 0;
}