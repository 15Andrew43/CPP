#include <iostream>
#include <cstring>
#include <iomanip>

#include "time.h"
#include "lib.h"
#include "exception.h"


void Time::SetHours(int hours) {
	if (hours >= 0 && hours < 24) {
		hours_ = hours;
	} else {
		throw DomainError("Domain Error: error in the setting of the hours.");
	}
}
void Time::SetMinutes(int minutes) {
	if (minutes >= 0 && minutes < 60) {
		minutes_ = minutes;
	} else {
		throw DomainError("Domain Error: error in the setting of the minutes.");
	}
}
void Time::SetSeconds(int seconds) {
	if (seconds >= 0 && seconds < 60) {
		seconds_ = seconds;
	} else {
		throw DomainError("Domain Error: error in the setting of the seconds.");
	}
}



int Time::GetHours() const {
	return hours_;
}
int Time::GetMinutes() const {
	return minutes_;
}
int Time::GetSeconds() const {
	return seconds_;
}

void PrintTime(const Time& time) {
	std::cout << std::setfill ('0') << std::setw (2) << time.GetHours() 
							<< ':'  << std::setw (2) << time.GetMinutes() 
							<< ':' << std::setw (2) << time.GetSeconds();
	if (time.GetHours() == 0 && time.GetMinutes() == 0 && time.GetSeconds() == 0) {
		throw Exception("Exception: perhaps the time is not set.");
	}
}

Time ReadTime(Time& time) {
	char time_str[15];
	std::cin >> time_str;
	int time_array[3];

	bool flag = ParseString(time_array, time_str, '/');  


	if (flag) { 
		time.SetHours(time_array[0]);
		time.SetMinutes(time_array[1]);
		time.SetSeconds(time_array[2]);
	}
	return time;
}