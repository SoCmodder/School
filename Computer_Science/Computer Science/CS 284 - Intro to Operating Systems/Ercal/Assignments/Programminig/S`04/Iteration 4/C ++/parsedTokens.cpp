/* Author: Matt Johnson
   FileName: parsedTokens.cpp 
   Course: CS 284 - Operating Systems
   Section: A 
   Instructor: Matt Johnson 

   This file contains the implementation of the parsedTokens class.

   Current Version is 0.2.
   See header file for Revision History.
*/

#include <string>
#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "parsedTokens.h"
#include "Executionist.h"

using namespace std;

ParsedTokens::ParsedTokens()
{
}

ParsedTokens::~ParsedTokens()
{
}

void ParsedTokens::ParseAndAddTokens(char * commandLine)
{
   int ii = 0;
   int leftSide = 0;
   int rightSide = 0;
   std::string temp = "";
   bool foundToken = false;
   
   while(commandLine[ii] != '\0')
   {
      // Strip out any delimiters, store any special characters
      while((commandLine[ii] != '\0') &&
            (IsDelimiter(commandLine[ii]) || 
             IsSpecialCharacter(commandLine[ii], true)))
      {
         ++ii;
      }
      leftSide = ii;

      foundToken = false;
      while(commandLine[ii] != '\0' &&
            !IsDelimiter(commandLine[ii]) &&
            !IsSpecialCharacter(commandLine[ii], false))
      {
         ++ii;
         foundToken = true;
      }
      if(foundToken)
      {
         rightSide = ii - 1;
         temp = "";
         temp.append(commandLine, leftSide, rightSide - leftSide + 1);
         tokens.push_back(temp);
      }
   }
}

bool ParsedTokens::IsDelimiter(char ch)
{
   return ch == ' ';
}

bool ParsedTokens::IsSpecialCharacter(char ch, bool addToContainer)
{ 
   static const int NUM_CHARS = 5;
   char specialChars[NUM_CHARS + 1] = {"|<>!@"};
   bool special = false;
   std::string chString = ""; 
   int ii = 0;

   for(ii = 0; ii < NUM_CHARS && !special; ++ii)
   {
     if(ch == specialChars[ii])
     {
        special = true;
     }
   }

   if(special && addToContainer)
   {
      chString = ch;
      tokens.push_back(chString);
   }

   return special;
}

void ParsedTokens::StartIterator()
{
   iterCount = 0;
}

bool ParsedTokens::GetNextToken(std::string &inToken)
{
   bool success = false;

   if(iterCount < tokens.size())
   {
      inToken = tokens[iterCount];
      iterCount++;
      success = true;
   }
   return success;
}

void ParsedTokens::PrintTokens(std::ostream &ofile, char *args[])
{
   unsigned int ii = 0; 

   if(args)
   {
      ofile << "----------------------------------------" << endl;
      ofile << "Executing: " << args[ii] << endl;
      ofile << "----------------------------------------" << endl;
      while(args[ii] != NULL)
      {
         ofile << args[ii] << endl;
         ii++;
      }
      ofile << "NULL" << endl; 
      ofile << "----------------------------------------" << endl;
   }
   else if(tokens.size())
   {
      ofile << "----------------------------------------" << endl;
      ofile << "Executing: " << tokens[ii] << endl;
      ofile << "----------------------------------------" << endl;
      for(ii = 0; ii < tokens.size(); ++ii)
      {
         ofile << tokens[ii] << endl;
      }
      ofile << "NULL" << endl; 
      ofile << "----------------------------------------" << endl;
   }
}

void ParsedTokens::Clear()
{
   tokens.clear();
}

void ParsedTokens::Execute()
{
   Executionist RunCommand;
   char **command = NULL;
   unsigned int ii = 0;
   unsigned int newCommand = 0;
   bool foundCommand = false;

   if(tokens.size() > 0)
   {
      command = new char*[tokens.size() + 1];
   
      for(ii = 0; ii < tokens.size(); ++ii)
      {
         if(!foundCommand)
         {
            newCommand = ii;
            foundCommand = true;
         }
         
         if(tokens[ii] == "|")
         {
            command[ii] = 0;
            if(command[newCommand])
            {
               PrintTokens(cout, &command[newCommand]);
               RunCommand(&command[newCommand]);
            }
            foundCommand = false;
         }
         else
         {
            command[ii] = new char[tokens[ii].size() + 1];
            strncpy(command[ii], tokens[ii].c_str(), tokens[ii].size() + 1);
         }
      }
      command[ii] = 0;
   
      if(command[newCommand])
      {
         PrintTokens(cout, &command[newCommand]);
         RunCommand(&command[newCommand]);
      }
   
      for(ii = 0; ii < tokens.size(); ++ii)
      {
         delete [] command[ii];
      }
      delete [] command;
   }
}
