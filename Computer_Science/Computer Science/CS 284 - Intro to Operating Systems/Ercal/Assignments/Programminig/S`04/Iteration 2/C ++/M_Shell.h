/* Author: Matt Johnson
   FileName: M_Shell.h 
   Course: CS 284 - Operating Systems
   Section: A 
   Instructor: Matt Johnson 
   Due Date: 

   This is the header file which contains the class definition of the 
   M_Shell class.
*/

/*
   Current Version is 0.1.

   Revision History
   Version 0.1:
   - Implemented version, help, and prompt echoing ability.
*/

#ifndef M_Shell_h
#define M_Shell_h

using namespace std;
#include <string>
#include "prompt.h"

class M_Shell
{
   public:
      // PreConditions:  All arguments should be identical to the arguments
      //                 passed into main.
      // PostConditions: M_Shell is off and running!
      M_Shell(int argc, char *argv[]);

      // PreConditions:  None.
      // PostConditions: Exogenous data will be destroyed and object will
      //                 terminate.
      ~M_Shell();

   private:
      // PreConditions:  ParseMainArgs has been called.
      // PostConditions: This object knows what prompt to give to the user.
      // void ConstructPrompt();

      // PreConditions:  Arguments have been parsed and prompt has been 
      //                 constructed.
      // Postconditions: Shell will execute until user indicates a desire
      //                 to quit the shell. 
      void MainLoop();

      // PreConditions:  All arguments should be identical to the arguments
      //                 passed into main.
      // PostConditions: The command line class variables have been
      //                 properly defined.
      void ParseMainArgs(int argc, char *argv[]);

      // PreConditions:  None.
      // PostConditions: A message is sent to the user via standard error 
      //                 indicating correct usage of M_Shell.
      void PrintHelp();

      // PreConditions:  ParseMainArgs has been called.
      // PostConditions: A message is sent to the user via standard error 
      //                 indicating the current version of M_Shell.
      void PrintVersion();

      const string VERSION;
      const string EXECUTABLE_NAME;
      Prompt prompt;
      bool enterLoop;
};

#endif
