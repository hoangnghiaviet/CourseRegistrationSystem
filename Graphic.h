#pragma once
#include <iostream>
#include "Console.h"

using namespace std;

void DrawRec(int X, int Y, int Width, int Height);

bool isLeftMousePressed(COORD& MousePosition);

class Button {
private:
    int PosX, PosY;
    int Width, Height;
    int PosTextX, PosTextY;
    string Text;
public:
    Button* pNext;
    Button() {
        PosX = 0, PosY = 0;
        Width = 0, Height = 0;
        PosTextX = 0, PosTextY = 0;
        Text = "";
        pNext = nullptr;
    }

    Button(int PosX, int PosY, int Width, int Height, string Text) {
        this->PosX = PosX;
        this->PosY = PosY;
        this->Width = Width;
        this->Height = Height;
        this->PosTextX = (Width - Text.size()) / 2 + PosX;
        this->PosTextY = (Height - 1) / 2 + PosY;
        this->Text = Text;
    }

    int GetX() {
        return PosX;
    }

    int GetY() {
        return PosY;
    }

    string GetText() {
        return Text;
    }

    void SetText(string Text) {
        this->Text = Text;
    }

    void DrawTextTable() {
        SetColor(0);
        gotoXY(PosX + (Width - Text.size()) / 2, PosY + (Height - 1) / 2);
        cout << Text;
    }

    void DrawButton() {
        DrawRec(PosX, PosY, Width, Height);
        gotoXY(PosTextX, PosTextY);
        SetColor(0);
        cout << Text;
        SetBGColor(0);
        SetColor(7);
    }

    void DrawButtonTable() {
        for(int i = 0; i < Height; ++i) {
            gotoXY(PosX, PosY + i);
            for(int j = 0; j < Width; ++j) cout << " ";
        }
        DrawTextTable();
    }

    bool isClick(COORD MousePosition) {
        return PosX <= MousePosition.X && MousePosition.X <= PosX + Width - 1 && PosY <= MousePosition.Y && MousePosition.Y <= PosY + Height - 1;
    }
};
