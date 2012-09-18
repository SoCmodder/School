/*
file: payroll.cpp
author: Brent Powers
date:1-27-05
*/
#include "stdafx.h"
#include "payroll.h"
using namespace std;

/*
Function: payroll()
Description: default constructor for the class
Parameters: none
PreCondition: constuctor is called
PostCondition: count is initialized to zero
*/
payroll::payroll()
{
	count=0;
}
/*
Function: add
Parameters: Cstring i_name  int i_overtime  int i_wage
Description: adds a new employee, their wage, and overtime hours to the paylist array
				or appends the hours worked if the employee already exists.
PreCondition: i_name is a valid CString, i_overtime is of type int, and i_wage is of
				type int. The array isn't full.
PostCondition: if a new name is entered with valid data for all passed variables, then
				that person is added to the array, if space allows it. if a name is entered
				that already exists in the system then the entered number of hours is then 
				added to their existing number of hours.

*/
void payroll::add(CString i_name, int i_overtime, int i_wage)
{
	int i=find_(i_name);//if name already exist it locates it
	bool j;
	if(i>=0&&i<=14)
	{
		paylist[i].overtime=paylist[i].overtime+i_overtime;//appends overtime total of exiting employee
	} 
	else if(i==-1)
	{
		j=isfull();
		if(j==FALSE)
		{
			paylist[count].name=i_name;//entering my name in to array
			paylist[count].overtime=i_overtime;
			paylist[count].wage=i_wage;
			count=count+1;
		}
		else MessageBox(0,"Datebase is too full.","Error",0);//array is to full for more
	}}
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
		if (i>=0&&i<14)
		{
			for(i;i<=count;i++)
			{
				paylist[i].name=paylist[i+1].name;//move down the entries after the one deleted
				paylist[i].overtime=paylist[i+1].overtime;
				paylist[i].wage=paylist[i+1].wage;
			}
			count=count-1;            
		}
		if(i==14)
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
			if one matches, or return's a -1 if there is no match.
PreCondition: Valid CString is passed, and there is valid CString entries in the database 
			to compare to
PostCondition: if the name passed is equal to a name in the array, then a value from 0 to 14
				is returned, and a -1 is returned if it doesn't match anything
*/

	int payroll::find_(CString f_name)
 	{
		bool found=FALSE;
		for(int i=0;(i<=14)&&(found==0);i++)
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
PostCondition: all names in database are equale to null, wage =0, and overtime =0, and count =0

*/
	void payroll::clear()
	{
		for(int i=0;i<=14;i++)
		{
			paylist[i].name="";//clearing data
			paylist[i].overtime=0;
			paylist[i].wage=0;
		}
	count=0;
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
		for(int i=0;i<=14;i++)
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
Function: isfull
Parameters: none
Description: gives a user a true or false value on weither or not the database is full
Precondition: none
Postcondition: returns true if there is a name in every database spot, and false if there
				is a spot open.
*/
	bool payroll::isfull()
	{
		bool full=TRUE;
		for(int i=0;i<=14;i++)
		{
			if (paylist[i].name=="")//searches for a null string in name
			{
				full=FALSE;
			}
		}
		return full;
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




		



