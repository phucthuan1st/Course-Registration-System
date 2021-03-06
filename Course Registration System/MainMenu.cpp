#include "Header.h"
#include "console.h"
//test

//
STATUS key(int _key_)
{
	if (_key_ == 224)
	{
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
	else if (_key_ == 27)
		return ESCAPE;
	else if (_key_ == 42)
		return CHANGE;
	else if (_key_ == 43) 
		return _ADD;
	else if (_key_ == 45) 
		return _DELETE;
	else if (_key_ == 47)
		return _ADDPOINT;
	return keynone;
}

void initLScore(listScore& lScore)
{
	lScore.pHead = lScore.pTail = NULL;
}



bool readScoreFromFile(string file, listScore& lScore) {
	ScoreBoard score;
	fstream f;
	f.open(file + ".csv", ios::in);
	if (!f.is_open())
		cout << "Khong mo duoc file";

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
		addTailScore(lScore, createScoreBoard(score));
	}

	f.close();
	return true;
}


void getTimeTable(TimeTableFromAdmin& admin) {
	int counter = 0;
	string c = "stop";
	while (admin.nameOfSubject[counter - 1] != c) {
		cin >> admin.nameOfSubject[counter];
		cin >> admin.weekDay[counter];
		cin >> admin.time[counter];
		counter++;
	}
}

void writeTimeTable(string file, TimeTableFromAdmin& admin)
{
	fstream f;
	int counter = 0;
	string c = "stop";
	int flag = 0;
	f.open(file + ".txt", ios::out);
	getTimeTable(admin);
	while (admin.nameOfSubject[counter] != c)
	{
		for (int counter1 = 0; counter1 < counter; counter1++)
		{
			if ((admin.nameOfSubject[counter] == admin.nameOfSubject[counter1]) && (admin.weekDay[counter] == admin.weekDay[counter1]) && (admin.time[counter] == admin.time[counter1]))
			{
				flag = 1;
			}
		}
		if (flag == 0) {
			f << admin.nameOfSubject[counter] << "\t";
			f << admin.weekDay[counter] << "_";
			f << admin.time[counter] << endl;
		}
		counter++;
		flag = 0;
	}
}

void addTailScore(listScore& lScore, NodeScore* p)
{
	if (lScore.pHead == NULL) {
		lScore.pHead = lScore.pTail = p;
	}
	else {
		lScore.pTail->pNext = p;
		lScore.pTail = p;
	}
}

NodeScore* createScoreBoard(ScoreBoard score)
{
	NodeScore* p = new NodeScore;
	p->pNext = NULL;
	p->data = score;
	return p;
}

void initL(list& l)
{
	l.pHead = l.pTail = NULL;
}

student insertStudent2()
{
	student student;
	
	cout << "MSSV: ";
	getline(cin, student.studentID);
	//cin.ignore();
	cout << "Ten: ";
	getline(cin, student.firstName);
	//cin.ignore();
	cout << "Ho: ";
	getline(cin, student.lastName);
	//cin.ignore();
	cout << "Gioi tinh: ";
	getline(cin, student.gender);
	cout << "Ngay: ";
	getline(cin, student.date.day);
	cout << "Thang: ";
	getline(cin, student.date.month);
	cout << "Nam: ";
	getline(cin, student.date.year);
	cout << "CMND: ";
	getline(cin, student.socialID);
	return student;
}
student insertStudent()
{
	student student;
	cout << "MSSV: ";
	getline(cin, student.studentID);
	//cin.ignore();
	cout << "Ten: ";
	getline(cin, student.firstName);
	//cin.ignore();
	cout << "Ho: ";
	getline(cin, student.lastName);
	//cin.ignore();
	cout << "Gioi tinh: ";
	getline(cin, student.gender);
	cout << "Ngay: ";
	getline(cin, student.date.day);
	cout << "Thang: ";
	getline(cin, student.date.month);
	cout << "Nam: ";
	getline(cin, student.date.year);
	cout << "CMND: ";
	getline(cin, student.socialID);
	return student;
}

Node* createNode(student student)
{
	Node* p = new Node;
	p->pNext = NULL;
	p->data = student;
	return p;
}

void addTail(list& l, Node* p)
{
	if (l.pHead == NULL) {
		l.pHead = l.pTail = p;
	}
	else {
		l.pTail->pNext = p;
		l.pTail = p;
	}
}

void delHead(list& l) {
	if (l.pHead == NULL) {
		cout << "Khong co phan tu";
	}
	else {
		l.pHead = l.pHead->pNext;
	}
}

void delTail(list& l) {
	if (l.pHead == NULL || l.pHead->pNext == NULL) {
		delHead(l);
	}
	else {
		Node* p = l.pHead;
		while (p->pNext->pNext != NULL) {
			p = p->pNext;
		}
		p->pNext = p->pNext->pNext;
	}
	
}

