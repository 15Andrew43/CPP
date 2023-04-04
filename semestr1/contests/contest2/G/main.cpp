#include <iostream>

using namespace std;

int bin_search(int * a, int x, int n) {
    int l = 0;
    int r = n;
    while (r-l > 1) {
        int m = (l+r)/2;
        if (a[m] < x)
            l = m;
        else
            r = m;
    }
    if (a[l] != x) {
        l++;
    }
    return l;
}

void hoarasort(int * a, int * b, int first, int last)
{

    int i = first, j = last;
    int tmp, x = a[(first + last) / 2];

    do {
        while (a[i] < x)
            i++;
        while (a[j] > x)
            j--;

        if (i <= j)
        {
            if (i < j)
            {
                swap(a[i], a[j]);
                swap(b[i], b[j]);
            }
            i++;
            j--;
        }
    } while (i <= j);

    if (i < last)
        hoarasort(a, b, i, last);
    if (first < j)
        hoarasort(a, b, first, j);
}


int main() {
    //int k[10] = {1, 2, 3, 3, 3, 3, 3, 6, 9, 10};
    //cout << bin_search(&k[0], 10, 10);


    int n;
    cin >> n;
    int *T_start = new int [n];
    int *cnt = new int [n];
    int *T_end = new int[n];
    for (int i = 0; i < n; ++i) {
        int l;
        cin >> T_start[i] >> l;
        T_end[i] = T_start[i]+l;
        cnt[i] = 1;
    }

    hoarasort(T_start, T_end, 0, n-1);

    for (int i = 0; i < n; ++i) {
        if (T_end[i] <= T_start[n-1]) {
            int ind = bin_search(T_start, T_end[i], n);
            //cout << ind << endl;
            cnt[ind]--;
        }
    }

    int max_work = 0;
    int s = 0;
    for (int i = 0; i < n; ++i) {
        s += cnt[i];
        if (max_work < s) {
            max_work = s;
        }
    }

    cout << max_work;
    return 0;
}