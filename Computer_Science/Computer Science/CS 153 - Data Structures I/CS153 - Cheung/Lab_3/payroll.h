/*
file: payroll.h
author: Brent Powers
date:2-3-05
Program Description: This program will allow the user to input a employee name, wage, and overtime hours
				, then these variables will be entered into a dynamc array. Once in this array the user
				can delete the entry from the array, search the array to find a particular name, calculate
				the total cost of all overtime hours in the array, and completely clear the array. This
				program must allow for an unlimited amount of entries to be entered. This has to be done with 
				a dynamic array.
*/
#ifndef PAYROLL_H
#define PAYROLL_H

struct employee
{
	CString name;
	int overtime;
	int wage;
};

class payroll
{
public:
	payroll();
	~payroll();
	void add(CString i_name, int i_overtime, int i_wage);
    void delete_(CString d_name);
	int find_(CString f_name);
	void clear();
	void total();
	void Display(CListBox & listing);
	employee passback(int index);
private:
	int count;
	int capacity;
	employee *paylist;
};



#endif