void printList(list l)
{
	clrscr();
	Node* pTmp = l.pHead;
	if (pTmp == NULL)
	{
		cout << "Trong";
		return;
	}
	int i = 0;
	cout << "Thong tin sinh vien:" << endl << endl;
	for (Node* p = l.pHead; p->pNext != NULL; p = p->pNext) {
		cout << "STT: " << ++i << endl;
		cout << "MSSV: " << p->data.studentID << endl;
		cout << "Ten: " << p->data.firstName << endl;
		cout << "Ho: " << p->data.lastName << endl;
		cout << "Gioi tinh: " << p->data.gender << endl;
		cout << "Ngay sinh: " << p->data.date.day << "/" << p->data.date.month << "/" << p->data.date.year << endl;
		cout << "CMND: " << p->data.socialID << endl << endl;
	}
	cout << "=====================================" << endl;
}

void printList2(list l)
{
	clrscr();
	Node* pTmp = l.pHead;
	if (pTmp == NULL)
	{
		cout << "Trong";
		return;
	}
	int i = 0;
	cout << "Thong tin sinh vien:" << endl << endl;
	for (Node* p = l.pHead; p->pNext != NULL; p = p->pNext) {
		cout << "STT: " << ++i << "\t|\t";
		cout << "MSSV: " << p->data.studentID << endl;
		cout << "Ten: " << p->data.firstName << endl;
		cout << "Ho: " << p->data.lastName << endl;
		cout << "Gioi tinh: " << p->data.gender << endl;
		cout << "Ngay sinh: " << p->data.date.day << "/" << p->data.date.month << "/" << p->data.date.year << endl;
		cout << "CMND: " << p->data.socialID << endl << endl;
	}
	cout << "=====================================" << endl;
}


void addHead(list& l, Node* p) {

	if (l.pHead == NULL) {
		l.pHead = l.pTail = p;
	}
	else {
		p->pNext = l.pHead;
		l.pHead = p;
	}

}

bool writeToFile_info(string file , student  l) {
	fstream f;
	f.open(file , ios::out);


	f << l.studentID << "\n";
	f << l.firstName << "\n";
	f << l.lastName << "\n";
	f << l.gender << "\n";
	f << l.date.day << "\n";
	f << l.date.month << "\n";
	f << l.date.year << "\n";
	f << l.socialID << "\n";

	f.close();
	return true;
}
//
bool writeToFile(string file, list& l) {
	fstream f;
	f.open(file + ".csv", ios::app);
	for (Node* k = l.pHead;k != NULL;k = k->pNext) {
		if (k->pNext != NULL)
		{
			f << k->data.studentID << ",";
			f << k->data.firstName << ",";
			f << k->data.lastName << ",";
			f << k->data.gender << ",";
			f << k->data.date.day << ",";
			f << k->data.date.month << ",";
			f << k->data.date.year << ",";
			f << k->data.socialID << "," << endl;
		}
		else {
			f << k->data.studentID << ",";
			f << k->data.firstName << ",";
			f << k->data.lastName << ",";
			f << k->data.gender << ",";
			f << k->data.date.day << ",";
			f << k->data.date.month << ",";
			f << k->data.date.year << ",";
			f << k->data.socialID << ",";
		}
	}
	f.close();
	return true;
}

bool readFromFile(string file, list& l) {
	student student;
	string temp;
	fstream f;
	f.open(file + ".csv", ios::in);
	if (!f.is_open())
	{
		cout << "Khong the mo file" << endl;
		system("pause");
		return false;
	}

	while (!f.eof()) {
		getline(f, student.studentID, ',');
		getline(f, student.firstName, ',');
		getline(f, student.lastName, ',');
		getline(f, student.gender, ',');
		getline(f, student.date.day, ','); 
		getline(f, student.date.month, ',');
		getline(f, student.date.year, ',');
		getline(f, student.socialID, /*','*/'\n');
		/*getline(f, temp, ',');
		getline(f, temp, ',');
		getline(f, temp, ',');
		getline(f, temp,'\n');*/
		addTail(l, createNode(student));
	}
	f.close();
	return true;
}
//
bool readFromFile2(string file, list& l) {
	student student;
	string temp;
	fstream f;
	f.open(file += ".csv", ios::in);
	if (!f.is_open())
	{
		cout << "Khong the mo file" << endl;
		system("pause");
		return false;
	}

	while (!f.eof()) {
		getline(f, student.studentID, ',');
		getline(f, student.firstName, ',');
		getline(f, student.lastName, ',');
		getline(f, student.gender, ',');
		getline(f, student.date.day, ',');
		getline(f, student.date.month, ',');
		getline(f, student.date.year, ',');
		getline(f, student.socialID, ',');
		getline(f, temp, ',');
		getline(f, temp, ',');
		getline(f, temp, ',');
		getline(f, temp, '\n');
		addTail(l, createNode(student));
	}
	f.close();
	return true;
}
//


