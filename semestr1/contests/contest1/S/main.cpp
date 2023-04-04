#include <iostream>
#include <cstring>

using namespace std;

int main() {
    char str1[10000];
    char str2[10000];
    cin >> str1 >> str2;
    int L1 = strlen(str1);
    int L2 = strlen(str2);
    bool flag = false;
    bool IsGone = true;

    for (int i = 0; i < L2-L1+1; ++i) {
        for (int j = 0; j < L1; ++j) {
            IsGone = true;
            if (str1[j] != str2[i+j]) {
                IsGone = false;
                break;
            }
        }
        if (IsGone){
            flag = true;
            break;
        }
    }


    if (flag) {
        cout << "yes";
    }
    else {
        cout << "no";
    }
    return 0;
}