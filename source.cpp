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
