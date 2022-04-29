#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE
#include "StaffFunction.h"
#include "StudentFunction.h"

void InputStaff(Staff*& StaffList, User*& UserList) {
    ifstream fin("Data/Staff/StaffData.txt");
    if(!fin.is_open()) {
        fin.close();
        return;
    }
    Staff* DumStaff = new Staff;
    User* DumUser = new User;
    DumStaff->pNext = nullptr;
    DumUser->pNext = nullptr;
    StaffList = DumStaff;
    User* CurUser = DumUser;
    string strID;
    while(!fin.eof() && getline(fin, strID, ',')) {
        StaffList->pNext = new Staff;
        StaffList = StaffList->pNext;
        CurUser->pNext = new User;
        CurUser = CurUser->pNext;

        StaffList->ID = strID;

        getline(fin, StaffList->passWord, ',');

        getline(fin, StaffList->lastName, ',');

        getline(fin, StaffList->firstName, ',');

        getline(fin, StaffList->SocialID, ',');

        getline(fin, StaffList->gender, ',');

        string StrDOB;
        getline(fin, StrDOB, ',');
        StaffList->DOB = Date(StrDOB);

        fin.get();

        StaffList->userName = StaffList->ID;

        CurUser->setFullName(StaffList->firstName, StaffList->lastName);
        CurUser->setGender(StaffList->gender);
        CurUser->setUserName(StaffList->ID);
        CurUser->setPassWord(StaffList->passWord);
        CurUser->setMode(0);
    }
    StaffList = DumStaff->pNext;
    CurUser->pNext = UserList;
    UserList = DumUser->pNext;
    delete DumStaff;
    delete DumUser;
    fin.close();
}

Staff* FindStaff(Staff* StaffList, string StaffID) {
    for(Staff* Cur = StaffList; Cur; Cur = Cur->pNext) {
        if(Cur->ID == StaffID) {
            return Cur;
        }
    }
    return nullptr;
}

NodeClass* Staff::findClass(NodeClass* ListClass)
{
    string inputClassName;
    cout << "Input class name: ";
    getline(cin, inputClassName);
    NodeClass* currentClass = ListClass;
    while (currentClass)
    {
        if (currentClass->className == inputClassName)
        {
            return currentClass;
        }
    }

    return nullptr;
}
void displayStudentListtoViewScore(NodeClass* ListClass, Staff currentStaff)
{
    if (!currentStaff.findClass(ListClass)) return;
    int pos = 1;
    Student* currentStudent = ListClass->listStudents;
    if (!currentStudent) return;
    cout << "List of students in " << currentStaff.findClass(ListClass)->className << ":" << endl;
    while (currentStudent)
    {
        cout << pos << "/ " << currentStudent->getID() << "\t";
        cout << currentStudent->fullName() << endl;
        currentStudent = currentStudent->pNext;
    }

}

void CreateYear(ListYear*& YearList) {
    int ColSpace = 1;
    int TotButton = 3, BoxWidth = 40, ButtonHeight = 1;
    int BoxHeight = TotButton * ButtonHeight + (TotButton - 1) * ColSpace + 5;
    int ButtonWidth = BoxWidth - 10;
    int PosX = (GetWidth() - BoxWidth) / 2, PosY = 15;
    drawview(PosX, PosY, BoxWidth, BoxHeight, "Data/Staff/StaffLogo.txt", 56);
    gotoXY(PosX + 5, PosY + 2); SetBGColor(8); SetColor(0); cout << "School year";
    gotoXY(PosX + 5, PosY + 3); SetBGColor(15); for(int i = 0; i < ButtonWidth; ++i) cout << " ";
    Button Button_1 = Button(PosX + 5, PosY + 3, ButtonWidth, ButtonHeight, "");

    Button Button_2 = Button(PosX + 5, PosY + 5, ButtonWidth, ButtonHeight, "SAVE");
    Button_2.DrawButton();

    Button Button_3 = Button(PosX + 5, PosY + 7, ButtonWidth, ButtonHeight, "BACK");
    Button_3.DrawButton();
    string year_name = "";
    while(1) {
        gotoXY(0, 0);

        COORD MousePosition;
        while(!isLeftMousePressed(MousePosition));
        if(Button_1.isClick(MousePosition)) {
            gotoXY(PosX + 5 + year_name.size(), PosY + 3);
            SetBGColor(15);
            SetColor(0);
            GetUserName(year_name, ButtonWidth - 1);
        }
        else if(Button_2.isClick(MousePosition)) {
            if(YearList->pHead) {
                YearList->pTail->pNext=new NodeYear();
                YearList->pTail=YearList->pTail->pNext;
            }
            else YearList->pHead=YearList->pTail=new NodeYear();
            YearList->pTail->year_name=year_name;
            _mkdir(("Data/" + year_name).c_str());
            _mkdir(("Data/" + year_name + "/Class").c_str());
            _mkdir(("Data/" + year_name + "/Student").c_str());
            _mkdir(("Data/" + year_name + "/Sem1").c_str());
            _mkdir(("Data/" + year_name + "/Sem1/Course").c_str());
            _mkdir(("Data/" + year_name + "/Sem1/Student").c_str());
            _mkdir(("Data/" + year_name + "/Sem1/Student/Score").c_str());
            _mkdir(("Data/" + year_name + "/Sem1/Student/Course").c_str());

            _mkdir(("Data/" + year_name + "/Sem2").c_str());
            _mkdir(("Data/" + year_name + "/Sem2/Course").c_str());
            _mkdir(("Data/" + year_name + "/Sem2/Student").c_str());
            _mkdir(("Data/" + year_name + "/Sem2/Student/Score").c_str());
            _mkdir(("Data/" + year_name + "/Sem2/Student/Course").c_str());

            _mkdir(("Data/" + year_name + "/Sem3").c_str());
            _mkdir(("Data/" + year_name + "/Sem3/Course").c_str());
            _mkdir(("Data/" + year_name + "/Sem3/Student").c_str());
            _mkdir(("Data/" + year_name + "/Sem3/Student/Score").c_str());
            _mkdir(("Data/" + year_name + "/Sem3/Student/Course").c_str());
            ofstream fout("Data/Link/YearPath.txt");
            fout << year_name << "/";
            fout.close();
            SetBGColor(0);
            system("cls");
            return;
        }
        else if(Button_3.isClick(MousePosition)) {
            SetBGColor(0);
            system("cls");
            return;
        }
    }
}

void FixYear(ListYear*& YearList) {
    int ColSpace = 1;
    int TotButton = 3, BoxWidth = 40, ButtonHeight = 1;
    int BoxHeight = TotButton * ButtonHeight + (TotButton - 1) * ColSpace + 5;
    int ButtonWidth = BoxWidth - 10;
    int PosX = (GetWidth() - BoxWidth) / 2, PosY = 15;
    drawview(PosX, PosY, BoxWidth, BoxHeight, "Data/Staff/StaffLogo.txt", 56);
    gotoXY(PosX + 5, PosY + 2); SetBGColor(8); SetColor(0); cout << "School year";
    gotoXY(PosX + 5, PosY + 3); SetBGColor(15); for(int i = 0; i < ButtonWidth; ++i) cout << " ";
    gotoXY(PosX + 5, PosY + 3); SetColor(0); cout << YearList->pTail->year_name;
    Button Button_1 = Button(PosX + 5, PosY + 3, ButtonWidth, ButtonHeight, "");

    Button Button_2 = Button(PosX + 5, PosY + 5, ButtonWidth, ButtonHeight, "SAVE");
    Button_2.DrawButton();

    Button Button_3 = Button(PosX + 5, PosY + 7, ButtonWidth, ButtonHeight, "BACK");
    Button_3.DrawButton();
    string year_name = YearList->pTail->year_name;
    while(1) {
        gotoXY(0, 0);
        COORD MousePosition;
        while(!isLeftMousePressed(MousePosition));
        if(Button_1.isClick(MousePosition)) {
            gotoXY(PosX + 5 + year_name.size(), PosY + 3);
            SetBGColor(15);
            SetColor(0);
            GetUserName(year_name, ButtonWidth - 1);
        }
        else if(Button_2.isClick(MousePosition)) {
            rename(("Data/" + YearList->pTail->year_name).c_str(), ("Data/" + year_name).c_str());
            YearList->pTail->year_name=year_name;
            ofstream fout("Data/Link/YearPath.txt");
            fout << year_name << "/";
            fout.close();
            SetBGColor(0);
            system("cls");
            return;
        }
        else if(Button_3.isClick(MousePosition)) {
            SetBGColor(0);
            system("cls");
            return;
        }
    }
}

bool ImportFile(string DirIn, string DirOut) {
    ifstream fin(DirIn);

    bool isSuccess = false;

    if(fin.is_open()) {
        ofstream fout(DirOut);
        isSuccess = true;
        string s;
        while(getline(fin, s)) {
            fout << s << '\n';
        }
        fout.close();
    }
    fin.close();
    return isSuccess;
}

void ImportData(ListYear* YearList) {
    if(!YearList->pTail) {
        gotoXY(GetWidth() / 2 - 14, GetHeight() / 2 - 1);
        cout << "Please set school year first!";
        gotoXY(GetWidth() / 2 - 14, GetHeight() / 2 + 1);
        system("pause");
        return;
    }
    int ColSpace = 1;
    int TotButton = 2, BoxWidth = 40, ButtonHeight = 1;
    int BoxHeight = TotButton * ButtonHeight + (TotButton - 1) * ColSpace + 13;
    int ButtonWidth = BoxWidth - 10;
    int PosX = (GetWidth() - BoxWidth) / 2, PosY = 15;
    drawview(PosX, PosY, BoxWidth, BoxHeight, "Data/Staff/StaffLogo.txt", 56);

    SetBGColor(8); SetColor(0);
    gotoXY(PosX + 5, PosY + 2); cout << "Class directory";
    gotoXY(PosX + 5, PosY + 5); cout << "Student directory";
    gotoXY(PosX + 5, PosY + 8); cout << "Course directory";

    SetBGColor(15);
    gotoXY(PosX + 5, PosY + 3); for(int i = 0; i < ButtonWidth; ++i) cout << " ";
    gotoXY(PosX + 5, PosY + 6); for(int i = 0; i < ButtonWidth; ++i) cout << " ";
    gotoXY(PosX + 5, PosY + 9); for(int i = 0; i < ButtonWidth; ++i) cout << " ";

    Button Button_Class = Button(PosX + 5, PosY + 3, ButtonWidth, 1, "");
    Button Button_Student = Button(PosX + 5, PosY + 6, ButtonWidth, 1, "");
    Button Button_Course = Button(PosX + 5, PosY + 9, ButtonWidth, 1, "");

    Button Button_1 = Button(PosX + 5, PosY + 11, ButtonWidth, ButtonHeight, "IMPORT");
    Button_1.DrawButton();

    Button Button_2 = Button(PosX + 5, PosY + 13, ButtonWidth, ButtonHeight, "BACK");
    Button_2.DrawButton();
    string sClass = "", sStudent = "", sCourse = "";
    SetBGColor(15);
    SetColor(0);
    while(1) {
        gotoXY(0, 0);
        COORD MousePosition;
        while(!isLeftMousePressed(MousePosition));
        if(Button_1.isClick(MousePosition)) {
            SetBGColor(0);
            SetColor(15);
            system("cls");
            if(ImportFile(sClass, "Data/" + YearList->pTail->year_name + "/Class/ClassData.txt")) {
                cout << "Import class data success!\n\n";
            }
            else cout << "Import class data fail!\n\n";
            if(ImportFile(sStudent, "Data/" + YearList->pTail->year_name + "/Student/StudentData.txt")) {
                cout << "Import student data success!\n\n";
            }
            else cout << "Import student data fail!\n\n";
            if(ImportFile(sCourse, "Data/" + YearList->pTail->year_name +  "/" + GetSemPath() + "/Course/CourseData.txt")) {
                cout << "Import course data success!\n\n";
            }
            else cout << "Import course data fail!\n\n";
            system("pause");
            SetBGColor(0);
            system("cls");
            return;
        }
        else if(Button_2.isClick(MousePosition)) {
            SetBGColor(0);
            system("cls");
            return;
        }
        else if(Button_Class.isClick(MousePosition)) {
            gotoXY(PosX + 5 + sClass.size(), PosY + 3);
            GetUserName(sClass, ButtonWidth - 1);
        }
        else if(Button_Student.isClick(MousePosition)) {
            gotoXY(PosX + 5 + sStudent.size(), PosY + 6);
            GetUserName(sStudent, ButtonWidth - 1);
        }
        else if(Button_Course.isClick(MousePosition)) {
            gotoXY(PosX + 5 + sCourse.size(), PosY + 9);
            GetUserName(sCourse, ButtonWidth - 1);
        }
    }
}

