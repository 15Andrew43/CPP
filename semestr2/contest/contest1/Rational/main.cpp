#include <iostream>
#include <cstdlib>
#include <cstring>

class RationalDivisionByZero {
};

int64_t GCD(int64_t p, int64_t q);

class Rational {
private:
    int64_t p_ = 1;
    int64_t q_ = 1; // is maint64_tained to be positive

    void reduce()
    {
        int64_t sign = ( (p_ * q_ < 0) ? -1 : 1);
        p_ = abs(p_);
        q_ = abs(q_);
        int64_t gcd = GCD(p_, q_);
        p_ /= gcd;
        p_ *= sign;
        q_ /= gcd;
    }

public:
    Rational() = default;
    Rational(int64_t p) {
        p_ = p;
    }
    Rational(int64_t p, int64_t q) {
        p_ = p;
        q_ = q;
        reduce();
    }
    explicit Rational(const std::string& r) {
        char CharNumerator[6];
        char CharDenominator[6];
        CharNumerator[0] = CharDenominator[0] = '\0';
        int64_t Length = r.size();
        bool numerator = true;
        int64_t denominator_ind = 0;
        int64_t numerator_ind;
        for (numerator_ind = 0; numerator_ind < Length; ++numerator_ind) {
            if (r[numerator_ind] == '/') {
                CharNumerator[numerator_ind] = '\0';
                numerator = false;
                continue;
            }
            ((numerator) ? CharNumerator[numerator_ind] : CharDenominator[denominator_ind++]) = r[numerator_ind]; //          сделал буль флэг
        }
        if (strlen(CharDenominator) == 0) {
            CharNumerator[numerator_ind] = '\0';
        }
        CharDenominator[denominator_ind] = '\0';

        p_ = atoi(CharNumerator);
        if (strlen(CharDenominator) != 0) {
            q_ = atoi(CharDenominator);
        }
        reduce();
    }


    int64_t getNumerator() const {
        return p_;
    }
    int64_t getDenominator() const {
        return q_;
    }

  /*  void Print64_tRational() const {
        std::cout << p_;
        if (q_ != 1)
            std::cout << '/' << q_;
  }*/


};
bool operator==(Rational lhs, Rational rhs) {
    return (lhs.getNumerator() == rhs.getNumerator() && lhs.getDenominator() == rhs.getDenominator());
}
bool operator!=(Rational lhs, Rational rhs) {
    return !(lhs == rhs);
}
bool operator<(Rational lhs, Rational rhs) {
    return lhs.getNumerator() * rhs.getDenominator() < rhs.getNumerator() * lhs.getDenominator();
}
bool operator>=(Rational lhs, Rational rhs) {
    return !(lhs < rhs);
}
bool operator>(Rational lhs, Rational rhs) {
    return lhs.getNumerator() * rhs.getDenominator() > rhs.getNumerator() * lhs.getDenominator();
}
bool operator<=(Rational lhs, Rational rhs) {
    return !(lhs > rhs);
}

Rational operator+(const Rational& lhs, const Rational& rhs) {
    int64_t p = lhs.getNumerator() * rhs.getDenominator() + rhs.getNumerator() * lhs.getDenominator();
    int64_t q = lhs.getDenominator() * rhs.getDenominator();
    return {p, q};
}
Rational operator-(const Rational& lhs, const Rational& rhs) {
    int64_t p = lhs.getNumerator() * rhs.getDenominator() - rhs.getNumerator() * lhs.getDenominator();
    int64_t q = lhs.getDenominator() * rhs.getDenominator();
    return {p, q};
}

Rational operator*(const Rational& lhs, const Rational& rhs) {
    int64_t p = lhs.getNumerator() * rhs.getNumerator();
    int64_t q = lhs.getDenominator() * rhs.getDenominator();
    return {p, q};
}
Rational operator/(const Rational& lhs, const Rational& rhs) {
    int64_t p = lhs.getNumerator() * rhs.getDenominator();
    int64_t q = lhs.getDenominator() * rhs.getNumerator();
    if (rhs == 0) {
        throw RationalDivisionByZero();
    }
    return {p, q};
}


