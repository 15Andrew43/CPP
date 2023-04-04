#include <iostream>

class MatrixWrongSizeError : public std::exception {

};

class MatrixIndexError : public std::exception {

};

class MatrixIsDegenerateError : public std::exception {

};

// non-specified functions to get "zero" of type T

template<typename T>
T getZero() {
    return T(0);
}
template <typename T>

T getOne() {
    return T(1);
}

//=============== Matrix class ===============//

template <class T>
void mem_alloc_2array(T** &array, int x, int y) {
    array = new T* [x];
    for (int i = 0; i < x; ++i) {
        array[i] = new T [y];
    }
}

template <class T>
void delete_2array(T** &array, int x) {
    for (int i = 0; i < x; ++i) {
        delete[] array[i];
    }
    delete[] array;
}

template <class T>
void fill_zeros(T** &array, int x, int y) {
    for (int i = 0; i < x; ++i) {
        for (int j = 0 ; j < y; ++j) {
            array[i][j] = 0;
        }
    }
}
/*
template <class T>
void Copy(T** &to_array, T** &from_array, int x, int y) {
    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
            to_array[i][j] = from_array[i][j];
        }
    }
}
*/
class Rational;

template <class T>
class Matrix {
protected:
    int rowsCnt;
    int colsCnt;
    T** array;
    // type your code here
protected:
    // type your code here
public:
    Matrix(int rows, int cols) {
        rowsCnt = rows;
        colsCnt = cols;
        mem_alloc_2array(array, rowsCnt, colsCnt);
        fill_zeros(array, rowsCnt, colsCnt);
    }
    Matrix(const Matrix& other) {
        rowsCnt = other.getRowsNumber();
        colsCnt = other.getColumnsNumber();
        mem_alloc_2array(array, rowsCnt, colsCnt);
        Copy(other);
        /*
        for (int i = 0; i < rowsCnt; ++i) {
            for (int j = 0; j < colsCnt; ++j) {
                array[i][j] = other.array[i][j];
            }
        }
         */
    }
    Matrix& operator=(const Matrix& other) {
        if (&other == this) {
            return *this;
        }
        delete_2array(array, getRowsNumber());
        rowsCnt = other.getRowsNumber();
        colsCnt = other.getColumnsNumber();

        mem_alloc_2array(array, rowsCnt, colsCnt);
        for (int i = 0; i < getRowsNumber(); ++i) {
            for (int j = 0; j < getColumnsNumber(); ++j) {
                array[i][j] = other.array[i][j];
            }
        }
        return *this;
    }
    ~Matrix() {
        delete_2array(array, getRowsNumber());
    }

    void Copy(const Matrix<T>& other) {
        for (int i = 0; i < getRowsNumber(); ++i) {
            for (int j = 0; j < getColumnsNumber(); ++j) {
                array[i][j] = other.array[i][j];
            }
        }
    }

    const T operator()(int idx, int idy) const {
        if (idx < 0 || idx >= rowsCnt || idy < 0 || idy >= colsCnt) {
            throw MatrixIndexError();
        }
        return array[idx][idy];
    }
    T& operator()(int idx, int idy) {
        if (idx < 0 || idx >= rowsCnt || idy < 0 || idy >= colsCnt) {
            throw MatrixIndexError();
        }
        return array[idx][idy];
    }

    Matrix getTransposed() {
        Matrix res(colsCnt, rowsCnt);
        for (int i = 0; i < rowsCnt; ++i) {
            for (int j = 0; j < colsCnt; ++j) {
                res[j][i] = array[i][j];
            }
        }
        return res;
    }

    Matrix& Transpose() {
        *this = getTransposed();
        return *this;
    }

    const T* operator[](int index) const {
        return array[index];
    }
    T*& operator[](int index) {
        return array[index];
    }

    int getRowsNumber() const {
        return rowsCnt;
    }
    int getColumnsNumber() const {
        return colsCnt;
    }
};

