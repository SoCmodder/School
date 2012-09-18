/*
file: payroll.cpp
author: Brent Powers
date:2-03-05
Program Description: This program will allow the user to input a employee name, wage, and overtime hours
				, then these variables will be entered into a dynamc array. Once in this array the user
				can delete the entry from the array, search the array to find a particular name, calculate
				the total cost of all overtime hours in the array, and completely clear the array. This
				program must allow for an unlimited amount of entries to be entered. This has to be done with 
				a dynamic array.
*/
#include "stdafx.h"
#include "payroll.h"
using namespace std;

/*
Function: payroll()
Description: default constructor for the class
Parameters: none
PreCondition: constuctor is called
PostCondition: count is initialized to zero capacity to 10 and sets up pointer
*/
payroll::payroll()
{
    count=0;
	capacity=10;
	paylist=new employee[capacity];
}
/*
Function: ~payroll
Parameters: None
Description: Default Destructor for payroll class. Deletes unused variables and returns the memory space 
			back to the array.
PreCondition: called when variables from the class need to be deleted.
PostCondition: used variables are deleted and returned to available memory
*/
payroll::~payroll()
{
	delete []paylist;
}


/*
Function: add
Parameters: Cstring i_name  int i_overtime  int i_wage
Description: adds a new employee, their wage, and overtime hours to the paylist array
				or appends the hours worked if the employee already exists.
PreCondition: i_name is a valid CString, i_overtime is of type int, and i_wage is of
				type int.
PostCondition: if a new name is entered with valid data for all passed variables, then
				that person is added to the array, if space allows it. If the program doesn't
				have any more space in the array it will expand it be 5 for more space
				If a name is entered that already exists in the system then the entered number of hours is then 
				added to their existing number of hours.

*/
void payroll::add(CString i_name, int i_overtime, int i_wage)
{
	int i=payroll::find_(i_name);
	if(i==-1)
	{
		if(count>=capacity)
		{
			capacity=capacity+5;
			employee *newptr;
			newptr=new employee[capacity];
			for(int i=0;i<count;i++)
			{
				newptr[i]=paylist[i];
			}
			delete []paylist;
			paylist=newptr;
			MessageBox(0,"Database was expanded.","Database",0);
			payroll::add(i_name,i_overtime,i_wage);
		}
		else if(count<capacity)
		{
			paylist[count].name=i_name;
			paylist[count].overtime=i_overtime;
			paylist[count].wage=i_wage;
			count=count+1;
		}
		
	}
	if(i>=0)
	{
		paylist[i].overtime=paylist[i].overtime+i_overtime;

	}
}







/*
Function: delete_
Parameters: CString d_name
Description: This function deletes an entry from the database, if the name entered matches 
			one already in the database, if not it sends a message box that there was 
			no name found like that.
PreCondition: Valid CString passed to the function
PostCondition: The person's record will be removed from the array, or if the record 
				doesn't exist then a message box will pop up
*/
void payroll::delete_(CString d_name)
	{
		int i=find_(d_name);// finds the name if in the database
		if (i>=0&&i<(count-1))
		{
			for(i;i<count;i++)
			{
				paylist[i].name=paylist[i+1].name;//move down the entries after the one deleted
				paylist[i].overtime=paylist[i+1].overtime;
				paylist[i].wage=paylist[i+1].wage;
			}
			count=count-1;            
		}
		if (i==(count-1))
		{
			paylist[i].name="";//special delete case for the last one
			paylist[i].wage=0;
			paylist[i].overtime=0;
			count=count-1;
		}

		if(i==-1)
		{
			MessageBox(0,"Name is not in database.","Error",0);//if name not found
		}}

/*
function: find_
Parameters: Cstring f_name
Description: This functions takes a name and compares to existing names and returns it's location
			if one matches, return's a -1 if there is no match.
PreCondition: Valid CString is passed, and there is valid CString entries in the database 
			to compare to
PostCondition: if the name passed is equal to a name in the array, then a value from 0 to 14
				is returned, and a -1 is returned if it doesn't match anything
*/

	int payroll::find_(CString f_name)
 	{
		bool found=FALSE;//if ture then CString found
		for(int i=0;(i<count)&&(found==0);i++)
		{
			if (paylist[i].name==f_name) //comparison point
			{
				found=TRUE;
			}
		}
		i=i-1;//adjustment for the for loop 
		if (found==FALSE)
			i=-1;//not found situation
		return i;
	}
/*
Function: clear
Parameters: none
Description: Clears all values out of the database
PreCondition: none
PostCondition: all names in database are equale to null, wage =0, and overtime =0, and count =0, and capacity 5

*/
	void payroll::clear()
	{
	delete []paylist;
	count=0;
	capacity=10;
	paylist=new employee[capacity];
	}
/*
Function: total
Parameters: none
Description: Provides the user with a total of overtime hours, and how much that costs
Precondition: Valid Entries in the database that include integers for overtime and wage
Postcondition: Out puts a message box out with the total overtime hours, and how much it costs

*/

	void payroll::total()
	{
		char temp[50]="Total is ";//sting used to build on
		char c_sum[4]="";
		char t_sum[4]="";
		int sum=0;
		int h_sum=0;
		for(int i=0;i<count;i++)
		{
			sum=sum+(paylist[i].overtime*paylist[i].wage);//summing stuff up
			h_sum=h_sum+paylist[i].overtime;//more summing
		}
		_itoa(sum,c_sum,10);//convert int to char
		_itoa(h_sum,t_sum,10);
		strncat(temp,t_sum,5);//adds bits of strings to make a big string
		strncat(temp," overtime hours costing $",25);
		strncat(temp,c_sum,10);
		MessageBox(0,temp,"Total",0);// shows what we got
	}

/*
Function: Display
Parameters: CListBos & listing
Description: it displays all the information in the database in a particular format
PreCondition: count has to be correct for right data to be shown
PostCondition: strings sent to the list box based on count number
*/

	void payroll::Display(CListBox & listing)
	{
		
		
		listing.ResetContent();//starts with blank list
		for(int i=0; i<count; i++)//only displays information based on the count
		{
			char temp[50]="";//temp CString
			char wage[4]="";
			char hours[4]="";
			_itoa(paylist[i].wage,wage,10);
			_itoa(paylist[i].overtime,hours,10);
			strncat(temp,paylist[i].name,20);
			strncat(temp," - ",4);
			strncat(temp,hours,3);
			strncat(temp,"  hours",7);	
			strncat(temp," -  $",6);
			strncat(temp,wage,3);
			

			listing.AddString(temp);//sends it to the listbox
		}
	}
/*
Function: passback
Parameters: int index
Description: given a index number it returns the information that is in that spot in the database
PreCondition: correct index number passed, and information is in the database
PostCondition: returns tha specific information in the form of an employee struct
*/
	employee payroll::passback(int index)
	{
		employee temp;
		temp.name=paylist[index].name;
		temp.overtime=paylist[index].overtime;
		temp.wage=paylist[index].wage;
		return temp;
	}




		



