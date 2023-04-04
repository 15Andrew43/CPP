#ifndef DATE_H
#define DATE_H


class Date {
	int day_ = 0;
	int month_ = 0;
	int year_ = 0;

	bool IsLeapYear() const;

public:
	void SetDay(int day);
	void SetMonth(int month);
	void SetYear(int year);

	int GetDay() const;
	int GetMonth() const;
	int GetYear() const;

};


void PrintDate(const Date& date);
Date ReadDate(Date& date);

#endif // DATE_H