#include <iostream>
#include <fstream>
#include "SystemData.h"
#include "AcademicYear.h"
#include <time.h>

void InputYear(ListYear*& YearList) {
    YearList = new ListYear;
    string S;
    ifstream fin("Data/Year/ListYear.txt");
    while(getline(fin, S, ',')) {
        if(YearList->pHead) {
            YearList->pTail->pNext=new NodeYear();
            YearList->pTail=YearList->pTail->pNext;
        }
        else YearList->pHead=YearList->pTail=new NodeYear();
        YearList->pTail->year_name=S;
    }
    fin.close();
}

void UpdateYearToFile(ListYear* YearList) {
    ofstream fout("Data/Year/ListYear.txt");
    for(NodeYear* Cur = YearList->pHead; Cur; Cur = Cur->pNext) {
        fout << Cur->year_name << ',';
    }
    fout.close();
}

bool checkSem(Sem*& newSem)
{
	if (!newSem) return false;
	time_t now = time(0);
	tm* check=localtime(&now);
	if (newSem->SemStart.year > (1900 + check->tm_year)) return false;
	if (newSem->SemStart.month > (1 + check->tm_mon)) return false;
	if (newSem->SemStart.day > (check->tm_mday)) return false;
	if (newSem->SemStart.year < (1900 + check->tm_year)) return false;
	if (newSem->SemStart.month < (1 + check->tm_mon)) return false;
	if (newSem->SemStart.day < (check->tm_mday)) return false;
	return true;
}

void inputTimeRegist(timeStart& registDate)
{
	cout << "Input day start to regist:";
	cin >> registDate.ngay.day;
	cout << "Input month start to regist:";
	cin >> registDate.ngay.month;
	cout << "Input year start to regist:";
	cin >> registDate.ngay.year;
	registDate.check = true;
}
void OpenorCloseRegist(timeStart& registDate)
{
	if (registDate.check) registDate.check = false;
	else
	{
		registDate.check = true;
	}
}
bool checkRegistDate(timeStart registDate)
{
	if (!registDate.check) return false;
	time_t now = time(0);
	tm* kiemtra=localtime(&now);
	Date Now;
	Now.day = kiemtra->tm_mday, Now.month = 1 + kiemtra->tm_mon, Now.year = 1900 + kiemtra->tm_year;
	return DateToInt(registDate.ngay) <= DateToInt(Now) && DateToInt(Now) <= DateToInt(registDate.End);
}

//NodeYear* createYear(ListSem* SemList)
//{
//	AcademicYear newYear;
//	std::cout << "Input an academic year: ";
//	getline(std::cin, newYear.year_name, '\n');
//	NodeYear* ptr = new NodeYear;
//	ptr->year_name = newYear.year_name;
//	ptr->listSem = SemList;
//	ptr->pNext = nullptr;
//	return ptr;
//}
void setList(ListYear*& YearList, ListSem*& SemList)
{
	NodeYear* pYearHead = new NodeYear;
	cout << "Input academic year: ";
	cin >> pYearHead->year_name;
	pYearHead->listSem = SemList;
	pYearHead->pNext = nullptr;
	if (!YearList)
	{
	    YearList = new ListYear;
		YearList->pHead = pYearHead;
		YearList->pTail = pYearHead;
	}
	else
	{
		YearList->pTail->pNext = pYearHead;
		YearList->pTail = YearList->pTail->pNext;
	}
}

void insertYear(NodeYear*& pYearHead, NodeYear* newyear)
{
	if (pYearHead == nullptr)
		pYearHead = newyear;
	else
	{
		NodeYear* current = pYearHead;
		while (current->pNext)
			current = current->pNext;
		current->pNext = new NodeYear;
		current->pNext = newyear;
	}
}

void displayListYear(ListYear YearList)
{
	NodeYear* current = YearList.pHead;
	while (current)
	{
		std::cout << current->year_name << "\n";
		current = current->pNext;
	}
}

Sem* inputSemDate(NodeClass*& ClassList)
{
	Sem* semesterTail = new Sem;
	std::cout << "Input semester's start date\n";
	std::cout << "Day: ";
	std::cin >> semesterTail->SemStart.day;
	std::cout << "Month: ";
	std::cin >> semesterTail->SemStart.month;
	std::cout << "Year: ";
	std::cin >> semesterTail->SemStart.year;
	std::cout << "Input semester's end date\n";
	std::cout << "Day: ";
	std::cin >> semesterTail->SemEnd.day;
	std::cout << "Month: ";
	std::cin >> semesterTail->SemEnd.month;
	std::cout << "Year: ";
	std::cin >> semesterTail->SemEnd.year;
	semesterTail->listClass = ClassList;
	semesterTail->pNext = nullptr;
	return semesterTail;
}


bool setSem(ListSem*& SemList, NodeClass*& ClassList)
{
	Sem* newSem = inputSemDate(ClassList);
	if (!newSem) return false;
	if (!SemList)
	{
	    SemList = new ListSem;
		newSem->order = 1;
		SemList->pHead = newSem;
		SemList->pTail = newSem;
	}
	else
	{
		newSem->order = SemList->pTail->order + 1;
		SemList->pTail->pNext = newSem;
		SemList->pTail = SemList->pTail->pNext;
	}
	return true;
}

void ChangeSem(ListSem* SemList, Sem*& SemHead, int choose)
{
	if (!SemList->pHead) return;
	Sem* curr = SemList->pHead;
	while (curr->order != choose)
	{
		curr = curr->pNext;
	}
	SemHead = curr;
}
void ChangeYear(ListYear* YearList, NodeYear*& YearHead, string choose)
{
	if (!YearList->pHead) return;
	NodeYear* curr = YearList->pHead;
	while (curr->year_name != choose)
	{
		curr = curr->pNext;
	}
	YearHead = curr;
}
