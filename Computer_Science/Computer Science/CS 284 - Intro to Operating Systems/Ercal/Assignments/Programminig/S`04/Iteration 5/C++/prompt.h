/* Author: Matt Johnson
   FileName: prompt.h 
   Course: CS 284 - Operating Systems
   Section: A 
   Instructor: Matt Johnson 
   Due Date: 

   This is the header file which contains the class definition of the 
   prompt class. The prompt class stores the prompt and will update itelf 
   upon request.
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
      // PreConditions:  None.
      // PostConditions: Object is ready to go. 
      Prompt();

      // By default, the path will be limited to the current directory and the 
      // previous directory. This function can be used to change that setting.
      // PreConditions:  None. 
      // PostConditions: Will determine whether or not the path will be long. 
      void SetLongPath(bool isLong);

      // PreConditions:  None. 
      // PostConditions: The object will query the operating system and rebuild
      //                 the prompt.
      void ResetPrompt();

      // PreConditions:  ResetPrompt has been called for Prompt object at
      //                 least once. The ostream object is ready to be written
      //                 to.
      // PostConditions: Prompt has been sent to the ostream. 
      friend ostream& operator<<(ostream& out, Prompt pr);

   private:
      const unsigned int MAX_PROMPT_LEN;
      string prompt;
      bool longPath;
};

ostream& operator<<(ostream& out, Prompt pr);

#endif
