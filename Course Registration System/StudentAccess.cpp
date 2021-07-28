#include "console.h"
#include "Header.h"

bool confirmScreen() {
	str yn[2] = { "Yes", "No" };
	int choose = getProcess(yn, 2, "Confirm changing?");
	clearColor(yn, 2, "Comfirm changing?");
	return choose;
}

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
	system("pause");
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

bool convertTimeTableToList(TimeTable TKB, char* destination_file) {
	ofstream des(destination_file, ios::out);
	int day = 0;
	int shift = 0;
	while (day < 6) {
		while (shift < 4) {
			if (TKB.nameOfSubject[shift][day] == TKB.nameOfSubject[shift + 1][day] && TKB.nameOfSubject[shift][day] != "0") {
				des << TKB.nameOfSubject[shift][day] << "\tT" << day + 2 << "_" << shift + 1 << shift + 2 << endl;
				shift += 2;
			}
			else if (TKB.nameOfSubject[shift][day] != "0") {
				des << TKB.nameOfSubject[shift][day] << "\tT" << day + 2 << "_" << shift + 1 << endl;
				shift++;
			}
			else {
				shift += 1;
			}
		}
		shift = 0;
		day += 1;
	}
	return des.is_open();
}

int cancelCourses(char* registedcourse, TimeTable& TKB) {
	int running = 1;
	bool choose;
	convertTimeTableToList(TKB, registedcourse);
	while (running) {
		fileContent file = readFileStudyLesson(registedcourse);
		string buffer = getProcessFile(file, "HUY DANG KI");
 		if (buffer == "BACK") {
			running = 0;
			choose = confirmScreen();
		}
		else {
			str yn[2] = { "Yes", "No" };
			int confirm = getProcess(yn, 2, "Did you want to cancel this course?");
			clearColor(yn, 2, "Did you want to cancel this course?");
			if (!confirm) {
				int pos = buffer.find('\t');
				string subject = buffer.substr(0, pos);
				string time = buffer.substr(pos + 1, buffer.size() - pos - 1);
				for (int i = 0; i < 4; i++) {
					for (int j = 0; j < 6; j++) {
						if (TKB.nameOfSubject[i][j] == subject && j == time[1] - 48 - 2 && (i == time[3] - 48 - 1 || time[4] - 48 - 1 == i)) {
							TKB.nameOfSubject[i][j] = "0";
						}
					}
				}
				convertTimeTableToList(TKB, registedcourse);
			}
		}
	}
	return !choose;
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

void drawPassedRegistrationTimeNotification() {
	gotoXY(60, 15);
	cout << "----------------------------------------";
	gotoXY(60, 16);
	cout << "| KHONG PHAI THOI GIAN DANG KI HOC PHAN |";
	gotoXY(60, 17);
	cout << "----------------------------------------";
	getch();
}
bool infor() {
	fstream ff;
	
	ff.open("infor.txt", ios::in);
	if (!ff) {
		ff.close();
		ff.open("infor.txt", ios::out);
	}
	else return 1;
	clrscr;
	cout << "\n\n\n      LAN DAU DANG NHAP, NHAP THONG TIN CA NHAN:\n\n";
	writeToFile_info("infor.txt", insertStudent2());
	ff.close();
	return 1;
}
void showinfo() {
	student b;
	clrscr;
	fstream ff;
	ff.open("infor.txt", ios::in);
	cout << "\n\n Student Information:";


	


	getline(ff, b.studentID);
	getline(ff, b.firstName);
	getline(ff, b.lastName);
	getline(ff, b.gender);
	getline(ff, b.date.day);
	getline(ff, b.date.month);
	getline(ff, b.date.year);
	getline(ff, b.socialID);


	
	cout << "\n Student ID: " << b.studentID << endl;
	cout << " Name: " << b.firstName << " " << b.lastName << endl;
	cout << " Gender: " << b.gender << endl;
	cout << " Date of Birth: " << b.date.day <<"/" <<b.date.month <<"/"<< b.date.year << endl;
	cout << " Social ID: " << b.socialID << endl;


	ff.close();
	cout << "=====================================";
	system("pause");
}
void StudentAccess(char* studentID) {
	int running = 1;
	str studentProcess[6] = { "Dang ki hoc phan", "Xem diem cac mon da hoc", "Xem TKB", "Huy dang ki hoc phan","Thong Tin Ca Nhan", "Thoat"};
	TimeTable student;
	getStudentTimeTable(const_cast <char*>("TKB.txt"), student);
	infor();
	while (running) {
		clrscr();
		int choose = getProcess(studentProcess, 6, "HOC SINH");
		clearColor(studentProcess, 6, "HOC SINH");
		if (choose == 0) {
			registTime T1;
			registTime_s T1_s;
			readFromFile_T("dkhp.txt", T1_s);
			StrToInt(T1, T1_s);
			if (checktime(T1)) { // them dieu kien con mo dang ki hp//
				bool save = registSubject(const_cast<char*>("danh sach mon DKHP.txt"), student);
				if (save) {
					saveChange(const_cast <char*>("TKB.txt"), student, studentID);
				}
			}
			else
			{
				drawPassedRegistrationTimeNotification();
			}
		}
		else if (choose == 1) {

		}
		else if (choose == 2) {
			displayTimeTable(student);
		}
		else if (choose == 3) {
			int confirm = cancelCourses((char*)"Ds mon da dang ki.txt", student);
			if (confirm)
				saveChange((char*)"TKB.txt", student, (char*)"20120380");
		}
		else if (choose == 4) {
			showinfo();
		}
		else if (choose == -1 || choose == 5) {
			running = 0;
		}
	}
	
}
