#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include "processBag.h"

using std::cerr;
using std::cout;
using std::endl;

   ProcessBag::ProcessBag()
: lastProcess_(0)
{
}

ProcessBag::~ProcessBag()
{
}

void ProcessBag::KillProcess(const pid_t pid)
{
   // cerr << "ProcessBag::KillProcess " << pid << endl;
   if(pid)
   {
      sched_yield();
      kill(pid, SIGKILL);
   }
}

void ProcessBag::ForeGroundProcess()
{
   for(int ii = processes_.GetUsed() - 1; ii >= 0 && processes_.GetUsed(); --ii)
   {
      if(!processes_[ii].IsForeGround())
      {
         sched_yield();
         if(0 == kill(processes_[ii].pid_, SIGCONT))
         {
            processes_[ii].ForeGround();
            waitpid(processes_[ii].pid_, 0, WUNTRACED);
         }
         else
         {
            cerr << "Error sending SIGSTOP to " << processes_[ii].pid_ << "." << endl;
         }
         break;
      }
   }
}

void ProcessBag::SuspendProcess()
{
   for(int ii = processes_.GetUsed() - 1; ii >= 0 && processes_.GetUsed(); --ii)
   {
      if(!processes_[ii].IsSuspended())
      {
         sched_yield();
         if(0 == kill(processes_[ii].pid_, SIGSTOP))
         {
            processes_[ii].Suspend();
         }
         else
         {
            cerr << "Error sending SIGSTOP to " << processes_[ii].pid_ << "." << endl;
         }
         break;
      }
   }
}

void ProcessBag::BackGroundProcess()
{
   for(int ii = processes_.GetUsed() - 1; ii >= 0 && processes_.GetUsed(); --ii)
   {
      if(!processes_[ii].IsBackGround())
      {
         sched_yield();
         if(0 == kill(processes_[ii].pid_, SIGCONT))
         {
            processes_[ii].BackGround();
         }
         else
         {
            cerr << "Error sending SIGCONT to " << processes_[ii].pid_ << "." << endl;
         }
         break;
      }
   }
}

void ProcessBag::RemoveProcess(const pid_t pid)
{
   // cerr << "ProcessBag::RemoveProcess " << pid << endl;
   if(processes_.GetUsed() > 0)
   {
      unsigned int ii; 

      // If the last process is the one we are removing, set the lastProcess_
      // value to zero.
      if(pid == lastProcess_)
      {
         lastProcess_ = 0;
         // cerr << "ProcessBag::RemoveProcess 1" << endl;
         // cerr << "lastProcess_ = " << lastProcess_ << endl;
      }

      // If the last process is the one we are removing, and it happens to be
      // the last one on the vector, remove it.
      // cerr << "1 processes_.GetUsed() = " << processes_.GetUsed() << endl;
      if(processes_[processes_.GetUsed() - 1].pid_ == pid)
      {
         processes_.PopBack();
      }
      // Otherwise, search through the vector and set that spot in the vector
      // to zero.
      else
      {
         for(ii = 0; ii < processes_.GetUsed(); ++ii)
         {
            if(processes_[ii].pid_ == pid)
            {
               processes_[ii].ZeroAll();
            }
         }
      }

      // cerr << "2 processes_.GetUsed() = " << processes_.GetUsed() << endl;
      // Remove any zeros at the end of the vector.
      for(int ii = processes_.GetUsed() - 1; ii >= 0 && processes_.GetUsed(); --ii)
      {
         if(processes_[ii].pid_ == 0)
         {
            processes_.PopBack();
         }
         else
         {
            break;
         }
      }

      // If lastProcess is zero, and there is a process on the vector,
      // set the lastProcess to the last process on the vector.
      if(processes_.GetUsed() > 0 && lastProcess_ == 0)
      {
         lastProcess_ = processes_[processes_.GetUsed() - 1].pid_;
         // cerr << "ProcessBag::RemoveProcess 2" << endl;
         // cerr << "processes_.GetUsed() = " << processes_.GetUsed() << endl;
         // cerr << "lastProcess_ = " << lastProcess_ << endl;
      }
   }
}

void ProcessBag::PrintJobs(ostream & ofile)
{
   int ii = 0;
   for(ii = 0; ii < processes_.GetUsed(); ++ii)
   {
      ofile << processes_[ii].job_ << "  " << processes_[ii].pid_ << endl;
   }
}

pid_t ProcessBag::AddProcess(char * arg[])
{
   // cerr << "ProcessBag::AddProcess " << arg[0] << endl;

   pid_t pid = fork();

   // CHILD
   if(pid == 0)
   {
      // Create new process group.
      setpgid(0,0);

      // Execute the child
      execvp(arg[0], arg);

      cerr << endl << endl;
      cerr << "Beavis: \"Uuuhhh...  woah.  That was cool.\" " << endl;
      cerr << "Narrator: \"The small mind of Beavis begins to fry as he attempts";
      cerr << endl;
      cerr << "to understand your command.\""; 
      cerr << endl << endl << endl;

      exit(EXIT_FAILURE);
   }
   // PARENT
   else if(pid > 0)
   {
      // Store pid and name of new process.
      processes_.PushBack(ProcessData(pid, arg[0]));
      lastProcess_ = pid;
      waitpid(pid, 0, WUNTRACED);
   }
   else
   {
      exit(EXIT_FAILURE);
   }
   return pid;
}

pid_t ProcessBag::GetForeGroundPID()
{ 
   // cerr << "ProcessBag::GetForeGroundPID()" << endl;
   // cerr << "lastProcess_ = " << lastProcess_ << endl;
   return lastProcess_;
}

pid_t ProcessBag::operator[](const unsigned int index)
{
   return 0;
}
