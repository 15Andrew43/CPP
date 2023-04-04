#ifndef TIME_H
#define TIME_H


class Time {
	int hours_ = 0;
	int minutes_ = 0;
	int seconds_ = 0;

public:
	void SetHours(int hours);
	void SetMinutes(int minutes);
	void SetSeconds(int seconds);

	int GetHours() const;
	int GetMinutes() const;
	int GetSeconds() const;
};

void PrintTime(const Time& time);
Time ReadTime(Time& time);
#endif // TIME_H