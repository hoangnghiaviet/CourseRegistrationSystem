#include "User.h"

User* FindUser(User* UserList, string UserName, bool Mode) {
    for(User* Cur = UserList; Cur; Cur = Cur->pNext) {
        if(Cur->getUserName() == UserName && Cur->getMode() == Mode) {
            return Cur;
        }
    }
    return nullptr;
}

void GetPassWord(string& PassWord) {
    char ch = _getch();
    while(ch != 13) {
        if(ch == 8) {
            if(PassWord != "") {
                PassWord.pop_back();
                int x = whereX(), y = whereY();
                gotoXY(x - 1, y);
                cout << " ";
                gotoXY(x - 1, y);
            }
        }
        else {
            if(PassWord.size() < 29) {
                PassWord += ch;
                cout << "*";
            }
        }
        ch = _getch();
    }
    gotoXY(0, 0);
}


void User::changePassWord(User& Anon) {
    int num_inputs = 0;    //Variable to count the number of inputs
    string current_password;
    string new_password;
    string confirm_password;
    cout << "Enter current password: ";
    cout << "Enter new passowrd: ";
    cout << "Confirm new password: ";

    cin >> current_password;
    cin >> new_password;
    cin >> confirm_password;
    while ((current_password != Anon.getPassWord()) && (new_password != confirm_password) && (num_inputs <= 10))
    {
        cout << "Invalid password!!!\n";
        cout << "Warning: Entering wrong password more than 10 times";
        cout << " leads to permanent system lock\n";
        cout << "Enter current password: ";
        cout << "Enter new passowrd: ";
        cout << "Confirm new password: ";
    }

    Anon.setPassWord(new_password);
}

//void GetUserName(string& UserName, int Limit) {
//    char ch = _getch();
//    while (ch != 13) {
//        if (ch == 8) {
//            if (UserName != "") {
//                UserName.pop_back();
//                int x = whereX(), y = whereY();
//                gotoXY(x - 1, y);
//                cout << " ";
//                gotoXY(x - 1, y);
//            }
//        }
//        else {
//            if (UserName.size() < Limit) {
//                UserName += ch;
//                cout << ch;
//            }
//        }
//        ch = _getch();
//    }
//    gotoXY(0, 0);
//}
void GetUserName(string& UserName, int Limit) {
    if(UserName.size() > Limit) {
        int x = whereX() - UserName.size() + Limit, y = whereY();
        gotoXY(x, y);
    }
    char ch = _getch();
    while (ch != 13) {
        if (ch == 8) {
            if (UserName != "") {
                UserName.pop_back();
                if(UserName.size() < Limit) {
                    int x = whereX(), y = whereY();
                    gotoXY(x - 1, y);
                    cout << " ";
                    gotoXY(x - 1, y);
                }
                else {
                    int x = whereX() - Limit, y = whereY();
                    gotoXY(x, y);
                    for(int i = UserName.size() - Limit; i < UserName.size(); ++i) cout << UserName[i];
                }
            }
        }
        else {
            UserName += ch;
            if (UserName.size() <= Limit) {
                cout << ch;
            }
            else {
                int x = whereX() - Limit, y = whereY();
                gotoXY(x, y);
                for(int i = UserName.size() - Limit; i < UserName.size(); ++i) cout << UserName[i];
            }
        }
        ch = _getch();
    }
    gotoXY(0, 0);
}

/// Task 12
void LogIn(User* UserList, User*& UserInfo, bool Mode) {
    string UserName = "", PassWord = "";
    UserInfo = nullptr;
    int PosY = 15;
    DrawLoginWindow(PosY);
    Button UserNameButton = Button(GetWidth() / 2 - 12, PosY + 6, 30, 1, "");
    Button PassWordButton = Button(GetWidth() / 2 - 12, PosY + 10, 30, 1, "");
    Button LoginButton = Button(GetWidth() / 2 - 5, PosY + 12, 5, 1, "");
    Button BackButton = Button(GetWidth() / 2 + 4, PosY + 12, 4, 1, "");
    gotoXY(0, 0);
    int Click = -1;
    while(1) {
        COORD MousePosition;
        while(!isLeftMousePressed(MousePosition));
        if(UserNameButton.isClick(MousePosition)) {
            Click = 0;
        }
        else if(PassWordButton.isClick(MousePosition)) {
            Click = 1;
        }
        else if(LoginButton.isClick(MousePosition)) {
            Click = 2;
        }
        else if(BackButton.isClick(MousePosition)) {
            Click = 3;
        }
        else Click = -1;

        if(Click == 0) {
            gotoXY(GetWidth() / 2 - 12 + UserName.size(), PosY + 6);
            GetUserName(UserName, 29);
            Click = 1;
        }
        if(Click == 1) {
            gotoXY(GetWidth() / 2 - 12 + PassWord.size(), PosY + 10);
            GetPassWord(PassWord);
        }
        else if(Click == 2) {
            UserInfo = FindUser(UserList, UserName, Mode);
            if(!UserInfo || !UserInfo->loginSuccess(UserName, PassWord)) {
                UserInfo = nullptr;
                gotoXY(GetWidth() / 2 - 13, PosY + 15);
                cout << "Incorrect user name or password!";
                gotoXY(GetWidth() / 2 - 12, PosY + 6);
                for(int i = 0; i < 30; ++i) cout << " ";
                gotoXY(GetWidth() / 2 - 12, PosY + 10);
                for(int i = 0; i < 30; ++i) cout << " ";
                UserName = "";
                PassWord = "";
            }
            else {
                SetBGColor(0);
                system("cls");
                return;
            }
        }
        else if(Click == 3) {
            SetBGColor(0);
            system("cls");
            return;
        }
    }
    return;
}

