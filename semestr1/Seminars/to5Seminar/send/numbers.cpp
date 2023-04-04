#include <iostream>

using namespace std;

int main(){
    long N;
    int b;
    int number;
    int i = 0;
    char ans[100]={};
    cin >> N >> b;


    while (N != 0){
        number = N % b;
        N /= b;
        if (number > 9){
            ans[i] = (char)(number+55);
        }
        else{
            ans[i] = (char)(number+48);
        }
        i++;
    }

    int L = strlen(ans);

    for (int i = 0; i < L/2; ++i){
        swap(ans[i], ans[L-i-1]);
    }


    cout << ans;
    return 0;
}