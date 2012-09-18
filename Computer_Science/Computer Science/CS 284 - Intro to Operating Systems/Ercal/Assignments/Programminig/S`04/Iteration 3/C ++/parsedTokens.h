/* Author: Matt Johnson
   FileName: parsedTokens.h 
   Course: CS 284 - Operating Systems
   Section: A 
   Instructor: Matt Johnson 

   This is the header file which contains the class definition of the 
   parsedTokens class. The job of the parsedTokens class is to parse out the 
   command line and store the tokens.
*/

/*
   Current Version is 0.2.

   Revision History
   Version 0.1:
   - Created class.  
   Version 0.2: 
   - Added the ability to execute a basic command from from the command line.
   - Added a PrintTokens function which will output the data stored in the 
     object.
*/

#ifndef parsedTokens_h
#define parsedTokens_h

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

class ParsedTokens
{
   public:
      // PreConditions:  None. 
      // PostConditions: Object is created. 
      ParsedTokens();

      // PreConditions:  None.
      // PostConditions: Object is deystroyed.
      ~ParsedTokens();

      // PreConditions:  The char* argument must be a command line from the 
      //                 shell. It should be properly formatted and delimited. 
      // PostConditions: Tokens are removed and added to this container. 
      void ParseAndAddTokens(char * commandLine);

      // PreConditions:  None.
      // PostConditions: Internal iterator starts at the beginning of the 
      //                 containter. 
      void StartIterator();

      // PreConditions:  None.
      // PostConditions: The inToken argument has been set to the next token.
      //                 If the operation has succeeded, it will return true.
      //                 Otherwise, it will return false. 
      bool GetNextToken(std::string &inToken);

      // PreConditions:  The ostream object must be open and ready for writing. 
      // PostConditions: Contents of the container will be sent to the ostream
      //                 object.
      void PrintTokens(std::ostream &ofile);

      // PreConditions:  A correct command line has been passed into this 
      //                 object with the ParseAndAddTokens function.
      // PostConditions: The command has been executed.  Additionally, this
      //                 process will be overwritten with the process image
      //                 of the command executed. This will also cause a memory
      //                 leak.
      void Execute();

      // PreConditions:  None. 
      // PostConditions: Container is empty.
      void Clear();

   private:
      // PreConditions:  None.
      // PostConditions: Function will return true or false, which will 
      //                 indicate whether the input character is a delimiter.
      bool IsDelimiter(char ch);

      // PreConditions:  User must specify whether to add the special character
      //                 to the container with the second bool argument.
      // PostConditions: Function will return true or false, which will 
      //                 indicate whether the input character is a special
      //                 character. If the character is indeed a special 
      //                 character, and the user specified true in the second
      //                 argument, that character will be added to the 
      //                 container as a seperate token.
      bool IsSpecialCharacter(char ch, bool addToContainer);

      std::vector<std::string> tokens;
      unsigned int iterCount;
};

#endif
