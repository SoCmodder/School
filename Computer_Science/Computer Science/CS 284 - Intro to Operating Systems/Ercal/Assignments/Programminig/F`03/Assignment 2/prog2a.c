/*  CS284 Program 2a
 *
 *  Author: Brian Sea
 *  Date: 9/04/03
 *
 *  Description:
 *
 *  This program is meant to demonstrate the properties of processes
 *  through the use of the fork() function, the exec*(...) family of functions,
 *  and other process specific functions.
 *
 *  This program forks a child process that executes an external binary. The
 *  "parent" process then waits for the "child" process to complete running.
 *  The "parent" process then notifies the user of its exit codes.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>  /* standard UNIX types */
#include <sys/wait.h>   /* for waitpid() */
#include <unistd.h>     /* for standard UNIX functions, i.e. sleep() */

/* Define the name of the external program to run in the "child" process */
#define CHILDNAME "prog2b"

int main( int argc, char *argv[], char *env[] )
{
    int childPID;
    int childExitStatus;
    char *ParentName = *argv;
    
    /* Announce that we have started - give our PID */
    printf("%s: I'm a process.\n%s: My PID is %d and my parent's PID is %d\n",
            ParentName, ParentName, getpid(), getppid() );


    printf( "%s: Forking a child off.\n\n", ParentName );

    /* 
     * Fork off a child process and save the ID for later.  If fork() returns
     * anything below zero, then there was an error.
     *
     * If there was an error, then we exit because the program cannot
     * continue with any certainty.
     */
    if( (childPID = fork()) < 0 )
    {
        printf( "%s: The fork() failed!!  Aborting.\n", ParentName );
        exit( -1 );
    }

    /* 
     * Fork() returns the child's PID to the parent process, but it returns
     * zero to the child.  Therefore, if the PID we've saved from the above
     * fork() call is zero, we know that we are in the child
     */
    if( childPID == 0 ) 
    {
        /* This is all child code */
        printf( "Child: I have been created!\n");
        printf( "Child: My PID is %d and my parents's PID is %d\n", 
                getpid(), getppid() );
    
        /* Sleep for 5 seconds */
        sleep(5);

        /* 
         * Execute the outside binary.  The first argument supplied to the
         * executable is the name of itself.  Though this not enforced, it is
         * STANDARD.  The list of arguments MUST end with NULL.
         */
        printf( "Child: Executing \"%s\" with arguments.\n", CHILDNAME );
        execl( CHILDNAME, CHILDNAME, "Arg1", "Arg2", NULL );

        /* If we get here, then there was an error in executing the binary */
        printf( "Child:  Execution of file did not happen!\n\n" );
        perror( CHILDNAME );  /* print out the error */
        exit( -2 );           /* exit with a non-zero number to show error */
    }
    

    /* Print out the Process chart by calling on the UNIX Operating System */
    printf("\n%s: I created a child and its PID is %d\n", ParentName, childPID);
    printf("%s: Printing System Process chart using \"ps -al\" \n\n",
            ParentName);
    system( "ps -al" );  /* Call to the UNIX OS */

    /* Wait for the child process that we created to end and store its status */
    printf( "\n%s: Waiting for my child to die\n\n", ParentName );
    waitpid( childPID, &childExitStatus, 0 );

    /* Verify that it exited normally, then print out its exit codes */
    if( WIFEXITED(childExitStatus) )
    {
        printf( "\n%s: Child exited with status code -  %d\n", ParentName,
                WEXITSTATUS(childExitStatus) );
    }

    /* exit normally */
    printf( "%s: I is now gonna die\n", ParentName );

    return 0;
}

    
