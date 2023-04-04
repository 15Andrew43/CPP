#include <iostream>
#include <cmath>
#include <iomanip>

class Vector {
    long double x_ = 0;
    long double y_ = 0;
public:
    Vector() = default;
    Vector(long double x, long double y) {
        x_ = x;
        y_ = y;
    }
    Vector(const Vector& other) {
        x_ = other.x_;
        y_ = other.y_;
    }
    ~Vector() = default;

    long double getX() const {
        return x_;
    }
    long double & getX() {
        return x_;
    }

    long double getY() const {
        return y_;
    }
    long double & getY() {
        return y_;
    }
    Vector& operator=(const Vector& other) {
        x_ = other.x_;
        y_ = other.y_;
        return *this;
    }
    Vector& operator+=(const Vector& other) {
        x_ += other.x_;
        y_ += other.y_;
        return *this;
    }
    Vector operator+(const Vector& other) {
        return {x_ + other.x_, y_ + other.y_};
    }
    Vector& operator-=(const Vector& other) {
        x_ -= other.x_;
        y_ -= other.y_;
        return *this;
    }
    Vector operator-(const Vector& other) {
        return {x_ - other.x_, y_ - other.y_};
    }


    long double getLength() {
        return sqrt(x_*x_ + y_*y_);
    }
    long double ScalarProduct(const Vector& other) {
        return x_ * other.x_ + y_ * other.y_;
    }
    long double VectorProduct(const Vector& other) {
        return x_ * other.y_ - other.x_ * y_;
    }
};
std::istream& operator>>(std::istream& is, Vector& v) {
    long double x, y;
    std::cin >> x >> y;
    v = {x, y};
    return is;
}
std::ostream& operator<<(std::ostream& os, const Vector& v) {
    std::cout << v.getX() << ' ' << v.getY();
    return os;
}

int main() {
    int x1, y1, x2, y2;
    std::cin >> x1 >>y1 >> x2 >> y2;
    Vector a(x2 - x1, y2 - y1);
    std::cin >> x1 >>y1 >> x2 >> y2;
    Vector b(x2 - x1, y2 - y1);
    std::cout << std::fixed << std::setprecision(9)
              << a.getLength() << ' ' << b.getLength() << '\n'
              << a + b << '\n'
              << a.ScalarProduct(b) << ' ' << a.VectorProduct(b) << '\n'
              << fabs(a.VectorProduct(b))/2;
    return 0;
}