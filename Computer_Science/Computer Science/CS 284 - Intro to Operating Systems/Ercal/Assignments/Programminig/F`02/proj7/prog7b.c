/****************************************************************************
** CS284 Operating Systems
** Programming Assignment #7
** Program Name: prog7b.c
** Author: Chang Qian, Joe Wingbermuehle, Matt Walters
** Date: october 28, 2002
**
** This program is to read a string and put a suffix to it
** compilation: cc -o prog7b.out prog7b.c 
*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[], char *env[])
{
   char token[512];
   
   while( scanf("%s",token) != EOF )
   {  printf("%s-%s\n",token, argv[1]); /* add the suffix */
      fflush(stdout);
   }
   _exit(0);
   
}
