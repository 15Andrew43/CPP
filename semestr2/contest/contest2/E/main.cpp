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
    long double x_ = 0;
    long double y_ = 0;
public:
    Vector() = default;
    Vector(long double x, long double y) {
        x_ = x;
        y_ = y;
    }
    Vector(const Point& point1, const Point& point2) {
        x_ = point2.x_ - point1.x_;
        y_ = point2.y_ - point1.y_;
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

    Vector getNormalVector() const {
        long double A = 1, B = 1;
        if (x_ == 0) {
            B = 0;
        } else if (y_ == 0) {
            A = 0;
        } else {
            A = -y_ / x_;
        }
        return {A, B};
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
    Line(Point point1, Point point2) {
        Vector normal, direction;
        direction = {point2.x_ - point1.x_, point2.y_ - point1.y_};
        normal = direction.getNormalVector();
        A_ = normal.getX();
        B_ = normal.getY();
        C_ = -(A_ * point1.x_ + B_ * point1.y_);
    }
    Line(const Point& point, const Vector& vector) {
        Point point2(point.x_ + vector.getX(), point.y_ + vector.getY());
        //Line(point, point2);
        Vector normal, direction;
        direction = {point2.x_ - point.x_, point2.y_ - point.y_};
        normal = direction.getNormalVector();
        A_ = normal.getX();
        B_ = normal.getY();
        C_ = -(A_ * point.x_ + B_ * point.y_);
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

    Vector getDirectVector() const {
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

    bool ContainsPoint(const Point& point) const {
        //return A_ * point.x_ + B_ * point.y_ + C_ == 0;
        Point p = getPoint();
        Vector ap(point.x_ - p.x_, point.y_ - p.y_);
        return ap.VectorProduct(getDirectVector()) == 0;
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
    if ( line1.getDirectVector().VectorProduct(line2.getDirectVector()) == 0 ) {
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





class Ray {
    Point point_;
    Vector direct_vector_;
public:
    Ray() = default;
    Ray(const Point& point, const Vector& vector) : point_(point), direct_vector_(vector){
    }
    Ray(const Point& point_start, const Point& point_end) {
        Vector vector(point_end.x_ - point_start.x_, point_end.y_ - point_start.y_);
        //Ray(point_start, vector);
        point_ = point_start;
        direct_vector_ = vector;
    }
    ~Ray() = default;

    Ray& operator=(const Ray& other) {
        point_ = other.point_;
        direct_vector_ = other.direct_vector_;
        return *this;
    }

    Point getPoint() const {
        return point_;
    }
    Point& getPoint() {
        return point_;
    }
    Vector getDirectVector() const {
        return direct_vector_;
    }
    Vector& getDirectVector() {
        return direct_vector_;
    }

    bool ContainsPoint(const Point& point) const {
        Vector ap(point.x_ - point_.x_, point.y_ - point_.y_);
        return ap.VectorProduct(direct_vector_) == 0 && ap.ScalarProduct(direct_vector_) >= 0;
    }
};

std::istream& operator>>(std::istream& is, Ray& ray) {
    long double a, b, c, d;
    std::cin >> a >> b >> c >> d;
    ray = {{a, b}, Vector(c, d)};
    return is;
}
std::ostream& operator<<(std::ostream& os, const Ray& ray) {
    std::cout << ray.getPoint().x_ << ' ' << ray.getPoint().y_ << ' '
              << ray.getDirectVector().getX() << ' ' << ray.getDirectVector().getY();
    return os;
}





class Segment {
    Point point1_;
    Point point2_;
public:
    Segment() = default;
    Segment(const Point& point1, const Point& point2) : point1_(point1), point2_(point2) {
    }
    ~Segment() = default;

    Segment& operator=(const Segment& other) {
        point1_ = other.point1_;
        point2_ = other.point2_;
        return *this;
    }

    Point getPoint1() const {
        return point1_;
    }
    Point getPoint2() const {
        return point2_;
    }
    Point& getPoint1() {
        return point1_;
    }
    Point& getPoint2() {
        return point2_;
    }

    bool ContainsPoint(const Point& point) const {
        Ray ray(point1_, point2_);
        if (!ray.ContainsPoint(point)) {
            return false;
        }
        ray = {point2_, point1_};
        if (!ray.ContainsPoint(point)) {
            return false;
        }
        return true;
    }
};

std::istream& operator>>(std::istream& is, Segment& segment) {
    long double a, b, c, d;
    std::cin >> a >> b >> c >> d;
    segment = {{a, b}, {c, d}};
    return is;
}
std::ostream& operator<<(std::ostream& os, const Segment& segment) {
    std::cout << segment.getPoint1().x_ << ' ' << segment.getPoint1().y_ << ' '
              << segment.getPoint2().x_ << ' ' << segment.getPoint2().y_;
    return os;
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

long double getDistance(const Point& point, const Ray& ray) {
    Vector vector(point.x_ - ray.getPoint().x_, point.y_ - ray.getPoint().y_);
    if (vector.ScalarProduct(ray.getDirectVector()) >= 0) {
        return getDistance(point, Line(ray.getPoint(), ray.getDirectVector()));
    } else {
        return getDistance(point, ray.getPoint());
    }
}
long double getDistance(const Ray& ray, const Point& point) {
    Vector vector(point.x_ - ray.getPoint().x_, point.y_ - ray.getPoint().y_);
    if (vector.ScalarProduct(ray.getDirectVector()) >= 0) {
        return getDistance(point, Line(ray.getPoint(), ray.getDirectVector()));
    } else {
        return getDistance(point, ray.getPoint());
    }
}

long double getDistance(const Point& point, const Segment& segment) {
    Vector a_b(segment.getPoint1(), segment.getPoint2());
    Vector b_a(segment.getPoint2(), segment.getPoint1());
    if (a_b.ScalarProduct({segment.getPoint1(), point}) >= 0
        && b_a.ScalarProduct({segment.getPoint2(), point}) >= 0) {
        return getDistance(point, Line(segment.getPoint1(), segment.getPoint2()));
    } else {
        return std::min(getDistance(point, segment.getPoint1()), getDistance(point, segment.getPoint2()));
    }
}


int main() {
    Point A, B, C;
    std::cin >> C;
    std::cin >> A >> B;
    Line line(A, B);
    Ray a_b(A, B);
    Segment segment(A, B);

    std::cout << std::fixed << std::setprecision(9)
              << getDistance(C, line) << '\n'
              << getDistance(C, a_b) << '\n'
              << getDistance(C, segment);
}