#pragma once
#include <vector>
#include <string>
#include <ctime>
#include <iostream>
#include <fstream>
#include <conio.h>
#include <sstream>
#include <iomanip>

#include "CourseFunction.h"
#include "SystemData.h"
#include "StaffFunction.h"
#include "Console.h"
#include "User.h"

using namespace std;

class Student: public User {
private:
	string userName, passWord, firstName, lastName, Class, ID, SocialID, academicYear;
	string gender; // 1=nam, 0=nu
	Date DOB;
	float GPAsem, GPAall;
	int numCredits, maxCredits;
	Course* SubRegis;
	Score scoreBoardSem[5];
	bool courseDay[6][4]; // 1=co tiet
	int numCourses;//so luong course hien tai
    float prevGPA;
    int prevCredits;
    User* UserInfo;
public:
	Student* pNext;

	Student() {
	    passWord = "12345678";
        numCredits = 0, numCourses = 0, maxCredits = 50;
        pNext = nullptr;
        for(int i = 0 ; i < 6 ; ++i) {
            for(int j = 0 ; j < 4 ; ++j) courseDay[i][j] = false;
        }
	}

    void setUser(User* UserInfo) {
        this->UserInfo = UserInfo;
    }

    void setPassWord(string passWord) {
        this->passWord = passWord;
    }

    double getGPAall() {
        return GPAall;
    }
    string getClass()
    {
        return Class;
    }
    void setClass(string Class) {
        this->Class = Class;
    }
    string getID() {
        return ID;
    }
    int getNumCourses() {
        return numCourses;
    }
    Course* getRegCourse() {
        return SubRegis;
    }
    void setScore(int pos, double Total, double Final, double Midterm, double Other) {
        scoreBoardSem[pos].Total=Total;
        scoreBoardSem[pos].Final=Final;
        scoreBoardSem[pos].Midterm=Midterm;
        scoreBoardSem[pos].Other=Other;
    }

    float GPASem();

    float GPAAll();

	void LoadCourseFromFile(Course* CourseList);

	void UpdateCourseToFile();

	bool StudentFunction(Course*& CourseList);

    bool isEnrollSuccess(Course*& CourseInfo);

    bool isEnrollCourse(Course* CourseInfo);

    int GetCourseID(Course* CourseInfo);

    /// task 13
    void EnrollCourse(Course*& CourseList);

    /// task 15
    bool isRemoveSuccess(Course*& CourseInfo);

    /// task 14, 16
    void ViewStudentCourse();

    void ViewScoreboard();

    void FixScoreboard(Course* CourseList);

    void LoadScoreboardFromFile(string Directory);

    void UpdateScoreboardToFile(string Directory);

    void ViewCourseScore(int Cnt, int PosY, int NumLine);

    void ViewStudent();

    void ViewInfo(int Cnt, int PosX, int PosY);

    bool FixInfo();

    friend void InputStudent(Student*& StudentList, User*& UserList);

    friend Student* FindStudent(Student* StudentList, string StudentID);

    friend void ViewStudentInClass(NodeClass*& ClassInfo, Student*& StudentList, User*& UserList);
    //For staffs to access student scoreboard
    friend bool ChangeCourseScore(Student*& CurrentStudent);

    friend void UpdateStudentToFile(Student* StudentList);

    friend void DeleteStudentFromList(Student*& StudentList, User*& UserList, string StudentID);

    friend void AddStudentToList(Student*& StudentList, User*& UserList, Student*& StudentInfo);
    friend void clearOut(Student* &listStudent);

    friend void AddStudent(NodeClass*& ClassInfo, Student*& pTail, int& NumStudent, Student*& StudentList, User*& UserList);

    friend void StudentOption(NodeClass*& ClassInfo, Student*& pTail, int& NumStudent, Student*& StudentList, User*& UserList);

    friend void ViewStudentInCourse(Course* CourseInfo, Student* StudentList);

    friend void LoadCourseScore(Course* CourseInfo, Student* StudentList);
};

///------------///

void clearOut(Student* &listStudent);

void drawview(int PosX, int PosY, int BoxWidth, int BoxHeight, string Directory, int TextLen);
