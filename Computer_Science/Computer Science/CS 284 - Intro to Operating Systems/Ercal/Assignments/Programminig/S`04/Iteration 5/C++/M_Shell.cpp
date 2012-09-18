/* Author: Matt Johnson
FileName: M_Shell.cpp 
Course: CS 284 - Operating Systems
Section: A 
Instructor: Matt Johnson 

This file contains the implementation of the M_Shell class.

Current Version is 0.2.
See header file for Revision History.
 */

#include <iostream>
#include <string>
#include <string.h>
#include "M_Shell.h"
#include "prompt.h"
#include "parsedTokens.h"

#define MAX_INPUT_CHARS 1024

using std::cin;

M_Shell::M_Shell(int argc, char *argv[])
   :VERSION("0.1")
   ,EXECUTABLE_NAME(argv[0])
   ,enterLoop(true)
{
   // Specify that we will use a signal handler that takes three arguments
   // instead of one, which is the default.
   sVal.sa_flags = SA_SIGINFO;

   // Indicate which function is the signal handler.
   sVal.sa_sigaction = M_Shell::HandleSignal;

   sigaction(SIGTSTP, &sVal, NULL);
   sigaction(SIGCHLD, &sVal, NULL);
   //sigaction(SIGSEGV, &sVal, NULL);
   sigaction(SIGINT, &sVal, NULL);

   ParseMainArgs(argc, argv);
   if(enterLoop)
   {
      prompt.ResetPrompt();
      MainLoop();
   }
}

M_Shell::~M_Shell()
{
}

void M_Shell::HandleSignal(int sig, siginfo_t *si, void *context)
{
   pid_t cur_pid = processes.GetForeGroundPID();
   switch(sig)
   {
      case SIGTSTP:
         processes.SuspendProcess();
         break;

      case SIGINT:
         processes.KillProcess(cur_pid);
         break;

      case SIGCHLD:
         cout << endl;
         if(si->si_code == CLD_EXITED 
            || si->si_code == CLD_KILLED 
            || si->si_code == CLD_DUMPED)
         {
            processes.RemoveProcess(si->si_pid);
            cout << "Process " << si->si_pid << " is done!" << endl;
         }
         else if(si->si_code == CLD_TRAPPED)
         {
            cout << "Process " << si->si_pid << " is trapped!" << endl;
         }
         else if(si->si_code == CLD_STOPPED)
         {
            cout << "Process " << si->si_pid << " has stopped!" << endl;
         }
         else if(si->si_code == CLD_CONTINUED)
         {
            cout << "Process " << si->si_pid << " continued!" << endl;
         }
         cout << endl;
         break;

      case SIGSEGV:
         cerr << "Segmentation Fault occured." << endl;
         cerr << "Program exiting." << endl;
         exit(0);
         break;

      default:
         break;
   }
   receivedSignal = true;
}

void M_Shell::ParseMainArgs(int argc, char *argv[])
{
   int ii = 0;
   //char* myvalue = 0;

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
}

void M_Shell::MainLoop()
{
   char inLine[MAX_INPUT_CHARS];
   bool stillGoing = true;
   ParsedTokens tokens;
   string oneToken;

   while(stillGoing || receivedSignal)
   {
      stillGoing = true;
      receivedSignal = false;

      sched_yield(); 
      cout << prompt;
      cin.getline(inLine, MAX_INPUT_CHARS);

      // If there has been an error, exit the program.
      if(cin.fail())
      {
         stillGoing = false;
         cin.clear(ios::goodbit);
         cout << endl;
      }
      // If the user types "exit", exit the program.
      else if(!strncmp(inLine, "exit\0", 5))
      {
         stillGoing = false;
      }
      else if(!strncmp(inLine, "bg\0", 5))
      {
         processes.BackGroundProcess();
      }
      else if(!strncmp(inLine, "fg\0", 5))
      {
         processes.ForeGroundProcess();
      }
      else if(!strncmp(inLine, "jobs\0", 5))
      {
         processes.PrintJobs(cout);
      }
      else
      {
         tokens.ParseAndAddTokens(inLine);
         tokens.Execute(processes);
         tokens.Clear();
      }
   }
   cout << endl << "Program exit." << endl;
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
