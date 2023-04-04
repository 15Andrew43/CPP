//
// Created by Андрей Боровец on 17.11.2019.
//

#ifndef COMPARISON_OF_SORTS_SHAKERSORT_H
#define COMPARISON_OF_SORTS_SHAKERSORT_H

#endif //COMPARISON_OF_SORTS_SHAKERSORT_H

using namespace std;

void ShakerSort(int * a, int n) {
    int d;
    int start, end;

    for (int i = 0; i < n-1; i++){
        bool check = true;
        start = ( (i % 2 == 0) ? (i/2) : (n-i/2-2) );
        end = ( (i % 2 == 0) ? (n - i/2 - 1) : (i/2) );
        d = ( (i % 2 == 0) ? (1) : (-1) );

        for (int j = start; ((i%2==0) ? (j < end) : (j >= end)); j += d){
            if (a[j] > a[j+1]){
                swap(a[j], a[j+1]);
                check = false;
            }
        }

        if (check)
            break;
    }
}

