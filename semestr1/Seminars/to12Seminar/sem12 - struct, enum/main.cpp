#include "date.h"

#include <iostream>
using namespace std;

enum class Operation {INC, DEC};


void f() {

	static int cnt = 0;
	cout << "I was called " << cnt << " times" << endl;
	++cnt;
}

int main()
{
   // no implicit int -> Month conversion allowed, need explicit cast
	Month m = (Month)12;
	m = (Month)((int)m + 1);

    // Structure initialization
	Date d1 = {31, Month::DEC, 2019};
	
	// A structure may be passed to function as a parameter
	printDate(d1);
	// A structure type may be a return type of a function
	Date d2 = getTomorrow(d1);
	printDate(d2);

	Operation op = Operation::DEC;
	switch(op) {
	case Operation::INC:
		printDate(getTomorrow(d1));
		break;
	case Operation::DEC:
		printDate(getYesterday(d1));
		break;
	}

}
