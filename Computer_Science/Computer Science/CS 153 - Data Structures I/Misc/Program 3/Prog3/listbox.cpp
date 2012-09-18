#include "stdafx.h"
#include "listbox.h"


ListBox::Listbox()
{
	m_size=0;
	msg="";
}

CString ListBox::insert(int val)
{
	if (m_size == 10)
	{
		msg="The list is full";
		return msg;
	}
	m_data[m_size]=val;
	m_size++;
	return msg;
}

CString ListBox::find(int input)
{
	int i;

	for (i=0;i<m_size;i++)
	{
		if (m_data[i] == input)
			msg = "Success";
		else
			msg = "Failure";
	}
	
	return msg;
}

//logic is bad
CString ListBox::remove(int input)
{
	int i,j = 0;

	for (i = 0;(j == 0) && (i < m_size);i++)
	{
		if(m_data[i]=input)
		{
			if(i == (m_size-1))
				m_data[i] = 0;
			else
				m_data[i] = m_data[m_size-1];

			msg = "Removed";
			j = 1;
		}
		else
			msg = "Not Found";
	}
	
	return msg;
}


CString ListBox::empty()
{
	if(m_size==0)
		msg="True";
	else
		msg="False";

	return msg;
}

CString ListBox::full()
{
	if(m_size==10)
	{
		msg="True";
	}
	else
	{
		msg="False";
	}

	return msg;
}

void ListBox::display(CListBox & listbox)
{
	char temp[20];
	
	listbox.ResetContent();
	for(int i=0;i<m_size;i++)
	{
		itoa(m_data[i],temp,10);
		listbox.AddString(temp);
	}
}
