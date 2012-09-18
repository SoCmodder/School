#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include "Executionist.h"

void Executionist::operator()(char *arg[])
{
   int pid = fork();

   if(pid == 0)
   {
      execvp(arg[0], arg);
      exit(EXIT_FAILURE);
   }
   else if(pid > 0)
   {
      wait(NULL);
   }
   else
   {
      exit(EXIT_FAILURE);
   }
}