template <class T>
Matrix<T> operator+(const Matrix<T>& lhs, const Matrix<T>& rhs) {
    try{
        if (lhs.getRowsNumber() != rhs.getRowsNumber() || lhs.getColumnsNumber() != rhs.getColumnsNumber()) {
            throw MatrixWrongSizeError();
        }
        Matrix<T> res(lhs.getRowsNumber(), lhs.getColumnsNumber());
        for (int i = 0; i < lhs.getRowsNumber(); ++i) {
            for (int j = 0; j < lhs.getColumnsNumber(); ++j) {
                res[i][j] = lhs[i][j] + rhs[i][j];
            }
        }
        return res;
    } catch (MatrixWrongSizeError()) {
        //    std::cout << "MatrixWrongSizeError() in operator+ or +=\n";
        throw;
    }
}
template <class T>
Matrix<T>& operator+=(Matrix<T>& lhs, const Matrix<T>& rhs) {
    lhs = lhs + rhs;
    return lhs;
}
template <class T>
Matrix<T> operator-(const Matrix<T>& lhs, const Matrix<T>& rhs) {
    try{
        if (lhs.getRowsNumber() != rhs.getRowsNumber() || lhs.getColumnsNumber() != rhs.getColumnsNumber()) {
            throw MatrixWrongSizeError();
        }
        Matrix<T> res(lhs.getRowsNumber(), lhs.getColumnsNumber());
        for (int i = 0; i < lhs.getRowsNumber(); ++i) {
            for (int j = 0; j < lhs.getColumnsNumber(); ++j) {
                res[i][j] = lhs[i][j] - rhs[i][j];
            }
        }
        return res;
    } catch (MatrixWrongSizeError()) {
        //    std::cout << "MatrixWrongSizeError() in operator- or -=\n";
        throw;
    }
}
template <class T>
Matrix<T>& operator-=(Matrix<T>& lhs, const Matrix<T>& rhs) {
    lhs = lhs - rhs;
    return lhs;
}
template <class T>
Matrix<T> operator*(const Matrix<T>& matr, const T& val) {
    Matrix<T> res(matr.getRowsNumber(), matr.getColumnsNumber());
    for (int i = 0; i < matr.getRowsNumber(); ++i) {
        for (int j = 0; j < matr.getColumnsNumber(); ++j) {
            res[i][j] = matr[i][j] * val;
        }
    }
    return res;
}
template <class T>
Matrix<T> operator*(const T& val, const Matrix<T>& matr) {
    Matrix<T> res(matr.getRowsNumber(), matr.getColumnsNumber());
    for (int i = 0; i < matr.getRowsNumber(); ++i) {
        for (int j = 0; j < matr.getColumnsNumber(); ++j) {
            res[i][j] = matr[i][j] * val;
        }
    }
    return res;
}
template <class T>
Matrix<T>& operator*=(Matrix<T>& matr, const T& val) {
    matr = matr * val;
    return matr;
}
template <class T>
Matrix<T> operator*(const Matrix<T>& lhs, const Matrix<T>& rhs) {   // скорее всего где-то накосячил стоит проверить
    try {
        if (lhs.getColumnsNumber() != rhs.getRowsNumber()) {
            throw MatrixWrongSizeError();
        }
        Matrix<T> res(lhs.getRowsNumber(), rhs.getColumnsNumber());
        for (int i = 0; i < res.getRowsNumber(); ++i) {
            for (int j = 0; j < res.getColumnsNumber(); ++j) {
                res[i][j] = 0;
                for (int k = 0; k < lhs.getColumnsNumber(); ++k) {
                    res[i][j] += (lhs[i][k] * rhs[k][j]);
                }
            }
        }
    //    std::cout << res << '\n';
        return res;
    } catch (MatrixWrongSizeError()) {
    //    std::cout << "MatrixWrongSizeError() in matr*matr\n";
        throw;
    }
}
template <class T>
Matrix<T>& operator*=(Matrix<T>& lhs, const Matrix<T>& rhs) {
    lhs = lhs * rhs;
    return lhs;
}

template <class T>
std::istream& operator>>(std::istream& is, Matrix<T>& matr) {
    for (int i = 0; i < matr.getRowsNumber(); ++i) {
        for (int j = 0; j < matr.getColumnsNumber(); ++j) {
            std::cin >> matr[i][j];
        }
    }
    return is;
}
template <class T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& matr) {
    for (int i = 0; i < matr.getRowsNumber(); ++i) {
        for (int j = 0; j < matr.getColumnsNumber(); ++j) {
            std::cout << matr[i][j] << ' ';
        }
        std::cout << '\n';
    }
    return os;
}

