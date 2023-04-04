#include <iostream>

using namespace std;

int main() {
    int n, ind = 1;
    cin >> n;
    int *a = new int[2*n];

    for (int i = 0; i < 2*n; ++i){
        cin >> a[i];
    }

    for (int i = 1; i < 2*n-2; i += 2){
        int m = a[i];
        int m_ind = a[i-1];
        ind = i;

        for (int j = i+2; j < 2*n; j += 2){
            int score = a[j];
            int score_ind = a[j-1];

            if (m <= score){
                if(m != score){
                    m = score;
                    m_ind = score_ind;
                    ind = j;
                }
                else{
                    if (m_ind > score_ind){
                        m_ind = score_ind;
                        ind = j;
                    }
                }
            }

        }

        swap(a[i], a[ind]);
        swap(a[i - 1], a[ind - 1]);

    }

    for (int i = 0; i < 2*n; ++i){
        cout << a[i] << ( (i%2==1) ? ('\n') : ' ');
    }
    delete []a;
    return 0;
}