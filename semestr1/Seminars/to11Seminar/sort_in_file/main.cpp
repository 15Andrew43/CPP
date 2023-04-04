#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

void write_array_to_file(const char* filename, int N); // Сохраняет массив чисел в файл в бинарном режиме.
void sort_array_in_file(const char* filename);      // Открывает бинарный файл в режиме записи-чтения и сортирует содержимое файла непосредственно в нём.
void print_array_from_file(const char* filename); // Выводит на консоль содержимое файла в человеко-читаемом виде
void sift_down(int length, int i);

int main() {
    int N;
    cin >> N;
    const char filename[] = "file.bin";

    write_array_to_file(filename, N);
    sort_array_in_file(filename);
   // print_array_from_file(filename);

    return 0;
}

void write_array_to_file(const char* filename, int N) {

    cout << "input N numbers\n";

    ofstream file (filename, ios::binary);

    if (!file.is_open()) {
        cerr << "Cannot open file " << "file.bin" << endl;
        return;
    }

    // write to outfile
    for (int i = 0; i < N; ++i) {
        int digit;
        cin >> digit;
        file.write(reinterpret_cast<char*>(&digit), sizeof(int));
    }

    file.close();
}


void sort_array_in_file(const char* filename) {
    ifstream file (filename, ios::binary);
 //   ofstream outfile ("outfile.bin", ios::binary);
    file.seekg (0, file.end);
    int length = file.tellg(); // размер файла в байтах
    cout << length << endl;
    //for (long int i = length/2; i >= 1; --i) {
  //      sift_down(length, i);
    //}

    file.seekg (0, file.beg);

    char * buffer = new char [length+1];
    buffer[length] = 0;

//    char * c = new char;
    file.read(buffer, length);
    file.seekg (0, file.beg);
//    file.read(c, 4);
//    cout <<"c = " << *c << endl;
//    outfile.write(buffer, length);


    for (int i = 0; i < length; ++i) {
        cout << buffer[i] << endl;
    }

    delete []buffer;
}

/*
void sift_down(int length, int i) {
    fstream file;
    long int L = 2 * i;
    long int R = 2 * i + 1;
    long int max;

    if (L <= length && a[L] > a[i]) {
        max = L;
    } else {
        max = i;
    }
    if (R <= n && a[R] > a[max]) {
        max = R;
    }
    if (max != i) {
        swap(a[i], a[max]);
        sift_down(a, n, max);
    }
}

 */