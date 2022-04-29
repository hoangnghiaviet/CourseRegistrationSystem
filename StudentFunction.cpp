#include "StudentFunction.h"

Student* FindStudent(Student* StudentList, string StudentID) {
    for(Student* Cur = StudentList; Cur; Cur = Cur->pNext) {
        if(Cur->ID == StudentID) {
            return Cur;
        }
    }
    return nullptr;
}

void InputStudent(Student*& StudentList, User*& UserList) {
    ifstream fin("Data/Student/StudentData.csv");
    Student* DumStudent = new Student;
    User* DumUser = new User;
    DumStudent->pNext = nullptr;
    DumUser->pNext = nullptr;
    StudentList = DumStudent;
    UserList = DumUser;
    if (!fin.is_open())
    {
        cout << "Error opening the file!!!";
        fin.close();
        return;
    }
    string sID;
    getline(fin, sID);
    while(!fin.eof() && getline(fin, sID, ',')) {
        StudentList->pNext = new Student;
        StudentList = StudentList->pNext;
        UserList->pNext = new User;
        UserList = UserList->pNext;

        StudentList->SubRegis = new Course[5];

        StudentList->ID = sID;

        getline(fin, StudentList->passWord, ',');

        getline(fin, StudentList->lastName, ',');

        getline(fin, StudentList->firstName, ',');

        getline(fin, StudentList->Class, ',');

        getline(fin, StudentList->gender, ',');

        string StrDOB;
        getline(fin, StrDOB, ',');

        getline(fin, StudentList->academicYear, ',');

        getline(fin, StudentList->SocialID, ',');

        stringstream ss;

        string prevGPA, prevCredits;
        getline(fin, prevGPA, ',');
        getline(fin, prevCredits);

        ss << prevGPA << ' ' << prevCredits;
        ss >> StudentList->prevGPA >> StudentList->prevCredits;

        //fin.get();

        StudentList->userName = StudentList->ID;
        StudentList->DOB = Date(StrDOB);

        UserList->setFullName(StudentList->firstName, StudentList->lastName);
        UserList->setGender(StudentList->gender);
        UserList->setUserName(StudentList->ID);
        UserList->setPassWord(StudentList->passWord);
    }
    StudentList = DumStudent->pNext;
    UserList = DumUser->pNext;
    delete DumStudent;
    delete DumUser;
    fin.close();
}

bool Student::isEnrollSuccess(Course*& CourseInfo) {
    if(numCourses == 5 || isEnrollCourse(CourseInfo)) return false;
    for(int i = 0; i < 2; ++i) {
        int Day = CourseInfo->date[i] / 4, Session = CourseInfo->date[i] % 4;
        if(courseDay[Day][Session]) return false;
    }
    if(numCredits + CourseInfo->numCredits > maxCredits) return false;
    if(CourseInfo->numStudent + 1 > CourseInfo->maxStudent) return false;

    numCredits += CourseInfo->numCredits;
    SubRegis[numCourses] = *CourseInfo;
    numCourses += 1;
    CourseInfo->numStudent += 1;
    for(int i = 0; i < 2; ++i) {
        int Day = CourseInfo->date[i] / 4, Session = CourseInfo->date[i] % 4;
        courseDay[Day][Session] = 1;
    }

    ListID* NewID = new ListID;
    NewID->ID = ID;
    NewID->fullName = lastName + " " + firstName;
    NewID->pNext = CourseInfo->StudentList;
    CourseInfo->StudentList = NewID;
    return true;
}

bool Student::isEnrollCourse(Course* CourseInfo) {
    for(int i = 0; i < numCourses; ++i) {
        if(SubRegis[i].ID == CourseInfo->ID) return true;
    }
    return false;
}

int Student::GetCourseID(Course* CourseInfo) {
    for(int i = 0; i < numCourses; ++i) {
        if(SubRegis[i].ID == CourseInfo->ID) return i;
    }
    return -1;
}

/// Task 15
bool Student::isRemoveSuccess(Course*& CourseInfo) {
    if(!CourseInfo) {
        return false;
    }

    int PosCourse = -1;
    for(int i = 0; i < numCourses && PosCourse == -1; ++i) {
        if(SubRegis[i].ID == CourseInfo->ID) {
            PosCourse = i;
        }
    }
    if(PosCourse == -1) {
        return false;
    }

    numCredits -= CourseInfo->numCredits;
    CourseInfo->numStudent -= 1;
    for(int i = 0; i < 6; ++i) {
        for(int j = 0; j < 4; ++j) {
            for(int k = 0; k < 2; ++k)
            {
                if(i == CourseInfo->date[k] / 4 && j == CourseInfo->date[k] % 4) {
                    courseDay[i][j] = false;
                }
            }
        }
    }
    for(int i = PosCourse + 1; i < numCourses; ++i) {
        SubRegis[i - 1] = SubRegis[i];
    }
    numCourses -= 1;
    CourseInfo->RemoveStudentFromCourse(ID);
    return true;
}

