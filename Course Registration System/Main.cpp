#include "Header.h"



int main() {
	fstream f;
	f.open(filename, ios::in);
	f << "nothing" << "," << "1" << "," << "2";
	f.close();
	return 0;
}