#include <iostream>
#include "datetime.h"

void PrintDateTime(DateTime& datetime) {
	std::cout << "Date: ";
	PrintDate(datetime.date);
	std::cout << "\nTime: ";
	PrintTime(datetime.time);
}

DateTime ReadDateTime(DateTime& datetime) {
/*	
	ReadTime(datetime.time);
	std::cout << "";
	ReadDate(datetime.date);
*/
	ReadDate(datetime.date);
	std::cout << "";
	ReadTime(datetime.time);

	return datetime;
}