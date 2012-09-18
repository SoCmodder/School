/* Author: Matt Johnson
   FileName: M_Shell.cpp 
   Course: CS 284 - Operating Systems
   Section: A 
   Instructor: Matt Johnson 
   Due Date: 

   This file contains the implementation of the M_Shell class.

   Current Version is 0.1.
   See header file for Revision History.
*/

#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include "M_Shell.h"

#define MAX_INPUT_CHARS 1024

using namespace std;

M_Shell::M_Shell(int argc, char *argv[])
   :VERSION("0.1")
   ,EXECUTABLE_NAME(argv[0])
   ,MAX_PROMPT_LEN(128)
   ,hostName("(null)")
   ,userName("(null)")
   ,workingDirectory("(null)")
   ,enterLoop(true)
{
   ParseMainArgs(argc, argv);
   if(enterLoop)
   {
      ConstructPrompt();
      MainLoop();
   }
}

M_Shell::~M_Shell()
{
}

void M_Shell::ParseMainArgs(int argc, char *argv[])
{
   int ii = 0;
   char* myvalue = 0;

   // Handle command line arguments
   // Loop through argv looking for stuff we care about
   for(ii = 1; ii < argc; ++ii)
   {
      // look for --help
      if(!strncmp(argv[ii], "--help", 7))
      {
         enterLoop = false;
         PrintHelp();
      }

      // look for --version
      if(!strncmp(argv[ii], "--version", 10))
      {
         enterLoop = false;
         PrintVersion();
      }
   }

   // Define environment variables
   myvalue = getenv("USER");
   if(myvalue)
   {
      userName = myvalue;
   }
   myvalue = getenv("HOSTNAME");
   if(myvalue)
   {
      hostName = myvalue;
   }
}

void M_Shell::ConstructPrompt()
{
   char * temp = 0;

   prompt = userName;
   prompt += ":";
   prompt += hostName;
   prompt += ":";
   temp = getenv("PWD");
   if(temp)
   {
      prompt += temp;
   }
   else
   {
      prompt += "(null)";
   }
   prompt += ">";
   if(prompt.size() > MAX_PROMPT_LEN)
   {
      string temp = "";
      temp.assign(prompt, 0, MAX_PROMPT_LEN-1);
      temp += ">";
      prompt = temp;
   }
}

void M_Shell::MainLoop()
{
   char inLine[MAX_INPUT_CHARS];
   bool stillGoing = true;

   while(stillGoing)
   {
      cout << prompt;
      cin.getline(inLine, MAX_INPUT_CHARS);

      // If there has been an error, exit the program.
      if(cin.fail())
      {
         stillGoing = false;
         cerr << endl << endl << "Error in istream.  Program exiting.";
         cerr << endl;
      }
      // If the user types "exit", exit the program.
      else if(!strncmp(inLine, "exit\0", 5))
      {
         stillGoing = false;
         cout << endl << "Program exit." << endl;
      }
      else
      {
		  seperate_words(char inLine[]);
         //cout << "You just typed: " << inLine << endl;
      }
   }
}

void M_Shell::PrintHelp()
{
   cerr << "M_Shell version " << VERSION << "." << endl;
   cerr << "Usage: " << EXECUTABLE_NAME << " [option] ..." << endl;
   cerr << "Available options:" << endl;
   cerr << "   --version:   display the current version" << endl;
   cerr << "   --help:      print this menu" << endl;
}

void M_Shell::PrintVersion()
{
   cerr << "M_Shell version " << VERSION << "." << endl;
   cerr << "This sorry excuse for a shell was written by Matt Johnson ";
   cerr << "for kicks and" << endl;
   cerr << "grins during the spring semester, 2004.  If it does not work ";
   cerr << "right, don't" << endl;
   cerr << "complain.  Use a real shell instead." << endl;
}

void M_Shell::seperatate_words(char inLine[])
{  
   string input( "ls| grep | apples" );
   vector<string> words;
   string::size_type pos = 0, prev_pos = 0;

   while((pos = input.find_first_of( ' ', pos))
             != string::npos )
   {
     words.push_back( input.substr(prev_pos, pos-prev_pos));
     prev_pos = ++pos;
   }

   words.push_back(input.substr(prev_pos, pos - prev_pos));
   for (int i=0; i<words.size(); i++)
   {
     cout<<"token"<<i+1<<" = "<<words[i]<<endl;
   }
 }