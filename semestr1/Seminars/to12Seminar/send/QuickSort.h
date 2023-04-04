//
// Created by Андрей Боровец on 17.11.2019.
//

#ifndef COMPARISON_OF_SORTS_QUICKSORT_H
#define COMPARISON_OF_SORTS_QUICKSORT_H

#endif //COMPARISON_OF_SORTS_QUICKSORT_H

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

