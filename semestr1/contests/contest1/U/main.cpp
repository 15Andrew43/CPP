#include <iostream>
#include <cstring>

using namespace std;

int main() {
    char str[256];
    char ans[256];
    cin.getline(str, 256);
    int l = strlen(str);
    bool flag = false;
    int k = 0;

    for (int i = 0; i < l; ++i) {
        if (str[i] != ' ') {
            ans[k++] = str[i];
            flag = true;
        }
        else {
            if (flag) {
                ans[k++] = ' ';
                flag = false;
            }
        }
    }

    ans[k++] = '\n';
    ans[k] = '\0';

    for (char *i = ans; *i; ++i){
        cout << *i;
    }
    return 0;
}