void SetYearOption(ListYear*& YearList) {
    if(!YearList) YearList = new ListYear;
    int ColSpace = 1;
    int TotButton = 4, BoxWidth = 40, ButtonHeight = 1;
    int BoxHeight = TotButton * ButtonHeight + (TotButton - 1) * ColSpace + 6;
    int ButtonWidth = BoxWidth - 10;
    int PosX = (GetWidth() - BoxWidth) / 2, PosY = 15;
    drawview(PosX, PosY, BoxWidth, BoxHeight, "Data/Staff/StaffLogo.txt", 56);
    gotoXY(PosX + 5, PosY + 2); SetBGColor(8); SetColor(0); cout << "School year: ";
    if(YearList->pTail) cout << YearList->pTail->year_name;
    else cout << "no data";

    Button Button_1 = Button(PosX + 5, PosY + 4, ButtonWidth, ButtonHeight, "SET NEW SCHOOL YEAR");
    Button_1.DrawButton();

    Button Button_2 = Button(PosX + 5, PosY + 6, ButtonWidth, ButtonHeight, "FIX CURRENT SCHOOL YEAR");
    Button_2.DrawButton();

    Button Button_3 = Button(PosX + 5, PosY + 8, ButtonWidth, ButtonHeight, "IMPORT DATA");
    Button_3.DrawButton();

    Button Button_4 = Button(PosX + 5, PosY + 10, ButtonWidth, ButtonHeight, "BACK");
    Button_4.DrawButton();
    while(1) {
        gotoXY(0, 0);
        COORD MousePosition;
        while(!isLeftMousePressed(MousePosition));
        if(Button_1.isClick(MousePosition)) {
            system("cls");
            CreateYear(YearList);
            SetBGColor(0);
            system("cls");
            drawview(PosX, PosY, BoxWidth, BoxHeight, "Data/Staff/StaffLogo.txt", 56);
            gotoXY(PosX + 5, PosY + 2); SetBGColor(8); SetColor(0); cout << "School year: ";
            if(YearList->pTail) cout << YearList->pTail->year_name;
            else cout << "no data";
            Button_1.DrawButton();
            Button_2.DrawButton();
            Button_3.DrawButton();
            Button_4.DrawButton();
        }
        else if(Button_2.isClick(MousePosition)) {
            if(YearList->pTail) {
                system("cls");
                FixYear(YearList);
                SetBGColor(0);
                system("cls");
                drawview(PosX, PosY, BoxWidth, BoxHeight, "Data/Staff/StaffLogo.txt", 56);
                gotoXY(PosX + 5, PosY + 2); SetBGColor(8); SetColor(0); cout << "School year: ";
                if(YearList->pTail) cout << YearList->pTail->year_name;
                else cout << "no data";
                Button_1.DrawButton();
                Button_2.DrawButton();
                Button_3.DrawButton();
                Button_4.DrawButton();
            }
        }
        else if(Button_3.isClick(MousePosition)) {
            system("cls");
            ImportData(YearList);
            SetBGColor(0);
            system("cls");
            drawview(PosX, PosY, BoxWidth, BoxHeight, "Data/Staff/StaffLogo.txt", 56);
            gotoXY(PosX + 5, PosY + 2); SetBGColor(8); SetColor(0); cout << "School year: ";
            if(YearList->pTail) cout << YearList->pTail->year_name;
            else cout << "no data";
            Button_1.DrawButton();
            Button_2.DrawButton();
            Button_3.DrawButton();
            Button_4.DrawButton();
        }
        else if(Button_4.isClick(MousePosition)) {
            SetBGColor(0);
            system("cls");
            return;
        }
    }
}

// At the console menu, let staff members choose the year
// New idea: Create a menu to allow staff member to choose the
void CreateSem(NodeYear*& Year) {
    int sem=0;
    while(sem<1 || sem>3) {
        cout << "Please enter the order of the semester (1-3): ";
        cin >> sem;

        if(1<=sem && sem<=3) {
            for(Sem* cur=Year->listSem->pHead; cur; cur=cur->pNext) {
                if(cur->order==sem) {
                    cout << "This semester has already been created!\n";
                    sem=-1;
                    break;
                }
            }

            if(sem!=-1) {
                if(Year->listSem->pHead) {
                    Year->listSem->pTail->pNext=new Sem();
                    Year->listSem->pTail=Year->listSem->pTail->pNext;
                }

                else Year->listSem->pHead=Year->listSem->pTail=new Sem();
                Year->listSem->pTail->order=sem;
            }
        }

        else cout << "Invalid input, please try again!\n";
    }

    // enter the beginning and ending date of the semester
}

void SetSemWindow(NodeYear*& YearInfo) {
    if(!YearInfo) {
        gotoXY(GetWidth() / 2 - 14, GetHeight() / 2 - 1);
        cout << "Please set school year first!";
        gotoXY(GetWidth() / 2 - 14, GetHeight() / 2 + 1);
        system("pause");
        return;
    }
    string d[3] = {"", "", ""};
    string m[3] = {"", "", ""};
    string y[3] = {"", "", ""};
    for(int i = 0; i < 3; ++i) {
        ifstream fin("Data/" + GetPath() + "Sem" + char(i + '1') + "/SemDate.txt");
        if(fin.is_open()) {
            fin >> d[i] >> m[i] >> y[i];
        }
        fin.close();
    }
    Button Button_Day[3], Button_Month[3], Button_Year[3];

    int ColSpace = 1;
    int TotButton = 2, BoxWidth = 40, ButtonHeight = 1;
    int BoxHeight = TotButton * ButtonHeight + (TotButton - 1) * ColSpace + 13;
    int ButtonWidth = BoxWidth - 10;
    int PosX = (GetWidth() - BoxWidth) / 2, PosY = 15;
    drawview(PosX, PosY, BoxWidth, BoxHeight, "Data/Staff/StaffLogo.txt", 56);

    for(int i = 0; i < 3; ++i) {
        Button_Day[i] = Button(PosX + 5, PosY + 3 + i * 3, 3, ButtonHeight, "");
        Button_Month[i] = Button(PosX + 11, PosY + 3 + i * 3, 3, ButtonHeight, "");
        Button_Year[i] = Button(PosX + 17, PosY + 3 + i * 3, 6, ButtonHeight, "");
    }

    for(int i = 0; i < 3; ++i) {
        gotoXY(PosX + 5, PosY + 2 + i *  3); SetBGColor(8); SetColor(0); cout << "Semester " << i + 1;
        gotoXY(PosX + 5, PosY + 3 + i * 3);
        SetBGColor(15); cout << d[i]; for(int j = d[i].size(); j < 3; ++j) cout << " ";
        SetBGColor(8); cout << " / ";
        SetBGColor(15); cout << m[i]; for(int j = m[i].size(); j < 3; ++j) cout << " ";
        SetBGColor(8); cout << " / ";
        SetBGColor(15); cout << y[i]; for(int j = y[i].size(); j < 6; ++j) cout << " ";
    }

    Button Button_1 = Button(PosX + 5, PosY + 11, ButtonWidth, ButtonHeight, "SAVE");
    Button_1.DrawButton();

    Button Button_2 = Button(PosX + 5, PosY + 13, ButtonWidth, ButtonHeight, "BACK");
    Button_2.DrawButton();

    while(1) {
        gotoXY(0, 0);

        COORD MousePosition;
        while(!isLeftMousePressed(MousePosition));
        if(Button_2.isClick(MousePosition)) {
            SetBGColor(0);
            system("cls");
            return;
        }
        else if(Button_1.isClick(MousePosition)) {
            Date ds[3];
            stringstream ss;
            for(int i = 0; i < 3; ++i) {
                ss << d[i] << ' ' << m[i] << ' ' << y[i] << ' ';
                ss >> ds[i].day >> ds[i].month >> ds[i].year;
            }
            if(checkSyntaxDate(ds[0]) && checkSyntaxDate(ds[1]) && checkSyntaxDate(ds[2]) && DateToInt(ds[0]) < DateToInt(ds[1]) && DateToInt(ds[1]) < DateToInt(ds[2])) {
                for(int i = 0; i < 3; ++i) {
                    ofstream fout("Data/" + GetPath() + "Sem" + char(i + '1') + "/SemDate.txt");
                    fout << d[i] << ' ' << m[i] << ' ' << y[i];
                    fout.close();
                }
                SetBGColor(0);
                system("cls");
                UpdateSemLink();
                return;
            }
            else {
                SetBGColor(8);
                SetColor(0);
                gotoXY(PosX + 5, PosY + BoxHeight - 1);
                cout << "Please check your input!";
            }
        }
        else {
            SetBGColor(15);
            SetColor(0);
            for(int i = 0; i < 3; ++i) {
                if(Button_Day[i].isClick(MousePosition)) {
                    gotoXY(PosX + 5 + d[i].size(), PosY + 3 + i * 3);
                    GetUserName(d[i], 2);
                }
                else if(Button_Month[i].isClick(MousePosition)) {
                    gotoXY(PosX + 11 + m[i].size(), PosY + 3 + i * 3);
                    GetUserName(m[i], 2);
                }
                else if(Button_Year[i].isClick(MousePosition)) {
                    gotoXY(PosX + 17 + y[i].size(), PosY + 3 + i * 3);
                    GetUserName(y[i], 5);
                }
            }
        }
    }
}

///----------///

void ViewListStudent(Student* StudentList) {
    if(StudentList) {
        StudentList->ViewStudent();
        ViewListStudent(StudentList->pNext);
    }
}

void drawStatistics(float d, float c, float b, float a)
{
    int Tang = 24;
    //d
    TextColor(5);
    for (float j = 0; j < d; (float)(j += 5.5))
    {
        gotoXY(29, Tang); printf("%c%c%c", 178, 178, 178);
        Tang -= 1;
    }
    TextColor(9);
    gotoXY(28, Tang); printf("%0.2f%%", d);
    //c
    Tang = 24;
    TextColor(6);
    for (float j = 0; j < c; (float)(j += 5.5))
    {
        gotoXY(41, Tang); printf("%c%c%c", 178, 178, 178);
        Tang -= 1;
    }
    TextColor(9);
    gotoXY(40, Tang); printf("%0.2f%%", c);
    //b
    TextColor(11);
    Tang = 24;
    for (float j = 0; j < b; (float)(j += 5.5))
    {
        gotoXY(53, Tang); printf("%c%c%c", 178, 178, 178);
        Tang -= 1;
    }
    TextColor(9);
    gotoXY(52, Tang); printf("%0.2f%%", b);
    //a
    TextColor(10);
    Tang = 24;
    for (float j = 0; j < a; (float)(j += 5.5))
    {
        gotoXY(65, Tang); printf("%c%c%c", 178, 178, 178);
        Tang -= 1;
    }
    TextColor(9);
    gotoXY(64, Tang); printf("%0.2f%%", a);
}

bool CalScores(Student* StudentList, float& d, float& c, float& b, float& a)
{
    if (!StudentList) return false;
    int d1 = 0, c1 = 0, b1 = 0, a1 = 0;
    while (StudentList)
    {
        if (StudentList->getGPAall() <= 5.4 && StudentList->getGPAall() >= 4.0)
        {
            d1 += 1;
        }
        if (StudentList->getGPAall() <= 6.9 && StudentList->getGPAall() >= 5.5)
        {
            c1 += 1;
        }
        if (StudentList->getGPAall() <= 8.4 && StudentList->getGPAall() >= 7.0)
        {
            b1 += 1;
        }
        if (StudentList->getGPAall() <= 10 && StudentList->getGPAall() >= 8.5)
        {
            a1 += 1;
        }
    }
    int sum = d1 + c1 + b1 + a1;
    d = float(100.0 * d1 / sum);
    c = float(100.0 * c1 / sum);
    b = float(100.0 * b1 / sum);
    a = float(100.0 * a1 / sum);
    return true;

}
void PrintALLStatistics(Student* StudentList)
{
    float a,b,c,d;
    if (!CalScores(StudentList, d, c, b, a))
    {
        cout << "Empty List" << endl;
        return;
    }
    else
    {
        cout << "Statistics:" << endl;
    }
    gotoXY(20, 4); printf("^");
    gotoXY(17, 3); printf("(%%)");
    gotoXY(20, 25); printf("%c", 192);
    for (int i = 21; i < 80; i++) {
        gotoXY(i, 25); printf("%c", 196);
    }
    for (int i = 5; i < 25; i++) {
        gotoXY(20, i); printf("%c", 179);
    }
    gotoXY(78, 26); printf("(Score)");
    gotoXY(80, 25); printf(">");
    for (int i = 30; i < 70; i = i + 12)
    {
        gotoXY(i, 25);
        printf("%c", 193);
        if (i == 30) {
            gotoXY(i - 3, 26); printf("4.0-5.4");
        }
        if (i == 42)
        {
            gotoXY(i - 3, 26); printf("5.5-6.9");
        }
        if (i == 54)
        {
            gotoXY(i - 3, 26); printf("7.0-8.4");
        }
        if (i == 66)
        {
            gotoXY(i - 3, 26); printf("8.5-10");
        }
    }
    int PhanTram = 100;
    for (int i = 5; i < 25; i = i + 4)
    {
        gotoXY(20, i); printf("%c", 197);
        gotoXY(16, i); printf("%d%%", PhanTram);
        PhanTram -= 20;
    }
    gotoXY(17, 25); printf("0%%");
    gotoXY(35, 28); printf("Table Score Of Students In Percent");
    drawStatistics(d, c, b, a);
    TextColor(7);
}

