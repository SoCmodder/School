#ifndef processBag_h
#define processBag_h

#include <vector>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include "Array.h"

using std::string;

class ProcessBag
{
   public:
      // PreConditions:  None.
      // PostConditions: Bag is ready to go.
      ProcessBag();

      // PreConditions:  None.
      // PostConditions: Bag is dead.
      ~ProcessBag();

      // PreConditions:  Argument must contain a correct table for use with 
      //                 exec. 
      // PostConditions: Process has been executed and added to the process
      //                 list.
      pid_t AddProcess(char *arg[]);

      void KillProcess(const pid_t pid);

      // PreConditions:  Process id must be valid.
      // PostConditions: Process has been removed from list.
      void RemoveProcess(const pid_t pid);

      // PreConditions:  None.
      // PostConditions: Returns the pid of the foreground process.  Or zero 
      //                 if there is not one. 
      pid_t GetForeGroundPID();

      pid_t operator[](const unsigned int index);

      void SuspendProcess();

      void BackGroundProcess();

      void ForeGroundProcess();

      void PrintJobs(ostream & ofile);

   private:
      struct ProcessData
      {
         ProcessData(char jobName[] = "null") 
            : pid_(0)
            , job_(jobName)
            , suspended_(false)
            , backgrounded_(false)
         {
         }
         
         ProcessData(const pid_t p, char jobName[] = "null")
            : pid_(p)
            , job_(jobName)
            , suspended_(false)
            , backgrounded_(false)
         {
         }

         void ZeroAll()
         {
            pid_ = 0;
            suspended_ = false;
            backgrounded_ = false;
         }

         void BackGround()
         {
            suspended_ = false;
            backgrounded_ = true;
         }

         bool IsBackGround()
         {
            return backgrounded_;
         }

         void Suspend()
         {
            suspended_ = true;
            backgrounded_ = false;
         }

         bool IsSuspended()
         {
            return suspended_;
         }

         void ForeGround()
         {
            suspended_ = false;
            backgrounded_ = false;
         }

         bool IsForeGround()
         {
            return (!suspended_ && !backgrounded_);
         }

         pid_t pid_;
         string job_;

         private:
         bool suspended_;
         bool backgrounded_;
      };

      Array<ProcessData> processes_;
      pid_t lastProcess_;
};

#endif
