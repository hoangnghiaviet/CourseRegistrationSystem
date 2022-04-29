#include <vector>
#include <string>
#include <ctime>
#include <iostream>
#include <conio.h>
using namespace std;

#include "SystemData.h"
#include "StudentFunction.h"
#include "StaffFunction.h"
#include "Console.h"
#include "User.h"
#include "Graphic.h"
#include "AcademicYear.h"


int main()
{
    system("mode 650");
    _getch();
    UpdateSemLink();
    ListYear* YearList = nullptr;
    NodeYear* YearHead = nullptr;
    ListSem* SemList = nullptr;
    Sem* SemHead = nullptr;
    drawMode1();
    Button StaffButton = Button(25, 15, 15, 5, "");
    Button StudentButton = Button(120, 15, 15, 5, "");
    Button QuitButton = Button(73, 28, 15, 4, "");
    Course* CourseList = nullptr;
    Student* StudentList = nullptr;
    Staff* StaffList = nullptr;
    User* UserList = nullptr;
    NodeClass* ClassList = nullptr;

    InputStudent(StudentList, UserList);
    InputStaff(StaffList, UserList);
    CreateListClass(ClassList, StudentList);
    InputYear(YearList);

    while(1) {
        gotoXY(0, 0);
        COORD MousePosition;
        while(!isLeftMousePressed(MousePosition));
        if(QuitButton.isClick(MousePosition)) {
            system("cls");
            break;
        }
        else if(StudentButton.isClick(MousePosition)) {
            system("cls");
            /*if(!YearList) {
                DrawInfor();
                system("pause");
                system("cls");
                drawMode1();
                continue;
            }*/
            User* UserInfo = nullptr;
            LogIn(UserList, UserInfo, 1);
            if(UserInfo) {
                Student* StudentInfo = FindStudent(StudentList, UserInfo->getUserName());
                if(StudentInfo) {
                    /// deallocate CourseList
                    CourseList = nullptr;
                    StudentInfo->setUser(UserInfo);
                    bool isContinue = StudentInfo->StudentFunction(CourseList);
                    StudentInfo->setPassWord(UserInfo->getPassWord());
                    if(!isContinue) break;
                }
            }
            drawMode1();
        }
        else if(StaffButton.isClick(MousePosition)) {
            system("cls");
            User* UserInfo = nullptr;
            LogIn(UserList, UserInfo, 0);
            if(UserInfo) {
                Staff* StaffInfo = FindStaff(StaffList, UserInfo->getUserName());
                if(StaffInfo) {
                    /// deallocate CourseList
                    CourseList = nullptr;
                    InputCourse(CourseList, "Data/" + GetPath() + GetSemPath() + "Course/CourseData.txt");
                    for(Student* CurStudent = StudentList; CurStudent; CurStudent = CurStudent->pNext) CurStudent->LoadCourseFromFile(CourseList);
                    StaffInfo->setUser(UserInfo);
                    bool isContinue = StaffInfo->StaffFunction(ClassList, StudentList, CourseList, UserList, YearList, SemList);
                    StaffInfo->setPassWord(UserInfo->getPassWord());
                    if(!isContinue) break;
                }
            }
            drawMode1();
        }
    }
    UpdateStaffToFile(StaffList);
    UpdateStudentToFile(StudentList);
    UpdateYearToFile(YearList);
}