bool Staff::StaffFunction(NodeClass*& ClassList, Student*& StudentList, Course*& CourseList, User*& UserList, ListYear*& YearList, ListSem*& SemList) {
    int ColSpace = 1;
    int TotButton = 8, BoxWidth = 40, ButtonHeight = 1;
    int BoxHeight = TotButton * ButtonHeight + (TotButton - 1) * ColSpace + 4;
    int ButtonWidth = BoxWidth - 10;
    int PosX = (GetWidth() - BoxWidth) / 2, PosY = 15;
    drawview(PosX, PosY, BoxWidth, BoxHeight, "Data/Staff/StaffLogo.txt", 56);
    Button Button_1 = Button(PosX + 5, PosY + 2, ButtonWidth, ButtonHeight, "PROFILE");
    Button_1.DrawButton();

    Button Button_2 = Button(PosX + 5, PosY + 4, ButtonWidth, ButtonHeight, "COURSES");
    Button_2.DrawButton();

    Button Button_3 = Button(PosX + 5, PosY + 6, ButtonWidth, ButtonHeight, "CLASSES");
    Button_3.DrawButton();

    Button Button_4 = Button(PosX + 5, PosY + 8, ButtonWidth, ButtonHeight, "STUDENTS");
    Button_4.DrawButton();

    Button Button_5 = Button(PosX + 5, PosY + 10, ButtonWidth, ButtonHeight, "SCORE BOARD");
    Button_5.DrawButton();

    Button Button_6 = Button(PosX + 5, PosY + 12, ButtonWidth, ButtonHeight, "SETTING");
    Button_6.DrawButton();

    Button Button_7 = Button(PosX + 5, PosY + 14, ButtonWidth, ButtonHeight, "CHANGE PASSWORD");
    Button_7.DrawButton();

    Button Button_8 = Button(PosX + 5, PosY + 16, ButtonWidth, ButtonHeight, "LOG OUT");
    Button_8.DrawButton();

    Button QuitButton = Button(PosX + BoxWidth - 1, PosY, 1, 1, "X");
    QuitButton.DrawButton();
    while(1) {
        gotoXY(0, 0);

        COORD MousePosition;
        while(!isLeftMousePressed(MousePosition));
        if(Button_1.isClick(MousePosition)) {
            system("cls");
            ViewStaff();
            SetBGColor(0);
            system("cls");
            drawview(PosX, PosY, BoxWidth, BoxHeight, "Data/Staff/StaffLogo.txt", 56);
            Button_1.DrawButton();
            Button_2.DrawButton();
            Button_3.DrawButton();
            Button_4.DrawButton();
            Button_5.DrawButton();
            Button_6.DrawButton();
            Button_7.DrawButton();
            Button_8.DrawButton();
            QuitButton.DrawButton();
        }
        else if(Button_2.isClick(MousePosition)) {
            system("cls");
            ChooseClass(ClassList, CourseList, 0, StudentList, UserList);
            SetBGColor(0);
            system("cls");
            drawview(PosX, PosY, BoxWidth, BoxHeight, "Data/Staff/StaffLogo.txt", 56);
            Button_1.DrawButton();
            Button_2.DrawButton();
            Button_3.DrawButton();
            Button_4.DrawButton();
            Button_5.DrawButton();
            Button_6.DrawButton();
            Button_7.DrawButton();
            Button_8.DrawButton();
            QuitButton.DrawButton();
        }
        else if(Button_3.isClick(MousePosition)) {
            system("cls");
            ViewClass(ClassList, CourseList, StudentList, UserList);
            SetBGColor(0);
            system("cls");
            drawview(PosX, PosY, BoxWidth, BoxHeight, "Data/Staff/StaffLogo.txt", 56);
            Button_1.DrawButton();
            Button_2.DrawButton();
            Button_3.DrawButton();
            Button_4.DrawButton();
            Button_5.DrawButton();
            Button_6.DrawButton();
            Button_7.DrawButton();
            Button_8.DrawButton();
            QuitButton.DrawButton();
        }
        else if(Button_4.isClick(MousePosition)) {
            system("cls");
            ChooseClass(ClassList, CourseList, 1, StudentList, UserList);
            SetBGColor(0);
            system("cls");
            drawview(PosX, PosY, BoxWidth, BoxHeight, "Data/Staff/StaffLogo.txt", 56);
            Button_1.DrawButton();
            Button_2.DrawButton();
            Button_3.DrawButton();
            Button_4.DrawButton();
            Button_5.DrawButton();
            Button_6.DrawButton();
            Button_7.DrawButton();
            Button_8.DrawButton();
            QuitButton.DrawButton();
        }
        else if(Button_5.isClick(MousePosition)) {
            system("cls");
            ChooseStudent(StudentList, CourseList);
            SetBGColor(0);
            system("cls");
            drawview(PosX, PosY, BoxWidth, BoxHeight, "Data/Staff/StaffLogo.txt", 56);
            Button_1.DrawButton();
            Button_2.DrawButton();
            Button_3.DrawButton();
            Button_4.DrawButton();
            Button_5.DrawButton();
            Button_6.DrawButton();
            Button_7.DrawButton();
            Button_8.DrawButton();
            QuitButton.DrawButton();
        }
        else if(Button_6.isClick(MousePosition)) {
            system("cls");
            SettingWindow(YearList, SemList, ClassList, StudentList, CourseList, UserList);
            SetBGColor(0);
            system("cls");
            drawview(PosX, PosY, BoxWidth, BoxHeight, "Data/Staff/StaffLogo.txt", 56);
            Button_1.DrawButton();
            Button_2.DrawButton();
            Button_3.DrawButton();
            Button_4.DrawButton();
            Button_5.DrawButton();
            Button_6.DrawButton();
            Button_7.DrawButton();
            Button_8.DrawButton();
            QuitButton.DrawButton();
        }
        else if(Button_7.isClick(MousePosition)) {
            system("cls");
            bool isChange = DrawChangePasswordWindow(15, UserInfo);
            SetBGColor(0);
            system("cls");
            if(isChange) return true;
            else {
                drawview(PosX, PosY, BoxWidth, BoxHeight, "Data/Student/StudentLogo.txt", 68);
                Button_1.DrawButton();
                Button_2.DrawButton();
                Button_3.DrawButton();
                Button_4.DrawButton();
                Button_5.DrawButton();
                Button_6.DrawButton();
                Button_7.DrawButton();
                Button_8.DrawButton();
                QuitButton.DrawButton();
            }
        }
        else if(Button_8.isClick(MousePosition)) {
            SetBGColor(0);
            system("cls");
            return true;
        }
        else if(QuitButton.isClick(MousePosition)) {
            SetBGColor(0);
            system("cls");
            return false;
        }
    }
    return true;
}

