#include <cstring>
#include <math.h>
#include <cstdio>
#include <iostream>
#include <iomanip>

#include <utility>

typedef uint64_t digit_type;

using namespace std;

size_t ConvertToBase(digit_type* arrN, digit_type N, digit_type kBase);

class BigIntegerOverflow {
};

class BigInteger {
private:
    const static size_t maxLength_ = 3000; // number of digits, количество болок по baselog цифр
    const static uint8_t baseLog_ = 9; // use 1 or 2 for debug, по умлчанию 9

//    typedef uint32_t digit_type;
    typedef uint64_t double_digit_type; // for multiplication

    //const static uint32_t kBase_ = static_cast<digit_type>(pow(10, baseLog_));  // base of numeral system
    const static uint64_t kBase_ = 1000000000;
    const static size_t maxReadSize_ = 20010; // for reading (buffer size), максимальное количество символов на входе

    digit_type digits_[maxLength_] = {}; //         должен был обнулиться
    //bool is_negative_;

    size_t Length_ = 0;

public:
    BigInteger() = default;
    BigInteger(int N) {                      //  только для положительных, про отрицательные не думал
        this->Length_ = ConvertToBase(digits_, N, kBase_);
    }
    BigInteger(const uint64_t N) {                      //  только для положительных, про отрицательные не думал
        this->Length_ = ConvertToBase(digits_, N, kBase_);
    }
    BigInteger(const char* ChN) {               //  только для положительных, про отрицательные не думал
        long long int ind = strlen(ChN);
        char category[baseLog_+1];
        size_t L = 0;
        while (ind > baseLog_) {
            ind -= baseLog_;
            for (long long int i = ind; i < ind + baseLog_; ++i) {
                category[i - ind] = ChN[i];
            }
            category[baseLog_] = '\0';
            digits_[L++] = atoi(category);
        }

        for (long long int i = 0; i < ind; ++i) {
            category[i] = ChN[i];
        }
        if (ind == 1 && category[0] == '0') { // раньше у нуля была длина 1, теперь 0
            Length_ = 0;
        } else {
            category[ind] = '\0';
            digits_[L++] = atoi(category);
            Length_ = L;
        }
    }

    friend bool operator==(const BigInteger& lhs, const BigInteger& rhs);
    friend bool operator!=(const BigInteger& lhs, const BigInteger& rhs);
    friend bool operator<(const BigInteger& lhs, const BigInteger& rhs);
    friend bool operator>(const BigInteger& lhs, const BigInteger& rhs);
    friend bool operator>=(const BigInteger& lhs, const BigInteger& rhs);
    friend bool operator<=(const BigInteger& lhs, const BigInteger& rhs);


    friend BigInteger operator+(const BigInteger& lhs, const BigInteger& rhs);
    friend BigInteger operator-(const BigInteger& lhs, const BigInteger& rhs);
    friend BigInteger operator*(const BigInteger& lhs, const BigInteger& rhs);
    friend BigInteger operator/(const BigInteger& lhs, const BigInteger& rhs);
    friend uint64_t divide_binary_search(const BigInteger& residual, const BigInteger& rhs);

    friend istream& operator>>(istream& is, BigInteger& N);
    friend ostream& operator<<(ostream& os, BigInteger N);

    BigInteger sqrt() { // не работает почему-то
        BigInteger l(1);
        BigInteger r(*this);
        while (r - l > 1) {
         //   cout << "l = " << l << "       r = " << r << '\n';
//            cout << (l + r) << endl;
//            cout << ((l + r) / (BigInteger)2);
            BigInteger m = ((l + r) / 2);
            BigInteger comparison = m * m;
       //     cout << "m = " << m  << "      m^2 = " << comparison << '\n';
            if (comparison > (*this)) {
                r = m;
     //       cout << " r = " << r << '\n';
            } else if (comparison < (*this)) {
                l = m;
   //         cout << " l = " << l << '\n';
            } else {
                return m;
            }
 //           cout << "----------------------------------------\n";
        }
        return l;
    }
};



size_t ConvertToBase(digit_type* arrN, digit_type N, digit_type kBase) { //           CHECK!
    digit_type L = 0;
    while (N) {
        arrN[L++] = N % kBase;
        N /= kBase;
    }
    return L;
}

BigInteger sqrt_binary_search(const BigInteger& BI) {
    BigInteger l = 0;
    BigInteger r = BI;
    while (r - l > 1) {
        BigInteger m = (l + r) / 2;
        BigInteger comparison = m * m;
//        cout << "comparison = " << comparison  << "      residual = " << residual << '\n';
        if (comparison > BI) {
            r = m;
//            cout << " r = " << r << '\n';
        } else if (comparison < BI) {
            l = m;
//            cout << " l = " << r << '\n';
        } else {
            return m;
        }
    }
    return l;
}

