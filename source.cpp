#include <iostream>
#include <ctime>
#include<fstream>
#include <string>
#include <conio.h>
#include <Windows.h>

using namespace std;
//
struct Time {
	int hour;
	int min;
	int sec;
};
//
struct date {
	int day;
	int month;
	int year;
	Time time;
};
//
struct registTime {
	date DayBegin;
	date DayFinish;
};
//
struct Time_s {
	string hour;
	string min;
	string sec;
};
//
struct date_s {
	string day;
	string month;
	string year;
	Time_s time;
};
//
struct registTime_s {
	date_s DayBegin_s;
	date_s DayFinish_s;
};
//
//
void StrToInt(registTime &T, registTime_s &T_s)
{
	T.DayBegin.day = atoi(T_s.DayBegin_s.day.c_str());
	T.DayBegin.month = atoi(T_s.DayBegin_s.month.c_str());
	T.DayBegin.year = atoi(T_s.DayBegin_s.year.c_str());
	T.DayBegin.time.hour = atoi(T_s.DayBegin_s.time.hour.c_str());
	T.DayBegin.time.min = atoi(T_s.DayBegin_s.time.min.c_str());
	T.DayBegin.time.sec = atoi(T_s.DayBegin_s.time.sec.c_str());
	T.DayFinish.day = atoi(T_s.DayFinish_s.day.c_str());
	T.DayFinish.month = atoi(T_s.DayFinish_s.month.c_str());
	T.DayFinish.year = atoi(T_s.DayFinish_s.year.c_str());
	T.DayFinish.time.hour = atoi(T_s.DayFinish_s.time.hour.c_str());
	T.DayFinish.time.min = atoi(T_s.DayFinish_s.time.min.c_str());
	T.DayFinish.time.sec = atoi(T_s.DayFinish_s.time.sec.c_str());
}
//
//
date Today()
{
	date today;
	time_t now = time(NULL); 
	tm* ltm = new tm;
	localtime_s(ltm, &now);
	today.year = 1900 + ltm->tm_year;
	today.month = 1 + ltm->tm_mon;
	today.day = ltm->tm_mday;
	today.time.hour = ltm->tm_hour;
	today.time.min = ltm->tm_min;
	today.time.sec = ltm->tm_sec;
	return today;
}
//
bool checkLeapYear(int year)
{
	return (((year % 4 == 0) && (year % 100 != 0)) ||
		(year % 400 == 0));
}
//
bool checkDate(date Date)
{
	if (Date.month==4||Date.month==6||Date.month==9||Date.month==11)
	{
		if (Date.day == 31)
		{
			return false;
		}
		else {
			return true;
		}
	}
	else if(Date.month==2){
		if (Date.day > 29)
		{
			return false;
		}
		else if (Date.day==29)
		{
			if (checkLeapYear(Date.year))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else {
			return true;
		}
	}
	else {
		return true;
	}
}
