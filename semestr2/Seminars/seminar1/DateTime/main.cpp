#include <iostream>
#include <string>
#include "datetime.h"
#include "exception.h"

int main() {
/*	
	Date MyBirthday;
	MyBirthday.SetMonth(5);
	MyBirthday.SetDay(3);
	MyBirthday.SetYear(2001);
	std::cout << "Date: ";
	PrintDate(MyBirthday);
	std::cout << "\n-----------------\n";

	Time meeting;
	meeting.SetHours(9);
	meeting.SetMinutes(23);
	meeting.SetSeconds(37);
	std::cout << "Time: ";
	PrintTime(meeting);
	std::cout << "\n-----------------\n";

*/
/*
	Date NewYear;
	Time dinner;
//	std::cout << NewYear.GetYear() << '\n';
	ReadDate(NewYear);
	std::cout << "";
//	std::cout << NewYear.GetDay() << '\n';
//	std::cout << dinner.GetHours() << '\n';
	
	ReadTime(dinner);
//	std::cout << NewYear.GetDay() << '\n';
//	std::cout << dinner.GetHours() << '\n';
	std::cout << "\n-----------------\n";

	
//	std::cout << dinner.GetHours() << '\n';
	std::cout << "Time: ";
	PrintTime(dinner);
	std::cout << "\n----------------\n";
	std::cout << "Date: ";
	PrintDate(NewYear);

*/
/*
//  хорошо работает
	DateTime event;
	ReadDate(event.date);
	std::cout << "Date: ";
	PrintDate(event.date);
	std::cout << "\n-----------------\n";

	ReadTime(event.time);
	std::cout << "Time: ";
	PrintTime(event.time);
	std::cout << "\n-----------------\n";

	PrintDateTime(event);
*/

/*
//  плохо работает. Если убрать cout<<"" то почему-то перестает работать()
	DateTime event1;
	ReadDate(event1.date);
	std::cout << "";
	ReadTime(event1.time);

	
	std::cout << "Date: ";
	PrintDate(event1.date);
	std::cout << "\n-----------------\n";
	std::cout << "Time: ";
	PrintTime(event1.time);
	std::cout << "\n-----------------\n";	

	PrintDateTime(event1);
*/	


//  
	DateTime event;
	try {
		ReadDateTime(event);
		PrintDateTime(event);
	} catch (Exception& ex) {
		std::cout << ex.what();
	}

}