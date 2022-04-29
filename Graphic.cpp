#include "Graphic.h"

void DrawRec(int X, int Y, int Width, int Height) {
    SetColor(7);
    SetBGColor(7);
    gotoXY(X, Y);
    for(int i = 0; i < Width; ++i) cout << char(219);
    gotoXY(X, Y + Height - 1);
    for(int i = 0; i < Width; ++i) cout << char(219);
    for(int i = 0; i < Height; ++i) {
        gotoXY(X, Y + i);
        cout << char(219);
        gotoXY(X + Width - 1, Y + i);
        cout << char(219);
    }
}

bool isLeftMousePressed(COORD& MousePosition) {
    DWORD cNumRead, fdwMode, i;
    INPUT_RECORD irInBuf[128];
    HANDLE hStdin;
    DWORD fdwSaveOldMode;

    hStdin = GetStdHandle(STD_INPUT_HANDLE);
    if(hStdin == INVALID_HANDLE_VALUE) {
        cout << "GetStdHandle";
    }
    if(!GetConsoleMode(hStdin, &fdwSaveOldMode)) {
        cout << "GetConsoleMode";
    }
    fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT | ENABLE_INSERT_MODE | ENABLE_EXTENDED_FLAGS;
    if(!SetConsoleMode(hStdin, fdwMode)) {
        cout << "SetConsoleMode";
    }
    if(!ReadConsoleInput(hStdin, irInBuf, 128, &cNumRead)) {
        cout << "ReadConsoleInput";
    }
    for(i = 0; i < cNumRead; i++) {
        if(irInBuf[i].EventType == MOUSE_EVENT) {
            MOUSE_EVENT_RECORD mer = irInBuf[i].Event.MouseEvent;
            if((mer.dwEventFlags == 0 && mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) || mer.dwEventFlags == DOUBLE_CLICK) {
                MousePosition = mer.dwMousePosition;
                SetConsoleMode(hStdin, fdwSaveOldMode);
                return true;
            }
        }
    }
    SetConsoleMode(hStdin, fdwSaveOldMode);

    return false;
}
