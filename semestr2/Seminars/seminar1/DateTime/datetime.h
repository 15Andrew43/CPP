#ifndef DATETIME_H
#define DATETIME_H

#include "date.h"
#include "time.h"

struct DateTime {
	Date date;
	Time time;
};

void PrintDateTime(DateTime& datetime);
DateTime ReadDateTime(DateTime& datetime);

#endif // DATETIME_H