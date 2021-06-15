#include<iostream>
#include<fstream>
#include<string>
using namespace std;

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
		getline(f, student.socialID, ',');
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
		getline(f, score.other);
		cout << endl;


		addTailScore(lScore, createScoreBoard(score));

	}

	f.close();
	return true;
}

int main() {
	list l;
	initL(l);
	listScore lScore;
	initLScore(lScore);
	//addTail(l, createNode(insertStudent()));
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



