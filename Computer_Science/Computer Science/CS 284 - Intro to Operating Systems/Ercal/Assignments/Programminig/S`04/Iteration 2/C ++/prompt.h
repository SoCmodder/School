/* Author: Matt Johnson
   FileName: prompt.h 
   Course: CS 284 - Operating Systems
   Section: A 
   Instructor: Matt Johnson 
   Due Date: 

   This is the header file which contains the class definition of the 
   prompt class.
*/

/*
   Current Version is 0.1.

   Revision History
   Version 0.1:
   - Created class
*/

#ifndef prompt_h
#define prompt_h

using namespace std;
#include <string>


class Prompt
{
   public:
      Prompt();
      void SetLongPath(bool isLong);
      void ResetPrompt();

      friend ostream& operator<<(ostream& out, Prompt pr);

   private:
      const unsigned int MAX_PROMPT_LEN;
      string prompt;
      bool longPath;
};

ostream& operator<<(ostream& out, Prompt pr);

#endif
