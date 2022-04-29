#pragma once
#include <iostream>
#include <conio.h>
#include <fstream>
#include <string>
#include "SystemData.h"
#include "Console.h"
#include "Graphic.h"

using namespace std;

class User {
private:
    string userName;
    string passWord;
    string firstName;
    string lastName;
    string gender; // 1=nam, 0=nu
    bool Mode; // 0=staff, 1=student
public:
    User* pNext;
    User() {
        pNext = nullptr;
        userName="abcxyz";
        passWord="12345678";
        firstName=lastName="";
        Mode = 1;
    }
    User(string userName, string passWord, string firstName, string lastName, string gender, bool Mode) {
        this->userName=userName;
        this->passWord=passWord;
        this->firstName=firstName;
        this->lastName=lastName;
        this->gender=gender;
        this->Mode = Mode;
    }
    // login data (username, password)
    void setUserName(string userName) {
        this->userName=userName;
    }
    void setPassWord(string passWord) {
        this->passWord=passWord;
    }
    string getUserName() {
        return userName;
    }
    string getPassWord() {
        return passWord;
    }
    bool loginSuccess(string userName, string passWord) {
        return getUserName()==userName && getPassWord()==passWord;
    }

    // user data (name, gender)
    void setFirstName(string firstName) {
        this->firstName=firstName;
    }
    void setLastName(string lastName) {
        this->lastName=lastName;
    }
    void setFullName(string firstName, string lastName) {
        this->firstName=firstName;
        this->lastName=lastName;
    }
    string getFirstName() {
        return firstName;
    }
    string getLastName() {
        return lastName;
    }
    string fullName() {
        return lastName+" "+firstName;
    }
    void setGender(string gender) {
        this->gender=gender;
    }
    string getGender() {
        return gender;
    }

    void changePassWord(User& Anon);

    void setMode(bool Mode) {
        this->Mode = Mode;
    }
    bool getMode() {
        return Mode;
    }

};

User* FindUser(User* UserList, string UserName, bool Mode);

void GetPassWord(string& PassWord);

void GetUserName(string& UserName, int Limit);

/// Task 12
void LogIn(User* UserList, User*& UserInfo, bool Mode);

//draw mode
void DrawRecUpgrade(int X, int Y, int Width, int Height, int t);
void printINfor();
void drawMode1();
void DrawLoginWindow(int PosY);
bool DrawChangePasswordWindow(int PosY, User*& UserInfo);
