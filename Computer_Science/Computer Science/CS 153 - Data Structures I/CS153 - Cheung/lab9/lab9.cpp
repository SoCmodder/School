/*
File: lab9.cpp
Description: main part of program
Date: 4-21-05
Author: Brent Powers
*/

#include "stdafx.h"
#include <iostream>
#include "heap.h"
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	heap tree;//class tree
	char chose='A';//choice
	while((chose!='q')&&(chose!='Q'))//quit loop
	{
		cout<<endl<<endl;
		cout<<"Welcome to the heap sort sample program"<<endl;
		cout<<"Please choose one of the options below"<<endl;
		cout<<"I = input data into the tree"<<endl;
		cout<<"R = remove the root of the tree"<<endl;
		cout<<"C = clear all data in the tree"<<endl;
		cout<<"Q = exit the program"<<endl;
		cout<<"F = flip the tree"<<endl;
		cout<<"User inputs here ->";//menu garbage
		cin.clear();//clear buffer
		cin>>chose;//input menu choice
		if((chose=='i')||(chose=='I'))//insert part
		{
			cout<<endl<<"Please enter the value to placed in the tree"<<endl;
			int temp=-123456;//check number
			cin>>temp;//input number
			tree.insert(temp);//insert
			cout<<endl<<endl<<endl;
			tree.display();//display
			
        }else if((chose=='r')||(chose=='R'))//remove root
		{
			cout<<endl<<"The root value of "<<tree.remove()<<" has been removed"<<endl;
			tree.display();
		}else if((chose=='c')||(chose=='C'))//clear tree
		{
			cout<<endl<<"The tree has been reset."<<endl;
			tree.clear();
			tree.display();
		}else if((chose=='f')||(chose=='F'))
		{
			tree.flipflop();
			tree.display();
			tree.reheap();
		}
	}



	return 0;
}

