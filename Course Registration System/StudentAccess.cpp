#include "console.h"
#include "Header.h"


bool checkRegisted(string info, TimeTable studentTimeTable) {
	string day = "";
		day += info[1];
	string shift = "";
		shift += info[3];
	int dayOfWeek = stoi(day, nullptr, 10);
	int study_shift = stoi(shift, nullptr, 10);
	return studentTimeTable.table[study_shift - 1][dayOfWeek - 2];
}

bool getStudentTimeTable(char* filename, TimeTable& student) {
	fstream f;
	f.open(filename, ios::in);
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 6; j++) {
			getline(f, student.nameOfSubject[i][j], '\t');
			if (student.nameOfSubject[i][j] == "0") {
				student.table[i][j] = 0;
			}
			else
				student.table[i][j] = 1;
		}
		getline(f, student.nameOfSubject[i][j], '\n');
		if (student.nameOfSubject[i][j] == "0") {
			student.table[i][j] = 0;
		}
		else
			student.table[i][j] = 1;
	}
	f.close();
	return 1;
}

fileContent readFileStudyLesson(char* filepath) {
	fstream f;
	fileContent _fileContent;
	_fileContent.numberOfOptions = 0;
	f.open(filepath, ios::in);
	string temp, xs;
	while (!f.eof()) {
		_fileContent.numberOfOptions += 1;
		getline(f, temp);
	}
	f.close();
	f.open(filepath, ios::in);
	_fileContent.options = new string[_fileContent.numberOfOptions];
	for (int i = 0; i < _fileContent.numberOfOptions; i++) {
		getline(f, _fileContent.options[i]);
	}
	f.close();
	return _fileContent;
}

void displayTimeTable(TimeTable student) {
	TextColor(7);
	int baseX = whereX() + 8;
	int baseY = whereY() + 4;
	gotoXY(baseX, baseY);
	for (int i = 2; i <= 7; i++) {
		cout << "Thu " << i << "\t|\t";
	}
	cout << "CN";
	cout << endl << _line << _line << endl;
	for (int i = 0; i < 4; i++) {
		cout << "Ca " << i+1 << " |" << endl;
	}

	for (int i = 0; i < 4; i++) {
		gotoXY(baseX, baseY + i + 2);
		for (int j = 0; j < 7; j++) {
			cout <<student.nameOfSubject[i][j] << "\t|\t";
		}
		cout << endl;
	}
	cout << endl;
}

void getDayAndShift(char* result, string& time, string& subject) {
	string s = result;
	int pos = (int)s.find('\t') + 1;
	time = s.substr(pos, 4);
	subject = s.substr(0, s.length() - pos);
}

bool registSubject(char* filepath, TimeTable &student) {
	int running = 1;
	while (running) {
		fileContent danhSachMonDKHP = readFileStudyLesson(filepath);
		char* result = new char[20];
		strcpy(result, getProcessFile(danhSachMonDKHP, "DANG KI HOC PHAN").c_str());
		if (strcmp(result, "BACK") == 0)
			running = 0;
		else {
			string time;
			string subject;
			clearColor(danhSachMonDKHP, "DANG KI HOC PHAN");
			getDayAndShift(result, time, subject);
			if (checkRegisted(time, student)) {
				gotoXY(60, 15);
				cout << "----------------------------------";
				gotoXY(60, 16);
				cout << "| DA DANG KI O THOI GIAN NAY ROI |";
				gotoXY(60, 17);
				cout << "----------------------------------";
				getch();
			}
			else {
				int day = int(time[1]) - 48;
				int shift = int(time[3]) - 48;
				str yes_no[2] = { "Yes", "No" };
				int confirm = getProcess(yes_no, 2, "Confirm");
				if (confirm == 0) {
					student.nameOfSubject[shift - 1][day - 2] = subject;
					student.table[shift - 1][day - 2] = 1;
				}
			}
		}
	}
	str yes_no[2] = { "Yes", "No" };
	int confirm = getProcess(yes_no, 2, "Confirm");
	return !confirm;
}

void InitColor() {

}

void clearColor(fileContent file, const char* nameOfProcess) {
	clrscr();
	int x = 30;
	int y = 7;
	gotoXY(x, y - 2);
	cout << nameOfProcess;
	int* color = new int[file.numberOfOptions];
	TextColor(TEXTCOLOR);
	for (int i = 0; i < file.numberOfOptions; i++) {		//
		gotoXY(x, y);//
		cout << file.options[i] << endl;
		y += 2;
	}
}

void clearColor(str listOfProcess[], int numberOfOptions, const char* nameOfProcess) {
	int x = 30;
	int y = 7;
	gotoXY(x, y - 2);
	cout << nameOfProcess;
	int* color = new int[numberOfOptions];
	TextColor(TEXTCOLOR);
	for (int i = 0; i < numberOfOptions; i++) {		//
		gotoXY(x, y);//
		cout << listOfProcess[i] << endl;
		y += 2;
	}
}

void saveChange(char* tkb, TimeTable student, char* studentID) {
	fstream f;
	f.open(tkb, ios::out | ios::trunc);
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 6; j++) {
			f << student.nameOfSubject[i][j] << "\t";
		}
		f << student.nameOfSubject[i][j] << "\n";
	}
	f.close();
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 7; j++) {
			if (student.nameOfSubject[i][j] != "0") {
				string filepath = "./" + string(studentID) + "/" + student.nameOfSubject[i][j] + "Score.csv";
				FILE* g = fopen(filepath.c_str(), "w");
				fclose(g);
			}
		}
	}
}

void StudentAccess(char* studentID) {
	int running = 1;
	str studentProcess[5] = { "Dang ki hoc phan", "Xem diem cac mon da hoc", "Xem TKB", "Thoat" };
	TimeTable student;
	getStudentTimeTable(const_cast <char*>("TKB.txt"), student);
	while (running) {
		clrscr();
		int choose = getProcess(studentProcess, 5, "HOC SINH");
		clearColor(studentProcess, 3, "HOC SINH");
		if (choose == 0) {
			if (true) { // them dieu kien con mo dang ki hp//
				bool save = registSubject(const_cast<char*>("danh sach mon DKHP.txt"), student);
				if (save) {
					saveChange(const_cast <char*>("TKB.txt"), student, studentID);
				}
			}
		}
		else if (choose == 1) {

		}
		else if (choose == 2) {
			displayTimeTable(student);
			system("pause");
		}
		else if (choose == -1 || choose == 3) {
			running = 0;
		}
	}
	
}

int main() {
	char* studentID = new char[9];
	strcpy(studentID, "20120380");
	StudentAccess(studentID);
	clrscr();
	return 0;
}
