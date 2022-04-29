#include "CourseFunction.h"

void Course::RemoveStudentFromCourse(string StudentId) {
    ListID* DumStudent = new ListID;
    DumStudent->pNext = StudentList;
    for(ListID* Cur = DumStudent; Cur && Cur->pNext; Cur = Cur->pNext) {
        if(Cur->pNext->ID == StudentId) {
            ListID* DelStudent = Cur->pNext;
            Cur->pNext = Cur->pNext->pNext;
            delete DelStudent;
            StudentList = DumStudent->pNext;
            delete DumStudent;
            return;
        }
    }
    delete DumStudent;
}

void Course::ViewCourseTable(bool isExist, int Num, int PosX, int PosY) {
    int ListLen[7] = {3, 21, 37, 8, 20, 37, 8};
    for(int i = 0; i < 7; ++i) {
        if(i % 2 == 0) SetBGColor(7);
        else SetBGColor(8);

        for(int k = 0; k < 4; ++k) {
            for(int u = 0; u < ListLen[i]; ++u) {
                gotoXY(PosX + u, k + PosY);
                cout << " ";
            }
        }

        if(i == 0) {
            gotoXY(PosX + 1, PosY + 1);
            cout << Num;
        }

        if(isExist) {
            switch(i) {
            case 0:
                break;
            case 1:
                gotoXY(PosX + (ListLen[i] - ID.size()) / 2, PosY + 1);
                cout << ID;
                break;
            case 2:
                gotoXY(PosX + (ListLen[i] - courseName.size()) / 2, PosY + 1);
                cout << courseName;
                break;
            case 3:
                gotoXY(PosX + (ListLen[i] - 1) / 2, PosY + 1);
                cout << numCredits;
                break;
            case 4:
                for(int j = 0; j < 2; ++j)
                {
                    gotoXY(PosX + (ListLen[i] - 13) / 2, PosY + j + 1);
                    cout << "T" << date[j] / 4 + 2 << " ";
                    switch (date[j] % 4) {
                    case 0:
                        cout << "7:30-9:10";
                        break;
                    case 1:
                        cout << "9:30-11:10";
                        break;
                    case 2:
                        cout << "13:30-15:10";
                        break;
                    case 3:
                        cout << "15:30-17:10";
                        break;
                    default:
                        break;
                    }
                }
                break;
            case 5:
                gotoXY(PosX + (ListLen[i] - teacherName.size()) / 2, PosY + 1);
                cout << teacherName;
                break;
            case 6:
                gotoXY(PosX + (ListLen[i] - 2) / 2, PosY + 1);
                cout << maxStudent - numStudent;
                break;
            default:
                break;
            }
        }

        PosX += ListLen[i];
    }
    SetBGColor(0);
}

Course* FindCourse(Course* CourseList, string CourseID) {
    for(Course* Cur = CourseList; Cur; Cur = Cur->pNext) {
        if(Cur->ID == CourseID) {
            return Cur;
        }
    }
    return nullptr;
}

void InputCourse(Course*& CourseList, string Directory) {
    ifstream fin(Directory);
    Course* DumCourse = new Course;
    DumCourse->pNext = nullptr;
    CourseList = DumCourse;
    if (!fin.is_open())
    {
        CourseList = DumCourse->pNext;
        delete DumCourse;
        fin.close();
        return;
    }
    while(!fin.eof()) {
        CourseList->pNext = new Course;

        getline(fin, CourseList->pNext->ID, ',');

        if(CourseList->pNext->ID == "") {
            delete CourseList->pNext;
            CourseList->pNext = nullptr;
            break;
        }

        getline(fin, CourseList->pNext->courseName, ',');

        getline(fin, CourseList->pNext->teacherName, ',');

        fin >> CourseList->pNext->numCredits;
        fin.get();

        fin >> CourseList->pNext->maxStudent;
        fin.get();

        fin >> CourseList->pNext->numStudent;
        fin.get();

        for(int i = 0; i < 2; ++i) {
            int Day, Session;
            fin >> Day;
            fin.get();
            fin >> Session;
            fin.get();
            CourseList->pNext->date[i] = (Day - 2) * 4 + Session - 1;
        }
        CourseList = CourseList->pNext;
        fin.get();
    }
    CourseList = DumCourse->pNext;
    delete DumCourse;
    fin.close();
}

