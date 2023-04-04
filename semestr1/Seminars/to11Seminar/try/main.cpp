#include <iostream>
#include <fstream>

using namespace std;

int main() {

    fstream outfile ("new.txt", ofstream::binary);
    if (!outfile.is_open()) {
        cerr << "Cannot open file " << "test.txt" << endl;
    }
/*
    // get size of file
    infile.seekg (0,infile.end);
    long size = infile.tellg();
    infile.seekg (0);

    // allocate memory for file content
    char* buffer = new char[size];
*/
    // read content of infile
    //infile.read (buffer,size);
    int n;
    cin >> n;
    char* buffer = new char[n];
    for (int i = 0; i < n; ++i) {
        cin >> buffer[i];
    }

    // write to outfile
    outfile.write (buffer, n);


    // release dynamically-allocated memory
    delete[] buffer;

    outfile.close();
    return 0;
}