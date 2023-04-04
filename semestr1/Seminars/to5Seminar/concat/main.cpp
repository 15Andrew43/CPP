#include <iostream>

using namespace std;

int main() {
    char name[1000];
    char concat[1000];
    char *p;
    p = concat;

    while (cin >> name, *name != '0'){
        for (char *q = name; *q; ++p, ++q){
            *p = *q;
        }
        *(p++) = ' ';
    }
    *p = '\0';
    cout << concat;

    return 0;
}