void printMyAllSubjectScore(listScore lScore)
{
	clrscr();
	NodeScore* pTmp = lScore.pHead;
	if (pTmp == NULL)
	{
		cout << "Trong" << endl;
		return;
	}
	int i = 0;
	cout << "Diem mon hoc:" << endl << endl;
	for (NodeScore* p = lScore.pHead; p->pNext != NULL; p = p->pNext) {

		cout << "STT: " << ++i << endl;
		cout << "MSSV: " << p->data.studentID << endl;
		cout << "Ten: " << p->data.firstName << endl;
		cout << "Ho: " << p->data.lastName << endl;
		cout << "Gioi tinh: " << p->data.gender << endl;
		cout << "Ngay sinh: " << p->data.date.day << "/" << p->data.date.month << "/" << p->data.date.year << endl;
		cout << "CMND: " << p->data.socialID << endl;
		cout << "Diem TB: " << p->data.aveScore << endl;
		cout << "Diem CK: " << p->data.finalTermScore << endl;
		cout << "Diem GK: " << p->data.middleTermScore << endl;
		cout << "Diem cong: " << p->data.other << endl << endl;
	}
	cout << "=====================================" << endl;
}

void readDay(string filepath, string& s1, string& s2)
{
	fstream f;
	f.open(filepath + ".txt", ios::in);
	dateOfBirth d1, d2;
	getline(f, d1.day, ',');
	getline(f, d1.month, ',');
	getline(f, d1.year, '\n');
	getline(f, d2.day, ',');
	getline(f, d2.month, ',');
	getline(f, d2.year, ',');
	s1 = "Ngay bat dau:" + d1.day + "/" + d1.month + "/" + d1.year;
	s2 = "Ngay ket thuc" + d2.day + "/" + d2.month + "/" + d2.year;
	f.close();
}

course InputCourse()
{
	course course;
	cout << "========================================" << endl;
	cout << "Nhap ID khoa hoc:";
	getline(cin,course.id);
	cout << "Nhap ten khoa hoc:";
	getline(cin, course.name);
	cout << "Nhap ten giao vien:";
	getline(cin, course.teacher);
	cout << "Nhap so tin chi:";
	getline(cin, course.NOCredits);
	cout << "Nhap so sinh vien toi da:";
	getline(cin, course.MaxNOStudent);
	cout << "Nhap thu day trong tuan:";
	getline(cin, course.day);
	cout << "Nhap ca day:";
	getline(cin, course.session);
	return course;
}

int getProcess(str listOfProcess[], int numberOfOptions, const char* nameOfProcess) {
	clrscr();
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
		gotoXY(30, 5);
		int x = 30;
		int y = 5;
		cout << nameOfProcess << endl << endl;
		y += 2;
		for (int i = 0; i < numberOfOptions; i++) {		//
			TextColor(color[i]);
			gotoXY(x, y);//
			cout << listOfProcess[i] << endl;
			y += 2;
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
			case ENTER: {
				clearColor(listOfProcess, numberOfOptions, nameOfProcess);
				return processing;
			}
			case ESCAPE: {
				clearColor(listOfProcess, numberOfOptions, nameOfProcess);
				return -1;
			}	
		}
		for (int i = 0; i < numberOfOptions; i++) { //thay doi mau cua thao tac dang tro den
			color[i] = TEXTCOLOR;
		}
		color[processing] = WHITE_TEXTCOLOR;
	}
}

void Del_option(string str, fileContent CD) 
{
	fstream ff;
	string _del;
	bool kt;
	  
	cout << "NAME: "; getline(cin, _del , '\n');
	ff.open(str+=".txt", ios::out);            
	for(int i=0;i<4;i++)
        ff<<endl;
	for (int i = 0; i < CD.numberOfOptions; i++)
	{
		kt = false;
		if (CD.options[i] != _del  ) 
			{
				ff << CD.options[i];
				kt=true;
			}
		if ((i < CD.numberOfOptions-1)&&(kt)) 			
			ff << endl;
	}
		
	
	ff.close();
}

void add_option(string str)
{
	fstream ff, file;

	string _addop;

	cout << "NAME: "; getline(cin, _addop, '\n');
	ff.open(str += ".txt", ios::app);
	file.open(_addop+".txt", ios::out);
	for (int i = 0; i < 4; i++) file << endl;
	file.close();
	ff << _addop<<endl;
	ff.close();
}

