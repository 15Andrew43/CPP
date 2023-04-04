#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include "ShakerSort.h"
#include "QuickSort.h"
#include <fstream>

using namespace std;

int  Trans_digit_to_char(char * StrDigit, int n) {
    int i = 0;
    while (n) {
        int z = n%10;
        n /= 10;
        StrDigit[i++] = (char)(z+(int)'0');
    }
    if (i == 0) {
        i++;
        StrDigit[0] = '0';
    }
    for (int j = 0; j < i/2; ++j) {
        swap(StrDigit[j], StrDigit[i-j-1]);
    }
    return i;
}

int main() {
    ofstream file("digits.txt");

    int max = 10000;//MaxElement

    srand(time(NULL));

    int n = 1000; // amount of elements
    int *array = new int[n]; //array for ShakerSort
    int *array2 = new int[n]; // array for QuickSort

// headers + HelpSigns
    char numbers = 'n';
    char * StrDigit = new char [20];
    char time_ShakefSort[] = "time_ShakerSort";
    char time_QuickSort[] = "time_QuickSort";
    char transition[] = "\n";
    char gap[] = "\t";
// write headers
    file.write(reinterpret_cast<char*>(&numbers), sizeof(char));
    file.write(reinterpret_cast<char*>(&gap), strlen(gap)*sizeof(char));
    file.write(reinterpret_cast<char*>(&time_ShakefSort), strlen(time_ShakefSort)*sizeof(char));
    file.write(reinterpret_cast<char*>(&gap), strlen(gap)*sizeof(char));
    file.write(reinterpret_cast<char*>(&time_QuickSort), strlen(time_QuickSort)*sizeof(char));
    file.write(reinterpret_cast<char*>(&transition), strlen(transition)*sizeof(char));

    int L;
    for (int j = 0; j < n; ++j) {
// input arrays
        for (int i = 0; i < j; i++) {
            array[i] = rand() % max;
            array2[i] = array[i];
        }

        clock_t t1, t2;
// amount of elements
        L = Trans_digit_to_char(StrDigit, j);
        file.write(reinterpret_cast<char*>(StrDigit), L*sizeof(char));
        file.write(reinterpret_cast<char*>(&gap), strlen(gap)*sizeof(char));

// ShakerSort
        t1 = clock();
        ShakerSort(array, j);
        t2 = clock();

        L = Trans_digit_to_char(StrDigit, t2-t1);
        file.write(reinterpret_cast<char*>(StrDigit), L*sizeof(char));
        file.write(reinterpret_cast<char*>(&gap), strlen(gap)*sizeof(char));

//QuickSort
        t1 = clock();
        QuickSort(array2, 0, j - 1);
        t2 = clock();

        L = Trans_digit_to_char(StrDigit, t2-t1);
        file.write(reinterpret_cast<char*>(StrDigit), L*sizeof(char));
        file.write(reinterpret_cast<char*>(&transition), strlen(transition)*sizeof(char));

    }

/*
    //SgakerSort
    for (int i = 0; i < n; ++i) {
        cout << array[i] << ' ';
    }
    delete []array;
    cout << endl;
//QuickSort
    for (int i = 0; i < n; ++i) {
        cout << array2[i] << ' ';
    }
    delete []array2;
    cout << endl;
*/
    delete []StrDigit;
    delete []array;
    delete []array2;

    file.close();
    return 0;
}