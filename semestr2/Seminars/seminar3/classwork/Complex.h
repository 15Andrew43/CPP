#include <iostream>

class Complex {
	double re_;
	double im_;

public:
	Complex() = default;
	Complex(double re);
	Complex(double re, double im);
	Complex(const Complex& other) =  default; // копирования

	Complex& operator=(const Complex& other) = default; // оператор присваивания

	void SetRe();
	void SetIm();

	double GetRe() const;
	double GetIm() const;
/*
	Complex operator+(const Complex& other) const {  // по константной ссылке, тк тип "комплекс"" весит больше чем "ссылка"
		//return Complex(re_ + other.re_, im_ + other.im_); // {re_ + other.re_, im_ + other.im_}
		Complex result = *this;
		return result += other;
	}
*/
	Complex& operator+=(const Complex& other) {
		*this.re_ += other.re_; // this->re_ += other.re_
		*this.im_ += other.im_;
		return *this;
	}

	Complex operator*() const {
		return {re_, -im_};
	}
}

Complex operator+(const Complex& lhs, const Complex& rhs) {
	Complex result  = lhs;
	return result += rhs;
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

std::istream& operator>>(std::istream &is, Complex& value) {
	double re;
	double im;
	is >> re >> im;
	value = {re, im};
	return value;
} 

int main() {
	Complex x(1, 1);
	Complex x(1, 1);
	Complex z = x + y;
	// Complex t = 5. + x; // не работает, так как x.operator+(y), так как мы написали operatir+ как член класса
	Complex p = y + 8;

	std::cout << x;
}