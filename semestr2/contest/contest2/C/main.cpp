#include <iostream>
#include <cmath>
#include <iomanip>

class Point {
public:
    long double x_ = 0;
    long double y_ = 0;
    Point() = default;
    Point(long double x, long double y) : x_(x), y_(y){
    }
    Point(const Point& other) {
        x_ = other.x_;
        y_ = other.y_;
    }
    Point& operator=(const Point& other) {
        x_ = other.x_;
        y_ = other.y_;
        return *this;
    }
    ~Point() = default;
};
std::istream& operator>>(std::istream& is, Point& point) {
    long double x, y;
    std::cin >> x >> y;
    point = {x, y};
    return is;
}
std::ostream& operator<<(std::ostream& os, const Point& point) {
    std::cout << point.x_ << ' ' << point.y_;
    return os;
}





class Vector {
    Point point_;
public:
    Vector() = default;
    Vector(long double x, long double y) {
        point_.x_ = x;
        point_.y_ = y;
    }
    Vector(const Vector& other) {
        point_.x_ = other.point_.x_;
        point_.y_ = other.point_.y_;
    }
    ~Vector() = default;

    long double getX() const {
        return point_.x_;
    }
    long double & getX() {
        return point_.x_;
    }

    long double getY() const {
        return point_.y_;
    }
    long double & getY() {
        return point_.y_;
    }
    Vector& operator=(const Vector& other) {
        point_.x_ = other.point_.x_;
        point_.y_ = other.point_.y_;
        return *this;
    }
    Vector& operator+=(const Vector& other) {
        point_.x_ += other.point_.x_;
        point_.y_ += other.point_.y_;
        return *this;
    }
    Vector operator+(const Vector& other) {
        return {point_.x_ + other.point_.x_, point_.y_ + other.point_.y_};
    }
    Vector& operator-=(const Vector& other) {
        point_.x_ -= other.point_.x_;
        point_.y_ -= other.point_.y_;
        return *this;
    }
    Vector operator-(const Vector& other) {
        return {point_.x_ - other.point_.x_, point_.y_ - other.point_.y_};
    }


    long double getLength() {
        return sqrt(point_.x_ * point_.x_ + point_.y_ * point_.y_);
    }
    long double ScalarProduct(const Vector& other) {
        return point_.x_ * other.point_.x_ + point_.y_ * other.point_.y_;
    }
    long double VectorProduct(const Vector& other) {
        return point_.x_ * other.point_.y_ - other.point_.x_ * point_.y_;
    }
 //   friend std::istream& operator>>(std::istream& is, Vector& v);
 //   friend std::ostream& operator<<(std::ostream& os, const Vector& v);

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





class Line {
    long double A_ = 0;
    long double B_ = 0;
    long double C_ = 0;

public:
    Line() = default;
    Line(long double A, long double B, long double C) : A_(A), B_(B), C_(C) {
    }
    Line(const Line& other) : A_(other.A_), B_(other.B_), C_(other.C_) {
    }
    ~Line() = default;

    Line& operator=(const Line& other) {
        A_ = other.A_;
        B_ = other.B_;
        C_ = other.C_;
        return *this;
    }

    long double getA() const {
        return A_;
    }
    long double getB() const {
        return B_;
    }
    long double getC() const {
        return C_;
    }
    long double& getA() {
        return A_;
    }
    long double& getB() {
        return B_;
    }
    long double& getC() {
        return C_;
    }

    Vector getDirectVect() const {
        long double x, y;
        if (A_ != 0) {
            y = 1;
            x = -B_/A_;
        } else if (B_ != 0) {
            x = 1;
            y = -A_/B_;
        }
        return {x, y};
    }
    Point getPoint() const {
        long double x, y;
        if (A_ != 0) {
            y = 0;
            x = -C_/A_;
        } else if (B_ != 0) {
            x = 0;
            y = -C_/B_;
        }
        return {x, y};
    }
};
std::istream& operator>>(std::istream& is, Line& line) {
    long double a, b, c;
    std::cin >> a >> b >> c;
    line = {a, b, c};
    return is;
}
std::ostream& operator<<(std::ostream& os, const Line& line) {
    std::cout << line.getA() << ' ' << line.getB() << ' ' << line.getC();
    return os;
}

Point getIntersection(const Line& line1, const Line& line2) {
    if ( line1.getDirectVect().VectorProduct(line2.getDirectVect()) == 0 ) {
        throw "no Intersection";
    }
    //std::cout << "line1 = " << line1 << '\n' << "line2  = " << line2 << '\n';
    long double numerator, denominator;
    long double x;
    numerator = line2.getC() * line1.getB() - line1.getC() * line2.getB();
    denominator = line1.getA() * line2.getB() - line2.getA() * line1.getB();
    x = numerator / denominator;
    long double y = 0;
    numerator = line2.getC() * line1.getA() - line1.getC() * line2.getA();
    denominator = line1.getB() * line2.getA() - line2.getB() * line1.getA();
    y = numerator / denominator;
    return {x, y};
}


long double getDistance(const Point& point, const Line& line) {
    return fabs(line.getA() * point.x_ + line.getB() * point.y_ + line.getC())
            / sqrt(line.getA() * line.getA() + line.getB() * line.getB());
}
long double getDistance(const Line& line, const Point& point) {
    return fabs(line.getA() * point.x_ + line.getB() * point.y_ + line.getC())
           / sqrt(line.getA() * line.getA() + line.getB() * line.getB());
}
long double getDistance(const Point& point1, const Point& point2) {
    return sqrt((point1.x_ - point2.x_) * (point1.x_ - point2.x_)
    + (point1.y_ - point2.y_) * (point1.y_ - point2.y_));
}

int main() {
    Line line1, line2;
    std::cin >> line1 >> line2;

    std::cout << std::fixed << std::setprecision(9)
              << line1.getDirectVect() << '\n'
              << line2.getDirectVect() << '\n';
    try {
        std::cout << getIntersection(line1, line2);
    } catch (...) {
        std::cout << getDistance(line1.getPoint(), line2);
    }
    return 0;
}