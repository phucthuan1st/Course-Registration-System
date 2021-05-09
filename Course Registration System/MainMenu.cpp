#include "Header.h"
#include "console.h"

#define BACKGROUND 0
#define GREENGROUND 10
#define TEXTCOLOR 10
#define WHITE_TEXTCOLOR 175

typedef char str[31];

str process[5] = { "[ Process 1 ]", "[ Process 2 ]", "[ Process 3 ]", "[ Process 4 ]", "[ Process 5 ]" };
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

int getProcess(str listOfProcess[5], int numberOfOptions) {

	//khoi tao ban dau
	int processing = 0;
	int* color = new int[numberOfOptions];
	for (int i = 0; i < numberOfOptions; i++) {
		color[i] = TEXTCOLOR;
	}
	color[0] = WHITE_TEXTCOLOR;

	while (true) {
		clrscr();										//cap nhat lai frame moi
		for (int i = 0; i < numberOfOptions; i++) {		//
			TextColor(color[i]);						//
			cout << listOfProcess[i] << endl;			//
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

int main() {
	getProcess(process, 5);
	return 0;
}