void add_optioncsv(string str)
{
	fstream ff, file;

	string _addop;

	cout << "NAME: "; getline(cin, _addop, '\n');
	ff.open(str + ".txt", ios::app);
	file.open(_addop+".csv", ios::out);
	file.close();
	ff << "\n" << _addop;
	ff.close();
}

void add_course(string str)
{
	fstream ff, file,file1;
	fstream f;
	string _addop;
	
	cout << "NAME: "; getline(cin, _addop, '\n');
	ff.open(str += ".txt", ios::app);
	file.open(_addop + ".txt", ios::out);
	course course = InputCourse();
	for (int i = 0; i < 4; i++) file << endl;
	file <<"ID khoa hoc:"<< course.id << endl;
	file << "Ten khoa hoc:" << course.name << endl;
	file << "Ten giao vien:" << course.teacher << endl;
	file << "So tin chi:" << course.NOCredits << endl;
	file << "So luong sinh vien toi da:" << course.MaxNOStudent << endl;
	file << "Ngay day:" << course.day << endl;
	file << "Ca day:" << course.session << endl;
	file << endl;
	file << "Xem danh sach sinh vien" << endl;
	file << "Xem diem cua sinh vien" << endl;
	file << "Cap nhat thong tin mon hoc" << endl;
	file.close();
	file1.open(_addop + ".csv", ios::out);
	file1.close();
	ff << "\n" << _addop;
	ff.close();
	f.open("danh sach mon DKHP.txt", ios::app);
	f <<_addop<<"	"<<"T"<<course.day<<"_"<<course.session<<"\n";
	f.close();

}

void changeCourseInfo(string str)
{
	fstream file;
	file.open(str + ".txt", ios::out);
	course course = InputCourse();
	for (int i = 0; i < 4; i++) file << endl;
	file << "ID khoa hoc:" << course.id << endl;
	file << "Ten khoa hoc:" << course.name << endl;
	file << "Ten giao vien:" << course.teacher << endl;
	file << "So tin chi:" << course.NOCredits << endl;
	file << "So luong sinh vien toi da:" << course.MaxNOStudent << endl;
	file << "Ngay day:" << course.day << endl;
	file << "Ca day:" << course.session << endl;
	file << endl;
	file << "Xem danh sach sinh vien" << endl;
	file << "Xem diem cua sinh vien" << endl;
	file << "Cap nhat thong tin mon hoc" << endl;
	file.close();
}

fileContent readFile(string filepath)
{
	fstream f;
	fileContent _fileContent;
	_fileContent.numberOfOptions = 0;
	f.open(filepath+=".txt", ios::in);
	string temp,xs;
	getline(f, xs); getline(f, xs); getline(f, xs); getline(f, xs);
	while (!f.eof()) {
		_fileContent.numberOfOptions += 1;
		getline(f, temp);
	}
	f.close();
	f.open(filepath, ios::in);
	_fileContent.options = new string[_fileContent.numberOfOptions];
	getline(f, xs); getline(f, xs); getline(f, xs); getline(f, xs);
	for (int i = 0; i < _fileContent.numberOfOptions; i++) {
		getline(f, _fileContent.options[i]);
	}
	f.close();
	return _fileContent;
}

void addToClass(string file, student b)
{
	fstream f;
	string temp = file + ".csv";
	f.open(temp, ios::app);
	if (!f.is_open())
		cout << "Khong mo duoc file";
	f << b.studentID << ",";
	f << b.firstName << ",";
	f << b.lastName << ",";
	f << b.gender << ",";
	f << b.date.day << ",";
	f << b.date.month << ",";
	f << b.date.year << ",";
	f << b.socialID << "\n";
	f.close();
}

string getProcessFile(fileContent file,const char* nameOfProcess) {
	clrscr();
	//khoi tao ban dau
	int processing = 0;
	int* color = new int[file.numberOfOptions];
	for (int i = 0; i < file.numberOfOptions; i++) {
		color[i] = TEXTCOLOR;
	}
	color[0] = WHITE_TEXTCOLOR;

	while (true) {
		clrscr();					//cap nhat lai frame moi
		TextColor(TEXTCOLOR);
		gotoXY(30, 5);
		int x = 30;                                        // new game
		int y = 5;
		cout << nameOfProcess;
		y += 2;
		for (int i = 0; i < file.numberOfOptions; i++) {		//
			TextColor(color[i]);
			gotoXY(x, y);
			cout << file.options[i] << endl;
			y += 2;
		}

		int z = _getch();
		STATUS status = key(z); //nhan vao thao tac moi
		switch (status) {
		case UP: {
			if (processing > 0)
				processing--;
			else processing = file.numberOfOptions - 1;
			break;
		}
		case DOWN: {
			if (processing < file.numberOfOptions - 1)
				processing++;
			else processing = 0;
			break;
		}
		case ENTER: {
			clearColor(file, nameOfProcess);
			return file.options[processing];
		}
		case ESCAPE: {
			clearColor(file, nameOfProcess);
			return "BACK";
		}
		case _ADD:
			//add_option(nameOfProcess);

			return "add";
			break;
		case CHANGE:
			return "change";
			break;
		case _DELETE:
			return "_dele";
			break;
		case _ADDPOINT:
			return "addpoint";
			break;
		}
		for (int i = 0; i < file.numberOfOptions; i++) { //thay doi mau cua thao tac dang tro den
			color[i] = TEXTCOLOR;
		}
		color[processing] = WHITE_TEXTCOLOR;
	}
}