void Staff::ViewStaff() {
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
    cout << "STAFFF  PROFILE";
    SetBGColor(8);
    string ListTitle[NumInfo] = {"Staff ID", "First name", "Last name", "Gender", "Date of birth", "Identification", "Phone number"};
    string ListInfo[NumInfo] = {ID, firstName, lastName, gender, "", SocialID, ""};
    for(int i = 0; i < NumInfo / 2; ++i) {
        gotoXY((GetWidth() - RowLen) / 2 + RowSpace, Row + 3 + 2 * (2 * i + 1) + 1);
        for(int j = 0; j < BoxLen; ++j) cout << " ";
        if(i < NumInfo / 2 - 1) {
            gotoXY((GetWidth() - RowLen) / 2 + RowSpace * 3 + BoxLen, Row + 3 + 2 * (2 * i + 1) + 1);
            for(int j = 0; j < BoxLen; ++j) cout << " ";
        }
    }
    SetColor(0);
    for(int i = 0; i < NumInfo / 2; ++i) {
        SetBGColor(7);
        gotoXY((GetWidth() - RowLen) / 2 + RowSpace, Row + 3 + 2 * (2 * i + 1));
        cout << ListTitle[i];
        if(i < NumInfo / 2 - 1) {
            gotoXY((GetWidth() - RowLen) / 2 + RowSpace * 3 + BoxLen, Row + 3 + 2 * (2 * i + 1));
            cout << ListTitle[i + NumInfo / 2];
        }

        SetBGColor(8);
        gotoXY((GetWidth() - RowLen) / 2 + RowSpace, Row + 3 + 2 * (2 * i + 1) + 1);
        cout << ListInfo[i];
        if(i < NumInfo / 2 - 1) {
            gotoXY((GetWidth() - RowLen) / 2 + RowSpace * 3 + BoxLen, Row + 3 + 2 * (2 * i + 1) + 1);
            if(i == 0) cout << DOB.day << "/" << DOB.month << "/" << DOB.year;
            else cout << ListInfo[i + NumInfo / 2];
        }
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

void Staff::ViewClass(NodeClass* ClassList, Course* CourseList, Student*& StudentList, User*& UserList) {
    string Year = GetPath();
    if(Year.size() < 4) {
        gotoXY(GetWidth() / 2 - 14, GetHeight() / 2 - 1);
        cout << "Please set school year first!";
        gotoXY(GetWidth() / 2 - 14, GetHeight() / 2 + 1);
        system("pause");
        return;
    }
    int iYear = (Year[2] - '0') * 10 + Year[3] - '0';

    int ColSpace = 1;
    int TotButton = 5, BoxWidth = 40, ButtonHeight = 1;
    int BoxHeight = TotButton * ButtonHeight + (TotButton - 1) * ColSpace + 4;
    int ButtonWidth = BoxWidth - 10;
    int PosX = (GetWidth() - BoxWidth) / 2, PosY = 15;
    drawview(PosX, PosY, BoxWidth, BoxHeight, "Data/Staff/StaffLogo.txt", 56);
    while(1) {
        Button Button_1 = Button(PosX + 5, PosY + 2, ButtonWidth, ButtonHeight, "FIRST YEAR CLASSES");
        Button_1.DrawButton();

        Button Button_2 = Button(PosX + 5, PosY + 4, ButtonWidth, ButtonHeight, "SECOND YEAR CLASSES");
        Button_2.DrawButton();

        Button Button_3 = Button(PosX + 5, PosY + 6, ButtonWidth, ButtonHeight, "THIRD YEAR CLASSES");
        Button_3.DrawButton();

        Button Button_4 = Button(PosX + 5, PosY + 8, ButtonWidth, ButtonHeight, "FINAL YEAR CLASSES");
        Button_4.DrawButton();

        Button Button_5 = Button(PosX + 5, PosY + 10, ButtonWidth, ButtonHeight, "BACK");
        Button_5.DrawButton();

        gotoXY(0, 0);

        COORD MousePosition;
        while(!isLeftMousePressed(MousePosition));
        if(Button_1.isClick(MousePosition)) {
            system("cls");
            SetBGColor(0);
            stringstream ss;
            string sYear;
            ss << iYear << ' '; ss >> sYear;
            ViewListClass(sYear, ClassList, CourseList, StudentList, UserList);
            system("cls");
            drawview(PosX, PosY, BoxWidth, BoxHeight, "Data/Staff/StaffLogo.txt", 56);
        }
        else if(Button_2.isClick(MousePosition)) {
            system("cls");
            SetBGColor(0);
            stringstream ss;
            string sYear;
            ss << iYear - 1 << ' '; ss >> sYear;
            ViewListClass(sYear, ClassList, CourseList, StudentList, UserList);
            system("cls");
            drawview(PosX, PosY, BoxWidth, BoxHeight, "Data/Staff/StaffLogo.txt", 56);
        }
        else if(Button_3.isClick(MousePosition)) {
            system("cls");
            SetBGColor(0);
            stringstream ss;
            string sYear;
            ss << iYear - 2 << ' '; ss >> sYear;
            ViewListClass(sYear, ClassList, CourseList, StudentList, UserList);
            system("cls");
            drawview(PosX, PosY, BoxWidth, BoxHeight, "Data/Staff/StaffLogo.txt", 56);
        }
        else if(Button_4.isClick(MousePosition)) {
            system("cls");
            SetBGColor(0);
            stringstream ss;
            string sYear;
            ss << iYear - 3 << ' '; ss >> sYear;
            ViewListClass(sYear, ClassList, CourseList, StudentList, UserList);
            system("cls");
            drawview(PosX, PosY, BoxWidth, BoxHeight, "Data/Staff/StaffLogo.txt", 56);
        }
        else if(Button_5.isClick(MousePosition)) {
            system("cls");
            SetBGColor(0);
            system("cls");
            return;
        }
    }
}

void Staff::ViewListClass(string Year, NodeClass* ClassList, Course* CourseList, Student*& StudentList, User*& UserList) {
    int ColSpace = 1;
    int TotButton = 0;
    for(NodeClass* Cur = ClassList; Cur; Cur = Cur->pNext) {
        if(Cur->className.substr(0, 2) != Year) continue;
        TotButton++;
    }

    int BoxWidth = 40, ButtonHeight = 1;
    int BoxHeight = TotButton * ButtonHeight + (TotButton - 1) * ColSpace + 4;
    int ButtonWidth = BoxWidth - 10;
    int PosX = (GetWidth() - BoxWidth) / 2, PosY = 15;

    Button* ListButton = new Button[TotButton];
    int CurB = 0;
    for(NodeClass* Cur = ClassList; Cur; Cur = Cur->pNext) {
        if(Cur->className.substr(0, 2) != Year) continue;
        ListButton[CurB] = Button(PosX + 5, PosY + 2 * (CurB + 1), ButtonWidth, ButtonHeight, Cur->className);
        CurB++;
    }
    Button QuitButton = Button(PosX + BoxWidth - 1, PosY, 1, 1, "X");

    drawview(PosX, PosY, BoxWidth, BoxHeight, "Data/Staff/StaffLogo.txt", 56);
    while(1) {
        for(int i = 0; i < TotButton; ++i) ListButton[i].DrawButton();
        QuitButton.DrawButton();

        gotoXY(0, 0);

        COORD MousePosition;
        while(!isLeftMousePressed(MousePosition));
        if(QuitButton.isClick(MousePosition)) {
            system("cls");
            SetBGColor(0);
            system("cls");
            break;
        }
        for(int i = 0; i < TotButton; ++i) {
            if(ListButton[i].isClick(MousePosition)) {
                NodeClass* ClassInfo = FindClass(ClassList, ListButton[i].GetText());
                system("cls");
                if(ClassInfo) {
                    ViewStudentInClass(ClassInfo, StudentList, UserList);
                }
                SetBGColor(0);
                system("cls");
                drawview(PosX, PosY, BoxWidth, BoxHeight, "Data/Staff/StaffLogo.txt", 56);
                break;
            }
        }
    }
    delete[] ListButton;
}

void loadStudentIntoClass(NodeClass*& ClassList, Student* StudentList)
{
    string nameclass = ClassList->className;
    Student* curr = nullptr;
    while(StudentList)
    {
        if (StudentList->getClass() == nameclass)
        {
            if (!ClassList->listStudents)
            {
                ClassList->listStudents = new Student;
                curr = ClassList->listStudents;
            }
            else
            {
                curr->pNext = new Student;
                curr = curr->pNext;
            }
            (*curr) = (*StudentList);
        }
        StudentList = StudentList->pNext;
    }
    if(curr) curr->pNext = nullptr;
}

void CreateListClass(NodeClass*& ClassList, Student* StudentList)
{
    ifstream fin;
    fin.open("Data/" + GetPath() + "Class/ClassData.txt");
    if (!fin.is_open())
    {
        fin.close();
        return;
    }
    NodeClass* curr = nullptr;
    string S;
    while (!fin.eof() && getline(fin, S))
    {
        if(!ClassList)
        {
            ClassList = new NodeClass;
            curr = ClassList;
        }
        else
        {
            curr->pNext = new NodeClass;
            curr = curr->pNext;
        }
        curr->className = S;
        loadStudentIntoClass(curr, StudentList);
    }
    if(curr) curr->pNext = nullptr;
    fin.close();
}

void ViewCLass(NodeClass* ClassList)
{
    while (ClassList)
    {
        cout << ClassList->className;
        ClassList = ClassList->pNext;
    }
}

NodeClass* FindClass(NodeClass* ClassList, string ClassID) {
    for(NodeClass* Cur = ClassList; Cur; Cur = Cur->pNext) {
        if(Cur->className == ClassID) {
            return Cur;
        }
    }
    return nullptr;
}

void AddStudent(NodeClass*& ClassInfo, Student*& pTail, int& NumStudent, Student*& StudentList, User*& UserList) {
    Student* newStudent = new Student;
    newStudent->setClass(ClassInfo->className);
    if(newStudent->FixInfo()) {
        newStudent->SubRegis = new Course[5];
        newStudent->academicYear = "20" + ClassInfo->className.substr(0, 2);
        if(pTail) {
            pTail->pNext = newStudent;
        }
        else {
            ClassInfo->listStudents = newStudent;
        }
        pTail = newStudent;
        AddStudentToList(StudentList, UserList, newStudent);
        NumStudent++;
    }
    else {
        delete newStudent;
    }
}

void StudentOption(NodeClass*& ClassInfo, Student*& pTail, int& NumStudent, Student*& StudentList, User*& UserList) {
    int ColSpace = 1;
    int TotButton = 4, BoxWidth = 60, ButtonHeight = 1;
    int BoxHeight = TotButton * ButtonHeight + (TotButton - 1) * ColSpace + 5;
    int ButtonWidth = BoxWidth - 10;
    int PosX = (GetWidth() - BoxWidth) / 2, PosY = PosY = (GetHeight() - BoxHeight) / 2 - 2;
    TextColor(7);
    SetBGColor(8);
    for(int i = PosX; i < PosX + BoxWidth; ++i) {
        for(int j = PosY; j < PosY + BoxHeight; ++j) {
            gotoXY(i, j);
            cout << " ";
        }
    }
    gotoXY(PosX + 5, PosY + 2); SetBGColor(8); SetColor(0); cout << "Directory";
    gotoXY(PosX + 5, PosY + 3); SetBGColor(15); for(int i = 0; i < ButtonWidth; ++i) cout << " ";
    Button Button_1 = Button(PosX + 5, PosY + 3, ButtonWidth, ButtonHeight, "");

    Button Button_2 = Button(PosX + 5, PosY + 5, ButtonWidth, ButtonHeight, "ADD FROM FILE");
    Button_2.DrawButton();

    Button Button_3 = Button(PosX + 5, PosY + 7, ButtonWidth, ButtonHeight, "INPUT FROM KEYBOARD");
    Button_3.DrawButton();

    Button Button_4 = Button(PosX + 5, PosY + 9, ButtonWidth, ButtonHeight, "BACK");
    Button_4.DrawButton();
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
            if(fin.is_open())
            {
                string sID;
                while(!fin.eof() && getline(fin, sID, ',')) {
                    Student* newStudent = new Student;
                    newStudent->SubRegis = new Course[5];

                    newStudent->ID = sID;

                    getline(fin, newStudent->passWord, ',');

                    getline(fin, newStudent->lastName, ',');

                    getline(fin, newStudent->firstName, ',');

                    getline(fin, newStudent->Class, ',');

                    getline(fin, newStudent->gender, ',');

                    string StrDOB;
                    getline(fin, StrDOB, ',');

                    getline(fin, newStudent->academicYear, ',');

                    getline(fin, newStudent->SocialID, ',');

                    stringstream ss;

                    string prevGPA, prevCredits;
                    getline(fin, prevGPA, ',');
                    getline(fin, prevCredits, ',');

                    ss << prevGPA << ' ' << prevCredits;
                    ss >> newStudent->prevGPA >> newStudent->prevCredits;

                    fin.get();

                    newStudent->userName = newStudent->ID;
                    newStudent->DOB = Date(StrDOB);
                    newStudent->Class = ClassInfo->className;
                    if(pTail) {
                        pTail->pNext = newStudent;
                    }
                    else {
                        ClassInfo->listStudents = newStudent;
                    }
                    pTail = newStudent;
                    AddStudentToList(StudentList, UserList, newStudent);
                }
                gotoXY(PosX + 5, PosY + BoxHeight - 1);
                SetBGColor(8);
                SetColor(0);
                cout << "Update success!     ";
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
            AddStudent(ClassInfo, pTail, NumStudent, StudentList, UserList);
            TextColor(7);
            SetBGColor(8);
            for(int i = PosX; i < PosX + BoxWidth; ++i) {
                for(int j = PosY; j < PosY + BoxHeight; ++j) {
                    gotoXY(i, j);
                    cout << " ";
                }
            }
            gotoXY(PosX + 5, PosY + 2); SetBGColor(8); SetColor(0); cout << "Directory";
            gotoXY(PosX + 5, PosY + 3); SetBGColor(15); for(int i = 0; i < ButtonWidth; ++i) cout << " ";
            gotoXY(PosX + 5, PosY + 3); cout << Dir;
            Button_2.DrawButton();
            Button_3.DrawButton();
            Button_4.DrawButton();
        }
        else if(Button_4.isClick(MousePosition)) {
            SetBGColor(0);
            system("cls");
            return;
        }
    }
}

void ViewStudentInClass(NodeClass*& ClassInfo, Student*& StudentList, User*& UserList) {
    SetColor(0);
    int ListLen[7] = {5, 20, 45, 8, 21, 25, 8};
    string ListTitle[7] = {"#", "Student ID", "Student Name", "Gender", "Date of birth", "Class", "Option"};
    int TableWidth = 132;
    int Cur = (GetWidth() - TableWidth) / 2;
    for(int i = 0; i < 7; ++i) {
        if(i % 2 == 0) SetBGColor(7);
        else SetBGColor(8);

        for(int k = 0; k < 2; ++k) {
            for(int u = 0; u < ListLen[i]; ++u) {
                gotoXY(Cur + u, k + 1);
                if(k == 0) cout << " ";
                else cout << "_";
            }
        }
        gotoXY(Cur + (ListLen[i] - ListTitle[i].size()) / 2, 1);
        cout << ListTitle[i];
        Cur += ListLen[i];
    }

    int Page = 0;

    Button QuitButton = Button((GetWidth() - TableWidth) / 2 + TableWidth, 0, 1, 1, "X");
    QuitButton.DrawButton();
    SetColor(0);
    int Cnt = 1, NumStudent = 0;
    Button ButtonList[40];
    for(Cnt = 1; Cnt <= 20; ++Cnt) {
        ButtonList[Cnt * 2 - 2] = Button((GetWidth() - TableWidth) / 2 + 124, Cnt * 2 + 1, 4, 2, "X");
        ButtonList[Cnt * 2 - 1] = Button((GetWidth() - TableWidth) / 2 + 128, Cnt * 2 + 1, 4, 2, "@");
    }
    Cnt = 1;
    Student* pTail = nullptr;
    for(Student* Cur = ClassInfo->listStudents; Cur; pTail = Cur, Cur = Cur->pNext) {
        if(20 * Page + 1 <= Cnt && Cnt < 20 * Page + 21) {
            SetBGColor(7);
            ButtonList[Cnt * 2 - 2].DrawButtonTable();
            SetBGColor(7);
            ButtonList[Cnt * 2 - 1].DrawButtonTable();
            for(int i = 0; i < 8; ++i) {
                gotoXY((GetWidth() - TableWidth) / 2 + 124 + i, Cnt * 2 + 2);
                cout << "_";
            }
            Cur->ViewInfo(Cnt, (GetWidth() - TableWidth) / 2, Cnt * 2 + 1);
        }
        Cnt++;
        NumStudent++;
    }
    int LimPage = (NumStudent + 20) / 20;
    Button Button_Add;
    if(Page == LimPage - 1) {
        SetBGColor(7);
        Button_Add = Button((GetWidth() - TableWidth) / 2 + 124, Cnt * 2 + 1, 8, 2, "+");
        Button_Add.DrawButtonTable();
        SetBGColor(0);
    }

    SetColor(15);
    gotoXY(GetWidth() / 2 - 4, 44); cout << "Page " << Page + 1 << "/" << LimPage;
    Button Button_Left = Button((GetWidth() - TableWidth) / 2, 44, 2, 1, "");
    gotoXY((GetWidth() - TableWidth) / 2, 44);
    cout << "<<";
    Button Button_Right = Button((GetWidth() - TableWidth) / 2 + TableWidth - 2, 44, 2, 1, "");
    gotoXY((GetWidth() - TableWidth) / 2 + TableWidth - 2, 44);
    cout << ">>";

    gotoXY(0, 0);

    COORD MousePosition;
    while(1) {
        gotoXY(0, 0);
        SetColor(15);

        while(!isLeftMousePressed(MousePosition));

        if(QuitButton.isClick(MousePosition)) return;
        int Change = 0;
        if(Button_Left.isClick(MousePosition)) Change = -1;
        if(Button_Right.isClick(MousePosition)) Change = 1;

        Cnt = 1;
        int CntPos = 1;
        Student* Pre = nullptr;
        for(Student* Cur = ClassInfo->listStudents; Cur; Pre = Cur, Cur = Cur->pNext, Cnt++) {
            if(20 * Page + 21 <= Cnt) break;
            if(20 * Page + 1 <= Cnt) {
                if(ButtonList[CntPos * 2 - 2].isClick(MousePosition)) {
                    DeleteStudentFromList(StudentList, UserList, Cur->ID);
                    if(Pre) Pre->pNext = Cur->pNext;
                    else ClassInfo->listStudents = Cur->pNext;
                    delete Cur;
                    if(Pre && !Pre->pNext) pTail = Pre;
                    if(!ClassInfo->listStudents) pTail = nullptr;
                    NumStudent--;
                    LimPage = (NumStudent + 20) / 20;
                    Change = LimPage;
                    break;
                }
                if(ButtonList[CntPos * 2 - 1].isClick(MousePosition)) {
                    Student* StudentInfo = FindStudent(StudentList, Cur->ID);
                    User* UserInfo = FindUser(UserList, Cur->ID, 1);
                    Cur->FixInfo();
                    UserInfo->setUserName(Cur->ID);

                    StudentInfo->ID = Cur->ID;
                    StudentInfo->firstName = Cur->firstName;
                    StudentInfo->lastName = Cur->lastName;
                    StudentInfo->DOB = Cur->DOB;
                    StudentInfo->DOB.StrDOB = Cur->DOB.StrDOB;
                    StudentInfo->Class = Cur->Class;
                    StudentInfo->gender = Cur->gender;
                    StudentInfo->userName = Cur->ID;
                    StudentInfo->UserInfo->setUserName(Cur->ID);
                    Change = LimPage;
                    break;
                }
                CntPos++;
            }
        }
        if(Change == 0 && Page == LimPage - 1 && Button_Add.isClick(MousePosition)) {
            SetBGColor(0);
            system("cls");
            StudentOption(ClassInfo, pTail, NumStudent, StudentList, UserList);
            ViewStudentInClass(ClassInfo, StudentList, UserList);
            return;
        }

        if(Change != 0) {
            Page = (Page + Change + LimPage) % LimPage;
            SetColor(0);
            for(int i = (GetWidth() - TableWidth) / 2; i < (GetWidth() - TableWidth) / 2 + TableWidth; ++i) {
                for(int j = 3; j < 44; ++j) {
                    gotoXY(i , j);
                    cout << " ";
                }
            }
            Cnt = 1;
            int CntPos = 1;
            for(Student* Cur = ClassInfo->listStudents; Cur; Cur = Cur->pNext) {
                if(20 * Page + 21 <= Cnt) break;
                if(20 * Page + 1 <= Cnt) {
                    SetBGColor(7);
                    ButtonList[CntPos * 2 - 2].DrawButtonTable();
                    SetBGColor(7);
                    ButtonList[CntPos * 2 - 1].DrawButtonTable();
                    for(int i = 0; i < 8; ++i) {
                        gotoXY((GetWidth() - TableWidth) / 2 + 124 + i, CntPos * 2 + 2);
                        cout << "_";
                    }
                    Cur->ViewInfo(Cnt, (GetWidth() - TableWidth) / 2, CntPos * 2 + 1);
                    CntPos++;
                }
                Cnt++;
            }
            if(Page == LimPage - 1) {
                SetBGColor(7);
                Button_Add = Button((GetWidth() - TableWidth) / 2 + 124, CntPos * 2 + 1, 8, 2, "+");
                Button_Add.DrawButtonTable();
                SetBGColor(0);
            }
            SetColor(15);
            gotoXY(GetWidth() / 2 - 4, 44); cout << "Page " << Page + 1 << "/" << LimPage;
        }
    }
}

bool ChangeCourseScore(Student*& CurrentStudent)
{
    bool found_course = false;
    string inputCourseName;
    cout << "Input Course name: ";
    getline(cin, inputCourseName);
    int i = 0;
    for (i = 0; i < 5; ++i)
    {
        if (CurrentStudent->scoreBoardSem[i].CourseName == inputCourseName)
        {
            cout << "Found the course";
            found_course = true;
            break;
        }

    }
    if (found_course)
    {
        int option;
        while (1)
        {
            cout << "1. Update other score";
            cout << "2. Update midterm score ";
            cout << "3. Update final score";
            cout << "4. Update total score ";
            cout << "5. Exit";
            cout << "Enter an option: " << endl;
            cin >> option;
            if (option == 5)
            {
                cout << "Finished updating";
                cout << "Press any KEY to continue";
                _getch();
                return true;
            }

            switch (option)
            {
            case 1:
                system("cls");
                cout << "Input Student's other score: ";
                cin >> CurrentStudent->scoreBoardSem[i].Other;
                cout << "Press any KEY to continue";
                _getch();
                break;
            case 2:
                system("cls");
                cout << "Input Student's midterm score: ";
                cin >> CurrentStudent->scoreBoardSem[i].Midterm;
                cout << "Press any KEY to continue";
                _getch();
                break;
            case 3:
                system("cls");
                cout << "Input Student's final score: ";
                cin >> CurrentStudent->scoreBoardSem[i].Final;
                cout << "Press any KEY to continue";
                _getch();
                break;
            case 4:
                system("cls");
                cout << "Input Student's total score: ";
                cin >> CurrentStudent->scoreBoardSem[i].Total;
                cout << "Press any KEY to continue";
                _getch();
                break;
            }
        }

    }
    cout << "Failed to find the course to update score!!!";
    return false;
}

bool Staff::UpdateStudentScore(Student* StudentList, string StudentID)
{
    Student* currentStudent = FindStudent(StudentList, StudentID);

    if (currentStudent && ChangeCourseScore(currentStudent))
    {
        cout << "Update successfully!!!";
        return true;
    }

    return false;
}

void ChooseStudent(Student* StudentList, Course* CourseList) {
    int ColSpace = 1;
    int TotButton = 3, BoxWidth = 40, ButtonHeight = 1;
    int BoxHeight = TotButton * ButtonHeight + (TotButton - 1) * ColSpace + 5;
    int ButtonWidth = BoxWidth - 10;
    int PosX = (GetWidth() - BoxWidth) / 2, PosY = 15;
    drawview(PosX, PosY, BoxWidth, BoxHeight, "Data/Staff/StaffLogo.txt", 56);
    gotoXY(PosX + 5, PosY + 2); SetBGColor(8); SetColor(0); cout << "Student ID";
    gotoXY(PosX + 5, PosY + 3); SetBGColor(15); for(int i = 0; i < ButtonWidth; ++i) cout << " ";
    Button Button_1 = Button(PosX + 5, PosY + 3, ButtonWidth, ButtonHeight, "");

    Button Button_2 = Button(PosX + 5, PosY + 5, ButtonWidth, ButtonHeight, "SEARCH");
    Button_2.DrawButton();

    Button Button_3 = Button(PosX + 5, PosY + 7, ButtonWidth, ButtonHeight, "BACK");
    Button_3.DrawButton();
    string StudentID = "";
    while(1) {
        gotoXY(0, 0);

        COORD MousePosition;
        while(!isLeftMousePressed(MousePosition));
        if(Button_1.isClick(MousePosition)) {
            gotoXY(PosX + 5 + StudentID.size(), PosY + 3);
            SetBGColor(15);
            SetColor(0);
            GetUserName(StudentID, ButtonWidth - 1);
        }
        else if(Button_2.isClick(MousePosition)) {
            Student* StudentInfo = FindStudent(StudentList, StudentID);
            if(StudentInfo) {
                SetBGColor(0);
                system("cls");
                StudentInfo->FixScoreboard(CourseList);
                SetBGColor(0);
                system("cls");
                drawview(PosX, PosY, BoxWidth, BoxHeight, "Data/Staff/StaffLogo.txt", 56);
                gotoXY(PosX + 5, PosY + 2); SetBGColor(8); SetColor(0); cout << "Student ID";
                gotoXY(PosX + 5, PosY + 3); SetBGColor(15); for(int i = 0; i < ButtonWidth; ++i) cout << " ";
                Button_2.DrawButton();
                Button_3.DrawButton();
                gotoXY(PosX + 5, PosY + 3);
                SetBGColor(15);
                SetColor(0);
                cout << StudentID;
            }
        }
        else if(Button_3.isClick(MousePosition)) {
            SetBGColor(0);
            system("cls");
            return;
        }
    }
}

void AddSubjecttoClass(NodeClass* ListClass, Course* CourseList)
{
    ofstream file;
    file.open("Data/" + GetPath() + GetSemPath() + "Course/" + ListClass->className + ".txt", ios::app);
    if (!file.is_open())
    {
        cout << "Error opening the file!!!";
        return;
    }
    file << CourseList->ID << ',';
    file << CourseList->courseName << ',';
    file << CourseList->teacherName << ',';
    file << CourseList->numCredits << ',';
    file << CourseList->maxStudent << ',';
    file << CourseList->numStudent << ',';
    file << CourseList->date[0] / 4 + 2 << ',';
    file << CourseList->date[0] % 4 + 1 << ',';
    file << CourseList->date[1] / 4 + 2 << ',';
    file << CourseList->date[1] % 4 + 1 << ',';
    file << '\n';
    file.close();

}

void deleteCourseForClass(NodeClass*& ClassList, Course*& CourseList, Course*& curr)
{
    if(CourseList == nullptr || curr == nullptr) return;
    if(CourseList == curr) {
        CourseList = CourseList->pNext;
        curr->freeStudentList();
        delete curr;
    }
    else {
        for(Course* Cur = CourseList; Cur && Cur->pNext; Cur = Cur->pNext) {
            if(Cur->pNext == curr) {
                Cur->pNext = curr->pNext;
                curr->freeStudentList();
                delete curr;
                break;
            }
        }
    }
    LoadCourseToFile(CourseList, "Data/" + GetPath() + GetSemPath() + "Course/" + ClassList->className + ".txt");
}

void AddCourseWindow(Course* CourseList, NodeClass* ClassInfo) {
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
    SetColor(0);
    SetBGColor(8);
    SetColor(0);
    gotoXY(PosX + 7, PosY + 5); cout << "Course ID";
    SetBGColor(7);
    gotoXY(PosX + 7, PosY + 6); for(int i = 0; i < 20; ++i) cout << " ";

    SetBGColor(8);
    gotoXY(PosX + 33, PosY + 5); cout << "Credits";
    SetBGColor(7);
    gotoXY(PosX + 33, PosY + 6); for(int i = 0; i < 20; ++i) cout << " ";

    SetBGColor(8);
    gotoXY(PosX + 7, PosY + 8); cout << "Course name";
    SetBGColor(7);
    gotoXY(PosX + 7, PosY + 9); for(int i = 0; i < 46; ++i) cout << " ";

    SetBGColor(8);
    gotoXY(PosX + 7, PosY + 11); cout << "Teacher name";
    SetBGColor(7);
    gotoXY(PosX + 7, PosY + 12); for(int i = 0; i < 46; ++i) cout << " ";

    SetBGColor(8);
    gotoXY(PosX + 7, PosY + 14); cout << "Day  -  Session";
    SetBGColor(7);
    gotoXY(PosX + 7, PosY + 15); for(int i = 0; i < 3; ++i) cout << " ";
    for(int i = 0; i < 4; ++i) {
        gotoXY(PosX + 15 + 2 * i, PosY + 15);
        cout << i+1;
    }

    SetBGColor(8);
    gotoXY(PosX + 8 + BoxWidth / 2, PosY + 14); cout << "Day  -  Session";
    SetBGColor(7);
    gotoXY(PosX + 8 + BoxWidth / 2, PosY + 15); for(int i = 0; i < 3; ++i) cout << " ";
    for(int i = 0; i < 4; ++i) {
        gotoXY(PosX + 8 + BoxWidth / 2 + 8 + 2 * i, PosY + 15);
        cout << i+1;
    }

    SetBGColor(8);
    gotoXY(PosX + 22, PosY + BoxHeight - 2);
    cout << "SAVE";
    Button Button_Save = Button(PosX + 22, PosY + BoxHeight - 2, 4, 1, "");
    gotoXY(PosX + 36, PosY + BoxHeight - 2);
    cout << "BACK";
    Button Button_Back = Button(PosX + 36, PosY + BoxHeight - 2, 4, 1, "");

    Button Button_ID = Button(PosX + 7, PosY + 6, 20, 1, "");
    Button Button_Cre = Button(PosX + 33, PosY + 6, 20, 1, "");
    Button Button_Teacher = Button(PosX + 7, PosY + 12, 46, 1, "");
    Button Button_D[2][5];
    Button_D[0][0] = Button(PosX + 7, PosY + 15, 3, 1, "");
    Button_D[1][0] = Button(PosX + 8 + BoxWidth / 2, PosY + 15, 3, 1, "");
    for(int i = 0; i < 4; ++i) {
        Button_D[0][i + 1] = Button(PosX + 15 + 2 * i, PosY + 15, 1, 1, "");
        Button_D[1][i + 1] = Button(PosX + 8 + BoxWidth / 2 + 8 + 2 * i, PosY + 15, 1, 1, "");
    }

    int Click = -1;
    string ID = "", Cre = "", Teacher = "", D0 = "", D1 = "";
    int S[2] = {-1, -1};
    Course* newCourse = nullptr;
    while(1) {
        SetBGColor(7);
        gotoXY(0, 0);
        newCourse = FindCourse(CourseList, ID);
        if(newCourse) {
            newCourse->teacherName = Teacher;
            gotoXY(PosX + 7, PosY + 9);
            for(int i = 0; i < 45; ++i) cout << " ";
            gotoXY(PosX + 7, PosY + 9);
            cout << newCourse->courseName;
            gotoXY(0, 0);
        }
        COORD MousePosition;
        while(!isLeftMousePressed(MousePosition));
        if(Button_Back.isClick(MousePosition)) break;
        if(Button_ID.isClick(MousePosition)) {
            Click = 0;
        }
        else if(Button_Cre.isClick(MousePosition)) {
            Click = 1;
        }
        else if(Button_Teacher.isClick(MousePosition)) {
            Click = 2;
        }
        else if(Button_D[0][0].isClick(MousePosition)) {
            Click = 3;
        }
        else if(Button_D[1][0].isClick(MousePosition)) {
            Click = 4;
        }
        else Click = -1;

        for(int i = 0; i < 2; ++i) {
            for(int j = 1; j < 5; ++j) {
                if(Button_D[i][j].isClick(MousePosition)) {
                    S[i] = j;
                    for(int k = 1; k < 5; ++k) {
                        gotoXY(Button_D[i][k].GetX(), Button_D[i][k].GetY());
                        SetBGColor(7);
                        cout << k;
                    }
                    gotoXY(Button_D[i][j].GetX(), Button_D[i][j].GetY());
                    SetBGColor(4);
                    cout << j;
                    SetBGColor(7);
                }
            }
        }

        if(Click == 0) {
            gotoXY(Button_ID.GetX() + ID.size(), Button_ID.GetY());
            GetUserName(ID, 19);
            newCourse = FindCourse(CourseList, ID);
            if(newCourse) {
                newCourse->teacherName = Teacher;
                gotoXY(PosX + 7, PosY + 9);
                for(int i = 0; i < 45; ++i) cout << " ";
                gotoXY(PosX + 7, PosY + 9);
                cout << newCourse->courseName;
                gotoXY(0, 0);
            }
        }
        if(Click == 1) {
            gotoXY(Button_Cre.GetX() + Cre.size(), Button_Cre.GetY());
            GetUserName(Cre, 1);
        }
        if(Click == 2) {
            gotoXY(Button_Teacher.GetX() + Teacher.size(), Button_Teacher.GetY());
            GetUserName(Teacher, 45);
        }
        if(Click == 3) {
            gotoXY(Button_D[0][0].GetX() + D0.size(), Button_D[0][0].GetY());
            GetUserName(D0, 1);
        }
        if(Click == 4) {
            gotoXY(Button_D[1][0].GetX() + D1.size(), Button_D[1][0].GetY());
            GetUserName(D1, 1);
        }
        if(Button_Save.isClick(MousePosition)) {
            SetBGColor(15);
            gotoXY(Button_Save.GetX(), Button_Save.GetY() + 1);
            for(int i = 0; i < 26; ++i) cout << char(177);
            gotoXY(Button_Save.GetX(), Button_Save.GetY() + 1);
            SetBGColor(7);
            if(ID == "") {
                cout << "Please enter course ID!";
            }
            else if(!newCourse) {
                cout << "Invalid course ID!";
            }
            else if(Cre == "") {
                cout << "Please enter credits!";
            }
            else if(Cre[0] < '2' || Cre[0] > '4') {
                cout << "Invalid credits!";
            }
            else if(Teacher == "") {
                cout << "Please enter teacher name!";
            }
            else if(D0 == "") {
                cout << "Please enter day 1!";
            }
            else if(D0[0] < '2' || D0[0] > '7') {
                cout << "Invalid day 1!";
            }
            else if(D1 == "") {
                cout << "Please enter day 2!";
            }
            else if(D1[0] < '2' || D1[0] > '7') {
                cout << "Invalid day 2!";
            }
            else if(S[0] == -1) {
                cout << "Please choose session 1!";
            }
            else if(S[1] == -1) {
                cout << "Please choose session 2!";
            }
            else {
                newCourse->teacherName = Teacher;
                newCourse->numCredits = Cre[0] - '0';
                newCourse->date[0] = (D0[0] - '2') * 4 + S[0] - 1;
                newCourse->date[1] = (D1[0] - '2') * 4 + S[1] - 1;
                AddSubjecttoClass(ClassInfo, newCourse);
                break;
            }
        }
    }
    SetBGColor(0);
    system("cls");
}

void CourseOption(Course* CourseList, NodeClass* ClassInfo) {
    int ColSpace = 1;
    int TotButton = 4, BoxWidth = 60, ButtonHeight = 1;
    int BoxHeight = TotButton * ButtonHeight + (TotButton - 1) * ColSpace + 5;
    int ButtonWidth = BoxWidth - 10;
    int PosX = (GetWidth() - BoxWidth) / 2, PosY = PosY = (GetHeight() - BoxHeight) / 2 - 2;
    TextColor(7);
    SetBGColor(8);
    for(int i = PosX; i < PosX + BoxWidth; ++i) {
        for(int j = PosY; j < PosY + BoxHeight; ++j) {
            gotoXY(i, j);
            cout << " ";
        }
    }
    gotoXY(PosX + 5, PosY + 2); SetBGColor(8); SetColor(0); cout << "Directory";
    gotoXY(PosX + 5, PosY + 3); SetBGColor(15); for(int i = 0; i < ButtonWidth; ++i) cout << " ";
    Button Button_1 = Button(PosX + 5, PosY + 3, ButtonWidth, ButtonHeight, "");

    Button Button_2 = Button(PosX + 5, PosY + 5, ButtonWidth, ButtonHeight, "ADD FROM FILE");
    Button_2.DrawButton();

    Button Button_3 = Button(PosX + 5, PosY + 7, ButtonWidth, ButtonHeight, "INPUT FROM KEYBOARD");
    Button_3.DrawButton();

    Button Button_4 = Button(PosX + 5, PosY + 9, ButtonWidth, ButtonHeight, "BACK");
    Button_4.DrawButton();
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
            ofstream fout;
            ifstream fin(Dir);
            fout.open("Data/" + GetPath() + GetSemPath() + "Course/" + ClassInfo->className + ".txt", ios::app);
            if(fin.is_open())
            {
                string St;
                while(getline(fin, St)) {
                    fout << St << '\n';
                }
                gotoXY(PosX + 5, PosY + BoxHeight - 1);
                SetBGColor(8);
                SetColor(0);
                cout << "Update success!     ";
            }
            else {
                gotoXY(PosX + 5, PosY + BoxHeight - 1);
                SetBGColor(8);
                SetColor(0);
                cout << "Invalid directory!";
            }
            fin.close();
            fout.close();
        }
        else if(Button_3.isClick(MousePosition)) {
            AddCourseWindow(CourseList, ClassInfo);
            TextColor(7);
            SetBGColor(8);
            for(int i = PosX; i < PosX + BoxWidth; ++i) {
                for(int j = PosY; j < PosY + BoxHeight; ++j) {
                    gotoXY(i, j);
                    cout << " ";
                }
            }
            gotoXY(PosX + 5, PosY + 2); SetBGColor(8); SetColor(0); cout << "Directory";
            gotoXY(PosX + 5, PosY + 3); SetBGColor(15); for(int i = 0; i < ButtonWidth; ++i) cout << " ";
            gotoXY(PosX + 5, PosY + 3); cout << Dir;
            Button_2.DrawButton();
            Button_3.DrawButton();
            Button_4.DrawButton();
        }
        else if(Button_4.isClick(MousePosition)) {
            SetBGColor(0);
            system("cls");
            return;
        }
    }
}

