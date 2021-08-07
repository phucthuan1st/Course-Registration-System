#pragma once
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <Windows.h>
#include<ctime>


#define _line "--------------------------------------------------------"
#define BACKGROUND 0
#define GREENGROUND 10
#define TEXTCOLOR 10
#define WHITE_TEXTCOLOR 175

enum STATUS { UP, DOWN, LEFT, RIGHT, ENTER, BACKSPACE, ESCAPE, CHANGE,_ADD, _DELETE,_ADDPOINT ,keynone};

using namespace std;
typedef char str[31];

struct fileContent {
	string* options;
	int numberOfOptions;
};

struct TimeTable {
	bool table[4][7] = {false};
	string nameOfSubject[4][7];
};

struct TimeTableFromAdmin {
	string nameOfSubject[30];
	string weekDay[30];
	string time[30];
};

struct dateOfBirth {
	string day;
	string month;
	string year;
};

struct student {
	string No;
	string studentID;
	string firstName;
	string lastName;
	string gender;
	dateOfBirth date;
	string socialID;
};

struct Node {
	student data;
	Node* pNext;
};



struct list {
	Node* pHead;
	Node* pTail;
};

struct ScoreBoard {
	string studentID;
	string firstName;
	string lastName;
	string gender;
	dateOfBirth date;
	string socialID;
	string aveScore;
	string finalTermScore;
	string middleTermScore;
	string other;
};

struct NodeScore {
	ScoreBoard data;
	NodeScore* pNext;
};

struct listScore {
	NodeScore* pHead;
	NodeScore* pTail;
};
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
struct course {
	string id;
	string name;
	string teacher;
	string NOCredits;
	string MaxNOStudent;
	string day;
	string session;
};
//
bool infor();
string checkTK(string str);
void showinfo();
void GHIDANH(string str);
student insertStudent2();
student insertStudent();
bool writeToFile(char* file, int data);
bool writeToFile_info(string file, student  l);
int readFileData(const char* file);
string getProcessFile(fileContent file, const char* nameOfProcess);
int getProcess(str listOfProcess[], int numberOfOptions, const char* nameOfProcess);
void InitColor();
STATUS key(int _key_);
void clearColor(fileContent file, const char* nameOfProcess);
void clearColor(str listOfProcess[], int numberOfOptions, const char* nameOfProcess);
void initLScore(listScore& lScore);
ScoreBoard insertStudentScore();
void printScoreBoard(listScore lScore);
bool writeScoreToFile(string file, listScore& lScore);
bool readScoreFromFile(string file, listScore& lScore);
void getTimeTable(TimeTableFromAdmin& admin);
void writeTimeTable(string file, TimeTableFromAdmin& admin);
void addTailScore(listScore& lScore, NodeScore* p);
void loading();
NodeScore* createScoreBoard(ScoreBoard score);
void StudentAccess(char* studentID);
void StrToInt(registTime& T, registTime_s& T_s);
date Today();
bool checkLeapYear(int year);
bool checkDate(date Date);
date InputDate();
bool ComparDay(date Date1, date Date2);
registTime InputregistTime();
bool checktime(registTime RegistTime);
void writeToFile_T(string file, registTime& T);
void readFromFile_T(string file, registTime_s& T_s);
void readDay(string filepath, string& s1, string& s2);
