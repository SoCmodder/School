/*
File Name: virusprime.h
Author: Brent Powers
Date : 2-17-05
Description: Struct node declarations and class virus declarations

*/

#ifndef VIRUSPRIME_H
#define VIRUSPRIME_H

struct node//node for the linked list
{
	node(void); //constructor
	~node(void);//destructor
	CString name;//name
	int age;//age
	bool vacinated;//status of vaccination
	node *next;//next node
	node *prev;//next node
    
};

class virus//class used to handle the linked list
{
public:
	virus(void);
	~virus(void);
	void insert(CString i_name, int i_age, bool i_vacinated);
	void vacinate(CString i_name, CString & output);
	void clear(CListBox & dbox,CString &output);
	void infect(CString& output, CListBox & dbox, CString i_name);
    void display(CListBox & lbox, CListBox & dbox);
private:
	node* Find(CString i_name);
	node *head;
	node *tail;
	};
#endif