/// Task 13
void Student::EnrollCourse(Course*& CourseList)
{
    timeStart registDate;
    ifstream fin("Data/" + GetPath() + GetSemPath() + "Course/EnrollDate.txt");

    if(!fin.is_open()) {
        fin.close();
        gotoXY((GetWidth() - 33) / 2, 15);
        cout << "Registration session is not open!";
        gotoXY((GetWidth() - 33) / 2, 17);
        system("pause");
        return;
    }

    fin >> registDate.check;
    if(registDate.check) {
        fin >> registDate.ngay.day >> registDate.ngay.month >> registDate.ngay.year;
        fin >> registDate.End.day >> registDate.End.month >> registDate.End.year;
    }
    fin.close();

    if(!registDate.check || !checkRegistDate(registDate)) {
        gotoXY((GetWidth() - 33) / 2, 15);
        cout << "Registration session is not open!";
        gotoXY((GetWidth() - 33) / 2, 17);
        system("pause");
        return;
    }

    int PosX = (GetWidth() - 142) / 2, PosY = 8;
	ViewListCourseTable(CourseList, PosX, PosY);
    SetBGColor(8);
    for(int k = 1; k < 4; ++k) {
        for(int u = 0; u < 8; ++u) {
            gotoXY(134 + PosX + u, k + 8);
            cout << " ";
        }
    }
    gotoXY(134 + PosX + 1, 10);
    cout << "Option";

    Button* DumButton = new Button;
    Button* ButtonList = DumButton;
    int i = 0;
    for(Course* Cur = CourseList; Cur; Cur = Cur->pNext) {
        ButtonList->pNext = new Button(134 + PosX, (i + 1) * 5 + PosY, 8, 4, "+");
        if(isEnrollCourse(Cur)) ButtonList->pNext->SetText("-");
        ButtonList = ButtonList->pNext;
        ButtonList->DrawButtonTable();
        i++;
    }
    ButtonList = DumButton->pNext;
    delete DumButton;

    SetBGColor(0);
    gotoXY(PosX, 6);
    SetColor(4);
    cout << "Semester: " << GetSemPath()[3] << "      " << "Year: " << GetPath().substr(0, GetPath().size() - 1);
    gotoXY(PosX, 7);
    SetColor(15);
    cout << "Registration session: ";
    cout << registDate.ngay.day << '/' << registDate.ngay.month << '/' << registDate.ngay.year << " - ";
    cout << registDate.End.day << '/' << registDate.End.month << '/' << registDate.End.year;

    Button QuitButton = Button(134 + PosX + 7, 7, 1, 1, "X");
    QuitButton.DrawButton();
    gotoXY(0, 0);

    SetBGColor(7);
    COORD MousePosition;
    while(1) {
        while(!isLeftMousePressed(MousePosition));

        if(QuitButton.isClick(MousePosition)) {
            OutputCourse(CourseList, "Data/" + GetPath() + GetSemPath() + "Course/" + Class + ".txt");
            return;
        }
        Button* CurButton = ButtonList;
        int i = 0;
        for(Course* CurCourse = CourseList; CurCourse; CurCourse = CurCourse->pNext, CurButton = CurButton->pNext) {
            if(CurButton->isClick(MousePosition)) {
                if(CurButton->GetText() == "+") {
                    if(isEnrollSuccess(CurCourse)) {
                        CurButton->SetText("-");
                    }
                }
                else {
                    if(isRemoveSuccess(CurCourse)) {
                        CurButton->SetText("+");
                    }
                }
                SetBGColor(8);
                CurButton->DrawTextTable();
                gotoXY(PosX + 129, (i + 1) * 5 + PosY + 1);
                SetBGColor(7);
                SetColor(0);
                cout << CurCourse->maxStudent - CurCourse->numStudent << "  ";
                break;
            }
            i++;
        }
        gotoXY(0, 0);
    }
}

/// Task 14, 16
void Student::ViewStudentCourse() {
    SetColor(0);
    int ListLen[7] = {3, 21, 37, 8, 20, 37, 8};
    string ListTitle[7] = {"#", "Course ID", "Course Name", "Credit", "Date", "Teacher", "Remain"};
    int Cur = (GetWidth() - 134) / 2;
    for(int i = 0; i < 7; ++i) {
        if(i % 2 == 0) SetBGColor(7);
        else SetBGColor(8);

        for(int k = 1; k < 4; ++k) {
            for(int u = 0; u < ListLen[i]; ++u) {
                gotoXY(Cur + u, k + 8);
                cout << " ";
            }
        }
        gotoXY(Cur + (ListLen[i] - ListTitle[i].size()) / 2, 10);
        cout << ListTitle[i];
        Cur += ListLen[i];
    }

    for(int i = 0; i < 5; ++i) {
        if(i < numCourses) (&(SubRegis[i]))->ViewCourseTable(1, i + 1, (GetWidth() - 134) / 2, (i + 1) * 5 + 8);
        else {
            Course* DumCourse = new Course;
            DumCourse->ViewCourseTable(0, i + 1, (GetWidth() - 134) / 2, (i + 1) * 5 + 8);
            delete DumCourse;
        }
    }

    Button QuitButton = Button((GetWidth() - 134) / 2 + 133, 7, 1, 1, "X");
    QuitButton.DrawButton();

    gotoXY(0, 0);

    COORD MousePosition;
    while(1) {
        while(!isLeftMousePressed(MousePosition));

        if(QuitButton.isClick(MousePosition)) return;
    }
}

