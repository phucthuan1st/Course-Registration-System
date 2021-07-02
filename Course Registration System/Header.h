#pragma once
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <Windows.h>


#define _line "--------------------------------------------------------"
#define BACKGROUND 0
#define GREENGROUND 10
#define TEXTCOLOR 10
#define WHITE_TEXTCOLOR 175

enum STATUS { UP, DOWN, LEFT, RIGHT, ENTER, BACKSPACE, ESCAPE, _ADD, _DELETE, keynone };

using namespace std;
typedef char str[31];

struct fileContent {
	string* options;
	int numberOfOptions;
};

struct TimeTable {
	bool table[4][7];
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
	string No;
	string studentID;
	string fullName;
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

bool writeToFile(char* file, int data);
int readFileData(const char* file);
fileContent readFile(char* filepath);
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
NodeScore* createScoreBoard(ScoreBoard score);
void StudentAccess(char* studentID);