void OutputCourse(Course* CourseList, string Directory) {
    ofstream fout(Directory);
    for(Course* CourseInfo = CourseList; CourseInfo; CourseInfo = CourseInfo->pNext) {
        fout << CourseInfo->ID << ',';

        fout << CourseInfo->courseName << ',';

        fout << CourseInfo->teacherName << ',';

        fout << CourseInfo->numCredits << ',';

        fout << CourseInfo->maxStudent << ',';

        fout << CourseInfo->numStudent << ',';

        fout << CourseInfo->date[0] / 4 + 2 << ',' << CourseInfo->date[0] % 4 + 1 << ',';

        fout << CourseInfo->date[1] / 4 + 2 << ',' << CourseInfo->date[1] % 4 + 1 << ',';

        fout << '\n';
    }
    fout.close();
}

void LoadCourseToFile(Course* CourseList, string location)
{
    ofstream fout(location);
    while (CourseList)
    {
        fout << CourseList->ID << ',';
        fout << CourseList->courseName << ',';
        fout << CourseList->teacherName << ',';
        fout << CourseList->numCredits << ',';
        fout << CourseList->maxStudent << ',';
        fout << CourseList->numStudent << ',';
        fout << CourseList->date[0] / 4 + 2 << ',';
        fout << CourseList->date[0] % 4 + 1 << ',';
        fout << CourseList->date[1] / 4 + 2 << ',';
        fout << CourseList->date[1] % 4 + 1 << ',';
        fout << '\n';
        CourseList = CourseList->pNext;
    }
    fout.close();
}

/// Load course list from text file
void loadListofCourses(Course*& currentSubHead)
{
//	helpStaffInputSynax();
//	cout << "Input with syntax (K-year-require-faculty)" << endl;
//	cout << "Example: K-21-AGAIN-IT" << endl;
//	string khoa;
//	getline(cin, khoa, '\n');
//	khoa = khoa + ".txt";
//	ifstream fin;
//	fin.open(khoa);
//	Course* curr = nullptr;
//    if (!fin.is_open())
//    {
//        cout << "Error opening the file!!!";
//        return;
//    }
//
//	while(!fin.eof())
//	{
//		if (!currentSubHead)
//		{
//			currentSubHead = new Course;
//			curr = currentSubHead;
//		}
//		else
//		{
//			curr->pNext = new Course;
//			curr = curr->pNext;
//		}
//		getline(fin, curr->ID, '\n');
//		getline(fin, curr->courseName, '\n');
//		fin >> curr->numCredits;
//		fin >> curr->date[0];
//		fin >> curr->date[1];
//		fin >> curr->maxStudent;
//		fin >> curr->numStudent;
//		getline(fin, curr->teacherName, '\n');
//	}
//	curr->pNext = nullptr;
//	fin.close();
}

bool deleteCourseChoose(string input, Course*& currentSubHead)
{
	Course* curr = currentSubHead;
	if (curr->ID == input)
	{
        currentSubHead = curr->pNext;
		delete curr;
		return true;
	}
	while (curr->pNext)
	{
		if (curr->pNext->ID == input)
		{
			Course* here = curr->pNext;
			curr->pNext = here->pNext;
			delete here;
			return true;
		}
	}
	return false;
}
void loadDanhSachMonForStaff(Course*& currentSubHead, string& location)
{
//	helpStaffInputSynax();
//	cout << "Input with syntax (K-year-require-faculty)" << endl;
//	cout << "Example: K-21-AGAIN-IT" << endl;
//	string khoa;
//	getline(cin, khoa, '\n');
//	khoa = khoa + ".txt";
//	location = khoa;
//	ifstream fin;
//	fin.open(khoa);
//    if (!fin.is_open())
//    {
//        cout << "Error opening the file!!!";
//        return;
//    }
//	Course* curr = nullptr;
//	while (!fin.eof())
//	{
//		if (!currentSubHead)
//		{
//			currentSubHead = new Course;
//			curr = currentSubHead;
//		}
//		else
//		{
//			curr->pNext = new Course;
//			curr = curr->pNext;
//		}
//		getline(fin, curr->ID, '\n');
//		getline(fin, curr->courseName, '\n');
//		fin >> curr->numCredits;
//		fin >> curr->date[0];
//		fin >> curr->date[1];
//		fin >> curr->maxStudent;
//		fin >> curr->numStudent;
//		getline(fin, curr->teacherName, '\n');
//	}
//	curr->pNext = nullptr;
//	fin.close();
}

