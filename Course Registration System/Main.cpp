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

struct Node {
	student data;
	Node* pNext;
};

struct list {
	Node* pHead;
	Node* pTail;
};

void initL(list& l)
{
	l.pHead = l.pTail = NULL;
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
		getline(f, student.socialID);
		cout << endl;


		addTail(l, createNode(student));

	}

	f.close();
	return true;
}

int main() {
	list l;
	initL(l);
	//addTail(l, createNode(insertStudent()));
	//addTail(l, createNode(insertStudent()));

	//printList(l);
	//writeToFile("student2.csv", l);
	readFromFile("student2.csv", l);
	printList(l);
}