void Student::ViewCourseScore(int Cnt, int PosY, int NumLine) {
    int ListLen[7] = {5, 20, 45, 15, 15, 15, 15};
    int PosX = 0;
    for(int i = 0; i < 7; ++i) PosX += ListLen[i]; PosX = (GetWidth() - PosX) / 2;
    string ListContent[7] = {"", "", "", "", "", "", ""};
    if(Cnt >= 0) {
        stringstream ss;
        ss << Cnt + 1 << ' '; ss >> ListContent[0];
        if(Cnt < numCourses) {
            if(NumLine == 3) {
                ListContent[2] = SubRegis[Cnt].courseName;
                ListContent[1] = SubRegis[Cnt].ID;
            }
            else {
                ListContent[2] = lastName + " " + firstName;
                ListContent[1] = ID;
            }

            ss << scoreBoardSem[Cnt].Midterm << ' ' << scoreBoardSem[Cnt].Other << ' ' << scoreBoardSem[Cnt].Final << ' ' << scoreBoardSem[Cnt].Total << ' ';
            ss >> ListContent[3] >> ListContent[4] >> ListContent[5] >> ListContent[6];
            for(int i = 3; i <= 6; ++i) {
                if(ListContent[i] == "-1") ListContent[i] = "-";
            }
        }
    }
    else {
        ListContent[0] = "#", ListContent[1] = "Course ID", ListContent[2] = "Course name", ListContent[3] = "Midterm";
        ListContent[4] = "Other", ListContent[5] = "Final", ListContent[6] = "Total";
    }
    SetColor(0);
    int CurX = PosX;
    for(int i = 0; i < 7; ++i) {
        if(i % 2 == 0) SetBGColor(7);
        else SetBGColor(8);
        for(int X = CurX; X < CurX + ListLen[i]; ++X) {
            for(int Y = PosY; Y < PosY + NumLine; ++Y) {
                gotoXY(X, Y);
                if(NumLine == 2 && Y == PosY + 1) cout << "_";
                else cout << " ";
            }
        }
        gotoXY(CurX + (ListLen[i] - ListContent[i].size()) / 2, PosY + (NumLine - 1) / 2); cout << ListContent[i];
        CurX += ListLen[i];
    }
}

void Student::LoadScoreboardFromFile(string Directory) {
    ifstream fin(Directory);
    if(fin.is_open()) {
        for(int i = 0; i < 5; ++i) {
            fin >> scoreBoardSem[i].Midterm; fin.get();
            fin >> scoreBoardSem[i].Other; fin.get();
            fin >> scoreBoardSem[i].Final; fin.get();
            fin >> scoreBoardSem[i].Total; fin.get();
            fin.get();
        }
    }
    else {
        for(int i = 0; i < 5; ++i) {
            scoreBoardSem[i].Midterm = -1;
            scoreBoardSem[i].Other = -1;
            scoreBoardSem[i].Final = -1;
            scoreBoardSem[i].Total = -1;
        }
    }
    fin.close();
}

void Student::UpdateScoreboardToFile(string Directory) {
    ofstream fout(Directory);
    for(int i = 0; i < 5; ++i) {
        fout << scoreBoardSem[i].Midterm << ",";
        fout << scoreBoardSem[i].Other << ",";
        fout << scoreBoardSem[i].Final << ",";
        fout << scoreBoardSem[i].Total << ",";
        fout << '\n';
    }
    fout.close();
}

void Student::ViewScoreboard() {
    LoadScoreboardFromFile("Data/" + GetPath() + GetSemPath() + "Student/Score/" + ID + ".txt");
    for(int i=-1; i<5; ++i) {
        ViewCourseScore(i, 13 + 4 * i, 3);
    }
    Button QuitButton = Button((GetWidth() - 130) / 2 + 129, 7, 1, 1, "X");
    QuitButton.DrawButton();
    gotoXY(0, 0);
    COORD MousePosition;
    while(1) {
        while(!isLeftMousePressed(MousePosition));

        if(QuitButton.isClick(MousePosition)) return;
    }
}

void Student::ViewStudent() {
    const int NumInfo = 8, RowSpace = 5, BoxLen = 50, RowLen = BoxLen * 2 + RowSpace * 4;
    int Row = GetHeight() / 2 - 10, RowHeight = ((NumInfo + 1) / 2) * 4 + 5;
    SetBGColor(7);
    for(int i = 0; i < RowLen; ++i) {
        for(int j = 0; j < RowHeight; ++j) {
            gotoXY(i + (GetWidth() - RowLen) / 2, j + Row);
            cout << " ";
        }
    }
    SetBGColor(0);
    for(int i = RowSpace; i < RowLen - RowSpace; ++i) {
        for(int j = 0; j < 2; ++j) {
            gotoXY(i + (GetWidth() - RowLen) / 2, j + Row + 1);
            cout << " ";
        }
    }
    SetColor(15);
    gotoXY(52 + (GetWidth() - RowLen) / 2, Row + 2);
    cout << "STUDENT  PROFILE";
    SetBGColor(8);
    string ListTitle[NumInfo] = {"Student ID", "First name", "Last name", "Class", "Academic year", "Gender", "Date of birth", "Social ID"};
    string ListInfo[NumInfo] = {ID, firstName, lastName, Class, academicYear, gender, DOB.StrDOB, SocialID};
    for(int i = 0; i < NumInfo / 2; ++i) {
        gotoXY((GetWidth() - RowLen) / 2 + RowSpace, Row + 3 + 2 * (2 * i + 1) + 1);
        for(int j = 0; j < BoxLen; ++j) cout << " ";
        gotoXY((GetWidth() - RowLen) / 2 + RowSpace * 3 + BoxLen, Row + 3 + 2 * (2 * i + 1) + 1);
        for(int j = 0; j < BoxLen; ++j) cout << " ";
    }
    SetColor(0);
    for(int i = 0; i < NumInfo / 2; ++i) {
        SetBGColor(7);
        gotoXY((GetWidth() - RowLen) / 2 + RowSpace, Row + 3 + 2 * (2 * i + 1));
        cout << ListTitle[i];
        gotoXY((GetWidth() - RowLen) / 2 + RowSpace * 3 + BoxLen, Row + 3 + 2 * (2 * i + 1));
        cout << ListTitle[i + NumInfo / 2];

        SetBGColor(8);
        gotoXY((GetWidth() - RowLen) / 2 + RowSpace, Row + 3 + 2 * (2 * i + 1) + 1);
        cout << ListInfo[i];
        gotoXY((GetWidth() - RowLen) / 2 + RowSpace * 3 + BoxLen, Row + 3 + 2 * (2 * i + 1) + 1);

        cout << ListInfo[i + NumInfo / 2];
    }
    Button QuitButton = Button(RowLen - 1 + (GetWidth() - RowLen) / 2, Row, 1, 1, "X");
    QuitButton.DrawButton();

    gotoXY(0, 0);

    COORD MousePosition;
    while(1) {
        while(!isLeftMousePressed(MousePosition));

        if(QuitButton.isClick(MousePosition)) return;
    }
}
void drawview(int PosX, int PosY, int BoxWidth, int BoxHeight, string Directory, int TextLen)
{
    ifstream fin(Directory);
    TextColor(4);
    for (int i = 0; i < 7; ++i) {
        gotoXY((GetWidth() - TextLen) / 2, 2 + i);
        string S;
        getline(fin, S);
        for (int j = 0; j < S.size(); ++j) {
            if (S[j] == '*') cout << char(219);
            if (S[j] == ' ') cout << ' ';
        }
        cout << '\n';
    }
    TextColor(7);
    fin.close();
    SetBGColor(8);
    for(int i = PosX; i < PosX + BoxWidth; ++i) {
        for(int j = PosY; j < PosY + BoxHeight; ++j) {
            gotoXY(i, j);
            cout << " ";
        }
    }
    SetBGColor(0);
}

