#ifndef LISTBOX_H
#define LISTBOX_H


#include "stdafx.h"


class ListBox
{

	public:

		Listbox();
		CString insert(int val);
		CString find(int input);
		CString remove(int input);
		CString empty();
		CString full();
		void display(CListBox &);

	private:

		int m_data[10];
		int m_size;
		CString msg;

};


//ListBox my_list;

#endif