Rational operator+(const Rational& lhs) {
    return lhs;
}
Rational operator-(const Rational& lhs) {
    return (-1) * lhs;
}

Rational& operator+=(Rational& lhs, const Rational& rhs) {
    lhs = lhs + rhs;
    return lhs;
}
Rational& operator-=(Rational& lhs, const Rational& rhs) {
    lhs = lhs - rhs;
    return lhs;

}
Rational& operator*=(Rational& lhs, const Rational& rhs) {
    lhs = lhs * rhs;
    return lhs;
}
Rational& operator/=(Rational& lhs, const Rational& rhs) {
    lhs = lhs / rhs;
    return lhs;
}
Rational& operator++(Rational& lhs) {
    lhs += 1;
    return lhs;
}
Rational operator++(Rational& lhs, int) {
    return ++lhs - 1;
}
Rational& operator--(Rational& lhs) {
    lhs -= 1;
    return lhs;
}
Rational operator--(Rational& lhs, int) {
    return --lhs + 1;
}


std::istream& operator>>(std::istream& is, Rational& r) {
    std::string r_str;
    is >> r_str;
    r = Rational(r_str);
    return is;
}
std::ostream& operator<<(std::ostream& os, Rational r) {
    std::cout << r.getNumerator();
    if (r.getDenominator() != 1)
        std::cout << '/' << r.getDenominator();
    return os;
}


int64_t GCD(int64_t p, int64_t q) {
    while (q != 0) {
        p %= q;
        std::swap(p, q);
    }
    return p;
}

int main() {
//    cout << Rational (-1111, 9);

    int64_t a;
    std::cin >> a;

    int64_t p, q;
    std::cin >> p >> q;
    const Rational rc(p, q); // q != 0 is guaranteed by author of tests
    std::cout << rc.getNumerator() << ' ' << rc.getDenominator() << std::endl;

    Rational r1, r2;
    std::cin >> r1 >> r2;

    std::cout << r1 << std::endl;
    std::cout << r2 << std::endl;

    try {
        std::cout << 1/r1 << std::endl;
    } catch (const RationalDivisionByZero& ex) {
        std::cout << "Cannot get reciprocal of r1." << std::endl;
    }

    try {
        std::cout << rc/r2 << std::endl;
    } catch (const RationalDivisionByZero& ex) {
        std::cout << "Cannot divide by r2." << std::endl;
    }

    std::cout << (r1 < r2) << std::endl;
    std::cout << (r1 <= r2) << std::endl;
    std::cout << (r1 > r2) << std::endl;
    std::cout << (r1 >= r2) << std::endl;
    std::cout << (r1 == r2) << std::endl;
    std::cout << (r1 != r2) << std::endl;

    std::cout << (r1 < a) << std::endl;
    std::cout << (r1 <= a) << std::endl;
    std::cout << (r1 > a) << std::endl;
    std::cout << (r1 >= a) << std::endl;
    std::cout << (r1 == a) << std::endl;
    std::cout << (r1 != a) << std::endl;

    std::cout << (a < r2) << std::endl;
    std::cout << (a <= r2) << std::endl;
    std::cout << (a > r2) << std::endl;
    std::cout << (a >= r2) << std::endl;
    std::cout << (a == r2) << std::endl;
    std::cout << (a != r2) << std::endl;

    std::cout << rc + a << std::endl
         << a + rc << std::endl
         << -rc * r1 << std::endl
         << (+r1 - r2 * rc) * a << std::endl;

    std::cout << ++r1 << std::endl;
    std::cout << r1 << std::endl;
    std::cout << r1++ << std::endl;
    std::cout << r1 << std::endl;
    std::cout << --r1 << std::endl;
    std::cout << r1 << std::endl;
    std::cout << r1-- << std::endl;
    std::cout << r1 << std::endl;
    std::cout << ++(++r1) << std::endl;
    std::cout << r1 << std::endl;

    std::cout << ((((r1 += r2) /= Rational(-5,3)) -= rc) *= a) << std::endl;
    std::cout << (r1 += r2 /= 3) << std::endl;
    std::cout << r1 << std::endl;
    std::cout << r2 << std::endl;
    return 0;

}