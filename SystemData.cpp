#include "SystemData.h"
#include "StudentFunction.h"
#include "CourseFunction.h"
#include "StaffFunction.h"
#include <fstream>

string GetPath() {
    ifstream fin("Data/Link/YearPath.txt");
    string s = "no/";
    if(fin.is_open()) getline(fin, s);
    fin.close();
    return s;
}
string GetSemPath() {
    ifstream fin("Data/Link/SemPath.txt");
    string s = "no/";
    if(fin.is_open()) getline(fin, s);
    fin.close();
    return s;
}

void UpdateSemLink() {
    Date Day;
    time_t now = time(0);
	tm* kiemtra=localtime(&now);
	Date Now;
	Now.day = kiemtra->tm_mday, Now.month = 1 + kiemtra->tm_mon, Now.year = 1900 + kiemtra->tm_year;
    ifstream fin;
    for(int i = 3; i >= 1; --i) {
        fin.open("Data/" + GetPath() + "Sem" + char(i + '0') + "/SemDate.txt");
        if(fin.is_open()) {
            fin >> Day.day >> Day.month >> Day.year;
            if(DateToInt(Day) <= DateToInt(Now)) {
                ofstream fout("Data/Link/SemPath.txt");
                fout << "Sem" << i << "/";
                fout.close();
                fin.close();
                return;
            }
        }
        fin.close();
    }
    ofstream fout("Data/Link/SemPath.txt");
    fout << "null/";
    fout.close();
}

// converts Gregorian date to integer (Julian day number)
int DateToInt(Date &date) {
	return
		1461*(date.year+4800+(date.month-14)/12)/4+
		367*(date.month-2-(date.month-14)/12*12)/12-
		3*((date.year+4900+(date.month-14)/12)/100)/4+
		date.day-32075;
}

// check if the date exists
bool checkSyntaxDate(Date &date) {
	if(date.day<1 || date.month<1 || date.year<2021 || date.day>31 || date.month>12) return false;
	if(date.month==2) {
		if(date.day<29) return true;
		// check leap year -> 29/2 exists
		if(date.year%400==0 || (date.year%4==0 && date.year%100!=0))
			return date.day<=29;
		return false;
	}

	// April, June, September, November have 30 days
	if(date.month==4 || date.month==6 || date.month==9 || date.month==11)
		return date.day<=30;

	return date.day<=31;
}

void clearOut(Staff* &listStaff) {
	Staff* cur=listStaff;
	while(cur) {
		Staff* del=cur;
		cur=cur->pNext;
		delete del;
	}
}

void clearOut(User* &listUser) {
	User* cur=listUser;
	while(cur) {
		User* del=cur;
		cur=cur->pNext;
		delete del;
	}
}

void clearOut(Student* &listStudent) {
	Student* cur=listStudent;
	while(cur) {
		delete []cur->SubRegis;
		Student* del=cur;
		cur=cur->pNext;
		delete del;
	}
}

void clearOut(ListID* &listID) {
	ListID* cur=listID;
	while(cur) {
		ListID* del=cur;
		cur=cur->pNext;
		delete del;
	}
}

void clearOut(ListCourse* &listCourse) {
	Course* cur=listCourse->pHead;
	while(cur) {
		clearOut(cur->StudentList);
		Course* del=cur;
		cur=cur->pNext;
		delete del;
	}

	delete listCourse->pHead;
	delete listCourse->pTail;
}

// void clearOut(ListClasses* &listClasses) {
// 	NodeClass* cur=listClasses->pHead;
// 	while(cur) {

// 	}
// }

void clearOut(NodeClass* &listClass) {
	NodeClass* cur=listClass;
	while(cur) {
		clearOut(cur->listStudents);
		NodeClass* del=cur;
		cur=cur->pNext;
		delete del;
	}
}

void clearOut(ListYear* &listYear) {
	NodeYear* cur=listYear->pHead;
	while(cur) {
		clearOut(cur->listSem);
		NodeYear *del=cur;
		cur=cur->pNext;
		delete del;
	}

	delete listYear->pHead;
	delete listYear->pTail;
}

void clearOut(ListSem* &listSem) {
	Sem* cur=listSem->pHead;
	while(cur) {
		clearOut(cur->listClass);
		Sem* del=cur;
		cur=cur->pNext;
		delete del;
	}

	delete listSem->pHead;
	delete listSem->pTail;
}
