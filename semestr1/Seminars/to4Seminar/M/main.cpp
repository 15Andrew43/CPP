#include <iostream>

using namespace std;

int main() {
    int n, m, w;
    cin >> n >> m >> w;
    int v[1024]={};

    for (int i = 0; i < w; ++i){
        int x, y;
        cin >> x >> y;
        v[32*(x-1) + y-1] = -1;
    }

    for (int y = 0; y < n; ++y){
        for (int x = 0; x < m; ++x){
            int ind = 32*y + x;
            if (v[ind] == -1){

                int IndBypass = ind - 34;

                for (int i = 0; i < 3; ++i){
                    for (int j = 0; j < 3; ++j){
                        IndBypass++;
                        if (v[IndBypass] != -1 && IndBypass >= 0 && IndBypass < 1024){
                            v[IndBypass]++;
                        }

                    }
                    IndBypass += 29;
                }

            }
        }
    }

    for (int y = 0; y < n; ++y) {
        for (int x = 0; x < m; ++x) {
            int ind = 32 * y + x;
            if (v[ind]==-1){
                cout << "* ";
            }
            else{
                cout << v[ind] << " ";
            }
        }
        cout << endl;
    }

    return 0;
}