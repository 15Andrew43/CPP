#include <iostream>
#include <string>

// Variadic Min example
// Usage: Min(x, y, z, t);

// End of recursion
template <class T>
T Min(const T& value) {
    return value;
}

// Recursive definition
template <class T, class... Args>
T Min(const T& first, const T& second, const Args&... args) {
    T min_value = (first < second) ? first : second;
    return Min(min_value, args...);
}
// args... <=> args[0], args[1], ...
// pattern(args)... <=> pattern(args[0]), pattern(args[1]), ...


// Variadic Print example
// Usage: Print(5, "aba", true, 7.8);

// End of recursion
void Print() {
    std::cout << "\n";
}

// Recursive definition
template <class T, class... Args>
void Print(const T& value, const Args&... args) {
    std::cout << value << ' ';
    Print(args...);
}

// Variadic templates usage example 1
class A {
    int x_;
    std::string y_;
    int z_;

public:
    explicit A(int x = 0, const std::string& y = "_", int z = 0)
        : x_(x)
        , y_(y)
        , z_(z) {

        std::cout << x_ << ' ' << y_ << ' ' << z_ << '\n';
    }
};

class B {
    A a_;

public:
    template <class... Args>
    explicit B(const Args&... args) : a_(args...) {
    }
};
// A a(4, "an", 6);

// Variadic templates usage example 2
// std::vector::emplace_back
// v.push_back(A(0, "", 1)) vs v.emplace_back(0, "", 1);

// Metafunctions
template <class T>
struct IsConst {
    static const bool value = false;
};

template <class T>
struct IsConst<const T> {
    static const bool value  = true;
};

template <class T>
struct IsReference {
    static const bool value = false;
};

template <class T>
struct IsReference<T&> {
    static const bool value = true;
};

template <class T>
void PrintConst() {
    if (IsConst<T>::value) {
        std::cout << "const\n";
    } else {
        std::cout << "not const\n";
    }
}

template <class T, class U, class... Args>
struct IsSame {
    static const bool value = IsSame<T, U>::value && IsSame<U, Args...>::value;
};

template <class T, class U>
struct IsSame<T, U> {
    static const bool value = false;
};

template <class T>
struct IsSame<T, T> {
    static const bool value = true;
};

// Compile-time calculations
template <int... Values>
struct Sum;

template <int X, int... Values>
struct Sum<X, Values...> {
    static const int value = X + Sum<Values...>::value;
};

template <>
struct Sum<> {
    static const int value = 0;
};

// HW (21.04)
template <int... Values>
struct Mean; // Mean<Values...>::value == (Values[0] + Values[1] + ... Values[n - 1]) / n

template <int... Values>
struct Var; // Var<Values...>::value == Mean<Values^2> - Mean<Values>^2


// Bonus
#include <tuple>

std::tuple<int, double> Func() {
    return {5, 5.0};
}

template <class... Args>
struct Tuple;

template <class Head, class... Args>
struct Tuple<Head, Args...> {
    Head head_;
    Tuple<Args...> tail_;

    Tuple() = default;
    Tuple(const Head& head, const Args&... args) : head_(head), tail_(args...) {
    }
};

template <>
struct Tuple<> {
};

// [head_, tail_]
// (int, double, bool) -> (int, Tuple(double, bool))
                                //double, Tuple(bool)
                                //bool, Tuple()
                  // get<1>(tuple) = 1;
                  // std::cout << get<1>(tuple);

template <size_t Idx, class... Args>
struct GetHelper;

template <size_t Idx, class Head, class... Args>
struct GetHelper<Idx, Head, Args...> {
//    using ReturnType = ...; // YOUR CODE
//
//    static ReturnType& Get(Tuple<Head, Args...>& tuple) {
//        ...; // YOUR CODE
//    }
};

template <class Head, class... Args> // Tuple<Head, Args...>
struct GetHelper<0, Head, Args...> {
    using ReturnType = Head; // <=> typedef Head ReturnType;

    static ReturnType& Get(Tuple<Head, Args...>& tuple) {
        return tuple.head_;
    }
};


template <size_t Idx, class... Args>
typename GetHelper<Idx, Args...>::ReturnType& Get(Tuple<Args...>& tuple) {
    return GetHelper<Idx, Args...>::Get(tuple);
}

class C {
public:
    typedef int Type;
};

int main() {
    C::Type x = 8;
    Tuple<int, double, int> t{x, 2.0, 3};
    std::cout << t.head_ << ' ' << t.tail_.head_ << ' ' << t.tail_.tail_.head_;
    return 0;
}