/// Draw log in window
void DrawLoginWindow(int PosY) {
    ifstream fin("Data/Graphic/LoginBg.txt");
    TextColor(4);
    for(int i = 0; i < 10; ++i) {
        gotoXY(GetWidth() / 2 - 59, i + 3);
        string S;
        getline(fin, S);
        for(int j = 0; j < S.size(); ++j) {
            if(S[j] == '*') cout << char(219);
            if(S[j] == ' ') cout << ' ';
        }
        cout << '\n';
    }
    fin.close();
    SetBGColor(7);

    for (int i = 0; i < 18; i++)
    {
        for (int j = 0; j < 60; j++)
        {
            gotoXY(GetWidth() / 2 - 29 + j, PosY + i);
            cout << " ";
        }
    }
    SetBGColor(8);
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            gotoXY(GetWidth() / 2 - 24 + j, PosY + 4 + i);
            cout << " ";
        }
    }
    SetBGColor(0);
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            gotoXY(GetWidth() / 2 - 24 + j, PosY + 3 + i);
            cout << " ";
        }
    }
    gotoXY(GetWidth() / 2 - 5, PosY + 4);
    SetBGColor(0);
    SetColor(15);
    cout << "HCMUS - LOGIN";
    gotoXY(GetWidth() / 2 - 23, PosY + 6);
    SetBGColor(8);
    SetColor(0);
    cout << "Username:";
    gotoXY(GetWidth() / 2 - 23, PosY + 10);
    cout << "Password:";
    for (int i = 0; i < 30; i++)
    {
        SetBGColor(15);
        gotoXY(GetWidth() / 2 - 12 + i, PosY + 6);
        cout << " ";
    }
    for (int i = 0; i < 30; i++)
    {
        SetBGColor(15);
        gotoXY(GetWidth() / 2 - 12 + i, PosY + 10);
        cout << " ";
    }
    SetColor(12);
    gotoXY(GetWidth() / 2 - 5, PosY + 12);
    cout << "LOGIN";
    gotoXY(GetWidth() / 2 + 4, PosY + 12);
    cout << "BACK";
    SetColor(0);
}
//draw mode
void DrawRecUpgrade(int X, int Y, int Width, int Height, int t) {
    TextColor(t);
    gotoXY(X, Y);
    for (int i = 0; i < Width; ++i) cout << char(219);
    gotoXY(X, Y + Height - 1);
    for (int i = 0; i < Width; ++i) cout << char(219);
    for (int i = 0; i < Height; ++i) {
        gotoXY(X, Y + i);
        cout << char(219);
        gotoXY(X + Width - 1, Y + i);
        cout << char(219);
    }
    TextColor(15);
}
void printINfor()
{
    TextColor(7);
    gotoXY(68, 34);
    cout << "COPYRIGHT 2022 BY TEAM 1" << endl;
    gotoXY(68, 36);
    cout << "CONTACT WITH: 0002343423" << endl;
    gotoXY(71, 38);
    cout << "DESIGNED BY TEAM 1" << endl;
}
void drawMode1()
{
    ifstream fin("Data/Graphic/LoginBg.txt");
    TextColor(4);
    for (int i = 0; i < 20; ++i) {
        gotoXY(20, i);
        string S;
        getline(fin, S);
        for (int j = 0; j < S.size(); ++j) {
            if (S[j] == '*') cout << char(219);
            if (S[j] == ' ') cout << ' ';
        }
        cout << '\n';
    }
    fin.close();
    ifstream fon("Data/Graphic/mode.txt");
    TextColor(11);
    for (int i = 21; i < 41; ++i) {
        gotoXY(52, i);
        string S;
        getline(fon, S);
        for (int j = 0; j < S.size(); ++j) {
            if (S[j] == '*') cout << char(219);
            if (S[j] == ' ') cout << ' ';
        }
        cout << '\n';
    }
    fon.close();
    gotoXY(40, 17);
    for (int i = 0; i < 80; i++)
    {
        TextColor(7);
        printf("%c", 219);
    }
    DrawRecUpgrade(10, 32, 140, 10, 8);
    printINfor();
    for (int i = 0; i <= 10; i++)
    {
        gotoXY(80, 6 + i);
        printf("%c%c", 219, 219);
    }
    for (int i = 0; i < 12; i++)
    {
        gotoXY(32, 20 + i);
        printf("%c%c", 219, 219);
    }
    for (int i = 0; i < 12; i++)
    {
        gotoXY(126, 20 + i);
        printf("%c%c", 219, 219);
    }
    DrawRecUpgrade(25, 15, 15, 5, 6);
    gotoXY(10, 17);
    printf("CLICK HERE %c%c%c", 175, 175, 175);
    gotoXY(29, 17);
    cout << " STAFF";
    DrawRecUpgrade(120, 15, 15, 5, 6);
    gotoXY(136, 17);
    printf("%c%c%c CLICK HERE", 174, 174, 174);
    gotoXY(124, 17);
    cout << "STUDENT";
    DrawRecUpgrade(74, 28, 14, 4, 6);
    gotoXY(79, 29);
    TextColor(7);
    cout << "QUIT";
}

