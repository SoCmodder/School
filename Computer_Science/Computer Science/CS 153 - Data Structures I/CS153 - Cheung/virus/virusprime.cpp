/*
File: virusprime.cpp
Author: Brent Powers
Date: Feb. 17, 2005
Description: File for virus program, that allows user to input names, ages, and conditoin of pottentially
infected persons. Then the program lets you play with these poor souls and decide who lives or dies.
Then it keeps track of the dead.
*/
#include "stdafx.h"
#include "virusprime.h"

using namespace std;
/*
Function: node()
Description: This is the default constructor for the node struct, it initializes name to nothing
age to 0 and vacinated to false, along with setting next and prex to NULL.
PreCondition: none
PostCondition: a node is created with the default values
*/
node::node()
{
	name="";
	age=0;
	vacinated=FALSE;
	prev = NULL;
	next = NULL;
}
/*
Function: ~node
Description: The default destructor for the node struct, deletes all variables.
PreCondition: being called by or for a struct node to be deleted
PostCondition: everything is returned to the memery that is supposed to be.
*/

node::~node(){};
/*
Function: insert(CString i_name,int i_age, bool i_vacinated)
Description: Function takes user input and places it in the linked list in the form of a node. It puts
			this node at the top of the list. Then links the node to the other nodes, and begining of
			the list
PreCondition: Function must have valid variables passed to it, and the tail and head pointers must point
				to a valid node, or be both null
PostCondition: A new node is created at the top of the list and the according links are made, either
				to the next node and the head, or just the head and tail.

*/
void virus::insert(CString i_name, int i_age, bool i_vacinated)
{
	
	node* temp;
	temp = new node;
	
	if ((tail == NULL)||(head == NULL))//if there is nothing in the list yet
	{
		head=temp;
		tail=temp;
		temp->name=i_name;
		temp->age=i_age;
		temp->vacinated=i_vacinated;
		temp->next =NULL;
		temp->prev =NULL;
	}	
	else//if there is one or more nodes in the list
	{
		temp->name = i_name;
		temp->age = i_age;
		temp->vacinated = i_vacinated;
		temp->next = head;//linking nodes
		temp->prev = NULL;//linking nodes
		temp->next->prev = temp;
		head = temp;//linked to head
	}	
	
	temp = NULL;

	return;

}
/*
Function: virus
Description: Default Constructor for virus class
Precondition: none
PostCondition: head and tail both equalle NULL
*/
virus::virus()
{
	head = NULL;
	tail = NULL;
}
/*
Function: ~virus
Description: Destructor to return all nodes that are linked to head back to the heap
Precondition: there is a linked list of nodes in virus
Postcondition: the memory used for the nodes in the linked list are returned to the heap
*/
virus::~virus()
{
	node* temp = head;
	node* temp2 = NULL;

	while(temp!=NULL)
	{
		temp2 = temp->next;
		delete temp;
		temp = temp2;
	}
}
/*
Function: clear(CListBox &dbox, CString &output)
Description: This function starts at the head of the linked list and begins taking each node one by
			one and enerting it's information and how it died in to the dead box, and then deleting
			the node, and returning it's memory to the heap. It does this untill it reaches the end.
PreCondition: Valid list box and output strings passed to function, and all links in the list of nodes
			works correctly. 
PostCondition: The result is all the nodes in the list are added, with information on how they died
			to the dead list, and then they are removed from the list and returned to memory, then 
			it outputs it success in deleting the nodes.
*/
void virus::clear(CListBox &dbox, CString &output)
{
	node* temp = head;
	node* temp2 = NULL;
    if((head!=NULL)&&(tail!=NULL))//only if there is stuff in the list
	{
	while(temp->next!=NULL)
	{	
		int bday=(2005-(temp->age));//for displaying birthday stuff
		int dday=2005;
		char birthday[6]="";
		char deathday[6]="";
		_itoa(bday,birthday,10);
		_itoa(dday,deathday,10);
		dbox.AddString(temp->name+" "+birthday+" - "+deathday);
		dbox.AddString("Death By: Armageddon");
		dbox.AddString("********************");
		temp2=temp->next;//advance to next node
		delete temp;//delete node
		temp=temp2;
	}
	if(tail!=NULL)//special case for last node in list
	{
		int bday=(2005-(tail->age));
		int dday=2005;
		char birthday[6]="";
		char deathday[6]="";
		_itoa(bday,birthday,10);
		_itoa(dday,deathday,10);
		dbox.AddString(tail->name+" "+birthday+" - "+deathday);
		dbox.AddString("Death By: Armageddon");
		dbox.AddString("********************");
		delete tail;
     }
	output="Armageddon successful";

    head=NULL;//reset nead pointer
	tail=NULL;//reset tail pointer
	}else
	{
		output="No Names Currently In Live List.";
	}

}
/*
Function: Find(CString i_name)
Description: it searches the nodes of the linked list for the one that matches the inputted name
			then returns it's address if it is found, or returns null if it doesn't exist
PreCondition: must have a valid input passed to the function, and there has to be correct linking
				of nodes, head, and tail.
PostCondition: Will either return the address of the node if the name is found, or Null if it does
				not exist in the list

*/