bool Student::StudentFunction(Course*& CourseList) {
    InputCourse(CourseList, "Data/" + GetPath() + GetSemPath() + "Course/" + Class + ".txt");
    LoadCourseFromFile(CourseList);
    int ColSpace = 1;
    int TotButton = 6, BoxWidth = 40, ButtonHeight = 1;
    int BoxHeight = TotButton * ButtonHeight + (TotButton - 1) * ColSpace + 4;
    int ButtonWidth = BoxWidth - 10;
    int PosX = (GetWidth() - BoxWidth) / 2, PosY = 15;
    drawview(PosX, PosY, BoxWidth, BoxHeight, "Data/Student/StudentLogo.txt", 68);
    while(1) {
        Button Button_1 = Button(PosX + 5, PosY + 2, ButtonWidth, ButtonHeight, "PROFILE");
        Button_1.DrawButton();

        Button Button_2 = Button(PosX + 5, PosY + 4, ButtonWidth, ButtonHeight, "LIST COURSES");
        Button_2.DrawButton();

        Button Button_3 = Button(PosX + 5, PosY + 6, ButtonWidth, ButtonHeight, "ENROLL COURSES");
        Button_3.DrawButton();

        Button Button_4 = Button(PosX + 5, PosY + 8, ButtonWidth, ButtonHeight, "SCORE BOARD");
        Button_4.DrawButton();

        Button Button_5 = Button(PosX + 5, PosY + 10, ButtonWidth, ButtonHeight, "CHANGE PASSWORD");
        Button_5.DrawButton();

        Button Button_6 = Button(PosX + 5, PosY + 12, ButtonWidth, ButtonHeight, "LOG OUT");
        Button_6.DrawButton();

        Button QuitButton = Button(PosX + BoxWidth - 1, PosY, 1, 1, "X");
        QuitButton.DrawButton();


        gotoXY(0, 0);

        COORD MousePosition;
        while(!isLeftMousePressed(MousePosition));
        if(Button_1.isClick(MousePosition)) {
            system("cls");
            ViewStudent();
            SetBGColor(0);
            system("cls");
            drawview(PosX, PosY, BoxWidth, BoxHeight, "Data/Student/StudentLogo.txt", 68);
        }
        else if(Button_2.isClick(MousePosition)) {
            system("cls");
            ViewStudentCourse();
            SetBGColor(0);
            system("cls");
            drawview(PosX, PosY, BoxWidth, BoxHeight, "Data/Student/StudentLogo.txt", 68);
        }
        else if(Button_3.isClick(MousePosition)) {
            system("cls");
            EnrollCourse(CourseList);
            SetBGColor(0);
            system("cls");
            drawview(PosX, PosY, BoxWidth, BoxHeight, "Data/Student/StudentLogo.txt", 68);
        }
        else if(Button_4.isClick(MousePosition)) {
            system("cls");
            ViewScoreboard();
            SetBGColor(0);
            system("cls");
            drawview(PosX, PosY, BoxWidth, BoxHeight, "Data/Student/StudentLogo.txt", 68);
        }
        else if (Button_5.isClick(MousePosition)) {
            system("cls");
            bool isChange = DrawChangePasswordWindow(15, UserInfo);
            SetBGColor(0);
            system("cls");
            if(isChange) {
                UpdateCourseToFile();
                return true;
            }
            else drawview(PosX, PosY, BoxWidth, BoxHeight, "Data/Student/StudentLogo.txt", 68);
        }
        else if(Button_6.isClick(MousePosition)) {
            SetBGColor(0);
            system("cls");
            UpdateCourseToFile();
            return true;
        }
        else if(QuitButton.isClick(MousePosition)) {
            SetBGColor(0);
            system("cls");
            UpdateCourseToFile();
            return false;
        }
    }
    return true;
}

