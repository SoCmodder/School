#include "stdafx.h"
#include "List.h"

List::List ()
{
	header = NULL;
	tail = NULL;
	current = NULL;
}

List::~List ()  // Destructor For Linked List
{
	int i = 0;
	current = header;
	if (header != NULL)
	{
		while (current ->next != NULL)
		{
			header = header ->next;
			delete current;
			current = header;
		}
		delete current;
	}
	header = NULL;
	tail = NULL;
	current = NULL;
}



CString List::find (Node * newStudent)  //Finding matches for a specifiied GPA
{
//	char temp [10];
	int i = 0;
	message = "Not Found";
	current = header;
	if (header != NULL)
	{
		// Cycling through List looking for match
		while(current -> next != NULL)
		{
			if(*current == *newStudent)
			{
				i++;
				current = current->next;
			}
			else
			{
				current = current->next;
			}
		}
		// Testing Last Node or Only Node of List
		if(*current == *newStudent)
		{
			i++;
		}
	}
	if (i == 0)
	{
		message = "Not Found";
	}
	else
	{
		message = "Located in List";
	}

	return message;
}

CString List::insert (Node * newStudent) // Adds a student to the end of the linked list
{
	if (header == NULL)  //tests to see if list is empty, TRUE = EMPTY;
	{
		current = newStudent;
		header = current;
		tail = current;
		current = NULL;
		message = "";
	}
	else  // if list is not empty
	{
		current = newStudent;
		tail -> next = current;
		current -> previous = tail;
		tail = current;
		current = NULL;
		message = "";
		
	}
	
	return message;
}

CString List::insertHead (Node * newStudent) // Adds student to head of list
{
	if (header == NULL)  //tests to see if list is empty, TRUE = EMPTY;
	{
		current = newStudent;
		header = current;
		tail = current;
		current = NULL;
		message = "";
	}
	else  // if list is not empty
	{
		current = newStudent;
		current -> next = header;
		header -> previous = current;
		header = current;
		current = NULL;
		message = "";
		
	}
	
	return message;
}

Node * List::GetNext ()  // Returns data from the next node in the list
{
	Node * temp = current;
	if (temp == NULL)
	{
		return temp;	
	}
	else
	{
		current = current -> next;
		return temp;
	}

	

}

bool List::EOL () // Returns value to indicate end of list
{
	if (current == NULL)
		return TRUE;
	else
		return FALSE;
}

void List::Reset ()
{
	current = header;
}


CString List::full () // Not going to be tested - Code from Vince Barkman
{
/*	Node * temp;
	if (temp = new Node)
	{
		delete temp;
		message = "False";
	}
	else
	{
		delete temp;
		message = "True";
	}*/
	CString message ="";
	return message;
}


CString List::empty ()
{
	if(header == NULL)
		message = "True";
	else
		message = "False";
	return message;
}

CString List::remove (Node * newStudent)
{
	message = "Not Found";
	current = header;
	if (header != NULL)
	{
		// Cycling through List looking for match
		while(current -> next != NULL)
		{
			if(*current == *newStudent)
			{
				message = "Removed";
				if(current == header) // Removing Header
				{
					header = current -> next;
					delete current;
					current = header;
					header -> previous = NULL;
				}
				else // Removing Middle
				{

						current -> previous -> next = current ->next;
						current -> next -> previous = current -> previous;
						
						delete current;
						current = header;
				}
			}
			else
			{
				current = current->next;
			}
		}
		// Testing Last Node or Only Node of List for match
		if(*current == *newStudent)
			{
				message = "Removed";
				if(tail == header) //Removing Only Node
				{
					header = NULL;
					tail = NULL;
					delete current;
				}
				else // Removing Tail
				{
						current -> previous -> next = NULL;
						tail = tail ->previous;
						delete current;
				}

			}
	}
	return message;
}


CString List::removeHead ()
{
	current = header;
	if (header != NULL)
	{

		if(tail == header) //Removing Only Node
		{
			header = NULL;
			tail = NULL;
			delete current;
		}
		else // Removing Head
		{
			header = current -> next;
			delete current;
			current = header;
			header -> previous = NULL;
		}
	}
	return " ";
}


CString List::removeTail ()
{
	current = header;
	if (header != NULL)
	{
		if(tail == header) //Removing Only Node
		{
			header = NULL;
			tail = NULL;
			delete current;
		}
		else // Removing Tail
		{
			current = tail;
			current -> previous -> next = NULL;
			tail = tail ->previous;
			delete current;
		}
	}
	return " ";
}