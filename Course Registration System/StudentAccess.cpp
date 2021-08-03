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
	int pos = (int)s.find('\t');
	time = s.substr(pos + 1, 4);
	subject = s.substr(0, pos);
}

void getSubjectName(char* result, string& subject)
{
	string s = result;
	int pos = (int)s.find('\t');
	subject = s.substr(0, pos);
}

string tack(string str)
{
	string a = "";
	for (int i = 0; i < str.length(); i++)
		if (str[i] != '\t')  a+= str[i];
		else
			break;
	return a;
}

bool registSubject(char* filepath, TimeTable &student, int &registedQuantity) {
	int running = 1;
	while (running) {
		if (registedQuantity >= 5) {
			clrscr();
			gotoXY(40, 10);
			TextColor(TEXTCOLOR);
			cout << "DA DANG KI DU 5 MON!!!" << endl;
			gotoXY(40, 13);
			cout << "Press any key to exit" << endl;
			int c = getch();
			running = 0;
		}
		else {
			fileContent danhSachMonDKHP = readFileStudyLesson(filepath);
			char* result = new char[20];
			strcpy(result, getProcessFile(danhSachMonDKHP, "DANG KI HOC PHAN").c_str());
			//tack(result);
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
					char c = getch();
				}
				else {
					int day = int(time[1]) - 48;
					int shift = int(time[3]) - 48;
					GHIDANH(tack(result));

					str yes_no[2] = { "Yes", "No" };
					int confirm = getProcess(yes_no, 2, "Confirm");
					if (confirm == 0) {
						student.nameOfSubject[shift - 1][day - 2] = subject;
						student.table[shift - 1][day - 2] = 1;
					}
					registedQuantity++;
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

int cancelCourses(char* registedcourse, TimeTable& TKB, int &registed) {
	int running = 1;
	bool choose;
	convertTimeTableToList(TKB, registedcourse);
	while (running) {
		fileContent file = readFileStudyLesson(registedcourse);
		file.numberOfOptions -= 1;
		if (registed == 0) {
			clrscr();
			gotoXY(40, 10);
			TextColor(TEXTCOLOR);
			cout << "CHUA DANG KI MON NAO!!!" << endl;
			gotoXY(40, 13);
			cout << "Press any key to exit" << endl;
			int c = getch();
			running = 0;
		}
		else {
			string buffer = getProcessFile(file, "HUY DANG KI");
			if (buffer == "BACK") {
				running = 0;
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
					registed--;
				}
			}
		}
	}
	choose = confirmScreen();
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
	f.open(tkb, ios::out);
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 6; j++) {
			f << student.nameOfSubject[i][j] << "\t";
		}
		f << student.nameOfSubject[i][j] << "\n";
	}
	f.close();
	/*for (i = 0; i < 4; i++) {
		for (j = 0; j < 7; j++) {
			if (student.nameOfSubject[i][j] != "0") {
				string filepath = "./" + string(studentID) + "/" + student.nameOfSubject[i][j] + "Score.csv";
				FILE* g = fopen(filepath.c_str(), "w");
				fclose(g);
			}
		}
	}*/
}

bool readScoreFromFile2(string file, ScoreBoard& score, student b) {
	fstream f;
	f.open(file + ".csv", ios::in);
	if (!f.is_open())
	{
		cout << "Error File Open\n";
		system("pause");
		return false;
	}

	while (!f.eof()) {
		getline(f, score.studentID, ',');
		getline(f, score.firstName, ',');
		getline(f, score.lastName, ',');
		getline(f, score.gender, ',');
		getline(f, score.date.day, ',');
		getline(f, score.date.month, ',');
		getline(f, score.date.year, ',');
		getline(f, score.socialID, ',');
		getline(f, score.aveScore, ',');
		getline(f, score.finalTermScore, ',');
		getline(f, score.middleTermScore, ',');
		getline(f, score.other, '\n');
		if (b.studentID == score.studentID)
		{
			break;
		}
	}

	f.close();
	return true;
}