/*
template <class T>
void P(int i, int j, Matrix<T>& matr) {
    Rational* help = matr[i];
    matr[i] = matr[j];
    matr[j] = help;
}
template <class T>
void D(int j, T lambda, Matrix<T>& matr) {
    for (int i = 0; i < matr.getColumnsNumber(); ++i) {
        matr[j][i] *= lambda;
    }
}
template <class T>
void T(int i, int j, T lambda, Matrix<T>& matr) {
    for (int k = 0; k < matr.getColumnsNumber(); ++k) {
        matr[i][k] -= (matr[j][k] * lambda);
    }
}
*/
//=============== SquareMatrix class ===============================================================//
/*
template <typename T>
class SquareMatrix : public Matrix<T> {
public:
    explicit SquareMatrix(int n) : Matrix<T>(n, n){
    }
    SquareMatrix(const SquareMatrix<T>& other) : Matrix<T>(other){
    }
    SquareMatrix<T>& operator=(const SquareMatrix<T>& other) {
        if (&other == this) {
            return (*this);
        }
        T** old_array = Matrix<T>::array;
        for (int i = 0; i < Matrix<T>::rowsCnt; ++i) {
            delete[] old_array[i];
        }
        delete[] old_array;
        Matrix<T>::rowsCnt = other.getRowsNumber();

        Matrix<T>::array = new T* [getSize()];
        for (int i = 0; i < getSize(); ++i) {
            Matrix<T>::array[i] = new T [getSize()];
        }

        for (int i = 0; i < getSize(); ++i) {
            for (int j = 0; j < getSize(); ++j) {
                Matrix<T>::array[i][j] = other.Matrix<T>::array[i][j];
            }
        }
  //      std::cout << (*this) << '\n';

        return (*this);
    }

    int getSize() const {
        return Matrix<T>::getRowsNumber();
    }

    SquareMatrix<T> getInverse() const {
        int L = getSize();
        SquareMatrix<T>E(L);
        for (int i = 0; i < L; ++i) {
            E[i][i] = 1;
        }
        for (int i = 0; i < L; ++i) {
            bool IsDegenerate = true;
            for (int j = i; j < L; ++j) {
   //             std::cout << (*this)[i][j] << '\n';
                if ((*this)[j][i] != 0) {
                    //P(i, j, (*this)); // выносим строку наверх с ненулевым первым символом
                    //P(i, j, E);
                    Rational* help = Matrix<T>::array[i];
                    Matrix<T>::array[i] = Matrix<T>::array[j];
                    Matrix<T>::array[j] = help;

                    help = E[i];
                    E[i] = E[j];
                    E[j] = help;

                    IsDegenerate = false;
                    //std::swap(matr[i], matr[j]);
                    break;
                }
            }
            if (IsDegenerate) {
                throw MatrixIsDegenerateError();
            }
            T lambda = 1/(*this)[i][i];
            //D(i, lambda, (*this)); // приводим первый элемент к 1
            //D(i, lambda, E);
            for (int k = 0; k < L; ++k) {
                Matrix<T>::array[i][k] *= lambda;
            }
            for (int k = 0; k < L; ++k) {
                E[i][k] *= lambda;
            }
   //         std::cout << "E = \n" << E << '\n';

            for (int j = 0; j < L; ++j) {
                if (j == i) {
                    continue;
                }
                lambda = (*this)[j][i];
//                T(j, i, lambda, (*this)); // делаем остальные числа в столбце нулями
 //               T(j, i, lambda, E);
                for (int k = 0; k < L; ++k) {
                    Matrix<T>::array[j][k] -= (Matrix<T>::array[i][k] * lambda);
                }
                for (int k = 0; k < L; ++k) {
                    E[j][k] -= (E[i][k] * lambda);
                }
            }
 //           std::cout << "E = \n" << E << '\n';
 //           std::cout << "---------------------------\n";
        }
        return E;
    }

    SquareMatrix<T>& Invert() {
        SquareMatrix res(getSize());
        (*this) = this->getInverse();
        return (*this);
    }

    T getTrace() const {
        T s = 0;
        for (int i = 0; i < getSize(); ++i) {
            s += (*this)[i][i];
        }
        return s;
    }

    T getDeterminant() const {
        return Determinate((*this));
    }

    SquareMatrix getTransposed() {
        SquareMatrix res(getSize());
        for (int i = 0; i < getSize(); ++i) {
            for (int j = 0; j < getSize(); ++j) {
                res[j][i] = (*this)[i][j];
            }
        }
        return res;
    }
    SquareMatrix& Transpose() {
        (*this) = getTransposed();
        return (*this);
    }

};

template <class T>
T Determinate(const SquareMatrix<T>& matr) {
    T d = 0;
    int k = 1;
    if (matr.getSize() == 1) {
        return (matr)[0][0];
    } else if (matr.getSize() == 2) {
        return matr[0][0] * matr[1][1] - matr[0][1] * matr[1][0];
    }
    else {

        for (int i = 0; i < matr.getSize(); ++i) {
   //         std:: cout << get_det_matr(0, i, matr) << '\n';
            d = d + (matr[0][i] * k * (get_det_matr(0, i, matr)).getDeterminant());
            k = -k;
        }
    }
    return d;
}

template <class T>
SquareMatrix<T> get_det_matr(int I, int J, const SquareMatrix<T>& matr) {
    SquareMatrix<T> res(matr.getSize()-1);
    for (int i = 0; i < matr.getSize(); ++i) {
        for (int j = 0; j < matr.getSize(); ++j) {
            if (i == I || j == J) {
                continue;
            }
            int x, y;
            if (i < I) {
                x = i;
            } else {
                x = i - 1;
            }
            if (j < J) {
                y = j;
            } else {
                y = j - 1;
            }
            res[x][y] = matr[i][j];
 //           std::cout << "i = "<<i << "   j = " << j << "    [][] = " << matr[i][j] << '\n';
        }
    }
    return res;
}

template <class T>
SquareMatrix<T> operator+(const SquareMatrix<T>& lhs, const SquareMatrix<T>& rhs) {
    try{
        if (lhs.getSize() != rhs.getSize()) {
            throw MatrixWrongSizeError();
        }
        SquareMatrix<T> res(lhs.getSize());
        for (int i = 0; i < lhs.getSize(); ++i) {
            for (int j = 0; j < lhs.getSize(); ++j) {
                res[i][j] = lhs[i][j] + rhs[i][j];
            }
        }
        return res;
    } catch (MatrixWrongSizeError()) {
        //    std::cout << "MatrixWrongSizeError() in operator+ or +=\n";
        throw;
    }
}
template <class T>
SquareMatrix<T>& operator+=(SquareMatrix<T>& lhs, const SquareMatrix<T>& rhs) {
    lhs = lhs + rhs;
    return lhs;
}
template <class T>
SquareMatrix<T> operator-(const SquareMatrix<T>& lhs, const SquareMatrix<T>& rhs) {
    try{
        if (lhs.getSize() != rhs.getSize()) {
            throw MatrixWrongSizeError();
        }
        SquareMatrix<T> res(lhs.getSize());
        for (int i = 0; i < lhs.getSize(); ++i) {
            for (int j = 0; j < lhs.getSize(); ++j) {
                res[i][j] = lhs[i][j] - rhs[i][j];
            }
        }
        return res;
    } catch (MatrixWrongSizeError()) {
        //    std::cout << "MatrixWrongSizeError() in operator- or -=\n";
        throw;
    }
}
template <class T>
SquareMatrix<T>& operator-=(SquareMatrix<T>& lhs, const SquareMatrix<T>& rhs) {
    lhs = lhs - rhs;
    return lhs;
}
template <class T>
SquareMatrix<T> operator*(const SquareMatrix<T>& matr, const T& val) {
    SquareMatrix<T> res(matr.getSize());
    for (int i = 0; i < matr.getSize(); ++i) {
        for (int j = 0; j < matr.getSize(); ++j) {
            res[i][j] = matr[i][j] * val;
        }
    }
    return res;
}
template <class T>
SquareMatrix<T> operator*(const SquareMatrix<T>& matr, const int& val) {
    SquareMatrix<T> res(matr.getSize());
    for (int i = 0; i < matr.getSize(); ++i) {
        for (int j = 0; j < matr.getSize(); ++j) {
            res[i][j] = matr[i][j] * val;
        }
    }
    return res;
}
template <class T>
SquareMatrix<T> operator*(const int& val, const SquareMatrix<T>& matr) {
    SquareMatrix<T> res(matr.getSize());
    for (int i = 0; i < matr.getSize(); ++i) {
        for (int j = 0; j < matr.getSize(); ++j) {
            res[i][j] = matr[i][j] * val;
        }
    }
    return res;
}
template <class T>
SquareMatrix<T> operator*(const T& val, const SquareMatrix<T>& matr) {
    SquareMatrix<T> res(matr.getSize());
    for (int i = 0; i < matr.getSize(); ++i) {
        for (int j = 0; j < matr.getSize(); ++j) {
            res[i][j] = matr[i][j] * val;
        }
    }
    return res;
}
template <class T>
SquareMatrix<T>& operator*=(SquareMatrix<T>& matr, const T& val) {
    matr = matr * val;
    return matr;
}
template <class T>
SquareMatrix<T> operator*(const SquareMatrix<T>& lhs, const SquareMatrix<T>& rhs) {   // скорее всего где-то накосячил стоит проверить
    try {
        if (lhs.getSize() != rhs.getSize()) {
            throw MatrixWrongSizeError();
        }
        SquareMatrix<T> res(lhs.getSize());
        for (int i = 0; i < res.getSize(); ++i) {
            for (int j = 0; j < res.getSize(); ++j) {
                T s = 0;
                for (int k = 0; k < lhs.getSize(); ++k) {
                    s += (lhs[i][k] * rhs[k][j]);
                }
                res[i][j] = s;
            }
        }
        //    std::cout << res << '\n';
        return res;
    } catch (MatrixWrongSizeError()) {
        //    std::cout << "MatrixWrongSizeError() in matr*matr\n";
        throw;
    }
}
template <class T>
SquareMatrix<T>& operator*=(SquareMatrix<T>& lhs, const SquareMatrix<T>& rhs) {
    lhs = lhs * rhs;
    return lhs;
}


*/