void Course::FixCourseWindow() {
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
    SetColor(0);
    SetBGColor(8);
    SetColor(0);
    gotoXY(PosX + 7, PosY + 5); cout << "Course ID";
    SetBGColor(7);
    gotoXY(PosX + 7, PosY + 6); for(int i = 0; i < 20; ++i) cout << " ";

    SetBGColor(8);
    gotoXY(PosX + 33, PosY + 5); cout << "Credits";
    SetBGColor(7);
    gotoXY(PosX + 33, PosY + 6); for(int i = 0; i < 20; ++i) cout << " ";

    SetBGColor(8);
    gotoXY(PosX + 7, PosY + 8); cout << "Course name";
    SetBGColor(7);
    gotoXY(PosX + 7, PosY + 9); for(int i = 0; i < 46; ++i) cout << " ";

    SetBGColor(8);
    gotoXY(PosX + 7, PosY + 11); cout << "Teacher name";
    SetBGColor(7);
    gotoXY(PosX + 7, PosY + 12); for(int i = 0; i < 46; ++i) cout << " ";

    SetBGColor(8);
    gotoXY(PosX + 7, PosY + 14); cout << "Day  -  Session";
    SetBGColor(7);
    gotoXY(PosX + 7, PosY + 15); for(int i = 0; i < 3; ++i) cout << " ";
    for(int i = 0; i < 4; ++i) {
        gotoXY(PosX + 15 + 2 * i, PosY + 15);
        cout << i+1;
    }

    SetBGColor(8);
    gotoXY(PosX + 8 + BoxWidth / 2, PosY + 14); cout << "Day  -  Session";
    SetBGColor(7);
    gotoXY(PosX + 8 + BoxWidth / 2, PosY + 15); for(int i = 0; i < 3; ++i) cout << " ";
    for(int i = 0; i < 4; ++i) {
        gotoXY(PosX + 8 + BoxWidth / 2 + 8 + 2 * i, PosY + 15);
        cout << i+1;
    }

    SetBGColor(8);
    gotoXY(PosX + 22, PosY + BoxHeight - 2);
    cout << "SAVE";
    Button Button_Save = Button(PosX + 22, PosY + BoxHeight - 2, 4, 1, "");
    gotoXY(PosX + 36, PosY + BoxHeight - 2);
    cout << "BACK";
    Button Button_Back = Button(PosX + 36, PosY + BoxHeight - 2, 4, 1, "");

    string Cre = "", Teacher = teacherName, D0 = "", D1 = "";
    int S[2] = {date[0] % 4 + 1, date[1] % 4 + 1};
    Cre += char(numCredits + '0');
    D0 += char(date[0] / 4 + 2 + '0');
    D1 += char(date[1] / 4 + 2 + '0');
    Button Button_Cre = Button(PosX + 33, PosY + 6, 20, 1, Cre);
    Button Button_Teacher = Button(PosX + 7, PosY + 12, 46, 1, Teacher);
    Button Button_D[2][5];
    Button_D[0][0] = Button(PosX + 7, PosY + 15, 3, 1, D0);
    Button_D[1][0] = Button(PosX + 8 + BoxWidth / 2, PosY + 15, 3, 1, D1);
    for(int i = 0; i < 4; ++i) {
        Button_D[0][i + 1] = Button(PosX + 15 + 2 * i, PosY + 15, 1, 1, "");
        Button_D[1][i + 1] = Button(PosX + 8 + BoxWidth / 2 + 8 + 2 * i, PosY + 15, 1, 1, "");
    }
    SetColor(0);
    SetBGColor(7);
    gotoXY(PosX + 7, PosY + 6); cout << ID;
    gotoXY(PosX + 33, PosY + 6); cout << Cre;
    gotoXY(PosX + 7, PosY + 9); cout << courseName;
    gotoXY(PosX + 7, PosY + 12); cout << Teacher;
    gotoXY(PosX + 7, PosY + 15); cout << D0;
    gotoXY(PosX + 8 + BoxWidth / 2, PosY + 15); cout << D1;
    for(int i = 0; i < 2; ++i) {
        if(S[i] != -1) {
            int j = S[i];
            for(int k = 1; k < 5; ++k) {
                gotoXY(Button_D[i][k].GetX(), Button_D[i][k].GetY());
                SetBGColor(7);
                cout << k;
            }
            gotoXY(Button_D[i][j].GetX(), Button_D[i][j].GetY());
            SetBGColor(4);
            cout << j;
            SetBGColor(7);
        }
    }


    int Click = -1;
    while(1) {
        SetBGColor(7);
        gotoXY(0, 0);
        COORD MousePosition;
        while(!isLeftMousePressed(MousePosition));
        if(Button_Back.isClick(MousePosition)) break;
        if(Button_Cre.isClick(MousePosition)) {
            Click = 1;
        }
        else if(Button_Teacher.isClick(MousePosition)) {
            Click = 2;
        }
        else if(Button_D[0][0].isClick(MousePosition)) {
            Click = 3;
        }
        else if(Button_D[1][0].isClick(MousePosition)) {
            Click = 4;
        }
        else Click = -1;

        for(int i = 0; i < 2; ++i) {
            for(int j = 1; j < 5; ++j) {
                if(Button_D[i][j].isClick(MousePosition)) {
                    S[i] = j;
                }
            }
            if(S[i] != -1) {
                int j = S[i];
                for(int k = 1; k < 5; ++k) {
                    gotoXY(Button_D[i][k].GetX(), Button_D[i][k].GetY());
                    SetBGColor(7);
                    cout << k;
                }
                gotoXY(Button_D[i][j].GetX(), Button_D[i][j].GetY());
                SetBGColor(4);
                cout << j;
                SetBGColor(7);
            }
        }

        if(Click == 1) {
            gotoXY(Button_Cre.GetX() + Cre.size(), Button_Cre.GetY());
            GetUserName(Cre, 1);
        }
        if(Click == 2) {
            gotoXY(Button_Teacher.GetX() + Teacher.size(), Button_Teacher.GetY());
            GetUserName(Teacher, 45);
        }
        if(Click == 3) {
            gotoXY(Button_D[0][0].GetX() + D0.size(), Button_D[0][0].GetY());
            GetUserName(D0, 1);
        }
        if(Click == 4) {
            gotoXY(Button_D[1][0].GetX() + D1.size(), Button_D[1][0].GetY());
            GetUserName(D1, 1);
        }
        if(Button_Save.isClick(MousePosition)) {
            SetBGColor(15);
            gotoXY(Button_Save.GetX(), Button_Save.GetY() + 1);
            for(int i = 0; i < 26; ++i) cout << char(177);
            gotoXY(Button_Save.GetX(), Button_Save.GetY() + 1);
            SetBGColor(7);
            if(Cre == "") {
                cout << "Please enter credits!";
            }
            else if(Cre[0] < '2' || Cre[0] > '4') {
                cout << "Invalid credits!";
            }
            else if(Teacher == "") {
                cout << "Please enter teacher name!";
            }
            else if(D0 == "") {
                cout << "Please enter day 1!";
            }
            else if(D0[0] < '2' || D0[0] > '7') {
                cout << "Invalid day 1!";
            }
            else if(D1 == "") {
                cout << "Please enter day 2!";
            }
            else if(D1[0] < '2' || D1[0] > '7') {
                cout << "Invalid day 2!";
            }
            else if(S[0] == -1) {
                cout << "Please choose session 1!";
            }
            else if(S[1] == -1) {
                cout << "Please choose session 2!";
            }
            else {
                this->teacherName = Teacher;
                this->numCredits = Cre[0] - '0';
                this->date[0] = (D0[0] - '2') * 4 + S[0] - 1;
                this->date[1] = (D1[0] - '2') * 4 + S[1] - 1;
                break;
            }
        }
    }
    SetBGColor(0);
    system("cls");
}

