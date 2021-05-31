#include<iostream>
#include<fstream>
#include<string>
using namespace std;

struct dateOfBirth {
	int day;
	int month;
	int year;
};

struct student {
	int No;
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
	cout << "Date: ";
	cin >> student.date.day;
	cin >> student.date.month;
	cin >> student.date.year;
	cin.ignore();
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

//void printList(list l)
//{
//	Node* pTmp = l.pHead;
//	if (pTmp == NULL)
//	{
//		cout << "Empty";
//		return;
//	}
//
//	cout << "Car Information:" << endl << endl;
//	for (Node* p = l.pHead; p != NULL; p = p->pNext) {
//		cout << "ID:" << p->data.ID << endl;
//		cout << "Name: " << p->data.name << endl;
//		cout << "Date: " << p->data.date.day << "/" << p->data.date.month << "/" << p->data.date.year << endl << endl;
//
//	}
//	cout << "=====================================" << endl;
//}

void addHead(list& l, Node* p) {

	if (l.pHead == NULL) {
		l.pHead = l.pTail = p;
	}
	else {
		p->pNext = l.pHead;
		l.pHead = p;
	}

}

bool writeToFile(string file, list l) {
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

int main() {
	list l;
	initL(l);
	addTail(l, createNode(insertStudent()));
	//printList(l);
	writeToFile("E:/Thanh Demo/First Year- Second Term/Midterm/student.csv", l);
}



//bool readFromFile(string file, list l) {
//	car car;
//	ifstream f("test1.csv");
//	if (!f.is_open())
//		cout << "Error File Open";
//
//	string line;
//	getline(f, line);
//	while (f) {
//		getline(f, car.ID, ',');
//		getline(f, car.name, ',');
//		getline(f, car.date.day, ',');
//		getline(f, car.date.month, ',');
//		getline(f, car.date.year, ',');
//		addTail(l, createNode(insertCar()));
//
//	}
//
//	f.close();
//}