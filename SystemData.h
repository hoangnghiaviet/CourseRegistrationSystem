#pragma once
#include <iostream>
#include <string>
using namespace std;

class User;

class Staff;

class Course;

class Student;

struct ListID {
    string ID;
	string fullName;
    ListID* pNext;

    ListID() {
        pNext = nullptr;
    }
};

struct Date {
	int day, month, year;
	string StrDOB;

	Date() {
        day = 0, month = 0, year = 0;
	}

	Date(string StrDOB) {
	    this->StrDOB = StrDOB;
        int Pos = 0;
        day = 0, month = 0, year = 0;
        for(; Pos < StrDOB.size() && StrDOB[Pos] != '/'; ++Pos) day = day * 10 + StrDOB[Pos] - '0';
        Pos++;
        for(; Pos < StrDOB.size() && StrDOB[Pos] != '/'; ++Pos) month = month * 10 + StrDOB[Pos] - '0';
        Pos++;
        for(; Pos < StrDOB.size() && StrDOB[Pos] != '/'; ++Pos) year = year * 10 + StrDOB[Pos] - '0';
	}
};

int DateToInt(Date &date);

bool checkSyntaxDate(Date &date);

// 1 course
struct Score {
	double Total, Final, Midterm, Other;
	string CourseName;
};

struct ListCourse {
	Course *pHead, *pTail;
	ListCourse() {
		pHead=nullptr;
		pTail=nullptr;
	}
};
struct NodeClass {
	string className;
	Student* listStudents;
	NodeClass* pNext;

	NodeClass() {
        listStudents = nullptr;
        pNext = nullptr;
	}
};
struct ListClasses {
	NodeClass *pHead, *pTail;
	ListClasses() {
		pHead=nullptr;
		pTail=nullptr;
	}
};
struct Sem {
	int order;
	NodeClass* listClass;
	Sem* pNext;
	Date SemStart;
	Date SemEnd;

	Sem() {
		order = 0;
        listClass = nullptr;
        pNext = nullptr;
	}
};
struct ListSem {
	Sem *pHead, *pTail;
	ListSem() {
		pHead=nullptr;
		pTail=nullptr;
	}
};


struct NodeYear {
	string year_name;
	ListSem* listSem;
	NodeYear* pNext;

	NodeYear() {
		year_name="";
        listSem = nullptr;
        pNext = nullptr;
	}
};
struct ListYear {
	NodeYear *pHead, *pTail;
	ListYear() {
		pHead=nullptr;
		pTail=nullptr;
	}
};

string GetPath();

string GetSemPath();

void UpdateSemLink();

void clearOut(ListClasses* &listClasses);
void clearOut(ListYear* &listYear);
void clearOut(ListSem* &listSem);
void clearOut(NodeClass* &listClass);
void clearOut(ListID* &listID);
void clearOut(User* &listUser);