bool DrawChangePasswordWindow(int PosY, User*& UserInfo)
{
    int BoxHeight = 15, BoxWidth = 44, PosX = (GetWidth() - BoxWidth) / 2;
    SetBGColor(7);
    for (int i = PosX; i < PosX + BoxWidth; i++)
    {
        for (int j = PosY; j < PosY + BoxHeight; j++)
        {
            gotoXY(i, j);
            cout << " ";
        }
    }
    SetBGColor(8);
    for (int i = PosX + 5; i < PosX + BoxWidth - 5; i++)
    {
        for (int j = PosY + 2; j < PosY + BoxHeight - 3; j++)
        {
            gotoXY(i, j);
            cout << " ";
        }
    }
    SetBGColor(0);
    for (int i = PosX + 5; i < PosX + BoxWidth - 5; i++)
    {
        for (int j = PosY + 2; j < PosY + 4; j++)
        {
            gotoXY(i, j);
            cout << " ";
        }
    }
    gotoXY(GetWidth() / 2 - 8, PosY + 3);
    SetBGColor(0);
    SetColor(15);
    cout << "CHANGE  PASSWORD";
    gotoXY(PosX + 7, PosY + 5);
    SetBGColor(8);
    SetColor(0);
    cout << "Current password";
    gotoXY(PosX + 7, PosY + 8);
    cout << "New password";
    for (int i = 0; i < 30; i++)
    {
        SetBGColor(15);
        gotoXY(PosX + 7 + i, PosY + 6);
        cout << " ";
    }
    for (int i = 0; i < 30; i++)
    {
        SetBGColor(15);
        gotoXY(PosX + 7 + i, PosY + 9);
        cout << " ";
    }

    SetColor(12);
    gotoXY(PosX + 15, PosY + 13);
    cout << "SAVE";
    gotoXY(GetWidth() / 2 + 3, PosY + 13);
    cout << "BACK";
    SetColor(0);

    Button Button_Cur = Button(PosX + 7, PosY + 6, 30, 1, "");
    Button Button_New = Button(PosX + 7, PosY + 9, 30, 1, "");
    Button Button_Save = Button(PosX + 15, PosY + 13, 4, 1, "");
    Button Button_Back = Button(GetWidth() / 2 + 3, PosY + 13, 4, 1, "");
    string CurPass = "", NewPass = "";
    while(1) {
        gotoXY(0, 0);
        COORD MousePosition;
        while(!isLeftMousePressed(MousePosition));

        if(Button_Cur.isClick(MousePosition)) {
            gotoXY(PosX + 7 + CurPass.size(), PosY + 6);
            GetPassWord(CurPass);
        }
        else if(Button_New.isClick(MousePosition)) {
            gotoXY(PosX + 7 + NewPass.size(), PosY + 9);
            GetPassWord(NewPass);
        }
        else if(Button_Back.isClick(MousePosition)) {
            return false;
        }
        else if(Button_Save.isClick(MousePosition)) {
            gotoXY(PosX + 7, PosY + 11);
            SetBGColor(8);
            if(UserInfo->getPassWord() != CurPass) {
                cout << "Incorrect password!";
            }
            else if(NewPass.size() < 6) {
                cout << "New password is too short!";
            }
            else {
                UserInfo->setPassWord(NewPass);
                return true;
            }
            SetBGColor(15);
        }
    }
}
