enum class Month {
	JAN = 1, FEB, MAR, APR, MAY, JUN,
	JUL,   AUG, SEP, OCT, NOV, DEC,
    MONTHS_CNT = 12
};

struct Date
{
	int day;
	Month month;
	int year;
};


void printDate(const Date&);
Date getTomorrow(const Date&);
Date getYesterday(const Date& date);
