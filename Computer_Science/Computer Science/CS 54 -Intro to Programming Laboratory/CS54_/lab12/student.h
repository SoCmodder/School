/* 
* Author: Elliot Gross
* Date: 4/4/06
* Filename: student.h
* Instructor: Brian Sea
* Description: This program gets the full name, 
* major and gpa of the student and
* outputs it to the screen
*/

#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>

using namespace std;

class Student
{
	string Fname;
	string Lname;
	double GPA;
	string Major;

	public:
		Student(); //default constructor for Student
		Student(const char[], const char[], double, const char[]);
		//constructor with all criteria for student
		Student(const char[], const char[]);
		//constructor with only first and last name
        string setLname(string lname);//prototype for setLname
		string setFname(string fname);//prototype for setFname
		bool setGPA(double GPA); //prototype for setGPA
		string setMajor(string major); //prototype setMajor
		string getFname() const;//prototype for getFname
		string getLname() const;//prototype for getLname 
		double getGPA() const;//prototype for getGPA
		string getMajor() const;//prototype for getMajor

};

#endif

