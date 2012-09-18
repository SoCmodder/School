/* 
* Author: Elliot Gross
* Date: 4/4/06
* Filename: student.cpp
* Instructor: Brian Sea
* Description: This program gets the full name, 
* major and gpa of the student and
* outputs it to the screen
*/

#include <iostream>
#include "student.h" //includes student.h
using namespace std;

Student::Student() //definition for default constructor
{
	Fname = "Unknown";
	Lname = " ";
	GPA = 0;
	Major = "Undecided";
}

Student::Student(const char[], const char[], double, const char[])
//definition for a student with all criteria
{
	Fname = "Brian";
	Lname = "Sea";
	GPA = 3.8;
	Major = "Computer Science";
}

Student::Student(const char[], const char[])
//definition for a student with just a name
{
	Fname = "Josh";
	Lname = "Wilkerson";
	GPA = 4.0;
	Major = "Undecided";
}

string Student::setLname(string lname)
//definition for setLname
{
	Lname = lname;
	return Lname;
}
string Student::setFname(string fname)
//definition for setFname
{
	Fname = fname;
	return Fname;
}

bool Student::setGPA(double GPA)
//definition for setGPA
{
	bool rtn = true;
	if (GPA > 4.0 || GPA < 0)
		rtn = false;
	this->GPA = GPA;
	return rtn;
}

string Student::setMajor(string major)
//definiton for setMajor
{
	Major = major;
	return Major;
}

string Student::getFname() const
//definition for getFname
{
	return Fname;
}

string Student::getLname() const
//definition for getLname
{
	return Lname;
}

double Student::getGPA() const
//definition for getGPA
{
	return GPA;
}

string Student::getMajor() const
//definition for getMajor
{
	return Major;
}


