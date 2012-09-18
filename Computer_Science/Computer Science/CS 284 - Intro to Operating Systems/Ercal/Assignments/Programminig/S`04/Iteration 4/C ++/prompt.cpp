/* Author: Matt Johnson
   FileName: prompt.cpp 
   Course: CS 284 - Operating Systems
   Section: A 
   Instructor: Matt Johnson 

   This file contains the implementation of the Prompt class.

   Current Version is 0.1.
   See header file for Revision History.
*/

#include <string>
#include <iostream>
#include "prompt.h"

Prompt::Prompt()
   : MAX_PROMPT_LEN(128)
   , prompt("")
   , longPath(false)
{
}

void Prompt::SetLongPath(bool isLong)
{
  longPath = isLong;
} 

void Prompt::ResetPrompt()
{
   char * temp = 0;

   string userName = "(null)";
   string hostName = "(null)";
   string pwd = "(null)";

   string::size_type currentFind = 0;
   string::size_type lastFound = 0;
   string::size_type nextToLastFound = 0;

   // Define environment variables
   temp = getenv("USER");
   if(temp)
   {
      userName = temp;
   }
   temp = getenv("HOSTNAME");
   if(temp)
   {
      hostName = temp;
   }

   prompt = userName;
   prompt += ":";
   prompt += hostName;
   prompt += ":";
   temp = getenv("PWD");
   if(longPath)
   {
      if(temp)
      {
         prompt += temp;
      }
      else
      {
         prompt += "(null)";
      }
   }
   else
   {
      pwd = temp;

      // Loop through the prompt to find the next to the last '/'
      while(string::npos != (currentFind = pwd.find("/", currentFind))) 
      {
         nextToLastFound = lastFound;
         lastFound = currentFind;
         currentFind++;
      }
      prompt.append(pwd, nextToLastFound, pwd.size() - nextToLastFound);
   }
   prompt += ">";

   // truncate if necessary
   if(prompt.size() > MAX_PROMPT_LEN)
   {
      string temp = "";
      temp.assign(prompt, 0, MAX_PROMPT_LEN-1);
      temp += ">";
      prompt = temp;
   }
}

ostream& operator<<(ostream& out, Prompt pr)
{
   out << pr.prompt;
   return out;
}