void ViewStudentInCourse(Course* CourseInfo, Student* StudentList) {
    SetColor(0);
    int ListLen[7] = {5, 20, 45, 15, 15, 15, 15};
    string ListTitle[7] = {"#", "Student ID", "Student Name", "Mid term", "Other", "Final", "Total"};
    int TableWidth = 130;
    int Cur = (GetWidth() - TableWidth) / 2;
    for(int i = 0; i < 7; ++i) {
        if(i % 2 == 0) SetBGColor(7);
        else SetBGColor(8);

        for(int k = 0; k < 2; ++k) {
            for(int u = 0; u < ListLen[i]; ++u) {
                gotoXY(Cur + u, k + 1);
                if(k == 0) cout << " ";
                else cout << "_";
            }
        }
        gotoXY(Cur + (ListLen[i] - ListTitle[i].size()) / 2, 1);
        cout << ListTitle[i];
        Cur += ListLen[i];
    }

    int Page = 0;

    Button QuitButton = Button((GetWidth() - TableWidth) / 2 + TableWidth, 0, 1, 1, "X");
    QuitButton.DrawButton();
    SetColor(0);
    int Cnt = 1, NumStudent = 0, PosX = (GetWidth() - TableWidth) / 2;
    Button Button_Mid[20], Button_Oth[20], Button_Fin[20], Button_Tot[20];
    string sMid[20], sOth[20], sFin[20], sTot[20];
    for(Cnt = 1; Cnt <= 20; ++Cnt) {
        Button_Mid[Cnt - 1] = Button(PosX + 70, Cnt * 2 + 1, 15, 2, "");
        Button_Oth[Cnt - 1] = Button(PosX + 70 + 15, Cnt * 2 + 1, 15, 2, "");
        Button_Fin[Cnt - 1] = Button(PosX + 70 + 30, Cnt * 2 + 1, 15, 2, "");
        Button_Tot[Cnt - 1] = Button(PosX + 70 + 45, Cnt * 2 + 1, 15, 2, "");
    }
    Cnt = 1;
    for(Student* Cur = StudentList; Cur; Cur = Cur->pNext) {
        if(!Cur->isEnrollCourse(CourseInfo)) continue;
        if(20 * Page + 1 <= Cnt && Cnt < 20 * Page + 21) {
            Cur->LoadScoreboardFromFile("Data/" + GetPath() + GetSemPath() + "Student/Score/" + Cur->getID() + ".txt");
            Cur->ViewCourseScore(Cur->GetCourseID(CourseInfo), Cnt * 2 + 1, 2);
            gotoXY(PosX + 2, Cnt * 2 + 1);
            SetBGColor(7); SetColor(0); cout << Cnt;
        }
        Cnt++;
        NumStudent++;
    }
    int LimPage = (NumStudent + 20) / 20;

    SetColor(15);
    SetBGColor(0);
    gotoXY(GetWidth() / 2 - 4, 44); cout << "Page " << Page + 1 << "/" << LimPage;
    Button Button_Left = Button((GetWidth() - TableWidth) / 2, 44, 2, 1, "");
    gotoXY((GetWidth() - TableWidth) / 2, 44);
    cout << "<<";
    Button Button_Right = Button((GetWidth() - TableWidth) / 2 + TableWidth - 2, 44, 2, 1, "");
    gotoXY((GetWidth() - TableWidth) / 2 + TableWidth - 2, 44);
    cout << ">>";

    Button Button_Load = Button(GetWidth() - 16, 0, 14, 1, "LOAD FROM FILE");
    Button_Load.DrawButton();

    Button Button_Export = Button(GetWidth() - 16, 2, 14, 1, "EXPORT TO FILE");
    Button_Export.DrawButton();

    gotoXY(0, 0);

    COORD MousePosition;
    while(1) {
        gotoXY(0, 0);
        SetColor(15);

        while(!isLeftMousePressed(MousePosition));

        if(QuitButton.isClick(MousePosition)) {
            for(Student* Cur = StudentList; Cur; Cur = Cur->pNext) {
                if(!Cur->isEnrollCourse(CourseInfo)) continue;
                Cur->UpdateScoreboardToFile("Data/" + GetPath() + GetSemPath() + "Student/Score/" + Cur->ID + ".txt");
            }
            return;
        }
        if(Button_Load.isClick(MousePosition)) {
            SetBGColor(0);
            system("cls");
            LoadCourseScore(CourseInfo, StudentList);
            ViewStudentInCourse(CourseInfo, StudentList);
            return;
        }
        if(Button_Export.isClick(MousePosition)) {
            SetBGColor(0);
            system("cls");
            CourseInfo->ExportListStudentWindow();
            ViewStudentInCourse(CourseInfo, StudentList);
            return;
        }
        int Change = 0;
        if(Button_Left.isClick(MousePosition)) Change = -1;
        if(Button_Right.isClick(MousePosition)) Change = 1;

        Cnt = 1;
        int CntPos = 1;
        for(Student* Cur = StudentList; Cur; Cur = Cur->pNext) {
            if(!Cur->isEnrollCourse(CourseInfo)) continue;
            if(20 * Page + 21 <= Cnt) break;
            if(20 * Page + 1 <= Cnt) {
                stringstream ss;
                ss << Cur->scoreBoardSem[Cur->GetCourseID(CourseInfo)].Midterm << ' '
                << Cur->scoreBoardSem[Cur->GetCourseID(CourseInfo)].Other << ' '
                << Cur->scoreBoardSem[Cur->GetCourseID(CourseInfo)].Final << ' '
                << Cur->scoreBoardSem[Cur->GetCourseID(CourseInfo)].Total << ' ';
                ss >> sMid[CntPos - 1] >> sOth[CntPos - 1] >> sFin[CntPos - 1] >> sTot[CntPos - 1];
                if(sMid[CntPos - 1] == "-1") sMid[CntPos - 1] = "-";
                if(sOth[CntPos - 1] == "-1") sOth[CntPos - 1] = "-";
                if(sFin[CntPos - 1] == "-1") sFin[CntPos - 1] = "-";
                if(sTot[CntPos - 1] == "-1") sTot[CntPos - 1] = "-";
                if(Button_Mid[CntPos - 1].isClick(MousePosition)) {
                    SetColor(0);
                    SetBGColor(8);
                    gotoXY(PosX + 74, CntPos * 2 + 1);
                    for(int j = 0; j < 7; ++j) cout << " ";
                    gotoXY(PosX + 74, CntPos * 2 + 1); cout << sMid[CntPos - 1];
                    GetUserName(sMid[CntPos - 1], 7);
                    gotoXY(PosX + 74, CntPos * 2 + 1);
                    for(int j = 0; j < 7; ++j) cout << " ";
                    gotoXY(PosX + 70 + (15 - sMid[CntPos - 1].size()) / 2, CntPos * 2 + 1); cout << sMid[CntPos - 1];
                    stringstream ss;
                    ss << sMid[CntPos - 1] << ' ';
                    ss >> Cur->scoreBoardSem[Cur->GetCourseID(CourseInfo)].Midterm;
                }
                else if(Button_Oth[CntPos - 1].isClick(MousePosition)) {
                    SetColor(0);
                    SetBGColor(7);
                    gotoXY(PosX + 74 + 15, CntPos * 2 + 1);
                    for(int j = 0; j < 7; ++j) cout << " ";
                    gotoXY(PosX + 74 + 15, CntPos * 2 + 1); cout << sOth[CntPos - 1];
                    GetUserName(sOth[CntPos - 1], 7);
                    gotoXY(PosX + 74 + 15, CntPos * 2 + 1);
                    for(int j = 0; j < 7; ++j) cout << " ";
                    gotoXY(PosX + 70 + 15 + (15 - sOth[CntPos - 1].size()) / 2, CntPos * 2 + 1); cout << sOth[CntPos - 1];
                    stringstream ss;
                    ss << sOth[CntPos - 1] << ' ';
                    ss >> Cur->scoreBoardSem[Cur->GetCourseID(CourseInfo)].Other;
                }
                else if(Button_Fin[CntPos - 1].isClick(MousePosition)) {
                    SetColor(0);
                    SetBGColor(8);
                    gotoXY(PosX + 74 + 30, CntPos * 2 + 1);
                    for(int j = 0; j < 7; ++j) cout << " ";
                    gotoXY(PosX + 74 + 30, CntPos * 2 + 1); cout << sFin[CntPos - 1];
                    GetUserName(sFin[CntPos - 1], 7);
                    gotoXY(PosX + 74 + 30, CntPos * 2 + 1);
                    for(int j = 0; j < 7; ++j) cout << " ";
                    gotoXY(PosX + 70 + 30 + (15 - sFin[CntPos - 1].size()) / 2, CntPos * 2 + 1); cout << sFin[CntPos - 1];
                    stringstream ss;
                    ss << sFin[CntPos - 1] << ' ';
                    ss >> Cur->scoreBoardSem[Cur->GetCourseID(CourseInfo)].Final;
                }
                else if(Button_Tot[CntPos - 1].isClick(MousePosition)) {
                    SetColor(0);
                    SetBGColor(7);
                    gotoXY(PosX + 74 + 45, CntPos * 2 + 1);
                    for(int j = 0; j < 7; ++j) cout << " ";
                    gotoXY(PosX + 74 + 45, CntPos * 2 + 1); cout << sTot[CntPos - 1];
                    GetUserName(sTot[CntPos - 1], 7);
                    gotoXY(PosX + 74 + 45, CntPos * 2 + 1);
                    for(int j = 0; j < 7; ++j) cout << " ";
                    gotoXY(PosX + 70 + 45 + (15 - sTot[CntPos - 1].size()) / 2, CntPos * 2 + 1); cout << sTot[CntPos - 1];
                    stringstream ss;
                    ss << sTot[CntPos - 1] << ' ';
                    ss >> Cur->scoreBoardSem[Cur->GetCourseID(CourseInfo)].Total;
                }
                CntPos++;
            }
            Cnt++;
        }

        if(Change != 0) {
            Page = (Page + Change + LimPage) % LimPage;
            SetColor(0);
            for(int i = (GetWidth() - TableWidth) / 2; i < (GetWidth() - TableWidth) / 2 + TableWidth; ++i) {
                for(int j = 3; j < 44; ++j) {
                    gotoXY(i , j);
                    cout << " ";
                }
            }
            Cnt = 1;
            int CntPos = 1;
            for(Student* Cur = StudentList; Cur; Cur = Cur->pNext) {
                if(!Cur->isEnrollCourse(CourseInfo)) continue;
                if(20 * Page + 21 <= Cnt) break;
                if(20 * Page + 1 <= Cnt) {
                    Cur->LoadScoreboardFromFile("Data/" + GetPath() + GetSemPath() + "Student/Score/" + Cur->getID() + ".txt");
                    Cur->ViewCourseScore(Cur->GetCourseID(CourseInfo), Cnt * 2 + 1, 2);
                    CntPos++;
                    SetBGColor(7); SetColor(0); cout << Cnt;
                }
                Cnt++;
            }
            SetColor(15);
            SetBGColor(0);
            gotoXY(GetWidth() / 2 - 4, 44); cout << "Page " << Page + 1 << "/" << LimPage;
        }
    }
}