//
int selectSubScreen(char* filepath) {
	list L;
	initL(L);
	listScore diem;
	initLScore(diem);
	int running = 1;


	while (running) {
		fileContent yearFile = readFile(filepath);
		char* termFilePath = new char[150];
		strcpy(termFilePath, getProcessFile(yearFile, "MON HOC").c_str());
		if (strcmp(termFilePath, "BACK") == 0)
			running = 0;
		else if (strcmp(termFilePath, "add") == 0)
			{
				running = 1;
				add_option(filepath);
			}
			else
				if (strcmp(termFilePath, "_dele") == 0)
				{
					running = 1;
					Del_option(filepath, yearFile);

				}
				else
				if (strcmp(termFilePath, "_dele") == 0)
				 {	
			       running = 1;
			       Del_option(filepath, yearFile);
	
				}
					else
					{
						char* temp = new char[50];
						temp = strcpy(temp, termFilePath);
						if (strcmp(temp, "Xem danh sach sinh vien") == 0)
						{
							running = 1;
							bool t = readFromFile2(filepath, L);
							clrscr();
							if (t == true)
							{
								cout << termFilePath << endl;
								printList2(L);
								system("pause");
							}
						}
						else 
							if (strcmp(temp, "Xem diem cua sinh vien") == 0)
							{
								running = 1;
								bool t = readScoreFromFile(filepath, diem);
								printMyAllSubjectScore(diem);
								system("pause");
							}
							else
								if (strcmp(temp, "Cap nhat thong tin mon hoc") == 0)
								{
									running = 1;
									changeCourseInfo(filepath);
									system("pause");
								}
					}
			   
	}
	return 1;
}



int selectSubjectScreen(char* filepath) 
{
	
	int running = 1;
	string s1;
	string s2;
	readDay(filepath, s1, s2);
	while (running) {
		fileContent termFile = readFile(filepath);
		string temp = "MON HOC    " + s1 + "     " + s2;
		char* c = new char[100];
		strcpy(c, temp.c_str());
		char* subjectFilePath = new char[50];
		strcpy(subjectFilePath, getProcessFile(termFile, c).c_str());
		
		if (strcmp(subjectFilePath, "BACK") == 0 )
			running = 0;
		else 
			if (strcmp(subjectFilePath, "add") == 0)
			{
				running = 1;
				//add_option(filepath);
				add_course(filepath);
			}
		else
			if (strcmp(subjectFilePath, "_dele") == 0)
			{
					running = 1;
					Del_option(filepath, termFile);

			}
		else
				selectSubScreen(subjectFilePath);
	}
	return 1;
}

int selectTermScreen(char* filepath) {

	int running = 1;
	while (running) {
		fileContent yearFile = readFile(filepath);
		char* termFilePath = new char[50];
		strcpy(termFilePath, getProcessFile(yearFile, "HOC KI").c_str());

		if (strcmp(termFilePath, "BACK") == 0)
			running = 0;
		else
			if (strcmp(termFilePath, "add") == 0)
			{
				running = 1;
				add_option(filepath);
			}
			else
				if (strcmp(termFilePath, "_dele") == 0)
				{
					running = 1;
					Del_option(filepath, yearFile);

				}
				else
					selectSubjectScreen(termFilePath);
	}
	return 1;
}

int selectClassScreen(char* filepath)
{
	list L;
	initL(L);
	int running = 1;
	while (running) {
		fileContent termFile = readFile(filepath);
		char* classFilePath = new char[50];
		strcpy(classFilePath, getProcessFile(termFile, "LOP HOC").c_str());
		if (strcmp(classFilePath, "BACK") == 0)
			running = 0;
		else
			if (strcmp(classFilePath, "add") == 0)
			{
				running = 1;
				add_optioncsv(filepath);
			}
			else
				if (strcmp(classFilePath, "_dele") == 0)
				{
					running = 1;
					Del_option(filepath, termFile);

				}
				else
				{
					//danh sach theo lop
					running = 1;
					bool t=readFromFile(classFilePath, L);
					clrscr();
					if (t == true)
					{
						printList(L);
					}
					int i = 0;
					int z = _getch();
					STATUS status = key(z); //nhan vao thao tac moi
					switch (status) {
					case _ADD:
						i = 1;
						break;
					default:
						break;
					}
					if (i == 1)
					{
						student b = insertStudent2();
						addToClass(classFilePath, b);
					}
					system("pause");
				}
	}
	return 1;
}

