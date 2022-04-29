

#include <iostream>
#include <string>

#include "SystemData.h"
#include "StaffFunction.h"
#include "StudentFunction.h"
#include "AcademicYear.h"





void inputCourseDate(Course*& courseCurrent)
{
	std::cout << "\nCourse Registration Session\n";
	std::cout << "Input course's start date\n";
	std::cout << "Day: ";
	std::cin >> courseCurrent->CourseStart.day;
	std::cout << "Month: ";
	std::cin >> courseCurrent->CourseStart.month;
	std::cout << "Year: ";
	std::cin >> courseCurrent->CourseStart.year;
	std::cout << "Input course's end date\n";
	std::cout << "Day: ";
	std::cin >> courseCurrent->CourseEnd.day;
	std::cout << "Month: ";
	std::cin >> courseCurrent->CourseEnd.month;
	std::cout << "Year: ";
	std::cin >> courseCurrent->CourseEnd.year;
}










int main()
{
	/*
	AcademicYear newYear;
	inputAcademicYear(newYear);
	createYear(newYear);
	NodeYear* pYearHead = new NodeYear;
	setList(pYearHead);
	insertYear(pYearHead, createYear(newYear));
	displayListYear(pYearHead);

	*/
	
}