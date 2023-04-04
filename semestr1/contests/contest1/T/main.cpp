#include <iostream>
#include <cstring>

using namespace std;

int main() {
    char input[201];
    cin >> input;
    int L = strlen(input);
    char password[201];
    int start = 0;
    int end = 0;
    for (int i = L; i >= 0; --i){
        if ((int)input[i] == 64){
            start = i+1;
            break;
        }
    }

    for (int i = start; i < L; ++i){
        if ((int)input[i] == 35){
            ((end > 0)?(end--):1);
        }
        else {
            password[end++] = input[i];
        }
    }

    int l = strlen(password);
    for (int i = 0; i < end; ++i){
        cout << password[i];
    }
    return 0;
}