void yearAccess(char* filepath) {
	int running = 1;
	str yearAccess[3] = { "LOP HOC", "HOC KI","THEM PHIEN DANG KI HOC PHAN" };
	while (running) {
		clrscr();
		int choose = getProcess(yearAccess, 3, "NAM HOC");
		clearColor(yearAccess, 3, "NAM HOC");
		if (choose == 0) {
			selectClassScreen(const_cast<char*>("class"));
		}
		else if (choose == 1) {
			selectTermScreen(filepath);
		}
		else if (choose == 2) {

			running = 1;
			registTime T = InputregistTime();
			writeToFile_T("dkhp.txt", T);
		}
		else if (choose == -1 || choose == 3) {
			running = 0;
		}
	}

}

int selectYearScreen(string filepath) {

	int running = 1;
	
	while (running) {                
		fileContent adminFile = readFile(filepath);
		char* yearFilePath = new char[50];

		strcpy(yearFilePath, getProcessFile(adminFile, "Admin").c_str());
		if (strcmp(yearFilePath, "BACK") == 0) 
			running = 0;
		else if (strcmp(yearFilePath, "add") == 0)
			{
				running = 1;
				add_option(filepath);
			
			}
			else if (strcmp(yearFilePath, "_dele") == 0)
				{
					running = 1;
					Del_option(filepath,adminFile);

				}
			else
			yearAccess(yearFilePath);
	}

	return 0;
}

int mainMenu() {

	const char* name = "=====  Main  =====";
	string filepath = "admin";
	fileContent file = readFile(filepath);
	int running = 0;

	do {

		running = selectYearScreen(filepath);
	} while (running);

	return running;
}

int init_MENU()
{
	int n = 41;
	int m = 15;
	int key = 1;

	gotoXY(n, m);
	cout << "*________________________________*"; gotoXY(n, m + 1);
	cout << "|              LOGIN             |"; gotoXY(n, m + 2);
	cout << "|                                |"; gotoXY(n, m + 3);
	cout << "|                                |"; gotoXY(n, m + 4);
	cout << "|                                |"; gotoXY(n, m + 5);
	cout << "|             ADMIN    <--       |"; gotoXY(n, m + 6);
	cout << "|             STUDENT            |"; gotoXY(n, m + 7);
	cout << "|                                |"; gotoXY(n, m + 8);
	cout << "|          RATE   *****          |"; gotoXY(n, m + 9);
	cout << "|________________________________|"; m += 5;

	while (true)
	{
		char c = _getch();

		if ((c == 72) || (c == 80))
		{
			if (key == 1)
			{
				gotoXY(n, m);
				cout << "|             ADMIN          ";  gotoXY(n, m + 1);
				cout << "|             STUDENT  <--  "; key = 2;
			}
			else
			{
				gotoXY(n, m);
				cout << "|             ADMIN    <--   ";  gotoXY(n, m + 1);
				cout << "|             STUDENT        "; key = 1;
			}

		}
		else if (c == 13) break;

	}
	return key;
}
void loading()
{
	int n = 42;
	int m = 22;  int j = 1;
	gotoXY(n, m-1);
	for (int i = n; i < 74; i++)
	{	
		cout <<'_';	//Sleep(100);
	}
	gotoXY(n, m+1);
	for (int i = n; i < 74; i++)
	{
		cout <<char(196);	//Sleep(100);
	}

	gotoXY(n, m);
	for (int i = n; i < 74; i++)
	{
		gotoXY(i, m);
		cout << char(177);
		gotoXY(n+14, m+2);
		
		
		if (i < 60) {
			
			cout <<" "<< j << " %"; j += 3;
			Sleep(300);
		}
		else {
			if (j > 100) j = 100;
			cout <<" "<< j << " %"; j += 4;
			Sleep(150);
		}
	}
	//cout << "|                                |"; gotoXY(n, m + 3);
//	cout << "|                                | "; gotoXY(n, m + 4);
}
string checkTK(string str)
{
	string a="";
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == '#') break;
		a += str[i];
	}
	return a;
}
int check(string tp, string a, string b)
{

	string kt, str = a + "####" + b;

	fstream file;
	bool ck = false;
	file.open(tp, ios::in);
	if (!file)
		file.open(tp, ios::out);
	while (!file.eof())
	{
		getline(file, kt);
		if (checkTK(kt) == a) ck = true;
		if (kt == str) return 1;
	}

	file.close();
	if (ck) return 2;
	else return 3;

}

