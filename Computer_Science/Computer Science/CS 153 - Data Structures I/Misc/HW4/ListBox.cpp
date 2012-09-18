#include "stdafx.h"
#include "ListBox.h"



ListBox::ListBox()  // Constructor for Class ListBox
{
	for (int i=0; i<10; i++)
	{
		data [i] = NULL;
	}
	size= 1;
}

ListBox::~ListBox()  //  Deletes an Array of Pointers such that there are no Memory Leaks
{
	for (int i=0; i<10; i++)
	{
		delete [] data [i];
		data [i] = NULL;
	}

}

CString ListBox::find (CString input) // Finds a given word in the ListBox "bag"
{
	int i = 0;
	int j = 0;
//	char wordCmp [20];
	int wordSize;
	

	while (i < size-1)
	{
		wordSize = strlen (input);   
		words = new char (wordSize);
		if ( !strcmp (words, input))
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



CString ListBox::remove(CString input) // Removes given string from "Bag"
{
	int i = 0;
	int j = 0;
//	char wordCmp [20];
	int wordSize;

	while (i < size)
	{
		wordSize = strlen (input);   
		words = new char (wordSize);
		if ( strcmp (words, input))
		{
			
			if (i == size-2) // if the bag only holds one value
			{
//				* data[i]= '\0';
				message = "Removed";
				j = 10;
				size = size -1;
			}
			else // if the bag holds multiple values
			{
				data [i] = data [size-2];
				message = "Removed";
				j = 10;
				size = size -1;
			}

		}
		else  // if a match is not found
		{
			i++;
		}
	}
	if (j == 0)
	{
		message = "Not Found";
	}
	return message;

}

CString ListBox::insert(CString input) //Inserts given string into bag
{
	int wordSize;

	if (size == 11)
	{
		message = "List Box is full!!";
	}
	else
	{   
		wordSize = strlen (input);   // conversions for insert
		words = new char (wordSize);  
		strcpy (words, input);
		data [size-1] = words;   // inserts into bag
		size = size++;
		message = " ";
	}
	return message;
}

void ListBox::display(CListBox &ListBox) // Converts bag into list box values to be displayed
{
	ListBox.ResetContent();
	for (int i=0; i<(size-1); i++)
	{
		ListBox.AddString (data[i]);
	}
	return;
}

CString ListBox::empty ()  // Checks if bag is empty
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

CString ListBox::full ()  // Checks if bag is full

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
