/*
File: heap.cpp
Author: Brent Powers
Date: 4-21-05
Description: heap class definitions 
*/
#include <stdafx.h>
#include "heap.h"
#include <iostream>//for input output
using namespace std;//regular type

/*
Function: heap()
Description: initializes the heap array to all zeros and sets used to 0
Precondition: none
Postcondition: used = 0  and array is set to all zeros
*/
heap::heap()
{
	used=0;//anount used
	for (int i = 0; i < 100; ++i)
		hp[i] = 0;//set all spots of array to zero
}

/*
Function: ~heap()
Description: Default Destructor
Precondition: none
Postcondtion: all memory is returned
*/
heap::~heap()
{
}

/*
Function: insert(const int x)
Description: function to insert a node in the heap and to reheapify
			the tree after that
Precondition: x is a valid int, heap is in a valid state
Postcondition: node is inserted in tree and the tree is reheapified
*/
void heap::insert(const int x)
{
	if(x==-123456)
		return;//check for bad input in x
	int temp = 0;
	int i = used;//temp counter variable
	hp[used] = x;//enter new value in the tree
	++used;//augment the counter
	while (i != 0)//until the top of the tree is reached
	{
		if (hp[((i-1)/2)] < hp[i])  //if child is bigger than parent
		{
			temp = hp[i];
			hp[i] = hp[((i-1)/2)];	
			hp[((i-1)/2)] = temp;//perform swap
			i = ((i-1)/2);//move to new node				
		}else
			i = 0;//in good order, done
	}
}
/*
Function: int remove()
Description: removes the root node of the tree and reheapifies
Precondition: tree is correctly heapified.
Postcondition: root node is removed and tree is reheapified
*/
int heap::remove()
{
	if(used == 0)//if tree is empty
	{
		return 0;
	}
	int temp = hp[0];//temp variable for return
	int i = 0;//counter
	int t_swap = 0;//swap
	hp[0] = hp[used - 1];//replace root with last node
	hp[used -1] = 0;//clear the last node				
	--used;//decrement amount of node's used

	while((hp[i] < hp[2*i])||(hp[i] < hp[2*i+1]))
	{//while at least one child is bigger than parrent
		if(hp[2*i] > hp[2*i+1])//bigger than right child
		{
			t_swap = hp[i];		
			hp[i]  = hp[2*i];//swap
			hp[2*i] = t_swap;
			i = 2*i;
		}
		if(hp[2*i+1] > hp[2*i])//bigger than left child
		{
			t_swap = hp[i];		
			hp[i] = hp[2*i+1];//swap
			hp[2*i+1] = t_swap;
			i = 2*i+1;
		}
	}

	return temp;//return value that was removed
}
/*
Function: void clear()
Description: cleats the entire tree
Precondition: none
Postcondition: all values in the tree array=0 and used =0
*/
void heap::clear()
{
	for(int i=0;i<=99;i++)
	{
		hp[i]=0;//reset all nodes
	}
	used=0;//zero used
}
/*
Function: void display()
Description: Display's the tree
Precondition: tree is in good order and used is accurate
Postcondition: the tree is displayed on the screen
*/
void heap::display()
{
	for(int i=0;i<=(used-1);i++)//for all nodes that are used
	{
		if(i==0)
			cout<<endl<<"				 "<<hp[i]<<endl;
		if(i==1)
			cout<<"			      /     \\"<<endl<<"			     "<<hp[i];
		if(i==2)
			cout<<"        "<<hp[i]<<endl;
		if(i==3)
			cout<<"			    / \\	     / \\"<<endl<<"			   "<<hp[i];
		if((i==4)||(i==6))
			cout<<"   "<<hp[i];
		if(i==5)
			cout<<"    "<<hp[i];
		if(i==7)
			cout<<endl<<"			  /\\   /\\   /\\   /\\"<<endl<<"			 "<<hp[i];
		if((((i==8)||(i==10))||(i==12))||(i==14))
			cout<<"  "<<hp[i];
		if(((i==9)||(i==11))||(i==13))
			cout<<" "<<hp[i];
		if(i==15)
		{
            cout<<endl<<endl<<"The remaining nodes will be outputted in a linear list";
			cout<<endl<<endl<<hp[i];
		}
		if(i>=16)
			cout<<endl<<hp[i];
		
	}
}
/*
function: flipflop()
description: places the array in asscending order
*/
void heap::flipflop()
{
	int temp;
	for(int i=0;i<used;i++)
	{
		for(int j=i;j<used;j++)
		{
			if(hp[j]<hp[i])
			{
				temp=hp[i];
				hp[i]=hp[j];
				hp[j]=temp;
			}
		}
	}
}


void heap::reheap()
{
	int temp;
	for(int i=0;i<used;i++)
	{
		for(int j=i;j<used;j++)
		{
			if(hp[j]>hp[i])
			{
				temp=hp[i];
				hp[i]=hp[j];
				hp[j]=temp;
			}
		}
	}
}