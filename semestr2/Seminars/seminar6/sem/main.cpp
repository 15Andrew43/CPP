#include <iostream>
#include <exception>
#include <string>

using namespace std;


class DivizionByZero : public exception {
public:
    const char* what() const noexcept override {
        return "In function...";
    }
};

//  принято под каждую ошибку заводить совй класс
int Divide(int x, int y) {
    if (y==0) {
        throw DivizionByZero(); //     примернго то же самое что и ретурн
        // throw 9;
    }
    return x/y;
}

int main() {
    Divide(1, 0);
    return 0;
}