void Student::LoadCourseFromFile(Course* CourseList) {
    string Link = "Data/" + GetPath() + GetSemPath() + "Student/Course/" + ID + ".txt";
    ifstream fin(Link);
    if (!fin.is_open()) {
        fin.close();
        return;
    }
    string CourseID;
    while (!fin.eof()) {
        getline(fin, CourseID);
        Course* CourseInfo = FindCourse(CourseList, CourseID);
        if (CourseInfo) isEnrollSuccess(CourseInfo);
    }
    fin.close();
}

void Student::UpdateCourseToFile() {
    string Link = "Data/" + GetPath() + GetSemPath() + "Student/Course/" + ID + ".txt";
    ofstream fout(Link);
    for(int i = 0; i < numCourses; ++i)
    {
        fout << SubRegis[i].ID << '\n';
    }
    fout.close();
}

float Student::GPASem() {
    if(numCourses==0) return 0;

    float semScore=0;
    for(int i=0; i<numCourses; ++i)
        semScore+=scoreBoardSem[i].Total*SubRegis[i].numCredits;

    return 1.0*semScore/numCredits;
}

float Student::GPAAll() {
    if(numCredits+prevCredits<=0) return 0;

    float totalScore=prevGPA*prevCredits;
    totalScore+=GPASem()*numCredits;
    totalScore/=(numCredits+prevCredits);

    return totalScore;
}

void Student::ViewInfo(int Cnt, int PosX, int PosY) {
    int ListLen[6] = {5, 20, 45, 8, 21, 25};
    for(int i = 0; i < 6; ++i) {
        if(i % 2 == 0) SetBGColor(7);
        else SetBGColor(8);

        for(int k = 0; k < 2; ++k) {
            for(int u = 0; u < ListLen[i]; ++u) {
                gotoXY(PosX + u, k + PosY);
                if(k == 0) cout << " ";
                else cout << "_";
            }
        }
        switch(i) {
        case 0:
            gotoXY(PosX + 1, PosY);
            cout << Cnt;
            break;
        case 1:
            gotoXY(PosX + (ListLen[i] - ID.size()) / 2, PosY);
            cout << ID;
            break;
        case 2:
            gotoXY(PosX + (ListLen[i] - (lastName.size() + firstName.size() + 1)) / 2, PosY);
            cout << lastName << " " << firstName;
            break;
        case 3:
            gotoXY(PosX + (ListLen[i] - gender.size()) / 2, PosY);
            cout << gender;
            break;
        case 4:
            gotoXY(PosX + (ListLen[i] - DOB.StrDOB.size()) / 2, PosY);
            cout << DOB.StrDOB;
            break;
        case 5:
            gotoXY(PosX + (ListLen[i] - Class.size()) / 2, PosY);
            cout << Class;
            break;
        default:
            break;
        }

        PosX += ListLen[i];
    }
    SetBGColor(0);
}