int init_LOGIN(int k)
{
	clrscr();




	int n = 41;
	int m = 15;
	string typelog;
	if (k == 1) typelog = "DATA_AD.txt";
	else typelog = "DATA_STU.txt";
	string ACC, PASS;
	//bool kt;
	gotoXY(n, m);
	cout << "*________________________________*"; gotoXY(n, m + 1);
	cout << "|              LOGIN             |"; gotoXY(n, m + 2);
	cout << "|                                |"; gotoXY(n, m + 3);
	cout << "|                                | "; gotoXY(n, m + 4);
	cout << "|                                |"; gotoXY(n, m + 5);
	cout << "| Account:                       |"; gotoXY(n, m + 6);
	cout << "| PASS:                          | "; gotoXY(n, m + 7);
	cout << "|                                |"; gotoXY(n, m + 8);
	cout << "|                                |"; gotoXY(n, m + 9);
	cout << "|________________________________|";


	while (1)
	{
		gotoXY(n + 12, m + 5);   getline(cin, ACC, '\n');
		gotoXY(n + 12, m + 6);   getline(cin, PASS, '\n');
		gotoXY(n, m + 7);
		if (check(typelog, ACC, PASS) == 1)
		{
			//loading();
			if (k == 1) return 1;
			else return 2;
			break;
		}
		else
			if (check(typelog, ACC, PASS) == 3)
				cout << "| TAI KHOAN KHONG TON TAI";
			else
				cout << "| MAT KHAU SAI            ";
		gotoXY(n, m + 5);
		cout << "| Account:                       |"; gotoXY(n, m + 6);
		cout << "| PASS:                          | "; gotoXY(n, m + 7);
	}


}

