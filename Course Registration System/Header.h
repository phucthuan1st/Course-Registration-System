#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>

const char* filename = "test.csv";

using namespace std;

bool writeToFile(char* file, int data);
int readFileData(const char* file);