/*
file: payroll.h
author: Brent Powers
date:1-27-05
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
	void add(CString i_name, int i_overtime, int i_wage);
    void delete_(CString d_name);
	int find_(CString f_name);
	void clear();
	void total();
	bool isfull();
	void Display(CListBox & listing);
	employee passback(int index);
private:
	int count;
	employee paylist[15];
};



#endif
