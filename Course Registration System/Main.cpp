#include<iostream>
#include<fstream>
#include<string>
using namespace std;

struct TimeTable {
	bool table[4][7];
	string nameOfSubject[4][7];
};

struct TimeTableFromAdmin {
	string nameOfSubject[30];
	string weekDay[30];
	string time[30];
};

struct dateOfBirth {
	string day;
	string month;
	string year;
};

struct student {
	string No;
	string studentID;
	string firstName;
	string lastName;
	string gender;
	dateOfBirth date;
	string socialID;
};

struct ScoreBoard {
	string No;
	string studentID;
	string fullName;
	string aveScore;
	string finalTermScore;
	string middleTermScore;
	string other;
};

struct Node {
	student data;
	Node* pNext;
};

struct NodeScore {
	ScoreBoard data;
	NodeScore* pNext;
};

struct list {
	Node* pHead;
	Node* pTail;
};

struct listScore {
	NodeScore* pHead;
	NodeScore* pTail;
};

void initLScore(listScore& lScore)
{
	lScore.pHead = lScore.pTail = NULL;
}

void initL(list& l)
{
	l.pHead = l.pTail = NULL;
}

NodeScore* createScoreBoard(ScoreBoard score)
{
	NodeScore* p = new NodeScore;
	p->pNext = NULL;
	p->data = score;
	return p;
}

