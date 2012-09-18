/*
 * file: Set.h
 */

#ifndef SET_H
#define SET_H

#include <string>
using namespace std;

const int maxElements = 10;

class Set
{

public:
  //add constructors here
	Set(string c_name);
	~Set();
    //member functions that need to be defined in Set.cpp  
	void addElement(const int x);
	void deleteElement(const int x);
	bool isElementOf(const int x) const;
	bool isEmpty() const;
	void print() const;
	Set set_union(const Set s) const;
	Set set_intersection(const Set s) const;
	string getName() const;
	void setName(const string sName);
private:
	//member variables go here
	bool elements[maxElements];
	string name;

  
};

#endif
