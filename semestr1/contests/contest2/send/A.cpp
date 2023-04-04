#include <iostream>

using namespace std;

void sift_up(long int *a, long int n, long int i);
void sift_down(long int *a, long int n, long int i);

int main() {
    int n, m;
    int count = 0;
    cin >> n >> m;
    long int *array = new long int[n];
    array[0] = 1543;

    for (int i = 0; i < m; ++i) {
        int operation;
        cin >> operation;
        if (operation==1) {
            if (count==1) {
                count--;
                cout << 0 << ' ' << array[1] << endl;
            }
            else if (count > 0) {
                int max = array[1];
                array[1] = array[count];
                count--;
                sift_down(array, count, 1);
                cout << array[0] << " " << max << endl;
            }
            else {
                cout << -1 << endl;
            }
        }
        else { //operation==2
            count++;
            int q;
            cin >> q;
            if (count <= n) {
                array[count] = q;
                sift_up(array, count, count);
                cout << array[0] << endl;
            }
            else {
                cout << -1 << endl;
                count--;
            }
        }
    }

    for (int i = 1; i <= count; ++i) {
        cout << array[i] << ' ';
    }
    return 0;
}

// просеиваем вверх в массиве а длины n i-ый элемент
void sift_up(long int *a, long int n, long int i) {
    long int parent = i/2;
    if (parent != 0 && a[parent] < a[i]) {
        swap(a[parent], a[i]);
        sift_up(a, n, parent);
    }
    else {
        a[0] = i;
    }
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
    else {
        a[0] = i;
    }
}