void ChooseClass(NodeClass* ClassList, Course* CourseList, bool isViewStudent, Student*& StudentList, User*& UserList) {
    int ColSpace = 1;
    int TotButton = 3 + (!isViewStudent), BoxWidth = 40, ButtonHeight = 1;
    int BoxHeight = TotButton * ButtonHeight + (TotButton - 1) * ColSpace + 10;
    int ButtonWidth = BoxWidth - 10;
    int PosX = (GetWidth() - BoxWidth) / 2, PosY = 15;
    drawview(PosX, PosY, BoxWidth, BoxHeight, "Data/Staff/StaffLogo.txt", 56);
    gotoXY(PosX + 5, PosY + 2); SetBGColor(8); SetColor(0); cout << "Class name";
    gotoXY(PosX + 5, PosY + 3); SetBGColor(15); for(int i = 0; i < ButtonWidth; ++i) cout << " ";
    Button Button_1 = Button(PosX + 5, PosY + 3, ButtonWidth, ButtonHeight, "");

    Button Button_2;
    if(!isViewStudent) Button_2 = Button(PosX + 5, PosY + 5, ButtonWidth, ButtonHeight, "VIEW COURSES OF CLASS");
    else Button_2 = Button(PosX + 5, PosY + 5, ButtonWidth, ButtonHeight, "VIEW STUDENT OF CLASS");
    Button_2.DrawButton();

    gotoXY(PosX + 5, PosY + 7); SetBGColor(8); SetColor(0); cout << "Course ID";
    gotoXY(PosX + 5, PosY + 8); SetBGColor(15); for(int i = 0; i < ButtonWidth; ++i) cout << " ";
    Button Button_5 = Button(PosX + 5, PosY + 8, ButtonWidth, ButtonHeight, "");

    Button Button_6 = Button(PosX + 5, PosY + 10, ButtonWidth, ButtonHeight, "VIEW STUDENTS OF COURSE");
    Button_6.DrawButton();

    Button Button_3, Button_4;
    if(isViewStudent) Button_3 = Button(PosX + 5, PosY + 12, ButtonWidth, ButtonHeight, "BACK");
    else Button_3 = Button(PosX + 5, PosY + 12, ButtonWidth, ButtonHeight, "VIEW ALL COURSES");
    Button_3.DrawButton();

    if(!isViewStudent) {
        Button_4 = Button(PosX + 5, PosY + 14, ButtonWidth, ButtonHeight, "BACK");;
        Button_4.DrawButton();
    }

    string ClassName = "", CourseID = "";
    while(1) {
        gotoXY(0, 0);

        COORD MousePosition;
        while(!isLeftMousePressed(MousePosition));
        if(Button_1.isClick(MousePosition)) {
            gotoXY(PosX + 5 + ClassName.size(), PosY + 3);
            SetBGColor(15);
            SetColor(0);
            GetUserName(ClassName, ButtonWidth - 1);
        }
        else if(Button_5.isClick(MousePosition)) {
            gotoXY(PosX + 5 + CourseID.size(), PosY + 8);
            SetBGColor(15);
            SetColor(0);
            GetUserName(CourseID, ButtonWidth - 1);
        }
        else if(Button_6.isClick(MousePosition)) {
            Course* CourseInfo = FindCourse(CourseList, CourseID);
            if(CourseInfo) {
                SetBGColor(0);
                system("cls");
                ViewStudentInCourse(CourseInfo, StudentList);
                SetBGColor(0);
                system("cls");
                drawview(PosX, PosY, BoxWidth, BoxHeight, "Data/Staff/StaffLogo.txt", 56);
                gotoXY(PosX + 5, PosY + 2); SetBGColor(8); SetColor(0); cout << "Class name";
                gotoXY(PosX + 5, PosY + 3); SetBGColor(15); for(int i = 0; i < ButtonWidth; ++i) cout << " ";
                gotoXY(PosX + 5, PosY + 7); SetBGColor(8); SetColor(0); cout << "Course ID";
                gotoXY(PosX + 5, PosY + 8); SetBGColor(15); for(int i = 0; i < ButtonWidth; ++i) cout << " ";
                Button_2.DrawButton();
                Button_3.DrawButton();
                Button_6.DrawButton();
                if(!isViewStudent) Button_4.DrawButton();
                gotoXY(PosX + 5, PosY + 3); SetBGColor(15); SetColor(0); cout << ClassName;
                gotoXY(PosX + 5, PosY + 8); SetBGColor(15); SetColor(0); cout << CourseID;
            }
            else {
                SetBGColor(8);
                SetColor(0);
                gotoXY(PosX + 5, PosY + BoxHeight - 1); for(int i = 0; i < ButtonWidth; ++i) cout << " ";
                gotoXY(PosX + 5, PosY + BoxHeight - 1); cout << "Invalid course ID!";
            }
        }
        else if(Button_2.isClick(MousePosition)) {
            NodeClass* ClassInfo = FindClass(ClassList, ClassName);
            if(ClassInfo) {
                SetBGColor(0);
                system("cls");
                if(isViewStudent) ViewStudentInClass(ClassInfo, StudentList, UserList);
                else ViewCourseInClass(ClassInfo, CourseList);
                SetBGColor(0);
                system("cls");
                drawview(PosX, PosY, BoxWidth, BoxHeight, "Data/Staff/StaffLogo.txt", 56);
                gotoXY(PosX + 5, PosY + 2); SetBGColor(8); SetColor(0); cout << "Class name";
                gotoXY(PosX + 5, PosY + 3); SetBGColor(15); for(int i = 0; i < ButtonWidth; ++i) cout << " ";
                gotoXY(PosX + 5, PosY + 7); SetBGColor(8); SetColor(0); cout << "Course ID";
                gotoXY(PosX + 5, PosY + 8); SetBGColor(15); for(int i = 0; i < ButtonWidth; ++i) cout << " ";
                Button_2.DrawButton();
                Button_3.DrawButton();
                Button_6.DrawButton();
                if(!isViewStudent) Button_4.DrawButton();
                gotoXY(PosX + 5, PosY + 3); SetBGColor(15); SetColor(0); cout << ClassName;
                gotoXY(PosX + 5, PosY + 8); SetBGColor(15); SetColor(0); cout << CourseID;
            }
            else {
                SetBGColor(8);
                SetColor(0);
                gotoXY(PosX + 5, PosY + BoxHeight - 1); for(int i = 0; i < ButtonWidth; ++i) cout << " ";
                gotoXY(PosX + 5, PosY + BoxHeight - 1); cout << "Invalid class name!";
            }
        }
        else if(Button_3.isClick(MousePosition)) {
            if(isViewStudent) {
                SetBGColor(0);
                system("cls");
                return;
            }
            else {
                SetBGColor(0);
                system("cls");
                NodeClass* DumClass = new NodeClass;
                DumClass->className = "CourseData";
                ViewCourseInClass(DumClass, CourseList);
                delete DumClass;
                SetBGColor(0);
                system("cls");
                drawview(PosX, PosY, BoxWidth, BoxHeight, "Data/Staff/StaffLogo.txt", 56);
                gotoXY(PosX + 5, PosY + 2); SetBGColor(8); SetColor(0); cout << "Class name";
                gotoXY(PosX + 5, PosY + 3); SetBGColor(15); for(int i = 0; i < ButtonWidth; ++i) cout << " ";
                gotoXY(PosX + 5, PosY + 7); SetBGColor(8); SetColor(0); cout << "Course ID";
                gotoXY(PosX + 5, PosY + 8); SetBGColor(15); for(int i = 0; i < ButtonWidth; ++i) cout << " ";
                Button_2.DrawButton();
                Button_3.DrawButton();
                Button_6.DrawButton();
                if(!isViewStudent) Button_4.DrawButton();
                gotoXY(PosX + 5, PosY + 3); SetBGColor(15); SetColor(0); cout << ClassName;
                gotoXY(PosX + 5, PosY + 8); SetBGColor(15); SetColor(0); cout << CourseID;
            }
        }
        else if(!isViewStudent) {
            if(Button_4.isClick(MousePosition)) {
                SetBGColor(0);
                system("cls");
                return;
            }
        }
    }
}