void LoadDanhSachToTxT(Course*& currentSubHead, string location)
{
//	ofstream fout;
//	fout.open(location);
//	while (currentSubHead)
//	{
//		Course* here = currentSubHead;
//		currentSubHead = currentSubHead->pNext;
//		fout << here->ID << endl;
//		fout << here->courseName << endl;
//		fout << here->numCredits << endl;
//		fout << here->date[0] << endl;
//		fout << here->date[1] << endl;
//		fout << here->maxStudent << endl;
//		fout << here->numStudent;
//		fout << here->teacherName << endl;
//		delete here;
//	}
//	fout.close();
}

void ViewListCourseTable(Course* CourseList, int PosX, int PosY) {
    SetColor(0);
    int ListLen[7] = {3, 21, 37, 8, 20, 37, 8};
    string ListTitle[7] = {"#", "Course ID", "Course Name", "Credit", "Date", "Teacher", "Remain"};
    int Cur = PosX;
    for(int i = 0; i < 7; ++i) {
        if(i % 2 == 0) SetBGColor(7);
        else SetBGColor(8);

        for(int k = 1; k < 4; ++k) {
            for(int u = 0; u < ListLen[i]; ++u) {
                gotoXY(Cur + u, k + PosY);
                cout << " ";
            }
        }
        gotoXY(Cur + (ListLen[i] - ListTitle[i].size()) / 2, PosY + 2);
        cout << ListTitle[i];
        Cur += ListLen[i];
    }

    int i = 0;
    for(Course* Cur = CourseList; Cur; Cur = Cur->pNext) {
        Cur->ViewCourseTable(1, i + 1, PosX, (i + 1) * 5 + PosY);
        i++;
    }
    gotoXY(0, 0);
}

void Course::freeStudentList()
{
    while (this->StudentList)
    {
        ListID* here = this->StudentList;
        this->StudentList = this->StudentList->pNext;
        delete here;
    }
}

void Course::RewriteInforOfCourse(Course* inputCourseNew)
{
    this->ID = inputCourseNew->ID;
    this->courseName = inputCourseNew->courseName;
    this->teacherName = inputCourseNew->teacherName;
    this->numCredits = inputCourseNew->numCredits;
    this->date[0] = inputCourseNew->date[0];
    this->date[1] = inputCourseNew->date[1];
    this->numStudent = inputCourseNew->numStudent;
    this->maxStudent = inputCourseNew->maxStudent;
    this->CourseStart = inputCourseNew->CourseStart;
    this->CourseEnd = inputCourseNew->CourseEnd;
    this->freeStudentList();
    this->StudentList = inputCourseNew->StudentList;
    this->pNext = inputCourseNew->pNext;
}

void Course::ExportListStudent(string Dir) {
    ofstream fout;
    fout.open(Dir);

    int no=1;
    fout << "#,Student ID,Student name\n";
    for(ListID *cur=StudentList; cur; cur=cur->pNext)
        fout << no++ << ',' << cur->ID << ',' << cur->fullName << '\n';
    fout.close();
}

// task 22
// incomplete
// still inefficient (have to traverse the list of every single student to check)
// can be improved if can track down the year the student belongs to (maybe?)
bool ImportScoreboardCSV(Course*& CourseList, string &CourseID, Student *StudentList, string Dir) {
    Course* course=FindCourse(CourseList, CourseID);
    if(!course) return false;

    ifstream fin;
    fin.open(Dir);
    if(!fin) return false;

    string temp, line;
    while(fin >> temp) {
        string word[6];

        getline(fin, line);
        stringstream ss(line);

        int pos=0;
        while(getline(ss, word[pos], ',')) ++pos;

        // Find student in the whole student list of the data
        Student *curStudent=FindStudent(StudentList, word[1]);

        // Found the student -> save the score
        if(curStudent && curStudent->getID()==word[1] && curStudent->fullName()==word[2]) {
            Course *SubRegis=curStudent->getRegCourse();
            for(int pos=0; pos<curStudent->getNumCourses(); ++pos) {
                if(SubRegis[pos].ID==course->getID()) {
                    // not so sure if this work...
                    // if works, it's supposed to save the score
                    double Total, Final, Midterm, Other;
                    stringstream ss;
                    ss << word[3];
                    ss >> Total;

                    ss << word[4];
                    ss >> Final;

                    ss << word[5];
                    ss >> Midterm;

                    ss << word[6];
                    ss >> Other;

                    curStudent->setScore(pos, Total, Final, Midterm, Other);
                    break;
                }
            }
        }
    }

    fin.close();
    return true;
}

void Course::ExportListStudentWindow() {
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

    Button Button_2 = Button(PosX + 5, PosY + 5, ButtonWidth, ButtonHeight, "EXPORT");
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
            ExportListStudent(Dir);
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
