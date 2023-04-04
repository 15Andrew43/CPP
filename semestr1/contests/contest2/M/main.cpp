#include<iostream>

using namespace std;

void push_back(int *&array, int v, int &size) {
    array[size++] = v;
}

void push_mid(int *&array, int v, int &size) {
    if (size % 2 == 1) {
        for (int i = size; i > size / 2 + 1; --i) {
            array[i] = array[i - 1];
        }
        array[size / 2 + 1] = v;
    }
    else{
        for (int i = size; i > size / 2; --i) {
            array[i] = array[i - 1];
        }
        array[size / 2] = v;
    }
    ++size;
}

int pop(int *&array, int &size) {
    int res = array[0];
    for (int i = 0; i < size; ++i) {
        array[i] = array[i + 1];
    }
    --size;
    return res;
}

int main() {
    int N;
    char operation;
    int v, size = 0;
    cin >> N;
    int *array = new int[N];
    for (int i = 0; i < N; ++i) {
        cin >> operation;
        if (operation == '+') {
            cin >> v;
            push_back(array, v, size);
        }
        if (operation == '*') {
            cin >> v;
            push_mid(array, v, size);
        }
        if (operation == '-') {
            cout << pop(array, size) << '\n';
        }
    }
    delete[] array;
    return 0;
}