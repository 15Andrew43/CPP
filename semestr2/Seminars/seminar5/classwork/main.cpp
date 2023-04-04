#include <iostream>



class Date {
	int day_;
	int month_;
	int year_;
public:
	Date() : Date(1, 1, 1970) {
	}

	Date(int day, int month, int year) : day_(day), month_(month), year_(year) {
	}

	void SetDay(int day);
	void SetMonth(int month);
	void SetYear(int year);

	int GetDay();
	int GetMonth();
	int GetYear();
};

void PrintDate(const Date& date) {
	std::cout << date.GetDay() << '.' << date.GetMonth() << '.' << date.GetYear();
}

class Event : public Date {
	std::string description_;

public:
	Event() = default;

	Event(int day, int month, int year, const std::string&descr = "") 
		: Date(day, month, year), description_ = descr {
	}

	void SetDescription(const std::string& descr);
	
};


int main() {
	Date ordinary_day{2, 3, 2018};
	PrintDate(ordinary_day);

	Event birthday{3, 3, 2019, "It's my birthday"};
	PrintDate(birthday);
}