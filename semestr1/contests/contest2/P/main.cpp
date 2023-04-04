#include <iostream>

using namespace std;

struct Student{
    int number;
    int score;
};

void sift_down(Student* &a, int n, int i) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int ind_min = i;
    if (left < n && a[left].score < a[i].score) {
        ind_min = left;
    }
    if (left < n && a[left].score == a[i].score){
        if (a[left].number > a[ind_min].number){
            ind_min = left;
        }
    }
    if (right < n && a[right].score < a[ind_min].score) {
        ind_min = right;
    }
    if (right < n && a[right].score == a[ind_min].score) {
        if (a[right].number > a[ind_min].number){
            ind_min = right;
        }
    }

    if (ind_min != i) {
        swap(a[i], a[ind_min]);
        sift_down(a, n, ind_min);
    }
}

void build_heap(Student* &a, int n) {
    for (int i = n / 2 - 1; i >= 0; --i) {
        sift_down(a, n, i);
    }
}

void heap_sort(Student* &array, int n) {
    build_heap(array, n);
    for (int i = n - 1; i >= 0; i--) {
        swap(array[0], array[i]);
        sift_down(array, i, 0);
    }
}


int main() {
    int n;
    cin >> n;
    Student* array = new Student[n];
    for (int i = 0; i < n; ++i) {
        cin >> array[i].number >> array[i].score ;
    }

    heap_sort(array, n);

    for (int i = 0; i < n; ++i) {
        cout << array[i].number << ' ' << array[i].score << '\n';
    }
    delete[] array;
    return 0;
}