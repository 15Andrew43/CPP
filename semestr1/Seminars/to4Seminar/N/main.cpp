#include <iostream>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    int v1[2500]={};
    int v2[2500]={};

    for (int i = 0; i < n*m; ++i){
            cin >> v1[i];
    }

    int k = 0;
    for (int x = n-1; x >= 0; --x){
        for (int y = 0; y < m; ++y){
            v2[50*y + x] = v1[k++];
        }
    }
    cout << m << " " << n << endl;

    for (int y = 0; y < m; ++y){
        for (int x = 0; x < n; ++x){
            cout << v2[50*y+x] << " ";
        }
        cout << endl;
    }
    return 0;
}