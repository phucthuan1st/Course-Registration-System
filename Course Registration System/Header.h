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

bool writeToFile(char* file, int data);
int readFileData(const char* file);
string getProcessFile(fileContent file, const char* nameOfProcess);
int getProcess(str listOfProcess[], int numberOfOptions, const char* nameOfProcess);
void InitColor();
STATUS key(int _key_);
void clearColor(fileContent file, const char* nameOfProcess);
void clearColor(str listOfProcess[], int numberOfOptions, const char* nameOfProcess);