void showPoint(string file)
{
	student b;
	fstream ff;
	ScoreBoard score;
	ff.open("infor.txt", ios::in);
	getline(ff, b.studentID);
	getline(ff, b.firstName);
	getline(ff, b.lastName);
	getline(ff, b.gender);
	getline(ff, b.date.day);
	getline(ff, b.date.month);
	getline(ff, b.date.year);
	getline(ff, b.socialID);
	ff.close();
	bool temp=readScoreFromFile2(file, score, b);
	clrscr;
	if (temp == true)
	{
		cout << "Student's Score" << endl;
		cout << "============================" << endl;
		cout << "Diem giua ki:" << score.middleTermScore << endl;
		cout << "Diem cuoi ki:" << score.finalTermScore << endl;
		cout << "Diem khac:" << score.other << endl;
		cout << "Diem tong:" << score.aveScore << endl;
		system("pause");
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
	clrscr();
	cout << "\n\n\n      LAN DAU DANG NHAP, NHAP THONG TIN CA NHAN:\n\n";
	writeToFile_info("infor.txt", insertStudent2());
	ff.close();
	return 1;
}

student showinfo(int a=0) {
	student b;
	clrscr();
	fstream ff;
	ff.open("infor.txt", ios::in);
	


	getline(ff, b.studentID);
	getline(ff, b.firstName);
	getline(ff, b.lastName);
	getline(ff, b.gender);
	getline(ff, b.date.day);
	getline(ff, b.date.month);
	getline(ff, b.date.year);
	getline(ff, b.socialID);
	if (a == 0) {
		cout << "\n\n Student Information:";
		cout << "\n Student ID: " << b.studentID << endl;
		cout << " Name: " << b.firstName << " " << b.lastName << endl;
		cout << " Gender: " << b.gender << endl;
		cout << " Date of Birth: " << b.date.day << "/" << b.date.month << "/" << b.date.year << endl;
		cout << " Social ID: " << b.socialID << endl;
		cout << "=====================================";
		system("pause");
	}
	ff.close();
	
	return b;
}

int countRegistedSubject(char* filename) {
	fstream fin(filename, ios::in);
	if (!fin.is_open()) {
		fin.close();
		return 0;
	}
	else {
		string temp;
		int res = 0;
		while (!fin.eof()) {
			res++;
			getline(fin, temp, '\n');
		}
		fin.close();
		return res - 1;
	}
}

void GHIDANH(string str)
{
	student b = showinfo(1);
	clrscr;
	fstream f;
	f.open(str+".csv", ios::app);
	f << b.studentID << ",";
	f << b.firstName << ",";
	f << b.lastName << ",";
	f << b.gender << ",";
	f << b.date.day << ",";
	f << b.date.month << ",";
	f << b.date.year << ",";
	f << b.socialID << "," << "\n";
	f.close();
	

}

void StudentAccess(char* studentID) {
	int running = 1;
	str studentProcess[7] = { "Dang ki hoc phan", "Xem diem cac mon da hoc", "Xem TKB","Xem cac mon hoc da dang ki", "Huy dang ki hoc phan","Thong Tin Ca Nhan", "Thoat"};
	TimeTable student;
	infor();
	while (running) {
		clrscr();
		getStudentTimeTable(const_cast <char*>("TKB.txt"), student);
		convertTimeTableToList(student, (char*)"Ds mon da dang ki.txt");
		int registed = countRegistedSubject((char*)"Ds mon da dang ki.txt");
		int choose = getProcess(studentProcess, 7, "HOC SINH");
		clearColor(studentProcess, 7, "HOC SINH");
		if (choose == 0) {
			registTime T1;
			registTime_s T1_s;
			readFromFile_T("dkhp.txt", T1_s);
			StrToInt(T1, T1_s);
			if (checktime(T1)) { // them dieu kien con mo dang ki hp//
				bool save = registSubject(const_cast<char*>("danh sach mon DKHP.txt"), student, registed);
				
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
			int running = 1;
			string subject;
			//string time;
			while (running) {
				fileContent file = readFileStudyLesson((char*)"Ds mon da dang ki.txt");
				char* FilePath = new char[50];
				strcpy(FilePath, getProcessFile(file, "XEM DIEM CAC MON HOC").c_str());
				if (strcmp(FilePath, "BACK") == 0)
					running = 0;
				else
				{
					running = 1;
					getSubjectName(FilePath ,subject);
					showPoint(subject);
				}
			}
		}
		else if (choose == 2) {
			displayTimeTable(student);
		}
		else if (choose == 3) {
			int running = 1;
			if (registed == 0) {
				clrscr();
				gotoXY(40, 10);
				TextColor(TEXTCOLOR);
				cout << "CHUA DANG KI MON NAO!!!" << endl;
				gotoXY(40, 13);
				cout << "Press any key to exit" << endl;
				int c = getch();
			}
			else 
				while (running) {
					fileContent file = readFileStudyLesson((char*)"Ds mon da dang ki.txt");
					file.numberOfOptions -= 1;
					char* FilePath = new char[50];
					strcpy(FilePath, getProcessFile(file, "DANH SACH MON HOC DA DANG KI").c_str());
					if (strcmp(FilePath, "BACK") == 0)
						running = 0;
				}
		}
		else if (choose == 4) {
			int confirm = cancelCourses((char*)"Ds mon da dang ki.txt", student, registed);
			if (confirm)
				saveChange((char*)"TKB.txt", student, (char*)"20120380");

		}
		else if (choose == 5) {
			showinfo(0);
		}
		else if (choose == -1 || choose == 6) {
			running = 0;
		}
	}
	
}
