#include <iostream>

using namespace std;

void sift_down(long int *a, long int *end, long int i);
void build_heap(long int *beg, long int *end);
void heap_sort(long int *beg, long int *end);

int main() {
    long int n, m;
    cin >> n;
    long int *array = new long int[n+1];

    for (long int i = 1; i < n+1; ++i) {
        cin >> array[i];
    }

    heap_sort(array, array+n);

    for (long int i = 1; i < n+1; ++i) {
        cout << array[i] << ' ';
    }
    return 0;
}

void sift_down(long int *beg, long int *end, long int i) {
    long int L = 2*i;
    long int R = 2*i+1;
    long int max;
    long int n = end-beg;
    if (L <= n && *(beg+L) > *(beg+i)){
        max = L;
    }
    else {
        max = i;
    }
    if  (R <= n && *(beg+R) > *(beg+max)) {
        max = R;
    }
    if (max != i) {
        swap(*(beg+i), *(beg+max));
        sift_down(beg, end, max);
    }
}

void build_heap(long int *beg, long int *end) {
    long int n = end-beg;

    for (long int i = n/2; i >= 1; --i) {
        sift_down(beg, end, i);
    }
}

void heap_sort(long int *beg, long int *end) {

    build_heap(beg, end); //работате правильно

    long int l = end-beg;// реальное количество элементов
    long int n = l;


    for (long int i = l; i >= 2; --i) {
        swap(*(beg+1), *(beg+i));
        sift_down(beg, --end, 1);
    }
}