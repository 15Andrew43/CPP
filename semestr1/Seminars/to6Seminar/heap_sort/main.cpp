#include <iostream>

using namespace std;

void sift_down(long int *a, long int n, long int i);
void build_heap(long int *a, long int n);
void heap_sort(long int *a, long int n);

int main() {
    long int n;
    cin >> n;
    long int *array = new long int[n+1];
    array[0] = 1543;
    for (long int i = 1; i < n+1; ++i) {
        cin >> array[i];
    }

    heap_sort(array, n);

    for (long int i = 1; i < n+1; ++i) {
        cout << array[i] << ' ';
    }
    return 0;
}

void sift_down(long int *a, long int n, long int i) {
    long int L = 2*i;
    long int R = 2*i+1;
    long int max;
    if (L <= n && a[L] > a[i]){
        max = L;
    }
    else {
        max = i;
    }
    if  (R <= n && a[R] > a[max]) {
        max = R;
    }
    if (max != i) {
        swap(a[i], a[max]);
        sift_down(a, n, max);
    }
}

void build_heap(long int *a, long int n) {
    for (long int i = n/2; i >= 1; --i) {
        sift_down(a, n, i);
    }
}

void heap_sort(long int *a, long int n) {
    build_heap(a, n);

    long int l = n;
    for (long int i = l; i >= 2; --i) {
        swap(a[1], a[i]);
        n--;
        sift_down(a, n, 1);
    }
}