void ViewCourseInClass(NodeClass* ClassInfo, Course* CourseList) {
    Course* ClassCourseList = nullptr;
    InputCourse(ClassCourseList, "Data/" + GetPath() + GetSemPath() + "Course/" + ClassInfo->className + ".txt");
    int PosX = (GetWidth() - 142) / 2, PosY = 3;
    ViewListCourseTable(ClassCourseList, PosX, PosY);
    SetBGColor(8);
    for(int k = 1; k < 4; ++k) {
        for(int u = 0; u < 8; ++u) {
            gotoXY(134 + PosX + u, k + PosY);
            cout << " ";
        }
    }
    gotoXY(134 + PosX + 1, PosY + 2);
    cout << "Option";

    Button* DumButton = new Button;
    Button* ButtonList = DumButton;
    int i = 0;
    for(Course* Cur = ClassCourseList; Cur; Cur = Cur->pNext) {
        ButtonList->pNext = new Button(134 + PosX, (i + 1) * 5 + PosY, 4, 4, "X");
        ButtonList = ButtonList->pNext;
        ButtonList->DrawButtonTable();
        ButtonList->pNext = new Button(134 + PosX + 4, (i + 1) * 5 + PosY, 4, 4, "@");
        ButtonList = ButtonList->pNext;
        ButtonList->DrawButtonTable();
        i++;
    }
    ButtonList = DumButton->pNext;
    delete DumButton;

    Button AddButton = Button(134 + PosX, (i + 1) * 5 + PosY, 8, 4, "+");
    AddButton.DrawButtonTable();
    Button QuitButton = Button(134 + PosX + 7, PosY - 1, 1, 1, "X");
    QuitButton.DrawButton();
    gotoXY(0, 0);

    SetBGColor(7);
    while(1) {
        COORD MousePosition;
        while(!isLeftMousePressed(MousePosition));
        bool isOk = false;

        if(QuitButton.isClick(MousePosition)) {
            Button* CurButton = ButtonList;
            for(Course* CurCourse = ClassCourseList; CurCourse;) {
                Course* DelCourse = CurCourse;
                Button* DelButton = CurButton;
                CurCourse = CurCourse->pNext, CurButton = CurButton->pNext;
                delete DelCourse;
                delete DelButton;
            }
            return;
        }
        if(AddButton.isClick(MousePosition)) {
            SetBGColor(0);
            system("cls");
            CourseOption(CourseList, ClassInfo);
            isOk = true;
        }
        else {
            Button* CurButton = ButtonList;
            for(Course* CurCourse = ClassCourseList; CurCourse; CurCourse = CurCourse->pNext, CurButton = CurButton->pNext) {
                if(CurButton->isClick(MousePosition)) {
                    deleteCourseForClass(ClassInfo, ClassCourseList, CurCourse);
                    SetBGColor(0);
                    system("cls");
                    isOk = true;
                    break;
                }
                CurButton = CurButton->pNext;
                if(CurButton->isClick(MousePosition)) {
                    CurCourse->FixCourseWindow();
                    LoadCourseToFile(ClassCourseList, "Data/" + GetPath() + GetSemPath() + "Course/" + ClassInfo->className + ".txt");
                    isOk = true;
                    break;
                }
            }
        }
        if(isOk) break;
    }
    Button* CurButton = ButtonList;
    for(Course* CurCourse = ClassCourseList; CurCourse;) {
        Course* DelCourse = CurCourse;
        Button* DelButton = CurButton;
        CurCourse = CurCourse->pNext, CurButton = CurButton->pNext;
        delete DelCourse;
        delete DelButton;
        DelButton = CurButton;
        CurButton = CurButton->pNext;
        delete DelButton;
    }
    gotoXY(0, 0);
    ViewCourseInClass(ClassInfo, CourseList);
}

void SetEnrollDate() {
    timeStart registDate;
    ifstream fin("Data/" + GetPath() + GetSemPath() + "Course/EnrollDate.txt");
    fin >> registDate.check;
    if(registDate.check) {
        fin >> registDate.ngay.day >> registDate.ngay.month >> registDate.ngay.year;
        fin >> registDate.End.day >> registDate.End.month >> registDate.End.year;
    }
    fin.close();

    int ColSpace = 1;
    int TotButton = 3, BoxWidth = 40, ButtonHeight = 1;
    int BoxHeight = TotButton * ButtonHeight + (TotButton - 1) * ColSpace + 8;
    int ButtonWidth = BoxWidth - 10;
    int PosX = (GetWidth() - BoxWidth) / 2, PosY = 15;
    drawview(PosX, PosY, BoxWidth, BoxHeight, "Data/Staff/StaffLogo.txt", 56);
    gotoXY(PosX + 5, PosY + 2); SetBGColor(8); SetColor(0); cout << "Start date";
    gotoXY(PosX + 5, PosY + 3);
    SetBGColor(15); for(int i = 0; i < 3; ++i) cout << " ";
    SetBGColor(8); cout << " / ";
    SetBGColor(15); for(int i = 0; i < 3; ++i) cout << " ";
    SetBGColor(8); cout << " / ";
    SetBGColor(15); for(int i = 0; i < 6; ++i) cout << " ";
    Button Button_Day = Button(PosX + 5, PosY + 3, 3, ButtonHeight, "");
    Button Button_Month = Button(PosX + 11, PosY + 3, 3, ButtonHeight, "");
    Button Button_Year = Button(PosX + 17, PosY + 3, 6, ButtonHeight, "");

    gotoXY(PosX + 5, PosY + 5); SetBGColor(8); SetColor(0); cout << "End date";
    gotoXY(PosX + 5, PosY + 6);
    SetBGColor(15); for(int i = 0; i < 3; ++i) cout << " ";
    SetBGColor(8); cout << " / ";
    SetBGColor(15); for(int i = 0; i < 3; ++i) cout << " ";
    SetBGColor(8); cout << " / ";
    SetBGColor(15); for(int i = 0; i < 6; ++i) cout << " ";
    Button Button_EDay = Button(PosX + 5, PosY + 6, 3, ButtonHeight, "");
    Button Button_EMonth = Button(PosX + 11, PosY + 6, 3, ButtonHeight, "");
    Button Button_EYear = Button(PosX + 17, PosY + 6, 6, ButtonHeight, "");

    string strButton_2 = registDate.check ? "CLOSE REGISTRATION" : "OPEN REGISTRATION";
    Button Button_2 = Button(PosX + 5, PosY + 8, ButtonWidth, ButtonHeight, strButton_2);
    Button_2.DrawButton();

    Button Button_3 = Button(PosX + 5, PosY + 10, ButtonWidth, ButtonHeight, "BACK");
    Button_3.DrawButton();
    string strDay = "", strMonth = "", strYear = "";
    string strEDay = "", strEMonth = "", strEYear = "";
    if(registDate.check) {
        stringstream ss;
        ss << registDate.ngay.day << ' ' << registDate.ngay.month << ' ' << registDate.ngay.year << ' ';
        ss << registDate.End.day << ' ' << registDate.End.month << ' ' << registDate.End.year << ' ';
        ss >> strDay >> strMonth >> strYear >> strEDay >> strEMonth >> strEYear;
        SetBGColor(8);
        SetColor(0);
        gotoXY(PosX + 5, PosY + 3); cout << strDay << " / "  << strMonth << " / " << strYear << "      ";
        gotoXY(PosX + 5, PosY + 6); cout << strEDay << " / "  << strEMonth << " / " << strEYear << "      ";
    }
    while(1) {
        gotoXY(0, 0);

        COORD MousePosition;
        while(!isLeftMousePressed(MousePosition));
        SetBGColor(15);
        SetColor(0);
        if(!registDate.check) {
            if(Button_Day.isClick(MousePosition)) {
                gotoXY(PosX + 5 + strDay.size(), PosY + 3);
                GetUserName(strDay, 2);
            }
            else if(Button_Month.isClick(MousePosition)) {
                gotoXY(PosX + 11 + strMonth.size(), PosY + 3);
                GetUserName(strMonth, 2);
            }
            else if(Button_Year.isClick(MousePosition)) {
                gotoXY(PosX + 17 + strYear.size(), PosY + 3);
                GetUserName(strYear, 5);
            }
            else if(Button_EDay.isClick(MousePosition)) {
                gotoXY(PosX + 5 + strEDay.size(), PosY + 6);
                GetUserName(strEDay, 2);
            }
            else if(Button_EMonth.isClick(MousePosition)) {
                gotoXY(PosX + 11 + strEMonth.size(), PosY + 6);
                GetUserName(strEMonth, 2);
            }
            else if(Button_EYear.isClick(MousePosition)) {
                gotoXY(PosX + 17 + strEYear.size(), PosY + 6);
                GetUserName(strEYear, 5);
            }
        }
        if(Button_2.isClick(MousePosition)) {
            if(registDate.check) {
                ofstream fout("Data/" + GetPath() + GetSemPath() + "Course/EnrollDate.txt");
                fout << 0;
                fout.close();
                OpenorCloseRegist(registDate);
                return;
            }
            else {
                stringstream ss;
                timeStart Tem;
                ss << strDay << ' ' << strMonth << ' ' << strYear << ' ' << strEDay << ' ' << strEMonth << ' ' << strEYear << ' ';
                ss >> Tem.ngay.day >> Tem.ngay.month >> Tem.ngay.year >> Tem.End.day >> Tem.End.month >> Tem.End.year;
                if(!checkSyntaxDate(Tem.ngay) || !checkSyntaxDate(Tem.End) || DateToInt(Tem.ngay) > DateToInt(Tem.End)) {
                    gotoXY(PosX + 5, PosY + BoxHeight - 1);
                    SetBGColor(8);
                    cout << "Invalid dates!";
                    SetBGColor(15);
                }
                else {
                    ofstream fout("Data/" + GetPath() + GetSemPath() + "Course/EnrollDate.txt");
                    fout << 1 << ' ' << strDay << ' ' << strMonth << ' ' << strYear << ' ';
                    fout << strEDay << ' ' << strEMonth << ' ' << strEYear;
                    fout.close();
                    OpenorCloseRegist(registDate);
                    return;
                }
            }
        }
        else if(Button_3.isClick(MousePosition)) {
            SetBGColor(0);
            system("cls");
            return;
        }
    }
}

void SettingWindow(ListYear*& YearList, ListSem*& SemList, NodeClass*& ClassList, Student*& StudentList, Course*& CourseList, User*& UserList) {
    int ColSpace = 1;
    int TotButton = 4, BoxWidth = 40, ButtonHeight = 1;
    int BoxHeight = TotButton * ButtonHeight + (TotButton - 1) * ColSpace + 4;
    int ButtonWidth = BoxWidth - 10;
    int PosX = (GetWidth() - BoxWidth) / 2, PosY = 15;
    drawview(PosX, PosY, BoxWidth, BoxHeight, "Data/Staff/StaffLogo.txt", 56);
    while(1) {
        Button Button_1 = Button(PosX + 5, PosY + 2, ButtonWidth, ButtonHeight, "SET SCHOOLYEAR");
        Button_1.DrawButton();

        Button Button_2 = Button(PosX + 5, PosY + 4, ButtonWidth, ButtonHeight, "SET SEMESTER");
        Button_2.DrawButton();

        Button Button_3 = Button(PosX + 5, PosY + 6, ButtonWidth, ButtonHeight, "SET ENROLL DATE");
        Button_3.DrawButton();

        Button Button_4 = Button(PosX + 5, PosY + 8, ButtonWidth, ButtonHeight, "BACK");
        Button_4.DrawButton();

        gotoXY(0, 0);

        COORD MousePosition;
        while(!isLeftMousePressed(MousePosition));
        if(Button_1.isClick(MousePosition)) {
            system("cls");
            SetYearOption(YearList);
            SetBGColor(0);
            system("cls");
            drawview(PosX, PosY, BoxWidth, BoxHeight, "Data/Staff/StaffLogo.txt", 56);
        }
        else if(Button_2.isClick(MousePosition)) {
            system("cls");
            SetSemWindow(YearList->pTail);
            SetBGColor(0);
            system("cls");
            drawview(PosX, PosY, BoxWidth, BoxHeight, "Data/Staff/StaffLogo.txt", 56);
        }
        else if(Button_3.isClick(MousePosition)) {
            system("cls");
            SetEnrollDate();
            SetBGColor(0);
            system("cls");
            drawview(PosX, PosY, BoxWidth, BoxHeight, "Data/Staff/StaffLogo.txt", 56);
        }
        else if(Button_4.isClick(MousePosition)) {
            SetBGColor(0);
            system("cls");
            break;
        }
    }
    /// Deallocate CourseList, StudentList, UserList, ClassList before these steps
    CourseList = nullptr;
    ClassList = nullptr;
    CreateListClass(ClassList, StudentList);
    InputCourse(CourseList, "Data/" + GetPath() + GetSemPath() + "Course/CourseData.txt");

//    StudentList = nullptr;
//    Cur
//    InputStudent(StudentList, UserList);
}

void UpdateStaffToFile(Staff* StaffList) {
    ofstream fout("Data/Staff/StaffData.txt");
    for(Staff* CurStaff = StaffList; CurStaff; CurStaff = CurStaff->pNext) {
        fout << CurStaff->ID << "," << CurStaff->passWord << "," << CurStaff->lastName << "," << CurStaff->firstName << "," << CurStaff->SocialID << "," << CurStaff->gender << "," << CurStaff->DOB.StrDOB << "," << '\n';
    }
    fout.close();
}

//Add Sound

void successSound()
{
    PlaySound(TEXT("hello.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void FailSound()
{
    PlaySound(TEXT("SystemStart"), NULL, SND_FILENAME | SND_ASYNC);
}
