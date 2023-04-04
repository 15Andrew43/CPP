#include <iostream>

class Complex {
	double re_;
	double im_;

public:
	Complex() = default;
	Complex(double re);
	Complex(double re, double im);
	Complex(const Complex& other) = default;

	Complex& operator=(const Complex& other) = default;

	void SetRe();
	void SetIm();

	double GetRe() const;
	double GetIm() const;



	Complex& operator+=(const Complex& other) {
		this->re_ += other.re_;
		this->im_ += other.im_;
		return *this;
	}

	Complex operator-(const Complex& other) const {
		Complex result = *this;
		return result -= other;
	}

	Complex operator-() const {
		return {-re_, -im_};
	}

	Complex& operator-=(const Complex& other) {
		this->re_ -= other.re_;
		this->im_ -= other.im_;
		return *this;
	}

	// operator*

	// operator/

	Complex operator*() const {
		return {re_, -im_};
	}

};

Complex operator+(const Complex& value) const {
		return value;
}

Complex operator+(Complex lhs, const Complex& rhs) {
	return lhs += rhs;
}

std::ostream& operator<<(std::ostream& os, const Complex& value) {
	const double re = value.GetRe();
	const double im = value.GetIm();
	os << re << ' ';
	if (im < 0) {
		os << "- " << -im << 'i';  
	} else {
		os << "+ " << im << 'i';
	}
	return os;
}

std::istream& operator>>(std::istream& is, Complex& value) {
	double re;
	double im;
	is >> re >> im;
	value = {re, im};
	return is;
}

int main() {
	Complex x(1, 1);
	Complex y(2, 2);
	Complex z = x + y;
	Complex t = 5. + x;
	Complex p = y + 8;
	std::cin >> x >> y;
	std::cout << z << t;
}