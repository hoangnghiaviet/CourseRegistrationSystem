#pragma once
#include <vector>
#include <string>
#include <ctime>
#include <iostream>
#include <fstream>
#include <conio.h>
#include <direct.h>
#include <Windows.h>
#include <mmsystem.h>

using namespace std;

#include "SystemData.h"
#include "StudentFunction.h"
#include "CourseFunction.h"
#include "Console.h"
#include "AcademicYear.h"

class Staff {
private:
    string userName, passWord, firstName, lastName, ID, SocialID;
	string gender; // 1=nam, 0=nu
	Date DOB;
	User* UserInfo;
public:
    Staff* pNext;

    Staff() {
        userName = "";
        passWord = "12345678";
        firstName = "";
        lastName = "";
        pNext = nullptr;
    }

    void setUser(User* UserInfo) {
        this->UserInfo = UserInfo;
    }

    void setPassWord(string passWord) {
        this->passWord = passWord;
    }

    bool StaffFunction(NodeClass*& ClassList, Student*& StudentList, Course*& CourseList, User*& UserList, ListYear*& YearList, ListSem*& SemList);

    void CreateSem(ListYear*& YearList, ListSem*& SemList);

    void ViewStaff();

    void ViewClass(NodeClass* ClassList, Course* CourseList, Student*& StudentList, User*& UserList);

    void ViewListClass(string Year, NodeClass* ClassList, Course* CourseList, Student*& StudentList, User*& UserList);

    friend void InputStaff(Staff*& StaffList, User*& UserList);

    friend Staff* FindStaff(Staff* StaffList, string StaffID);
    //Update student's score
    bool UpdateStudentScore(Student* StudentList, string StudentID);
    //View the scoreboard of a class
    NodeClass* findClass(NodeClass* ListClass);

    friend void displayStudentListtoViewScore(NodeClass* ListClass, Staff currentStaff);

    friend void UpdateStaffToFile(Staff* StaffList);

    friend void clearOut(Staff* &listStaff);
};

/// tạo cột phần trăm ở 4 cột
void drawStatistics(float d, float c, float b, float a);

/// vẽ bảng thống kê bao gồm các cột và trục
void PrintALLStatistics(Student* StudentList);

///-----------------///

void ViewListStudent(Student* StudentList);

//----Function of Class in StaffFucntion------

//Load students into each class
void loadStudentIntoClass(NodeClass*& ClassList, Student* StudentList);
// Create CLass and Load Students into this class
void CreateListClass(NodeClass*& ClassList, Student* StudentList);
//View Class
void ViewCLass(NodeClass* ClassList);

NodeClass* FindClass(NodeClass* ClassList, string ClassID);

void ChooseClass(NodeClass* ClassList, Course* CourseList, bool isViewStudent, Student*& StudentList, User*& UserList);

void ViewCourseInClass(NodeClass* ClassInfo, Course* CourseList);

// Delete Course
void deleteCourseForClass(NodeClass*& ClassList, Course*& CourseList, Course*& curr);

void AddCourseWindow(Course* CourseList, NodeClass* ClassInfo);

void CourseOption(Course* CourseList, NodeClass* ClassInfo);

void SetEnrollDate();

void SetSemWindow(NodeYear*& YearInfo);

void SettingWindow(ListYear*& YearList, ListSem*& SemList, NodeClass*& ClassList, Student*& StudentList, Course*& CourseList, User*& UserList);

void ChooseStudent(Student* StudentList, Course* CourseList);

void SetYearOption(ListYear*& YearList);

void CreateYear(ListYear*& YearList);

void FixYear(ListYear*& YearList);

bool ImportFile(string DirIn, string DirOut);

void ImportData(ListYear* YearList);

void AddStudent(NodeClass*& ClassInfo, Student*& pTail, int& NumStudent, Student*& StudentList, User*& UserList);

void StudentOption(NodeClass*& ClassInfo, Student*& pTail, int& NumStudent, Student*& StudentList, User*& UserList);

void ViewStudentInCourse(Course* CourseInfo, Student* StudentList);

//Play Sound
void successSound();
void FailSound();


