#include <iostream>
#include <vector>

template <class T>
void Partition(T* arr, int &l, int &r) {
    T middle = arr[(l + r) / 2];

    while (l <= r) {
        while (arr[l] < middle)
            ++l;
        while (arr[r] > middle)
            --r;
        if (l <= r) {
            if (l < r) {
                std::swap(arr[l], arr[r]);
            }
            ++l;
            --r;
        }
    }
}

template <class T>
void QuickSort (T* begin, T* end) {
    int l = 0;
    int r = end - begin;

    if (l < r) {
        Partition(begin, l, r);
        QuickSort(begin, begin + r);
        QuickSort(begin + l, end);
    }
}

int main() {

    int N;
    std::cin >> N;
    long long *numbers = new long long[N];
    for (int i = 0; i < N; ++i) {
        std::cin >> numbers[i];
    }
    QuickSort(numbers, numbers + N - 1);
    for (int i = 0; i < N; ++i) {
        std::cout << numbers[i] << ' ';
    }
    delete[]numbers;
    return 0;
}
