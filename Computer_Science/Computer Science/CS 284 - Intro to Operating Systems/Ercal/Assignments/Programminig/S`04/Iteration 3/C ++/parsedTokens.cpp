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

void ParsedTokens::PrintTokens(std::ostream &ofile)
{
   unsigned int ii = 0; 

   if(tokens.size())
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

void ParsedTokens::Execute()
{
   char **commands;
   unsigned int ii = 0;

   commands = new char*[tokens.size() + 1];

   for(ii = 0; ii < tokens.size(); ++ii)
   {
      commands[ii] = new char[tokens[ii].size() + 1];
      strncpy(commands[ii], tokens[ii].c_str(), tokens[ii].size() + 1);
   }
   commands[ii] = 0;

   execvp(commands[0], commands);

   for(ii = 0; ii < tokens.size(); ++ii)
   {
      delete [] commands[ii];
   }
   delete [] commands;
}

void ParsedTokens::Clear()
{
   tokens.clear();
}