bool Student::FixInfo() {
    bool Ok = false;
    SetBGColor(0);
    SetColor(0);
    int BoxWidth = 60, BoxHeight = 20, PosX = (GetWidth() - BoxWidth) / 2, PosY = (GetHeight() - BoxHeight) / 2 - 2;
    for(int i = PosX; i < PosX + BoxWidth; ++i) {
        for(int j = PosY; j < PosY + BoxHeight; ++j) {
            gotoXY(i, j);
            if(PosX + 5 <= i && i < PosX + BoxWidth - 5 && PosY + 2 <= j && j < PosY + BoxHeight - 3) {
                if(j < PosY + 4) SetBGColor(0);
                else SetBGColor(8);
                cout << ' ';
            }
            else {
                SetBGColor(15);
                cout << char(177);
            }
        }

    }
    string tID = ID, tClass = Class, tFirst = firstName, tLast = lastName, tGender = gender;
    string tDay, tMonth, tYear;
    stringstream ss; ss << DOB.day << ' ' << DOB.month << ' ' << DOB.year; ss >> tDay >> tMonth >> tYear;
    SetColor(0);
    SetBGColor(8);
    SetColor(0);
    gotoXY(PosX + 7, PosY + 5); cout << "Student ID";
    SetBGColor(7);
    gotoXY(PosX + 7, PosY + 6); for(int i = 0; i < 20; ++i) cout << " ";
    gotoXY(PosX + 7, PosY + 6); cout << ID;

    SetBGColor(8);
    gotoXY(PosX + 33, PosY + 5); cout << "Class";
    SetBGColor(7);
    gotoXY(PosX + 33, PosY + 6); for(int i = 0; i < 20; ++i) cout << " ";
    gotoXY(PosX + 33, PosY + 6); cout << Class;

    SetBGColor(8);
    gotoXY(PosX + 7, PosY + 8); cout << "First name";
    SetBGColor(7);
    gotoXY(PosX + 7, PosY + 9); for(int i = 0; i < 46; ++i) cout << " ";
    gotoXY(PosX + 7, PosY + 9); cout << firstName;

    SetBGColor(8);
    gotoXY(PosX + 7, PosY + 11); cout << "Last name";
    SetBGColor(7);
    gotoXY(PosX + 7, PosY + 12); for(int i = 0; i < 46; ++i) cout << " ";
    gotoXY(PosX + 7, PosY + 12); cout << lastName;

    SetBGColor(8);
    gotoXY(PosX + 7, PosY + 14); cout << "Date of birth";
    SetColor(0);
    gotoXY(PosX + 7, PosY + 15);
    SetBGColor(7); cout << "   ";
    SetBGColor(8); cout << " / ";
    SetBGColor(7); cout << "   ";
    SetBGColor(8); cout << " / ";
    SetBGColor(7); cout << "      ";
    gotoXY(PosX + 7, PosY + 15); cout << tDay;
    gotoXY(PosX + 13, PosY + 15); cout << tMonth;
    gotoXY(PosX + 19, PosY + 15); cout << tYear;

    SetBGColor(8);
    gotoXY(PosX + 33, PosY + 14); cout << "Gender";
    gotoXY(PosX + 33, PosY + 15);
    if(gender == "Male") SetBGColor(4);
    else SetBGColor(7);
    cout << "Male";
    SetBGColor(8); cout << " ";
    if(gender == "Female") SetBGColor(4);
    else SetBGColor(7);
    cout << "Female";

    SetBGColor(8);
    gotoXY(PosX + 22, PosY + BoxHeight - 2);
    cout << "SAVE";
    Button Button_Save = Button(PosX + 22, PosY + BoxHeight - 2, 4, 1, "");
    gotoXY(PosX + 36, PosY + BoxHeight - 2);
    cout << "BACK";
    Button Button_Back = Button(PosX + 36, PosY + BoxHeight - 2, 4, 1, "");

    Button Button_ID = Button(PosX + 7, PosY + 6, 20, 1, "");
    Button Button_FirstName = Button(PosX + 7, PosY + 9, 46, 1, "");
    Button Button_LastName = Button(PosX + 7, PosY + 12, 46, 1, "");
    Button Button_Day = Button(PosX + 7, PosY + 15, 3, 1, "");
    Button Button_Month = Button(PosX + 13, PosY + 15, 3, 1, "");
    Button Button_Year = Button(PosX + 19, PosY + 15, 6, 1, "");
    Button Button_Male = Button(PosX + 33, PosY + 15, 4, 1, "");
    Button Button_Female = Button(PosX + 38, PosY + 15, 6, 1, "");

    int Click = -1;
    while(1) {
        SetBGColor(7);
        gotoXY(0, 0);
        COORD MousePosition;
        while(!isLeftMousePressed(MousePosition));

        if(Button_ID.isClick(MousePosition)) {
            gotoXY(PosX + 7 + tID.size(), PosY + 6);
            GetUserName(tID, 19);
        }
        else if(Button_FirstName.isClick(MousePosition)) {
            gotoXY(PosX + 7 + tFirst.size(), PosY + 9);
            GetUserName(tFirst, 45);
        }
        else if(Button_LastName.isClick(MousePosition)) {
            gotoXY(PosX + 7 + tLast.size(), PosY + 12);
            GetUserName(tLast, 45);
        }
        else if(Button_Day.isClick(MousePosition)) {
            gotoXY(PosX + 7 + tDay.size(), PosY + 15);
            GetUserName(tDay, 2);
        }
        else if(Button_Month.isClick(MousePosition)) {
            gotoXY(PosX + 13 + tMonth.size(), PosY + 15);
            GetUserName(tMonth, 2);
        }
        else if(Button_Year.isClick(MousePosition)) {
            gotoXY(PosX + 19 + tYear.size(), PosY + 15);
            GetUserName(tYear, 5);
        }
        else if(Button_Male.isClick(MousePosition)) {
            tGender = "Male";
            gotoXY(PosX + 33, PosY + 15);
            SetBGColor(4);
            cout << "Male";
            SetBGColor(8); cout << " ";
            SetBGColor(7);
            cout << "Female";
        }
        else if(Button_Female.isClick(MousePosition)) {
            tGender = "Female";
            gotoXY(PosX + 33, PosY + 15);
            SetBGColor(7);
            cout << "Male";
            SetBGColor(8); cout << " ";
            SetBGColor(4);
            cout << "Female";
        }
        else if(Button_Back.isClick(MousePosition)) {
            Ok = false;
            break;
        }
        else if(Button_Save.isClick(MousePosition)) {
            this->ID = tID; this->Class = tClass; this->firstName = tFirst; this->lastName = tLast; this->gender = tGender;
            stringstream sx; sx << tDay << ' ' << tMonth << ' ' << tYear << ' ';
            sx >> this->DOB.day >> this->DOB.month >> this->DOB.year;
            this->DOB.StrDOB = tDay + "/" + tMonth + "/" + tYear;
            Ok = true;
            break;
        }
    }
    SetBGColor(0);
    for(int i = PosX; i < PosX + BoxWidth; ++i) {
        for(int j = PosY; j < PosY + BoxHeight; ++j) {
            gotoXY(i, j);
            cout << " ";
        }
    }
    return Ok;
}

void UpdateStudentToFile(Student* StudentList) {
    ofstream fout("Data/Student/StudentData.csv");
    fout << "Student ID,Password,Last name,First name,Class,Gender,Date of birth,Academic year,Social ID,Total GPA,Total credits\n";
    for(Student* CurStudent = StudentList; CurStudent; CurStudent = CurStudent->pNext) {
        fout << CurStudent->ID << "," << CurStudent->passWord << "," << CurStudent->lastName << "," << CurStudent->firstName << ",";
        fout << CurStudent->Class << "," << CurStudent->gender << "," << CurStudent->DOB.StrDOB << "," << CurStudent->academicYear << "," << CurStudent->SocialID << "," << CurStudent->prevGPA << "," << CurStudent->prevCredits << '\n';
    }
    fout.close();
}

