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
//
date InputDate()
{
	date Date;
	do {
		cout << "Nhap ngay:";
		cin >> Date.day;
	} while (Date.day < 1 || Date.day>31);
	do {
		cout << "Nhap thang :";
		cin >> Date.month;
	} while (Date.month < 1 || Date.month>12);
	do {
		cout << "Nhap nam :";
		cin >> Date.year;
	} while (Date.year <= 0);
	do {
		cout << "Nhap gio:";
		cin >> Date.time.hour;
	} while (Date.time.hour < 0 || Date.time.hour>24);
	do {
		cout << "Nhap phut:";
		cin >> Date.time.min;
	} while (Date.time.min < 0 || Date.time.min>59);
	do {
		cout << "Nhap giay:";
		cin >> Date.time.sec;
	} while (Date.time.sec < 0 || Date.time.sec>59);
	return Date;
}
//
bool ComparDay(date Date1, date Date2)
{
	if (Date2.year > Date1.year) {
		return true;
	}
	else if (Date2.year < Date1.year) {
		return false;
	}
	else {
		if (Date2.month > Date1.month)
		{
			return true;
		}
		else if (Date2.month < Date1.month) {
			return false;
		}
		else {
			if (Date2.day > Date1.day)
			{
				return true;
			}
			else if (Date2.day < Date1.day) {
				return false;
			}
			else {
				if (Date2.time.hour > Date1.time.hour)
				{
					return true;
				}
				else if (Date2.time.hour < Date1.time.hour) {
					return false;
				}
				else {
					if (Date2.time.min > Date1.time.min)
					{
						return true;
					}
					else if (Date2.time.min < Date1.time.min) {
						return false;
					}
					else {
						if (Date2.time.sec > Date1.time.sec)
						{
							return true;
						}
						else if (Date2.time.sec < Date1.time.sec) {
							return false;
						}
						else {
							return true;
						}
					}
				}
			}
		}
	}
}
//
registTime InputregistTime()
{
	registTime RegistTime;
	cout << "\nNhap ngay bat dau " << endl;
	cout << "-----------------------" << endl;
	RegistTime.DayBegin = InputDate();
	while (checkDate(RegistTime.DayBegin) == false)
	{
		cout << "-----------------------" << endl;
		cout << "Khong ton tai ngay nay " << endl;
		cout << "Vui long nhap lai ngay bat dau " << endl;
		RegistTime.DayBegin = InputDate();
	}
	cout << "\nNhap ngay ket thuc" << endl;
	cout << "-----------------------" << endl;
	RegistTime.DayFinish = InputDate();
	while (checkDate(RegistTime.DayFinish) == false)
	{
		cout << "-----------------------" << endl;
		cout << "Khong ton tai ngay nay " << endl;
		cout << "Vui long nhap lai ngay ket thuc " << endl;
		RegistTime.DayFinish = InputDate();
	}
	if (ComparDay(RegistTime.DayBegin, RegistTime.DayFinish) == false)
	{
		cout << "-------------------" << endl;
		cout << "Thoi gian ket thuc phai muon hon thoi gian bat dau " << endl;
		cout << "Vui long nhap lai " << endl;
		RegistTime = InputregistTime();
	}
	return RegistTime;
}
void checktime(registTime RegistTime)
{
	date today = Today();
	bool check1 = ComparDay(RegistTime.DayBegin, today);
	bool check2 = ComparDay(today, RegistTime.DayFinish);
	if (check1 && check2)
	{
		cout << "Load Dang ki" << endl;
	}
	else {
		cout << "Da het han dang ki" << endl;
	}
}
//
void writeToFile_T(string file, registTime &T) {
	fstream f;
	f.open(file, ios::out);
	f << T.DayBegin.day << ",";
	f << T.DayBegin.month << ",";
	f << T.DayBegin.year << ",";
	f << T.DayBegin.time.hour << ",";
	f << T.DayBegin.time.min << ",";
	f << T.DayBegin.time.sec << ",";
	f << T.DayFinish.day << ",";
	f << T.DayFinish.month << ",";
	f << T.DayFinish.year << ",";
	f << T.DayFinish.time.hour << ",";
	f << T.DayFinish.time.min << ",";
	f << T.DayFinish.time.sec <<",";
	f.close();
}
//
//
void readFromFile_T(string file, registTime_s &T_s) {
	fstream f;
	f.open(file, ios::in);
	if (!f.is_open())
	cout << "Error File Open";
	getline(f, T_s.DayBegin_s.day,',');
	getline(f, T_s.DayBegin_s.month, ',');
	getline(f, T_s.DayBegin_s.year, ',');
	getline(f, T_s.DayBegin_s.time.hour, ',');
	getline(f, T_s.DayBegin_s.time.min, ',');
	getline(f, T_s.DayBegin_s.time.sec, ',');
	getline(f, T_s.DayFinish_s.day, ',');
	getline(f, T_s.DayFinish_s.month, ',');
	getline(f, T_s.DayFinish_s.year, ',');
	getline(f, T_s.DayFinish_s.time.hour, ',');
	getline(f, T_s.DayFinish_s.time.min, ',');
	getline(f, T_s.DayFinish_s.time.sec, ',');
	f.close();
}
//
int main()
{
	date today = Today();
	registTime T = InputregistTime();
	writeToFile_T("test.txt", T);
	registTime T1;
	registTime_s T1_s;
	readFromFile_T("test.txt", T1_s);
	StrToInt(T1, T1_s);
	cout << T1.DayBegin.day << "/" << T1.DayBegin.month << "/" << T1.DayBegin.year << "/  " << T1.DayBegin.time.hour << ":" << T1.DayBegin.time.min << ":" << T1.DayBegin.time.sec << endl;
	cout << T1.DayFinish.day << "/" << T1.DayFinish.month << "/" << T1.DayFinish.year << "/  " << T1.DayFinish.time.hour << ":" << T1.DayFinish.time.min << ":" << T1.DayFinish.time.sec << endl;
	checktime(T1);
	return 0;
}
//
