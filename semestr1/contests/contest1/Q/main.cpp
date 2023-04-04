#include <iostream>
#include <cstring>

using namespace std;

void BubleSort(char **numbers, int *changed_numbers, int n);
bool IsBigger(char **numbers, int j);

int main() {
    int n;
    cin >> n;
    char **numbers = new char *[n];
    for (int i = 0; i < n; ++i){
        numbers[i] = new char[1001];
    }

    for (int i = 0; i < n; ++i) {
        cin >> numbers[i];
    }
// changed_numbers = bublesort(numbers)
    int *changed_numbers = new int[n];

// put summ of digits of every number(1 step )
    for (int i = 0; i < n; ++i) {
        int s = 0;
        for (char *p = numbers[i]; *p; ++p) {
            s += ((int)(*p)-48);
        }
        changed_numbers[i] = s;
    }

// function of problem
    for (int i = 0; i < n; ++i) {
        int s;
        int res = changed_numbers[i];
        while (res/10 != 0) {
            s = 0;
            while (res != 0) {
                s += (res % 10);
                res /= 10;
            }
            res = s;
        }
        changed_numbers[i] = res;
    }

    BubleSort(numbers, changed_numbers, n);

    for (int i = 0; i < n; ++i) {
        cout << numbers[i] << endl;
    }

    for (int i = 0 ; i < n; ++i) {
        delete []numbers[i];
    }
    delete []changed_numbers;
    delete []numbers;
    return 0;
}


void BubleSort(char **numbers, int *changed_numbers, int n) {
    for (int i = 0; i < n-1; i++) {
        bool check = true;
        for (int j = 0; j < n-i-1; j++) {
            if ((changed_numbers[j] > changed_numbers[j+1]) || (changed_numbers[j] == changed_numbers[j+1] && IsBigger(numbers, j))) {
                swap(changed_numbers[j], changed_numbers[j+1]);
                swap(numbers[j], numbers[j+1]);
                check = false;
            }
        }
        if (check)
            break;
    }
}

bool IsBigger(char **numbers, int j) {
    int a = strlen(numbers[j]);
    int b = strlen(numbers[j+1]);
    if (a > b) {
        return true;
    }
    else if (a < b) {
        return false;
    }
    else {
        for (int i = 0; i < a; ++i) {
            if ((int)(numbers[j][i]) > (int)(numbers[j+1][i])) {
                return true;
            }
            else if (((int)numbers[j][i]) < (int)(numbers[j+1][i])) {
                return false;
            }
        }
    }
}