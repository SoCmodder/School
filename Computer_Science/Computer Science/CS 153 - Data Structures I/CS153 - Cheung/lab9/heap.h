/*
File: heap.h
Author: Brent Powers
Date: 4-21-05
Description: Class declaratios for the heap class
*/
#ifndef HEAP_H
#define HEAP_H


class heap//the heap class
{
public:
	heap();//comsturctor
	~heap();//destructor
	void insert(const int x);//insert node function
	int remove();//remove the root of the tree
	void display();//display the tree
	void clear();//clear everything in the tree
	void flipflop();
	void reheap();
private:
	
	int hp[100];//the array used for the heap
    int used;//number of nodes of the tree used
};

#endif