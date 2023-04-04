#include <iostream>

using namespace std;

void sift_up(long int * &a, long int n, long int i) {
    long int parent = i/2;
    if (parent != 0 && a[parent] < a[i]) {
        swap(a[parent], a[i]);
        sift_up(a, n, parent);
    }
    else {
        a[0] = i;
    }
}


long long int RandomizedPartition(long long int * a, int l, int r) {
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

void QuickSort(long long int * a, int l, int r) {
    int pirot;
    if (l < r) {
        pirot = RandomizedPartition(a, l, r);
        QuickSort(a, l, pirot-1);
        QuickSort(a, pirot+1, r);
    }
}

void push(long long int* &s, int top, int &size) {
    if (size == top+1) {
        size *= 2;
        long long int *s1 = new long long int [size];
        memcpy(s1, s, size/2*sizeof(int));
        delete []s;
        s = s1;
    }
}

long long int min(long long int * a, int &n, bool &SortedA) {
    if (!SortedA) {
        QuickSort(a, 0, n - 1);
        SortedA = true;
    }
    n--;
    return a[0];
}

long long int max(long long int * a, int &n, bool &SortedB) {
    if (!SortedB) {
        QuickSort(a, 0, n - 1);
        SortedB = true;
    }
    n--;
    return a[n];
}



int main() {
    char operation[5];
    int m;
    cin >> m;
    bool SortedA = false;
    bool SortedB = false;
    int size = 100;
    int SizeA = 0;
    int SizeB = 0;
    long long int *a = new long long int[size];
    long long int *b = new long long int[size];


    for (int i = 0; i < m; ++i) {
        cin >> operation;
        if (operation[1] == 'd') {//add
            long long int v;
            cin >> v;
            if (SizeA == SizeB) {
                push(a, SizeA, size);
                a[SizeA++] = v;
            }
            else if (SizeA > SizeB) {
                push(a, SizeA, size);
                a[SizeA++] = v;
            }
        }
        else if (operation[1] == 'a') {//max
            cout << max(b, SizeB, SortedB);
        }
        else if (operation[1] == 'i' && operation[2] == 'n') {//min
            cout << min(a, SizeA, SortedA);
        }
        else if (operation[1] == 'i' && operation[2] == 'd') {//mid
            cout << max(a, SizeA, SortedA);
        }
    }
    return 0;
}
