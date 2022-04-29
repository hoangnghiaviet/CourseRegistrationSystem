#pragma once
#include <iostream>
#include <string>
using namespace std;

#include "SystemData.h"
#include "Console.h"
#include "StudentFunction.h"

class Course {
private:
	string courseName, ID, teacherName;
	int numCredits;
	int date[2];
	int numStudent;
	int maxStudent;
	Date CourseStart;
	Date CourseEnd;
	ListID* StudentList;
public:
	Course* pNext;

	friend class Student;

	Course() {
		numCredits = 0;
        numStudent = 0, maxStudent = 50;
		date[0] = date[1] = 0;
        pNext = nullptr;
        StudentList = nullptr;
	}

	string getID() {
		return ID;
	}

	int getnumStudent() {
        return numStudent;
	}

	void RewriteInforOfCourse(Course* inputCourseNew);

	void freeStudentList();

	void RemoveStudentFromCourse(string StudentId);

	void ExportListStudent(string Dir);

	void ExportListStudentWindow();

	void ViewCourseTable(bool isExist, int Num, int PosX, int PosY);

	void FixCourseWindow();

	friend Course* FindCourse(Course* CourseList, string CourseID);

	friend void InputCourse(Course*& CourseList, string Directory);

	friend void OutputCourse(Course* CourseList, string Directory);

	friend void AddSubjecttoClass(NodeClass* ListClass, Course* CourseList);

	friend bool updateCourse(Course*& currentSubHead);

	friend void LoadCourseToFile(Course* CourseList, string location);

	friend bool deleteCourseChoose(string input, Course*& currentSubHead);

	friend void AddCourseWindow(Course* CourseList, NodeClass* ClassInfo);

	friend bool ImportScoreboardCSV(Course*& CourseList, string &CourseID, Student *StudentList, string Dir);

	friend void clearOut(ListCourse* &listCourse);
};

void ViewListCourseTable(Course* CourseList, int PosX, int PosY);