student insertStudent()
{
	student student;
	cout << "No: ";
	cin >> student.No;
	cin.ignore();
	cout << "Student ID: ";
	getline(cin, student.studentID);
	//cin.ignore();
	cout << "First Name: ";
	getline(cin, student.firstName);
	//cin.ignore();
	cout << "Last Name: ";
	getline(cin, student.lastName);
	//cin.ignore();
	cout << "Gender: ";
	getline(cin, student.gender);
	cout << "Day: ";
	getline(cin, student.date.day);
	cout << "Month: ";
	getline(cin, student.date.month);
	cout << "Year: ";
	getline(cin, student.date.year);
	cout << "Social ID: ";
	getline(cin, student.socialID);
	return student;
}
//Nhap tay
ScoreBoard insertStudentScore()
{
	ScoreBoard score;

	cout << "No: ";
	cin >> score.No;
	cin.ignore();

	cout << "Student ID: ";
	getline(cin, score.studentID);

	cout << "Full Name: ";
	getline(cin, score.fullName);

	cout << "Average Score: ";
	getline(cin, score.aveScore);

	cout << "Middle Term Score: ";
	getline(cin, score.finalTermScore);

	cout << "Final Term Score: ";
	getline(cin, score.finalTermScore);

	cout << "Bonus score: ";
	getline(cin, score.other);

	return score;
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

void delHead(list& l) {
	if (l.pHead == NULL) {
		cout << "Don't have element";
	}
	else {
		l.pHead = l.pHead->pNext;
	}
}

void delTail(list& l) {
	if (l.pHead == NULL || l.pHead->pNext == NULL) {
		delHead(l);
	}
	Node* p = l.pHead;
	while (p->pNext->pNext != NULL) {
		p = p->pNext;
	}
	p->pNext = p->pNext->pNext;
}

void printList(list l)
{
	Node* pTmp = l.pHead;
	if (pTmp == NULL)
	{
		cout << "Empty";
		return;
	}

	cout << "Student Information:" << endl << endl;
	for (Node* p = l.pHead; p->pNext != NULL; p = p->pNext) {
		cout << "No: " << p->data.No << endl;
		cout << "Student ID: " << p->data.studentID << endl;
		cout << "First Name: " << p->data.firstName << endl;
		cout << "Last Name: " << p->data.lastName << endl;
		cout << "Gender: " << p->data.gender << endl;
		cout << "Date of Birth: " << p->data.date.day << "/" << p->data.date.month << "/" << p->data.date.year << endl;
		cout << "Social ID: " << p->data.socialID << endl << endl;
	}
	cout << "=====================================" << endl;
}

void printScoreBoard(listScore lScore)
{
	NodeScore* pTmp = lScore.pHead;
	if (pTmp == NULL)
	{
		cout << "Empty";
		return;
	}

	cout << "Student Information:" << endl << endl;
	for (NodeScore* p = lScore.pHead; p->pNext != NULL; p = p->pNext) {
		cout << "No: " << p->data.No << endl;
		cout << "Student ID: " << p->data.studentID << endl;
		cout << "Full Name: " << p->data.fullName << endl;
		cout << "Average Score: " << p->data.aveScore << endl;
		cout << "Final-Term Score: " << p->data.finalTermScore << endl;
		cout << "Mid-Term Score: " << p->data.middleTermScore << endl;
		cout << "Other: " << p->data.other << endl << endl;
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

bool writeToFile(string file, list& l) {
	fstream f;
	f.open(file, ios::app);
	for (Node* k = l.pHead;k != NULL;k = k->pNext) {
		f << k->data.No << ",";
		f << k->data.studentID << ",";
		f << k->data.firstName << ",";
		f << k->data.lastName << ",";
		f << k->data.gender << ",";
		f << k->data.date.day << ",";
		f << k->data.date.month << ",";
		f << k->data.date.year << ",";
		f << k->data.socialID << "," << endl;
	}
	f.close();
	return true;
}

bool readFromFile(string file, list& l) {
	student student;
	fstream f;
	f.open(file, ios::in);
	if (!f.is_open())
		cout << "Error File Open";

	while (!f.eof()) {
		getline(f, student.No, ',');
		getline(f, student.studentID, ',');
		getline(f, student.firstName, ',');
		getline(f, student.lastName, ',');
		getline(f, student.gender, ',');
		getline(f, student.date.day, ',');
		getline(f, student.date.month, ',');
		getline(f, student.date.year, ',');
		getline(f, student.socialID, '\n');
		addTail(l, createNode(student));

	}

	f.close();
	return true;
}

bool writeScoreToFile(string file, listScore& lScore) {
	fstream f;
	f.open(file, ios::app);
	for (NodeScore* k = lScore.pHead;k != NULL;k = k->pNext) {
		f << k->data.No << ",";
		f << k->data.studentID << ",";
		f << k->data.fullName << ",";
		f << k->data.aveScore << ",";
		f << k->data.finalTermScore << ",";
		f << k->data.middleTermScore << ",";
		f << k->data.other << "," << endl;
	}
	f.close();
	return true;
}

bool readScoreFromFile(string file, listScore& lScore) {
	ScoreBoard score;
	fstream f;
	f.open(file, ios::in);
	if (!f.is_open())
		cout << "Error File Open";

	while (!f.eof()) {
		getline(f, score.No, ',');
		getline(f, score.studentID, ',');
		getline(f, score.fullName, ',');
		getline(f, score.aveScore, ',');
		getline(f, score.finalTermScore, ',');
		getline(f, score.middleTermScore, ',');
		getline(f, score.other, '\n');
		cout << endl;


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
	f.open(file, ios::out);
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

void writeMyAllSubjectScore(string fileNameSubject, string ID, listScore& lScore, listScore& lScore1, string classname)
{
	ScoreBoard score;
	ScoreBoard score1;
	fstream f;

	f.open(fileNameSubject, ios::in);
	if (!f.is_open())
		cout << "Error File Open";

	while (!f.eof()) {
		getline(f, score.fullName, '\n');
		addTailScore(lScore, createScoreBoard(score));
	}
	f.close();
	for (NodeScore* p = lScore.pHead; p != NULL; p = p->pNext)
	{
		f.open(p->data.fullName + classname + "Score.csv", ios::in);
		if (!f.is_open())
			cout << "Error File Open";

		while (!f.eof()) {
			getline(f, score1.No, ',');
			getline(f, score1.studentID, ',');
			getline(f, score1.fullName, ',');
			getline(f, score1.aveScore, ',');
			getline(f, score1.finalTermScore, ',');
			getline(f, score1.middleTermScore, ',');
			getline(f, score1.other);
			cout << endl;
			addTailScore(lScore1, createScoreBoard(score1));
		}
		for (NodeScore* k = lScore1.pHead; k != NULL; k = k->pNext)
		{
			if (k->data.studentID == ID)
			{
				p->data.aveScore = k->data.aveScore;
				p->data.middleTermScore = k->data.middleTermScore;
				p->data.finalTermScore = k->data.finalTermScore;
				p->data.other = k->data.other;
			}
		}
		f.close();
	}
	f.open(ID + ".csv", ios::out);
	for (NodeScore* l = lScore.pHead;l != NULL;l = l->pNext) {
		f << l->data.fullName << ',';
		f << l->data.aveScore << ',';
		f << l->data.finalTermScore << ',';
		f << l->data.middleTermScore << ',';
		f << l->data.other << ',' << endl;
	}
	f.close();

}

void readMyAllSubjectScore(string file, listScore& lScore)
{
	ScoreBoard score;
	fstream f;
	f.open(file, ios::in);
	if (!f.is_open())
		cout << "Error File Open";

	while (!f.eof()) {
		getline(f, score.fullName, ',');
		getline(f, score.aveScore, ',');
		getline(f, score.finalTermScore, ',');
		getline(f, score.middleTermScore, ',');
		getline(f, score.other);
		cout << endl;


		addTailScore(lScore, createScoreBoard(score));

	}

	f.close();

}

int main() {
	list l;
	initL(l);
	listScore lScore;
	initLScore(lScore);
	//addTail(l, createNode(insertStudent()));
	
	
	//addTailScore(lScore, createScoreBoard(insertStudentScore()));
	//addTailScore(lScore, createScoreBoard(insertStudentScore()));
	//printList(l);
	//writeToFile("NMCNTT.csv", l);
	writeScoreToFile("NMCNTT-Score.csv", lScore);
	//readFromFile("student2.csv", l);
	readScoreFromFile("KTLTScore.csv", lScore);
	//printList(l);
	printScoreBoard(lScore);
}



