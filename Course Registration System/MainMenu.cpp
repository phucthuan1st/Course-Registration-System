#include "Header.h"
#include "console.h"

#define BACKGROUND 0
#define GREENGROUND 10
#define TEXTCOLOR 10
#define WHITE_TEXTCOLOR 175

typedef char str[31];

enum STATUS{UP, DOWN, LEFT, RIGHT, ENTER, BACKSPACE};

STATUS key(int _key_) {
	if (_key_ == 224) {
		char c = _getch();
		if (c == 72)
			return UP;
		if (c == 80)
			return DOWN;
		if (c == 75)
			return LEFT;
		if (c == 77)
			return RIGHT;
	}
	else if (_key_ == 13)
		return ENTER;
}


int getProcess(str listOfProcess[5], int numberOfOptions, const char* nameOfProcess) {

	//khoi tao ban dau
	int processing = 0;
	int* color = new int[numberOfOptions];
	for (int i = 0; i < numberOfOptions; i++) {
		color[i] = TEXTCOLOR;
	}
	color[0] = WHITE_TEXTCOLOR;

	while (true) {
		clrscr();										//cap nhat lai frame moi
		TextColor(TEXTCOLOR);
		cout << nameOfProcess << endl << endl << "==================" << endl;
		for (int i = 0; i < numberOfOptions; i++) {		//
			TextColor(color[i]);						//
			cout << listOfProcess[i] << endl;
		}												//
		int z = _getch();
		STATUS status = key(z); //nhan vao thao tac moi
		switch (status) {
		case UP: {
			if (processing > 0)
				processing--;
			else processing = numberOfOptions - 1;
			break;
		}
		case DOWN: {
			if (processing < numberOfOptions - 1)
				processing++;
			else processing = 0;
			break;
		}
		case ENTER:
			return processing;
		}
		for (int i = 0; i < numberOfOptions; i++) { //thay doi mau cua thao tac dang tro den
			color[i] = TEXTCOLOR;
		}
		color[processing] = WHITE_TEXTCOLOR;
	}
}


int subMenu1() {
	const char* name = "==== Sub 1 ====";
	str process[5] = { "[ Menu 1 ]", "[ Menu 2 ]", "[ Menu 3 ]", "[ Menu 4 ]", "[ Exit ]" };
	int running;
	do {
		running = getProcess(process, 5, name);
	} while (running != 4);
	return running;
}

int subMenu2() {
	const char* name = "==== Sub 2 ====";
	str process[5] = { "[ Menu 1 ]", "[ Menu 2 ]", "[ Menu 3 ]", "[ Menu 4 ]", "[ Exit ]" };
	int running;
	do {
		running = getProcess(process, 5, name);
	} while (running != 4);
	return running;
}

int subMenu3() {
	const char* name = "==== Sub 3 ===";
	str process[5] = { "[ Menu 1 ]", "[ Menu 2 ]", "[ Menu 3 ]", "[ Menu 4 ]", "[ Exit ]" };
	int running;
	do {
		running = getProcess(process, 5, name);
	} while (running != 4);
	return running;
}

int subMenu4() {
	const char* name = "==== Sub 4 ====";
	str process[5] = { "[ Menu 1 ]", "[ Menu 2 ]", "[ Menu 3 ]", "[ Menu 4 ]", "[ Exit ]" };
	int running;
	do {
		running = getProcess(process, 5, name);
	} while (running != 4);
	return running;
}

int mainMenu() {
	const char* name = "=====  Main  =====";
	str process[5] = { "[ Menu 1 ]", "[ Menu 2 ]", "[ Menu 3 ]", "[ Menu 4 ]", "[ Exit ]" };
	int running;
	do {
		running = getProcess(process, 5, name);
		if (running == 0)
			subMenu1();
		else if (running == 1)
			subMenu2();
		else if (running == 2)
			subMenu3();
		else if (running == 3)
			subMenu4();
	} while (running != 4);
	return running;
}



int main() {
	mainMenu();
	return 0;
}

bool writeToFile(string file, list l) {
	fstream f;
	f.open(file, ios::app);
	for (Node* k = l.pHead;k != NULL;k = k->pNext) {
		f << k->data.ID << ",";
		f << k->data.name << ",";
		f << k->data.date.day << ",";
		f << k->data.date.month << ",";
		f << k->data.date.year << "," << endl;
	}
	f.close();
	return true;
}

bool readFromFile(string file, list l) {
	car car;
	ifstream f("test1.csv");
	if (!f.is_open())
		cout << "Error File Open";

	string line;
	getline(f, line);
	while (f) {
		getline(f, car.ID, ',');
		getline(f, car.name, ',');
		getline(f, car.date.day, ',');
		getline(f, car.date.month, ',');
		getline(f, car.date.year, ',');
		addTail(l, createNode(insertCar()));

	}

	f.close();
}

.