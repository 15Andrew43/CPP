#include <iostream>
#include <fstream>

using namespace std;

int main() {
    fstream infile ("new.txt", ios::in | ios::out | ios::binary);
    if (!infile.is_open()) {
        cerr << "Cannot open file " << "new.txt" << endl;
    }

    // get length of file:
    infile.seekg (0, infile.end);
    int length = infile.tellg();
    cout << length<< endl;
    infile.seekg (3, infile.beg);

//    char * buffer = new char [length];
    char buffer[2];
    cout << "Reading " << length << " characters... ";
    // read data as a block:
    infile.read (&buffer[0], 1);
    cout << infile.tellg() << endl;
    infile.seekg (1, ios::beg);
    infile.read(&buffer[1], sizeof(buffer[1]));

    cout << buffer[0] << ' ' << buffer[1] << endl;

    infile.seekg (0, ios::beg);
    buffer[1] = '-';
    infile.write(&buffer[1], sizeof(buffer[1]));

    if (infile)
        cout << "all characters read successfully.";
    else
        cout << "error: only " << infile.gcount() << " could be read";
    infile.close();
//    delete[] buffer;
    return 0;
}