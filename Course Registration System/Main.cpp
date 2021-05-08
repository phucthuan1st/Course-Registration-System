#include "Header.h"

bool writeToFile(const char* file, int data) {
	fstream f;
	f.open(file, ios::app);
	f << data << endl;
	f.close();
	return true;
}

int readFileData(const char* file) {
	int data;
	fstream f;
	f.open(file, ios::app);
	f >> data;
	f.close();
	return data;
}

int main() {
	writeToFile(filename, 5);
	cout << readFileData(filename);
	return 0;
}