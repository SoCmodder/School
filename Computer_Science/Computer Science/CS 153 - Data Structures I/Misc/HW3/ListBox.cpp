#include "stdafx.h"
#include "ListBox.h"



ListBox::ListBox()
{
	data = new char[10];
	for(int i = 0;i < size;i++)
		data[i] = NULL;
	size = 1;
}

ListBox::~ListBox()
{
//	for(int i = 0;i < size;i++)
//	{
//		delete [] data [i];
//		data [i] = NULL;
//	}
}

CString ListBox::find (CString input)
{
	int i = 0;
	int j = 0;

	while (i < size)
	{
		if (input == data [i])
		{
			
			message = "Success";
			j = 10;

		}
		i++;
	}
	if (j == 0)
	{
		message = "Failure";
	}

	return message;
}



CString ListBox::remove(CString input)
{
	int i = 0;
	int j = 0;

	for(i;i < size;i++)
	{
		if(!strcmp(input, data[i]))
		{
			if(i == size-2)
			{
				delete[] data[i];
				data[i] = '\0';
				message = "Removed";
				size = size - 1;
				j = 1;
			}
			else
			{
				data[i] = data [size-2];
				message = "Removed";
				j = 1;
				size = size-1;
			}
		}
	}
	if(j == 0)
		message = "Not Found";
	return message;

		
	/*while (i < size)
	{
		if (input == data [i])
		{
			
			if (i == size-2)
			{
				data [i] = '\0';
				message = "Removed";
				j = 10;
				size = size -1;
			}
			else
			{
				data [i] = data [size-2];
				message = "Removed";
				j = 10;
				size = size -1;
			}

		}
		else
		{
			i++;
		}
	}
	if (j == 0)
	{
		message = "Not Found";
	}*/
}

CString ListBox::insert(CString input)
{
	int length;
	length = strlen(input);
	char * stuff[length];

	strcpy(input, stuff[]);
	
	if(size == 11)
		message = "List Box is full!!";
	else
	{
		data[size] = stuff[];
		size = size++;
		message = "";
	}

	return message;


	/*if (size == 11)
	{
		message = "List Box is full!!";
	}
	else
	{
		strcpy(data[size-1],input);
		//data [size-1] = input;
		size = size++;
		message = " ";
	}
	return message;*/
}

void ListBox::display(CListBox &ListBox)
{
	char temp [10];
	ListBox.ResetContent();
	for (int i=0; i<(size-1); i++)
	{
		strcpy(data[i], temp);
		//itoa (data[i], temp, 10);
		ListBox.AddString (temp);
	}
	return;
}

CString ListBox::empty ()
{
	if (size == 1)
	{
		message = "True";
	}
	else
	{
		message = "False";
	}
	return message;
}

CString ListBox::full ()
{
	if (size == 11)
	{
		message = "True";
	}
	else
	{
		message = "False";
	}
	return message;

}