void Student::FixScoreboard(Course* CourseList) {
    LoadCourseFromFile(CourseList);
    LoadScoreboardFromFile("Data/" + GetPath() + GetSemPath() + "Student/Score/" + ID + ".txt");
    for(int i=-1; i<5; ++i) {
        ViewCourseScore(i, 13 + 4 * i, 3);
    }
    int ListLen[7] = {5, 20, 45, 15, 15, 15, 15};
    int PosX = 0;
    for(int i = 0; i < 7; ++i) PosX += ListLen[i]; PosX = (GetWidth() - PosX) / 2;
    Button Button_Mid[5], Button_Oth[5], Button_Fin[5], Button_Tot[5];
    string sMid[5], sOth[5], sFin[5], sTot[5];
    for(int i = 0; i < numCourses; ++i) {
        Button_Mid[i] = Button(PosX + 70, 13 + 4 * i, 15, 3, "");
        Button_Oth[i] = Button(PosX + 70 + 15, 13 + 4 * i, 15, 3, "");
        Button_Fin[i] = Button(PosX + 70 + 30, 13 + 4 * i, 15, 3, "");
        Button_Tot[i] = Button(PosX + 70 + 45, 13 + 4 * i, 15, 3, "");
        stringstream ss;
        ss << scoreBoardSem[i].Midterm << ' ' << scoreBoardSem[i].Other << ' ' << scoreBoardSem[i].Final << ' ' << scoreBoardSem[i].Total << ' ';
        ss >> sMid[i] >> sOth[i] >> sFin[i] >> sTot[i];
        if(sMid[i] == "-1") sMid[i] = "-";
        if(sOth[i] == "-1") sOth[i] = "-";
        if(sFin[i] == "-1") sFin[i] = "-";
        if(sTot[i] == "-1") sTot[i] = "-";
    }

    Button QuitButton = Button((GetWidth() - 130) / 2 + 129, 7, 1, 1, "X");
    QuitButton.DrawButton();

    COORD MousePosition;
    while(1) {
        gotoXY(0, 0);
        while(!isLeftMousePressed(MousePosition));

        if(QuitButton.isClick(MousePosition)) break;
        for(int i = 0; i < numCourses; ++i) {
            if(Button_Mid[i].isClick(MousePosition)) {
                SetColor(0);
                SetBGColor(8);
                gotoXY(PosX + 74, 14 + 4 * i);
                for(int j = 0; j < 7; ++j) cout << " ";
                gotoXY(PosX + 74, 14 + 4 * i); cout << sMid[i];
                GetUserName(sMid[i], 7);
                gotoXY(PosX + 74, 14 + 4 * i);
                for(int j = 0; j < 7; ++j) cout << " ";
                gotoXY(PosX + 70 + (15 - sMid[i].size()) / 2, 14 + 4 * i); cout << sMid[i];
            }
            else if(Button_Oth[i].isClick(MousePosition)) {
                SetColor(0);
                SetBGColor(7);
                gotoXY(PosX + 74 + 15, 14 + 4 * i);
                for(int j = 0; j < 7; ++j) cout << " ";
                gotoXY(PosX + 74 + 15, 14 + 4 * i); cout << sOth[i];
                GetUserName(sOth[i], 7);
                gotoXY(PosX + 74 + 15, 14 + 4 * i);
                for(int j = 0; j < 7; ++j) cout << " ";
                gotoXY(PosX + 70 + 15 + (15 - sOth[i].size()) / 2, 14 + 4 * i); cout << sOth[i];
            }
            else if(Button_Fin[i].isClick(MousePosition)) {
                SetColor(0);
                SetBGColor(8);
                gotoXY(PosX + 74 + 30, 14 + 4 * i);
                for(int j = 0; j < 7; ++j) cout << " ";
                gotoXY(PosX + 74 + 30, 14 + 4 * i); cout << sFin[i];
                GetUserName(sFin[i], 7);
                gotoXY(PosX + 74 + 30, 14 + 4 * i);
                for(int j = 0; j < 7; ++j) cout << " ";
                gotoXY(PosX + 70 + 30 + (15 - sFin[i].size()) / 2, 14 + 4 * i); cout << sFin[i];
            }
            else if(Button_Tot[i].isClick(MousePosition)) {
                SetColor(0);
                SetBGColor(7);
                gotoXY(PosX + 74 + 45, 14 + 4 * i);
                for(int j = 0; j < 7; ++j) cout << " ";
                gotoXY(PosX + 74 + 45, 14 + 4 * i); cout << sTot[i];
                GetUserName(sTot[i], 7);
                gotoXY(PosX + 74 + 45, 14 + 4 * i);
                for(int j = 0; j < 7; ++j) cout << " ";
                gotoXY(PosX + 70 + 45 + (15 - sTot[i].size()) / 2, 14 + 4 * i); cout << sTot[i];
            }
        }
    }
    for(int i = 0; i < 5; ++i) {
        stringstream ss;
        if(sMid[i] == "-") scoreBoardSem[i].Midterm = -1;
        else {
            ss << sMid[i] << ' ';
            ss >> scoreBoardSem[i].Midterm;
        }
        if(sOth[i] == "-") scoreBoardSem[i].Other = -1;
        else {
            ss << sOth[i] << ' ';
            ss >> scoreBoardSem[i].Other;
        }
        if(sFin[i] == "-") scoreBoardSem[i].Final = -1;
        else {
            ss << sFin[i] << ' ';
            ss >> scoreBoardSem[i].Final;
        }
        if(sTot[i] == "-") scoreBoardSem[i].Total = -1;
        else {
            ss << sTot[i] << ' ';
            ss >> scoreBoardSem[i].Total;
        }
    }
    UpdateScoreboardToFile("Data/" + GetPath() + GetSemPath() + "Student/Score/" + ID + ".txt");
}

