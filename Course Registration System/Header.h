#pragma once
#include <iostream>
#include <fstream>
#include <string>

const char* filename = "test.csv";

using namespace std;

bool writeToFile(char* file, int data);
int readFileData(const char* file);