node* virus::Find(CString i_name)
{
	node* temp=NULL;
	temp=tail;
	if(temp->name == i_name)//special case for the end
	{
		return tail;
	}
		
	for(temp=head;temp->next!= NULL; temp=temp->next)//search stuff
	{
		if(temp->name == i_name)
		{
			return temp->next->prev;
		}
	}
	
	return NULL;
}

/*
Function: display(CListBox &lbox, CListBox &dbox)
Description: this function goes through all nodes in the list and displays them in a certain format
			from the head down to the tail.
PreCondition: Valid listbox's passed to the function, and all the nodes are linked in appropriate
				fassion.
PostCondition: The listbox's will be current with the data that is in the linked list, and then it 
				will send that to the display box.
*/

void virus::display(CListBox &lbox, CListBox &dbox)
{
	lbox.ResetContent();//resets live box
	node* temp;
	CString vacine="";
	char convert[20]="";
	if((head==NULL)&&(tail==NULL))//special case for if there is nothing in the list box
	{
		return;
	}
	else
	{
		for(temp=head; temp->next != NULL; temp=temp->next)//rolls through all the nodes
		{
			if(temp->vacinated==TRUE)//stuff for vaccinated
			{
				vacine="Yes";
			}else
			{
				vacine="No";//stuff for not vaccinated
			}
			_itoa(temp->age, convert, 10);//putting strings together
			lbox.AddString("Name: "+temp->name+" Age: "+convert);
			lbox.AddString("Vaccinated: "+vacine);//puttin stuff together
			lbox.AddString("********************");
		}
		if(temp->vacinated==TRUE)//special case
			{
				vacine="Yes";
			}else
			{
				vacine="No";
			}
			_itoa(temp->age, convert, 10);
			lbox.AddString("Name: "+temp->name+" Age: "+convert);
			lbox.AddString("Vaccinated: "+vacine);
			lbox.AddString("********************");

	}
}
/*
Function: infect(CString &output, CListBox &dbox, CString i_name)
Description: this function recieves the name of a person to infect with the virus and then finds the 
			location of that person in the memory and then infects that person and every person after
			that person that isn't vaccinated. It also removes those infected individuals from the list
			and lists them in the dead person box with the reason they died and their birth year and 
			death year.
PreCondition: There has to be valid inputs for all three parameters and there has to be the correct
				linking of the nodes in the list from the head to the tail.
PostCondition: The function lets the person know if the name isn't in the list, if the list is empty,
				or that it infected that person. It moves the infected people over to the dead box, 
				and then repair the list by properly linking the nodes. Then the function out puts, 
				the amount of people that were killed by the virus.

*/

void virus::infect(CString &output, CListBox &dbox, CString i_name)
{
	node* temp;
	node* temp2;
	
	int death_total=0;
	char total[4]="";
	if((head==NULL)&&(tail==NULL))//nothing is inside the list
	{
		output="Living Perons List Is Empty";
		return;
	}
	temp=Find(i_name);
	temp2=temp;
	if (temp==NULL)//name wasn't found in the list
	{
		output="Name Not Found";
		return;
	}
	if (temp->vacinated==TRUE)// person is vaccinated and can't be touched

	{
		output="Person is vaccinated from the virus";
		return;
	}else
	{
		while(temp!=NULL)//loop to continue in no vaccination
		{
			char sentence[60]="";
			if(temp->vacinated==TRUE)//escape for vacinated
			{
				return;
			}
			int bday=(2005-(temp->age));//prepareing info for dead box
			int dday=2005;
			char birthday[6]="";
			char deathday[6]="";
			_itoa(bday,birthday,10);
			_itoa(dday,deathday,10);
			dbox.AddString(temp->name+" "+birthday+" - "+deathday);//added to dead box
			dbox.AddString("Death By: Infection");
			dbox.AddString("********************");
			death_total++;//augment total dead
			_itoa(death_total,total,10);
			strncat(sentence,"The Virus claims ",25);
			strncat(sentence,total,5);
			strncat(sentence," live(s).",7);
			output=sentence;// lists of total killed by virus
            temp2=temp->next;
			
			if((temp==head)&&(temp==tail))//only one item in linked list
			{				
				head=NULL;
				tail=NULL;
			}else if((temp->next!=NULL)&&(temp->prev!=NULL))//middle link in multi list
			{
				temp->prev->next=temp->next;
				temp->next->prev=temp->prev;				
			}else if((temp->next!=NULL)&&(temp->prev==NULL))//beginning link in multi list
			{
				head=temp->next;
				temp->next->prev=NULL;
			}else if((temp->next==NULL)&&(temp->prev!=NULL))//last link in multi list
			{
				tail=temp->prev;
				temp->prev->next=NULL;
			}
			delete temp;
			temp=temp2;
			
		}
	}
}
/*
Function: vacinate(CString i_name, CString &output)
Description: This function finds the name passed to it and changes their vaccinated status to yes
PreCondition: Valid inputs passed to the function, and the string is properly linked 
PostCondition: Outputs weither or not it vaccinated anyone.


*/

void virus::vacinate(CString i_name, CString &output)
{
	node* temp;
	if((head==NULL)&&(tail==NULL))//no people in list
	{
        output="There are no entries to vaccinate";
		return;
	}
    temp=Find(i_name);//name not found
	if (temp==NULL)
	{
		output="Name not found";
		return;
	}else
	{
		temp->vacinated=TRUE;//the vaccination
		output="Person vaccinated";
	}
}
