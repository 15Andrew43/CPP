#include <iostream>
#include <cstring>

using namespace std;

void f(int k);

char str[256];
char number[256];
char ans[1000];
char *q = ans;

// 110^1010100110JKjdl;?.,lk1101101111Pk
// 110^1010100110JKjdl;?.,lk1101101111Pk
int main() {
    int start;
    int k = 0;
    cin.getline(str, 256);
    int l = strlen(str);
    char *p = str;

//находим нужные чары(число), функция f,
    for (int i = 0; i < l; ++i){
        if (isdigit(str[i])){
            k = 0;
            for (int j = i; j < 256; ++j){
                if (!isdigit(str[j])) {
                    break;
                }
                else {
                    number[k++] = str[j];
                }
            }
     //       cout << start << " " << end  << " " << k << endl;
            f(k);
            i += k-1;
        }
        else {
            *(q++) = str[i];
        }
    }
    *q = '\0';

    for (char *q = ans; *q; ++q){
        cout << *q;
    }
    return 0;
}


void f(int k){
//перевод массива чаров в инт(s)
    int deg = 1;
    long long int s = 0;
    for (int i = k-1; i >= 0; --i){
       // cout << deg << "deg" << ((int)number[i]-48) << " ((int)number[i]-48) " << endl;
        s += ( (deg != 1) ? (deg * ((int)number[i]-48)) : ((int)(number[i]-48)) );
        deg *= 10;
    }
 //   cout << s << " s " << endl;

//перевод инта(s) в двоичный массив чаров(number).
    int end = 0;
    while (s != 0){
        int z = s % 2;
        s /= 2;
        number[end++] = (char)(z+48);
    }
    int L = end;
    for (int i = 0; i < L/2; ++i){
        swap(number[i], number[L-i-1]);
    }
/*
    for (int i = 0; i < L; ++i){
        cout << number[i];
    }
    cout << endl; */

//запись в ответ массива чаров
    for (int i = 0; i < end; ++i){
        *(q++) = number[i];
    }
}

