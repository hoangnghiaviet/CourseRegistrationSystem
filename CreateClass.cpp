#include <iostream>
#include <string.h>

using namespace std;
#include "SystemData.h"
#include "StaffFunction.h"

bool CreateClass(Class*& classList) {
    string className;
    cout << "Please enter the name of the new class: ";
    getline(cin, className, '\n');

    // return false if exists an old class with the same name -> conflict
    Class* curr = classList;
    if (classList) {
        if (curr->className == className) return false;
        for (; curr->next; curr = curr->next)
            if (curr->next->className == className) return false;
    }

    // add the new class to the list
    Class* newClass = new Class({ className, nullptr });
    if (curr)
        curr->next = newClass;
    else
        classList = newClass;
    return true;
}

void addCourse(Course*& newCourse, ListCourse *&listCourse) {
    fflush(stdin);
    cout << "Please enter the ID of the new course: ";
    getline(cin, newCourse->ID, '\n');

    fflush(stdin);
    cout << "Please enter the name of the course: ";
    getline(cin, newCourse->courseName, '\n');

    fflush(stdin);
    cout << "Please enter the name of the teacher of the course: ";
    getline(cin, newCourse->teacherName, '\n');

    cout << "The number of credits for this course: ";
    cin >> newCourse->numCredits;

    cout << "Maximum number of students for this course: ";
    cin >> newCourse->maxStudent;

    newCourse->remain=newCourse->maxStudent;
    newCourse->StudentList=nullptr;

    cout << "Sessions of the course: \n";
    for(int i=0; i<2; ++i) {
        cout << "Session " << i << ": \n";
        
        // enter the day of the session
        cout << "Please enter the day of this session.\n";
        cout << "(Option 1-6 is correspondent to Monday-Saturday)\n";
        int day=-1, ses=-1;
        while(day<1 || day>6) {
            cin >> day;
            if(day<1||day>6) cout << "This option is invalid, please try again!\n";
        }

        // enter the order of the session
        cout << "Please enter the time of this session at the day.\n";
        cout << "{1-7h30} {2-9h30} {3-13h30} {4-15h30}\n";

        while(ses<1 || ses>4) {
            cin >> ses;
            if(ses<1 || ses>6) cout << "This option is invalid, please try again!\n";
        }

        newCourse->date[i]=4*(day-1)+ses-1;
    }

    // add new course to the end of the list
    if(!listCourse->pHead) {
        listCourse->pHead=listCourse->pTail=newCourse;
    else {
        listCourse->pTail->pNext=newCourse;
        listCourse->pTail=newCourse;
    }

    string faculty;
    cout << "Please enter the name of the faculty: ";
    getline(cin, faculty, '\n');

    ofstream fout;
	fout.open(faculty".txt", ios::app);
	fout << newCourse->ID << '\n';
	fout << newCourse->courseName << '\n';
	fout << newCourse->numCredits << '\n';
	fout << newCourse->maxStudent << '\n';
	fout << newCourse->remain << '\n';
	fout << newCourse->teacherName << '\n';
	fout.close();
}

void printClassList(Class*& classList) {
    if (classList) {
        cout << "Current active classes:\n";
        for (Class* curr = classList; curr; curr = curr->next)
            cout << curr->className << '\n';
    }

    else
        cout << "There are currently no classes.\n";
}