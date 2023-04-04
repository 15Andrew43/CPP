#include <iostream>
#include <vector>
#include <algorithm>

struct Point {
    int x_;
    int y_;
};

struct Vector {
    int x_;
    int y_;
    Vector(int x, int y) : x_(x), y_(y) {}
};

int GetMultiVect(const Vector& lhs, const Vector& rhs) {
    return abs(lhs.x_ * rhs.y_ - lhs.y_ * rhs.x_);
}

struct Segment {
    Point main_;
    Point A_;
    Point B_;
};

bool operator<(const Segment& lhs, const Segment& rhs) {
    Point main(lhs.main_);
    Vector MA(lhs.A_.x_ - main.x_, lhs.A_.y_ - main.y_);
    Vector MB(lhs.B_.x_ - main.x_, lhs.B_.y_ - main.y_);
    Vector MC(rhs.A_.x_ - main.x_, rhs.A_.y_ - main.y_);
    Vector MD(rhs.B_.x_ - main.x_, rhs.B_.y_ - main.y_);
    return GetMultiVect(MA, MB) < GetMultiVect(MC, MD);
}




class comp {
public:
    bool operator()(const Segment& lhs, const Segment& rhs) {
        return lhs < rhs;
    }
};


int main() {
    Point main;
    std::cin >> main.x_ >> main.y_;
    int N;
    std::cin >> N;
    std::vector<Segment> segments;
    for (int i = 0; i < N; ++i) {
        Point A;
        Point B;
        std::cin >> A.x_ >> A.y_;
        std::cin >> B.x_ >> B.y_;
        segments.push_back({main, A, B});
    }
    std::sort(segments.begin(), segments.end(), comp());

    for (const Segment segment : segments) {
        std::cout << segment.A_.x_ << ' ' << segment.A_.y_ << ' ' << segment.B_.x_ << ' ' << segment.B_.y_ << '\n';
    }
    return 0;
}