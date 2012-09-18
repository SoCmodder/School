/* Author: Matt Johnson
   FileName: main.cpp 
   Course: CS 284 - Operating Systems
   Section: A 
   Instructor: Matt Johnson 
   Due Date: 

   This file defines the entry point for the mshell, an experimental shell
   developed as the semester project for CS 284 - Operating Systems.
*/

/*
   Current Version is 0.1.

   Revision History
   - Created this file
   - Wrote the main function
   - Instantiate the M_Shell object
*/

#include "M_Shell.h"

int main(int argc, char *argv[])
{
   M_Shell myShell(argc, argv);
   return 0;
}
