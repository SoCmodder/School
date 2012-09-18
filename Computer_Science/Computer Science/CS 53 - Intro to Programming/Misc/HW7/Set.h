//Matt Ludwikosky  CS53
//11/22/04   7:15PM - 7:55PM
//Set.h

#ifndef SET_H
#define SET_H

#include <string>
using namespace std;

const int maxElements = 10;

class Set
{
   private:
      bool elements[maxElements];
	  string name;
   public:
	  Set(string elementName);
	  ~Set();
	  bool isEmpty();
	  bool isElementOf(int x);
	  void addElement(int x);
	  void deleteElement(int x);
	  Set set_union(Set s);
	  Set set_intersection(Set s);
	  void print();
	  string getName();
	  void setName(string elementName);
};

#endif