//================ class Rational =========================================================================//

#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

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



//=================== main() ===============//

using namespace std;

int main() {
    int m, n, p, q;
    cin >> m >> n >> p >> q;

    Matrix<int> A(m, n), B(p, q);
    cin >> A >> B;
    A = A;

    try {
        cout << A + B * 2 - m * A << endl;
        cout << (A -= B += A *= 2) << endl;
        cout << (((A -= B) += A) *= 2) << endl;
    } catch (const MatrixWrongSizeError&) {
        cout << "A and B are of different size." << endl;
    }
    B = A;
    {
        Matrix<int> AA(A);
        Matrix<int> AAA(1, 1);
        AAA = A;
        cout << AA << endl;
        cout << (AAA += Matrix<int>(m, n)) + B << endl;
    }

    Rational r;
    cin >> r;
    Matrix<Rational> C(m, n), D(p, q);
    cin >> C >> D;
    try {
        cout << C * D << endl;
        cout << (C *= D) << endl;
        cout << C << endl;
    } catch (const MatrixWrongSizeError&) {
        cout << "C and D have not appropriate sizes for multiplication." << endl;
    }

    cout << C.getTransposed() * (r * C) << endl;
    cout << C.Transpose() << endl;

    try {
        (C(0, 0) *= 6) /= 3;
        cout << C(0, 0) << endl;
        cout << C(m, m) << endl;
    } catch (const MatrixIndexError&) {
        cout << "Index out of range." << endl;
    }

    {
        const Matrix<Rational>& rC = C;
        cout << rC << endl;
        cout << rC.getRowsNumber() << ' ' << rC.getColumnsNumber() << ' ' << rC(0, 0) << endl;
        cout << (C = C) * (Rational(1, 2) * rC).getTransposed() << endl;
    }

    return 0;
}