//Programmer: Elliot Gross
//Class: CS153
//Teacher: Matt Johnson
//Program 4 Description: This program will implement
// a LinkedList class and will offer some basic forms of data 
// manipulation of the LinkedList using the GUI for functions 
// to simulate a car lot with various functionality.

#pragma once

class Automobile
{
public:
   Automobile(void); //default constructor 
   ~Automobile(void); //default deconstructor
   Automobile(const CString& make,const CString& model, const int& year);
   //constructor with non-default parameters
   Automobile(const Automobile& A); //copy constructor
   void SetMake(const CString& make); //mutator to set make
   void SetModel(const CString& model); //mutator to set model
   void SetYear(const int& year);//mutator to set year
   CString GetMake()const; //accessor to get make
   CString GetModel()const; // accessor to get model
   int GetYear()const;// accessor to get year
   CString GetAuto() const; //accessor to get Auto
   bool operator==(const Automobile&rhs); //overloaded == operator
   void operator=(const Automobile&rhs);// overloaded = operator
   void Copy(const CString& make, const CString& model, const int&year);
   //Copy mutator

private:
   //private data members
   CString make_;
   CString model_;
   int year_;
   
};