void DeleteStudentFromList(Student*& StudentList, User*& UserList, string StudentID) {
    Student* DumStudent = new Student;
    DumStudent->pNext = StudentList;
    for(Student* Cur = DumStudent; Cur && Cur->pNext; Cur = Cur->pNext) {
        if(Cur->pNext->ID == StudentID) {
            Student* DelStudent = Cur->pNext;
            Cur->pNext = DelStudent->pNext;
            delete DelStudent;
            break;
        }
    }
    StudentList = DumStudent->pNext;
    delete DumStudent;
    User* DumUser = new User;
    DumUser->pNext = UserList;
    for(User* Cur = DumUser; Cur && Cur->pNext; Cur = Cur->pNext) {
        if(Cur->pNext->getMode() == 1 && Cur->pNext->getUserName() == StudentID) {
            User* DelUser = Cur->pNext;
            Cur->pNext = DelUser->pNext;
            delete DelUser;
            break;
        }
    }
    UserList = DumUser->pNext;
    delete DumUser;
}

void AddStudentToList(Student*& StudentList, User*& UserList, Student*& StudentInfo) {
    Student* DumStudent = new Student;
    DumStudent->pNext = StudentList;
    User* DumUser = new User;
    DumUser->pNext = UserList;
    Student* Cur;
    for(Cur = DumStudent; Cur && Cur->pNext; Cur = Cur->pNext) {
    }
    User* CurUser = DumUser;
    while(CurUser) {
        if(CurUser->pNext) CurUser = CurUser->pNext;
        else break;
    }
    CurUser->pNext = new User;
    CurUser = CurUser->pNext;
    CurUser->setUserName(StudentInfo->ID);
    CurUser->setMode(1);
    UserList = DumUser->pNext;
    delete DumUser;

    Cur->pNext = StudentInfo;
    StudentInfo->pNext = nullptr;
    StudentList = DumStudent->pNext;
    delete DumStudent;
}

void LoadCourseScore(Course* CourseInfo, Student* StudentList) {
    int ColSpace = 1;
    int TotButton = 3, BoxWidth = 40, ButtonHeight = 1;
    int BoxHeight = TotButton * ButtonHeight + (TotButton - 1) * ColSpace + 5;
    int ButtonWidth = BoxWidth - 10;
    int PosX = (GetWidth() - BoxWidth) / 2, PosY = 15;

    SetBGColor(8);
    for(int i = PosX; i < PosX + BoxWidth; ++i) {
        for(int j = PosY; j < PosY + BoxHeight; ++j) {
            gotoXY(i, j);
            cout << " ";
        }
    }
    SetBGColor(0);
    gotoXY(PosX + 5, PosY + 2); SetBGColor(8); SetColor(0); cout << "Directory: ";
    gotoXY(PosX + 5, PosY + 3); SetBGColor(15); for(int i = 0; i < ButtonWidth; ++i) cout << " ";
    Button Button_1 = Button(PosX + 5, PosY + 3, ButtonWidth, ButtonHeight, "");

    Button Button_2 = Button(PosX + 5, PosY + 5, ButtonWidth, ButtonHeight, "LOAD");
    Button_2.DrawButton();

    Button Button_3 = Button(PosX + 5, PosY + 7, ButtonWidth, ButtonHeight, "BACK");
    Button_3.DrawButton();
    string Dir = "";
    while(1) {
        gotoXY(0, 0);

        COORD MousePosition;
        while(!isLeftMousePressed(MousePosition));
        if(Button_1.isClick(MousePosition)) {
            gotoXY(PosX + 5 + Dir.size(), PosY + 3);
            SetBGColor(15);
            SetColor(0);
            GetUserName(Dir, ButtonWidth - 1);
        }
        else if(Button_2.isClick(MousePosition)) {
            ifstream fin(Dir);
            if(fin.is_open()) {
                string sID;
                int Mid, Oth, Fin, Tot;
                while(!fin.eof() && getline(fin, sID, ',')) {
                    Student* StudentInfo = FindStudent(StudentList, sID);
                    fin >> Mid; fin.get();
                    fin >> Oth; fin.get();
                    fin >> Fin; fin.get();
                    fin >> Tot; fin.get();
                    fin.get();
                    if(StudentInfo && StudentInfo->isEnrollCourse(CourseInfo)) {
                        int i = StudentInfo->GetCourseID(CourseInfo);
                        StudentInfo->scoreBoardSem[i].Midterm = Mid;
                        StudentInfo->scoreBoardSem[i].Other = Oth;
                        StudentInfo->scoreBoardSem[i].Final = Fin;
                        StudentInfo->scoreBoardSem[i].Total = Tot;
                        StudentInfo->UpdateScoreboardToFile("Data/" + GetPath() + GetSemPath() + "Student/Score/" + StudentInfo->ID + ".txt");
                    }
                }
                gotoXY(PosX + 5, PosY + BoxHeight - 1);
                SetBGColor(8);
                SetColor(0);
                cout << "Update success!    ";
            }
            else {
                gotoXY(PosX + 5, PosY + BoxHeight - 1);
                SetBGColor(8);
                SetColor(0);
                cout << "Invalid directory!";
            }
            fin.close();
        }
        else if(Button_3.isClick(MousePosition)) {
            SetBGColor(0);
            system("cls");
            return;
        }
    }
}
