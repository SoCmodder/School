#include <string>
#include <iostream>
#include <cstring>
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

      //std::cerr << "leftSide = " << leftSide << endl;

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
       //  cerr << "push_back " << temp << endl;
         tokens.push_back(temp);
      }
      //std::cerr << "rightSide = " << rightSide << endl;

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
      //cerr << "push_back Special Char Func " << chString << endl;
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

void ParsedTokens::Clear()
{
   tokens.clear();
}
