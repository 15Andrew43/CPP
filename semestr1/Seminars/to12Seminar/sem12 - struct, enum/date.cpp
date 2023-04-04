#include <iostream>
#include <iomanip>
#include "date.h"
using namespace std;


void printDate(const Date& date)
{

	char oldFillChar = cout.fill('0');
    cout << setw(2) << date.day << '.'
    	 << setw(2) << static_cast<int>(date.month) << '.'
    	 << setw(4) << date.year << '\n';
   	cout.fill(oldFillChar);
}


int days_in_month[Month::MONTHS_CNT + 1] = {
    0, 31, 28, 31, 30, 31, 30,
	   31, 31, 30, 31, 30, 31
};

Date getTomorrow(const Date& date)
{
	Date t = date;

	if (date.day == days_in_month[static_cast<int>(date.month)])
	{
	    t.day = 1;
	    
	    if (date.day == Month::DEC)
	    {
		    t.month = Month::JAN;
		    t.year++;
	    }
	    else
	    {
		    t.month = static_cast<Month>(static_cast<int>(date.month) + 1);
	    }
	}
	else
	{
		t.day++;
	}
	return t;
}

Date getYesterday(const Date& date)
{
	Date y = date;
	//...
	return y;
}
