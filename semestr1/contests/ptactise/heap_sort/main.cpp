#include <iostream>

using namespace std;

int parent(int i) {
    return (i-1)/2;
}
int LeftChild(int i) {
    return 2*i+1;
}
int RightChild(int i) {
    return 2*i+2;
}

void sift_down(int *a, int n, int i) {
    int L = LeftChild(i);
    int R = RightChild(i);
    int max;

    if (L < n && a[L] > a[i]) {
        max = L;
    }
    else {
        max = i;
    }
    if (R < n && a[R] > a[max]) {
        max = R;
    }
    if (max != i) {
        swap(a[i], a[max]);
        sift_down(a, n, max);
    }
}

void sift_up(int *a, int n, int i) {
    int P = parent(i);
    if (i > 0 && P < a[i]) {
        swap(a[P], a[i]);
        sift_up(a, n, P);
    }
}

void build_heap(int *a, int n) {
    for (int i = n/2; i >= 0; --i) {
        sift_down(a, n, i);
    }
}

void heap_sort(int *a, int n) {
    build_heap(a, n);

    for (int i = n-1; i > 0; --i) {
        swap(a[i], a[0]);
        sift_down(a, i, 0);
    }
}

int main() {
    int n;
    cin >> n;
    int *a = new int [n];
    for (int i = 0 ; i < n; ++i) {
        cin >> a[i];
    }

    heap_sort(a, n);

    for (int i = 0 ; i < n; ++i) {
        cout << a[i];
    }
    delete []a;
    return 0;
}