//Programmer: Elliot Gross
//Class: CS153
//Teacher: Matt Johnson
//Program 4 Description: This program will implement
// a LinkedList class and will offer some basic forms of data 
// manipulation of the LinkedList using the GUI for functions 
// to simulate a car lot with various functionality.
#include "StdAfx.h"
#include ".\automobile.h"

//Preconditions: none
//PostConditions: Will make a car
Automobile::Automobile(void)
{
   make_ = "None";
   model_ = "None";
   year_ = 0;
}

//Preconditions: none
//PostConditions: none
Automobile::~Automobile(void)
{
}
//Preconditions: Pass in the required parameters
//PostConditions: Will create Automobile with the given
// make, model, and year
Automobile::Automobile(const CString& make,const CString& model, const int& year)
{
   Copy(make, model, year);
}
//Preconditions: Pass in the correct parameters
//PostConditions: Will make a copy of Automobile
Automobile::Automobile(const Automobile& A)
{
   Copy(A.make_, A.model_, A.year_);
}

//Preconditions: Pass in the required parameter
//PostConditions: Will set make in the automobile
void Automobile::SetMake(const CString& make)
{
   this->make_=make_;
}

//Preconditions: Pass in the required parameter
//PostConditions: Will set model in the automobile
void Automobile::SetModel(const CString& model)
{
   this->model_=model_;
}

//Preconditions: Pass in the required parameter
//PostConditions: Will set model in the automobile
void Automobile::SetYear(const int& year)
{
   this->year_=year_;
}

//Preconditions: none
//PostConditions: Will return make 
CString Automobile::GetMake()const
{
   return make_;
}
//Preconditions: none
//PostConditions: Will return model 
CString Automobile::GetModel()const
{
   return model_;
}

//Preconditions: none
//PostConditions: Will return year
int Automobile::GetYear()const
{
   return year_;
}
//Preconditions: none
//PostConditions: Will return a CString that has
// make model and year on one line
CString Automobile::GetAuto() const
{
  char buffer[50];
  itoa(year_, buffer,10);
  CString Auto = buffer;
  Auto += " " + make_ + " " + model_;
  return(Auto);

}

//Preconditions: none
//PostConditions: Will find out if two automobiles are the same
bool Automobile::operator==(const Automobile&rhs)
{
   bool tmp = false;
   if (model_==rhs.model_)
   {
      if(make_==rhs.make_)
      {
         if(year_==rhs.year_)
         {
            tmp = true;
         }
      }
   }
   return tmp;
}

//Preconditions: pass in the required parameters
//PostConditions: Overloads the = operator
void Automobile::operator=(const Automobile&rhs)
{
   make_=rhs.make_;
   model_=rhs.model_;
   year_=rhs.year_;

}

//Preconditions: pass in required parameters
//PostConditions: Will make year_, make_, and model_ = to 
// the parameters that are passed in
void Automobile::Copy(const CString& make, const CString& model, const int&year)
{
   this->make_=make;
   this->model_=model;
   this->year_=year;

}