uint64_t divide_binary_search(const BigInteger& residual, const BigInteger& rhs) {
    uint64_t l = 0, r = residual.kBase_;
    while (r - l > 1) {
        uint64_t m = (l + r) / 2;
        BigInteger comparison = m * rhs;
//        cout << "comparison = " << comparison  << "      residual = " << residual << '\n';
        if (comparison > residual) {
            r = m;
//            cout << " r = " << r << '\n';
        } else if (comparison < residual) {
            l = m;
//            cout << " l = " << r << '\n';
        } else {
            return m;
        }
    }
//    cout << "result_l = " << l << '\n';
    return l;
}

bool operator==(const BigInteger& lhs, const BigInteger& rhs) {
    if (lhs.Length_ != rhs.Length_) {
        return false;
    } else {
        for (int i = lhs.Length_; i >= 0; --i) {
            if (lhs.digits_[i] != rhs.digits_[i]) {
                return false;
            }
        }
        return true;
    }
}
bool operator!=(const BigInteger& lhs, const BigInteger& rhs) {
    return !(lhs == rhs);
}
bool operator<(const BigInteger& lhs, const BigInteger& rhs) {
    if (lhs.Length_ < rhs.Length_) {
        return true;
    } else if (lhs.Length_ > rhs.Length_) {
        return false;
    } else {
        for (int i = lhs.Length_-1; i >= 0; --i) {
            if (lhs.digits_[i] > rhs.digits_[i]) {
                return false;
            } else if (lhs.digits_[i] < rhs.digits_[i]) {
                return true;
            }
        }
        return false;
    }
}
bool operator>(const BigInteger& lhs, const BigInteger& rhs) {
    return (!(lhs < rhs) && lhs != rhs);
}
bool operator>=(const BigInteger& lhs, const BigInteger& rhs) {
    return !(lhs < rhs);
}
bool operator<=(const BigInteger& lhs, const BigInteger& rhs) {
    return !(lhs > rhs);
}



BigInteger operator+(const BigInteger& lhs, const BigInteger& rhs) {
    BigInteger res;
    digit_type residual = 0;
    size_t L = max(lhs.Length_, rhs.Length_);
    res.Length_ = L;
    for (size_t i = 0; i < L; ++i) {
        size_t sum = lhs.digits_[i] + rhs.digits_[i] + residual;
        res.digits_[i] = sum % res.kBase_;
        residual = sum / res.kBase_;
    }
    if (residual != 0) {
        res.Length_ = L+1;
        res.digits_[L] = residual;
    }
    return res;
}
BigInteger& operator+=(BigInteger& lhs, const BigInteger& rhs) {
    lhs = lhs + rhs;
    return lhs;
} // не по заданию

BigInteger operator-(const BigInteger& lhs, const BigInteger& rhs) {
    BigInteger res = lhs;
    size_t L = lhs.Length_;
    for (size_t i = 0; i < L; ++i) {
        if (res.digits_[i] < rhs.digits_[i]) {
            int borrow = i+1;
            while (res.digits_[borrow] == 0) {
                res.digits_[borrow] = res.kBase_-1;
                borrow++;
            }
            --res.digits_[borrow];
            res.digits_[i] += res.kBase_;
        }
        res.digits_[i] -= rhs.digits_[i];
    }
    for (long long int i = L-1; i >=0; --i) {
        if (res.digits_[i] != 0) {
            res.Length_ = i+1;
            return res;
        }
    }
    res.Length_ = 0;
    return res;
}
BigInteger& operator-=(BigInteger& lhs, const BigInteger& rhs) {
    lhs = lhs - rhs;
    return lhs;
} // не по заданию

BigInteger operator*(const BigInteger& lhs, const BigInteger& rhs) {
    if (lhs.Length_ == 0 || rhs.Length_ == 0) {
        return 0;
    }
    BigInteger res;
    size_t lenLHS = lhs.Length_;
    size_t lenRHS = rhs.Length_;
    size_t residual = 0;
    for (size_t i = 0; i < lenLHS; ++i) {
        BigInteger help;
        for (size_t j = 0; j < lenRHS; ++j) {
            size_t multiplication = lhs.digits_[i] * rhs.digits_[j] + residual;
            help.digits_[i+j] = multiplication % res.kBase_;
            residual = multiplication / res.kBase_;
        }
        help.Length_ = i + lenRHS;
        if (residual != 0) {
            help.digits_[i + lenRHS] = residual;
            ++help.Length_;
        }
        residual = 0;
        res += help;
    }
    return res;
}
BigInteger& operator*=(BigInteger& lhs, const BigInteger& rhs) {
    lhs = lhs * rhs;
    return lhs;
} // не по заданию

