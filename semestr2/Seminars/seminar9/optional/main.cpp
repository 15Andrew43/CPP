#include <iostream>
#include <string>

class Exception {
    std::string message_ = "exception";
public:
    Exception() = default;
    Exception(const std::string& message) {
        message_ = message;
    }
    virtual std::string what() const {
        return message_;
    }
};

class NoValue : public Exception {
    std::string message_ = "NoValue";
public:
    NoValue() = default;
    NoValue(const std::string& message) {
        message_ = message;
    }
    std::string what() const override {
        return message_;
    }
};


class A {
public:
    int a_ = -1;
    A() {
        std::cout << "default constructor for A\n";
    }
    A(int a) {
        a_ = a;
        std::cout << "constructor for A\n";
    }
    ~A() {
//        std::cout << "destructor for A\n";
    }
};



template <class T>
class Optional {
private:
    bool has_value_ = false;
    T* value_ = nullptr;
public:
    Optional() = default;
    Optional(const Optional& other) : has_value_(true), value_(static_cast<T*>(operator new(sizeof(T)))) {
        std::cout << "constr() const optional& other\n";
        new(value_) T(*other.value_);
    }
    explicit Optional(const T& value) : has_value_(true), value_(static_cast<T*>(operator new(sizeof(T)))) {// Optional<int> a = x;
        std::cout << "constr() const T& value\n";
        new(value_) T(value);
    }
    Optional(Optional&& other) noexcept : has_value_(other.has_value_), value_(other.value_) {
        other.value_ = nullptr;
    }
    explicit Optional(T&& value): has_value_(true), value_(static_cast<T*>(operator new(sizeof(T)))) {// Optional<int> a = 3
        std::cout << "constr() T&& value\n";
        new(value_) T(std::move(value));
    }

    Optional& operator=(const Optional& other) {// Optional<int> a, b; ... , a = b;
        std::cout << "operator= const Optional& other\n";
        has_value_ = other.has_value_;
        if (has_value_) {
            value_ = static_cast<T*>(operator new(sizeof(T)));
            new(value_) T(*other.value_);
        }
        return *this;
    }
    Optional& operator=(const T& value) {// Optional<int> a; a = x;
        std::cout << "operator= const T& value\n";
        has_value_ = true;
        value_ = static_cast<T*>(operator new(sizeof(T)));
        new(value_) T(value);
        return *this;
    }
    Optional& operator=(T&& value) {// Optional<int> a; a = 3;
        std::cout << "operator= T&& value\n";
        has_value_ = true;
        value_ = static_cast<T*>(operator new(sizeof(T)));
        new(value_) T(std::move(value));
        return *this;
    }

    ~Optional() {
        delete value_;
//        (*value_).~T();
//        operator delete(value_);
        std::cout << "destructor for optional\n";
    }

    bool hasValue() const {
        return has_value_;
    }
    T getValue() const {
        if (has_value_) {
            return *value_;
        }
        throw NoValue();
    }

};

int main() {
    Optional<A> opt;
    std::cout << opt.hasValue() << '\n';
    opt = A(3);
    std::cout << opt.hasValue() << '\n';
    std::cout << opt.getValue().a_ << "\n\n";

    Optional<A> opt1(A(5));
    std::cout << opt.hasValue() << '\n';
    std::cout << opt1.getValue().a_ << "\n\n";

    Optional<A> opt2(opt1);
    std::cout << opt.hasValue() << '\n';
    std::cout << opt2.getValue().a_ << "\n\n";

    Optional<A> opt3;
    std::cout << opt.hasValue() << '\n';
    opt3 = opt;
    std::cout << opt.hasValue() << '\n';
    std::cout << opt3.getValue().a_ << "\n\n";

    A b(8);
    Optional<A> opt4(b);
    std::cout << opt.hasValue() << '\n';
    std::cout << opt4.getValue().a_ << "\n\n";

    Optional<A> opt5;
    opt5 = b;

    std::cout << "------------------------------------------------------\n";

    Optional<A> opt10;
    try {
        std::cout << opt10.getValue().a_;
    } catch(Exception& ex) {
        std::cout << ex.what() << '\n';
    }
    std::cout << "------------------------------------------------------\ndestructors:\n";

    return 0;
}