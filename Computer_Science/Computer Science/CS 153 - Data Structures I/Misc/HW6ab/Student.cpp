#include "stdafx.h"
#include "Student.h"

Student::Student ()
{
	header = NULL;
	tail = NULL;
	current = NULL;
}

Student::~Student ()  // Destructor For Linked List
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



CString Student::find (double t_GPA)  //Finding matches for a specifiied GPA
{
	char temp [10];
	int i = 0;
	message = "Not Found";
	current = header;
	if (header != NULL)
	{
		// Cycling through List looking for match
		while(current -> next != NULL)
		{
			if(current ->GPA == t_GPA)
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
		if(current ->GPA == t_GPA)
		{
			i++;
		}
	}
	itoa (i, temp, 10);
	message = temp;
	return message;
}

CString Student::insert (CString t_name, int t_age, double t_GPA) // Adds a student to the end of the linked list
{
	if (header == NULL)  //tests to see if list is empty, TRUE = EMPTY;
	{
		current = new Node (t_name,t_age,t_GPA);
		header = current;
		tail = current;
		current = NULL;
		message = "";
	}
	else  // if list is not empty
	{
		current = new Node (t_name,t_age,t_GPA);
		tail -> next = current;
		current -> previous = tail;
		tail = current;
		current = NULL;
		message = "";
		
	}
	
	return message;
}

CString Student::insertHead (CString t_name, int t_age, double t_GPA) // Adds student to head of list
{
	if (header == NULL)  //tests to see if list is empty, TRUE = EMPTY;
	{
		current = new Node (t_name,t_age,t_GPA);
		header = current;
		tail = current;
		current = NULL;
		message = "";
	}
	else  // if list is not empty
	{
		current = new Node (t_name,t_age,t_GPA);
		current -> next = header;
		header -> previous = current;
		header = current;
		current = NULL;
		message = "";
		
	}
	
	return message;
}

CString Student::GetNext ()  // Returns data from the next node in the list
{
	char TempAge[3], TempGPA[5];
	char temp2 [50];

			
			itoa (current -> age, TempAge, 10);
			_gcvt (current -> GPA, 4, TempGPA);
			strcpy (temp2, current->name);
			strcat (temp2, ",     ");
			strcat (temp2, TempGPA);
			strcat (temp2, ",     ");
			strcat (temp2, TempAge);
	
			current = current ->next;

	return temp2;

}

bool Student::EOL () // Returns value to indicate end of list
{
	if (current == NULL)
		return FALSE;
	else
		return TRUE;
}

void Student::Reset ()
{
	current = header;
}


CString Student::full () // Not going to be tested - Code from Vince Barkman
{
	Node * temp;
	if (temp = new Node)
	{
		delete temp;
		message = "False";
	}
	else
	{
		delete temp;
		message = "True";
	}
	return message;
}


CString Student::empty ()
{
	if(header == NULL)
		message = "True";
	else
		message = "False";
	return message;
}
CString Student::remove (CString t_name)
{
	message = "Not Found";
	current = header;
	if (header != NULL)
	{
		// Cycling through List looking for match
		while(current -> next != NULL)
		{
			if(!strcmp(t_name,current->name))
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
		if(!strcmp(t_name,current->name))
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


CString Student::removeHead ()
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


CString Student::removeTail ()
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