BigInteger operator/(const BigInteger& lhs, const BigInteger& rhs) {
    if (lhs < rhs) {
        return 0;
    } else if (lhs == rhs) {
        return 1;
    }
    uint64_t res[lhs.maxLength_];
    int res_ind = 0;
    BigInteger residual;
    int lhs_ind = lhs.Length_ - rhs.Length_;
//    cout << "lhs_ind = " << lhs_ind << '\n';
//    cout << "lhs.Length_ = " << lhs.Length_ << '\n';

    // создаем residual
    for (size_t j = 0, i = lhs_ind; i < lhs.Length_; ++i, ++j) {
        residual.digits_[j] = lhs.digits_[i];
        ++residual.Length_;
    }
//    cout << residual << '\n';

    if (residual < rhs) {
        residual = (residual * residual.kBase_ + lhs.digits_[--lhs_ind]);
    }//                                                                 теперь residual точно больше rhs

    for (; lhs_ind >= 0;) {

        if (residual < rhs) {
//            residual = (residual * residual.kBase_ + lhs.digits_[lhs_ind]);
            res[res_ind++] = 0;
        } else {

    //    if (residual >= rhs) { // ????????????????????????????????????
//            cout << residual << '\n';

            res[res_ind] = divide_binary_search(residual, rhs);
            residual = (residual - rhs * res[res_ind++]); // остаток

//            cout << residual << '\n';
        }
        residual = (residual * residual.kBase_ + lhs.digits_[--lhs_ind]);
    }
//    cout << res_ind << '\n';
    BigInteger BIres;
    for (int i = res_ind-1, j = 0; i >=0; --i, ++j) {
        BIres.digits_[j] = res[i];
        ++BIres.Length_;
    }

    return BIres;
}
BigInteger& operator/=(BigInteger& lhs, const BigInteger& rhs) {
    lhs = lhs / rhs;
    return lhs;
} // не по заданию

BigInteger operator%(const BigInteger& lhs, const BigInteger& rhs) {
    return lhs - rhs * (lhs/rhs);
}
BigInteger& operator%=(BigInteger& lhs, const BigInteger& rhs) {
    lhs = lhs % rhs;
    return lhs;
} // не по заданию





BigInteger NOD(BigInteger p, BigInteger q) {
    while (q != 0) {
        p %= q;
        swap(p, q);
    }
    return p;
}

istream& operator>>(istream& is, BigInteger& N) {
    char N_ch[N.maxReadSize_+1];
    is >> N_ch;
    N_ch[N.maxReadSize_] = '\0';
    N = BigInteger(N_ch);
    return is;
}
ostream& operator<<(ostream& os, BigInteger N) {
    if (N.Length_==0) {
        os << 0;
    } else {
/*
        if (!true) {
            os << '-';
        }
*/
        os << N.digits_[N.Length_-1];
        for (long long int i = N.Length_-2; i >= 0 ; --i) {
            os<< setfill('0') << setw(N.baseLog_) << N.digits_[i]; //                   зависиит от kBase!
        }
    }
    return os;
}

int main() {
//    std::ios_base::sync_with_stdio(false); // отключает синхронизацию iostreams с stdio
//    std::cin.tie(nullptr);
/*
    BigInteger b("123");
    BigInteger c(91);
    BigInteger d;
    d = b+c;
    cout <<setw(2)<< d << '\n';
    cout << 1234124134;
*/

 //   cout << (BigInteger(201) / (BigInteger)(2)) << endl;
    BigInteger A;
//    BigInteger B;
    cin >> A;

    cout << A.sqrt();

/*
    BigInteger a, b;
    std::cin >> a >> b;
    int c;
    std::cin >> c;

    std::cout << (a * c == c * --b++) << '\n';
    std::cout << (a + 5 < ++b--) << '\n';
    std::cout << (a <= b) << '\n';
    std::cout << (a > b - 5) << '\n';
    std::cout << (a >= b - 5) << '\n';
    std::cout << (a != b * c) << '\n';
    std::cout << (a == -b) << '\n';

    BigInteger d("123"), e(1ULL << 63);
    std::cout << (d + c) * e << '\n';

    try {
        a += b;
        b = a - b;
        a -= b;
        std::cout << a + b << '\n';
        std::cout << a - b << '\n';
        std::cout << a * b << '\n';
    } catch (BigIntegerOverflow) {
        std::cout << "Overflow" << '\n';
    }
*/
}