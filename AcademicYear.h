#pragma once
#include "SystemData.h"

#include <iostream>
#include <string>

struct AcademicYear {
	string year_name;
};
struct timeStart {
	Date ngay;
	Date End;
	bool check = false;
};

void InputYear(ListYear*& YearList);

void UpdateYearToFile(ListYear* YearList);

void inputTimeRegist(timeStart& registDate);
void OpenorCloseRegist(timeStart& registDate);
bool checkRegistDate(timeStart registDate);
bool checkSem(Sem*& newSem);
NodeYear* createYear(ListSem* SemList);
void setList(ListYear*& YearList, ListSem*& SemList);
void displayListYear(ListYear YearList);
Sem* inputSemDate(NodeClass*& ClassList);
bool setSem(ListSem*& SemList, NodeClass*& ClassList);
void ChangeSem(ListSem* SemList, Sem*& SemHead, int choose);
void ChangeYear(ListYear* YearList, NodeYear*& YearHead, string choose);
