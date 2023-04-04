#include <iostream>
#include <string>

using namespace std;

int main() {
    char line[1000] = {};
    int count = 0;
    cin.getline(line, 1000);
    int Insert_ind = 0;

    for (int i = 0; i < 1000-1; i++){

        if (!isalpha(line[i]) && !isalpha(line[i+1])){
            line[i] = ' ';
            Insert_ind = i+1;
            count = 0;

            for (int find_end = Insert_ind; find_end < 1000; find_end++){
                if (isalpha(line[find_end])){
                    count++;
                }
                else if (count){
                   for (int k = count; k > 0; k--, Insert_ind++){
                       line[Insert_ind] = line[find_end-k];
                       line[find_end-k] = ' ';
                   }
                   i += (count);
                   break;
                }
            }

        }
        else {
            if (!isalpha(line[i])){
                line[i] = ' ';
            }
        }

    }

    cout << line;
    return 0;
}