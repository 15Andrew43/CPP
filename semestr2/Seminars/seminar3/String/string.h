#ifndef STRING_H 
#define STRING_H

#include <utility>


class String {
	char* buffer_;
	size_t size_ = 0;
	size_t capacity_ = 1;

	const static size_t kIncreaseFactor = 2;

public:
	String();
	String(char symbol);
	String(const char* str);
	String(const char* str, size_t n);
	String(size_t size, char symbol);
	
	String(const String& other);
	String& operator=(const String& other);
	~String();

	size_t Size() const;
	size_t Length() const; 
	size_t Capacity() const;
	void Resize(size_t new_size, char fill);
	bool Empty() const;
	void Clear();
	void Reserve(size_t new_capacity);
	void ShrinkToFit();

//////////// REMOVE THIS IF YOU ARE IMPLEMENTING COW //////////// BEGIN
	char& Back();
	char& Front();

	char operator[](size_t idx) const;
	char& operator[](size_t idx);

//////////// REMOVE THIS IF YOU ARE IMPLEMENTING COW //////////// END

	const char& Back() const;
	const char& Front() const;

//////////// UNCOMMENT THIS IF YOU ARE IMPLEMENTING COW //////////// BEGIN
/*	const char& Get(size_t idx) const;         // operator[] analogue
	void Set(size_t idx, char symbol);  // operator[] analogue
*/
//////////// UNCOMMENT THIS IF YOU ARE IMPLEMENTING COW //////////// END

	const char* CStr() const;
	const char* Data() const;

	String& operator+=(const String& other);
	String& operator+=(char symbol);

	void PushBack(char symbol);
	void PopBack();

};

String operator+(const String& lhs, const String& rhs);
String operator+(char symbol, const String& rhs);
String operator+(const String& rhs, char symbol);
//String operator+(String symbol_lhs, String symbol_rhs); //????????????????????????????????????????????????????????????????????

// < > >= <= == !=
bool operator<(const String& lhs, const String& rhs);
bool operator>(const String& lhs, const String& rhs);
bool operator<=(const String& lhs, const String& rhs);
bool operator>=(const String& lhs, const String& rhs);
bool operator==(const String& lhs, const String& rhs);
bool operator!=(const String& lhs, const String& rhs);

// operator>>
// operator<<
std::istream& operator>>(std::istream& is, String& string);
std::ostream& operator<<(std::ostream& os, String& string);


#endif