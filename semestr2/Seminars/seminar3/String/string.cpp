#include <iostream>

#include <cstring>

#include "string.h"

#include "exception.h"


//using namespace std;

void Copy(char* buffer_, const char* str, size_t n) {
	for (size_t i = 0; i < n; ++i) {
		buffer_[i] = str[i];
	}
}

void Rewrite(char*& buffer_, const char* other_buffer, const size_t capacity_) {
	char* old_buffer = buffer_;
	buffer_ = new char[capacity_];
	Copy(buffer_, other_buffer, strlen(other_buffer));
	delete[] old_buffer;
}

void ChCapacity(size_t& Capacity, const size_t& new_size, size_t kIncreaseFactor = 2) {
	while (Capacity < new_size) {
		Capacity *= kIncreaseFactor;
	}
}

void Fill(size_t new_size, String& string, char fill = 'a') {
	size_t old_size = string.Size();
	for (int i = old_size; i < new_size; ++i) {
		string += fill;
	}
}





String::String() {
	buffer_ = new char[capacity_];
}

String::String(char symbol) {
	buffer_ = new char[capacity_];
	size_ = 1;
	buffer_[0] = symbol;
}

String::String(const char* str) {
	size_ = strlen(str);
	ChCapacity(capacity_, size_);

	buffer_ = new char[capacity_];
	Copy(buffer_, str, strlen(str));
}

String::String(size_t size, char symbol) {
	ChCapacity(capacity_, size);
	size_ = size;

	buffer_ = new char[capacity_];
	for (int i = 0; i < size; ++i) {
		buffer_[i] = symbol;
	}
}

String::String(const char* str, size_t n) {
	size_ = n;
	ChCapacity(capacity_, size_);
	buffer_ = new char[capacity_];
	Copy(buffer_, str, n);
}

String::String(const String& other) {
	String(); // работает и без этой строчки!!!!!!!!!!!!?????????
	*this = other;
}

String& String::operator=(const String& other) {
	size_t L = other.Size();
	size_ = L;

	ChCapacity(capacity_, other.Capacity());
	
	Rewrite(buffer_, other.buffer_, capacity_);
	
	return *this;
}

String::~String() {
	delete[] buffer_;
}





size_t String::Size() const {
	return size_;
}
size_t String::Length() const {
	return Size();
}

size_t String::Capacity() const {
	return capacity_;
}

void String::Resize(size_t new_size, char fill = 'a') {
	size_t old_capacity = capacity_;

	if (new_size <= Size()) {
		(*this)[new_size] = '\0';
	} else {
		if (new_size > capacity_) {
			ChCapacity(capacity_, new_size);
			Rewrite(buffer_, buffer_, capacity_);
		} 
		Fill(new_size, *this);
	}

//	size_ = new_size;
}

bool String::Empty() const {
	return size_ == 0;
}

void String::Clear() {
	buffer_[0] = '\0';
	size_ = 0;
}

void String::Reserve(size_t new_capacity) {
	if (new_capacity < size_) {
		buffer_[new_capacity] = '\0';
	} else {
		capacity_ = new_capacity;
		Rewrite(buffer_, buffer_, capacity_);
	}
}

void String::ShrinkToFit() {
	capacity_ = Size();
}

char& String::Back() {
	if (Size() == 0) {
		throw LogicError("Logic Error: you can't use Back() in string, because size = 0");		
	}
	return (*this)[Size()-1];
}
char& String::Front() {	
		if (Size() == 0) {
			throw LogicError("Logic Error: you can't use Front() in string, because size = 0");
		}
		return (*this)[0];
}





char String::operator[](size_t idx) const {
	if (idx < 0 || idx >= Size()) {
		throw OutOfRange("index out of range");
	}
	return buffer_[idx];
}
char& String::operator[](size_t idx) {
	if (idx < 0 || idx >= Size()) {
		throw OutOfRange("index out of range");
	}
	return buffer_[idx];
}





const char* String::CStr() const {
	return buffer_;
}
const char* String::Data() const {
	return CStr();
}





String& String::operator+=(const String& other) {
	size_t old_size = Size();
	size_ = Size() + other.Size();
	size_t old_capacity = capacity_;
	ChCapacity(capacity_, size_);
	if (old_capacity != capacity_) { 
		Rewrite(buffer_, buffer_, capacity_);
	}
	for (size_t j=0, i=old_size; i < Size(); ++i, ++j) {
		(*this)[i] = other[j];
	}
	return *this;
}

String& String::operator+=(char symbol) {
	++size_;
	size_t old_capacity = capacity_;
	ChCapacity(capacity_, size_);
	if (old_capacity != capacity_) { 
		Rewrite(buffer_, buffer_, capacity_);
	}
	(*this)[Size()-1] = symbol;

	return (*this);
}





void String::PushBack(char symbol) {
	(*this) += symbol;
}
void String::PopBack() {
	if (Size() == 0) {
		throw LogicError("Logic Error: you can't use PopBack() in string, because size = 0");		
	}
	(*this)[Size()-1] = '\0';
	--size_;
}





String operator+(const String& lhs, const String& rhs) {
	String string = lhs;
	string += rhs;
	return string;
}
String operator+(char symbol, const String& rhs) {
	String string;
	string += symbol;
	string += rhs;
	return string;
}
String operator+(const String& rhs, char symbol) {
	String string;
	string += rhs;
	string += symbol;
	return string;
}
/* ?????????????????????????????????????????????????????????????????????????????????????
String operator+(char symbol_lhs, char symbol_rhs) {
	String string;
	string += symbol_lhs;
	string += symbol_rhs;
	return string;
}
*/


bool operator<(const String& lhs, const String& rhs) {
	size_t L = std::min(lhs.Size(), rhs.Size());
	for (size_t i = 0; i < L; ++i) {
		if (lhs[i] < rhs[i]) {
			return true;
		} 
		if (lhs[i] > rhs[i]) {
			return false;
		}
	}
	return lhs.Size() < rhs.Size();
}
bool operator==(const String& lhs, const String& rhs) {
	if (lhs.Size() != rhs.Size()) {
		return false;
	}
	size_t L = lhs.Size();
	for (int i = 0; i < L; ++i) {
		if (lhs[i] != rhs[i]) {
			return false;
		}
	}
	return true;
}
bool operator>(const String& lhs, const String& rhs) {
	return ( !(lhs < rhs) && !(lhs == rhs) ); 
}
bool operator<=(const String& lhs, const String& rhs) {
	return !(lhs > rhs);
}
bool operator>=(const String& lhs, const String& rhs) {
	return !(lhs < rhs);
}
bool operator!=(const String& lhs, const String& rhs) {
	return !(lhs == rhs);
}





std::istream& operator>>(std::istream& is, String& string) {
	char chars[100];
	is >> chars;
	String s = chars;
	string = s;
	return is;
}
std::ostream& operator<<(std::ostream& os, String& string) {
	size_t L = string.Size();
	for (int i = 0; i < L; ++i) {
		std::cout << string[i];
	}
	return os;
}
