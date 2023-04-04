#include <iostream>
#include <string>


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
struct Amount;

template <int X, int... Values>
struct Amount<X, Values...> {
    static const int value = 1 + Amount<Values...>::value;
};

template <>
struct Amount<> {
    static const int value = 0;
};


//template <int... Values>
//struct Mean;

template <int... Values>
struct Mean { // Mean<Values...>::value == (Values[0] + Values[1] + ... Values[n - 1]) / n
private:
    static const int amount_ = Amount<Values...>().value;
    static const int sum_ = Sum<Values...>().value;
public:
    double getMean() const {
        return (double)sum_ / amount_;
    }
//    static const double mean_ = (double)Amount<Values...>().value / Sum<Values...>().value;
};

template <int... Values>
struct Var { // Var<Values...>::value == Mean<Values^2> - Mean<Values>^2
private:
    static const int amount_ = Amount<Values...>().value;
public:
    double getVar() const {
        return Mean<(Values * Values)...>().getMean() - Mean<Values...>().getMean() * Mean<Values...>().getMean();
    }
};


int main() {
    std::cout << Var<1, 2, 3, 4>().getVar() << '\n';
    std::cout << Var<10>().getVar() << '\n';
    std::cout << Mean<9, 10, 11>().getMean() << '\n';
    std::cout << Mean<10>().getMean() << '\n';
    std::cout << Sum<1, 2, 3, 4>().value << '\n';
    std::cout << Sum<1>().value << '\n';
    std::cout << Sum<>().value << '\n';
    return 0;
}