void StrToInt(registTime& T, registTime_s& T_s)
{
	T.DayBegin.day = atoi(T_s.DayBegin_s.day.c_str());
	T.DayBegin.month = atoi(T_s.DayBegin_s.month.c_str());
	T.DayBegin.year = atoi(T_s.DayBegin_s.year.c_str());
	T.DayBegin.time.hour = atoi(T_s.DayBegin_s.time.hour.c_str());
	T.DayBegin.time.min = atoi(T_s.DayBegin_s.time.min.c_str());
	T.DayBegin.time.sec = atoi(T_s.DayBegin_s.time.sec.c_str());
	T.DayFinish.day = atoi(T_s.DayFinish_s.day.c_str());
	T.DayFinish.month = atoi(T_s.DayFinish_s.month.c_str());
	T.DayFinish.year = atoi(T_s.DayFinish_s.year.c_str());
	T.DayFinish.time.hour = atoi(T_s.DayFinish_s.time.hour.c_str());
	T.DayFinish.time.min = atoi(T_s.DayFinish_s.time.min.c_str());
	T.DayFinish.time.sec = atoi(T_s.DayFinish_s.time.sec.c_str());
}
//
date Today()
{
	date today;
	time_t now = time(NULL);
	tm* ltm = new tm;
	localtime_s(ltm, &now);
	today.year = 1900 + ltm->tm_year;
	today.month = 1 + ltm->tm_mon;
	today.day = ltm->tm_mday;
	today.time.hour = ltm->tm_hour;
	today.time.min = ltm->tm_min;
	today.time.sec = ltm->tm_sec;
	return today;
}
//
bool checkLeapYear(int year)
{
	return (((year % 4 == 0) && (year % 100 != 0)) ||
		(year % 400 == 0));
}
//
bool checkDate(date Date)
{
	if (Date.month == 4 || Date.month == 6 || Date.month == 9 || Date.month == 11)
	{
		if (Date.day == 31)
		{
			return false;
		}
		else {
			return true;
		}
	}
	else if (Date.month == 2) {
		if (Date.day > 29)
		{
			return false;
		}
		else if (Date.day == 29)
		{
			if (checkLeapYear(Date.year))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else {
			return true;
		}
	}
	else {
		return true;
	}
}
//
date InputDate()
{
	date Date;
	do {
		cout << "Nhap ngay:";
		cin >> Date.day;
	} while (Date.day < 1 || Date.day>31);
	do {
		cout << "Nhap thang :";
		cin >> Date.month;
	} while (Date.month < 1 || Date.month>12);
	do {
		cout << "Nhap nam :";
		cin >> Date.year;
	} while (Date.year <= 0);
	do {
		cout << "Nhap gio:";
		cin >> Date.time.hour;
	} while (Date.time.hour < 0 || Date.time.hour>24);
	do {
		cout << "Nhap phut:";
		cin >> Date.time.min;
	} while (Date.time.min < 0 || Date.time.min>59);
	do {
		cout << "Nhap giay:";
		cin >> Date.time.sec;
	} while (Date.time.sec < 0 || Date.time.sec>59);
	return Date;
}
//
bool ComparDay(date Date1, date Date2)
{
	if (Date2.year > Date1.year) {
		return true;
	}
	else if (Date2.year < Date1.year) {
		return false;
	}
	else {
		if (Date2.month > Date1.month)
		{
			return true;
		}
		else if (Date2.month < Date1.month) {
			return false;
		}
		else {
			if (Date2.day > Date1.day)
			{
				return true;
			}
			else if (Date2.day < Date1.day) {
				return false;
			}
			else {
				if (Date2.time.hour > Date1.time.hour)
				{
					return true;
				}
				else if (Date2.time.hour < Date1.time.hour) {
					return false;
				}
				else {
					if (Date2.time.min > Date1.time.min)
					{
						return true;
					}
					else if (Date2.time.min < Date1.time.min) {
						return false;
					}
					else {
						if (Date2.time.sec > Date1.time.sec)
						{
							return true;
						}
						else if (Date2.time.sec < Date1.time.sec) {
							return false;
						}
						else {
							return true;
						}
					}
				}
			}
		}
	}
}
//
registTime InputregistTime()
{
	registTime RegistTime;
	cout << "\nNhap ngay bat dau " << endl;
	cout << "-----------------------" << endl;
	RegistTime.DayBegin = InputDate();
	while (checkDate(RegistTime.DayBegin) == false)
	{
		cout << "-----------------------" << endl;
		cout << "Khong ton tai ngay nay " << endl;
		cout << "Vui long nhap lai ngay bat dau " << endl;
		RegistTime.DayBegin = InputDate();
	}
	cout << "\nNhap ngay ket thuc" << endl;
	cout << "-----------------------" << endl;
	RegistTime.DayFinish = InputDate();
	while (checkDate(RegistTime.DayFinish) == false)
	{
		cout << "-----------------------" << endl;
		cout << "Khong ton tai ngay nay " << endl;
		cout << "Vui long nhap lai ngay ket thuc " << endl;
		RegistTime.DayFinish = InputDate();
	}
	if (ComparDay(RegistTime.DayBegin, RegistTime.DayFinish) == false)
	{
		cout << "-------------------" << endl;
		cout << "Thoi gian ket thuc phai muon hon thoi gian bat dau " << endl;
		cout << "Vui long nhap lai " << endl;
		RegistTime = InputregistTime();
	}
	return RegistTime;
}
//
bool checktime(registTime RegistTime)
{
	date today = Today();
	bool check1 = ComparDay(RegistTime.DayBegin, today);
	bool check2 = ComparDay(today, RegistTime.DayFinish);
	if (check1 && check2)
	{
		return true;
	}
	else {
		return false;
	}
}
//
void writeToFile_T(string file, registTime& T) {
	fstream f;
	f.open(file, ios::out);
	f << T.DayBegin.day << ",";
	f << T.DayBegin.month << ",";
	f << T.DayBegin.year << ",";
	f << T.DayBegin.time.hour << ",";
	f << T.DayBegin.time.min << ",";
	f << T.DayBegin.time.sec << ",";
	f << T.DayFinish.day << ",";
	f << T.DayFinish.month << ",";
	f << T.DayFinish.year << ",";
	f << T.DayFinish.time.hour << ",";
	f << T.DayFinish.time.min << ",";
	f << T.DayFinish.time.sec << ",";
	f.close();
}
//
void readFromFile_T(string file, registTime_s& T_s) {
	fstream f;
	f.open(file, ios::in);
	if (!f.is_open())
		cout << "Error File Open";
	getline(f, T_s.DayBegin_s.day, ',');
	getline(f, T_s.DayBegin_s.month, ',');
	getline(f, T_s.DayBegin_s.year, ',');
	getline(f, T_s.DayBegin_s.time.hour, ',');
	getline(f, T_s.DayBegin_s.time.min, ',');
	getline(f, T_s.DayBegin_s.time.sec, ',');
	getline(f, T_s.DayFinish_s.day, ',');
	getline(f, T_s.DayFinish_s.month, ',');
	getline(f, T_s.DayFinish_s.year, ',');
	getline(f, T_s.DayFinish_s.time.hour, ',');
	getline(f, T_s.DayFinish_s.time.min, ',');
	getline(f, T_s.DayFinish_s.time.sec, ',');
	f.close();
}
//

void Login()
{
	int d = init_LOGIN(init_MENU());
	if (d == 1) mainMenu();
	else StudentAccess(const_cast<char*>("STUDENT ACCESS"));

}

int main() {
	Login();
	return 0;
}
