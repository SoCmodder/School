/*  Programming Assignment #4
 *  Author: Brian Sea
 *  Date: 9/13/03
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>   /* for waitpid() */
#include <time.h>       /* for time()   */
#include <signal.h>     /* for signal() */
#include <errno.h>


/* Name of the outside executable */
#define EXEC "prog4b"


/* Variable with FILE scope (not global) 
 * Needed so the signal functions can access them
 *
 * childPID - pids of the children
 * childDead - bool value that indicates if the child is dead
 * ProgName - name of the program
 */

#define NUMCHILD 2

int childPID[2] = { 0,0 };
int childDead[2] = { 0,0 };
char *ProgName;


/* signal handler for SIGQUIT (Ctrl-Z) */
void onSigQuit( int signum )
{
    /* 
     * Setup the signal handler again
     * Needed only because SysV systems reset handlers
     */
    signal( SIGQUIT, onSigQuit );

    
    /* Is the child Dead?
     * If not, then we send a SIGUSR1 to the second child
     * Otherwise we indicate to user that child is already dead.
     */
     printf( "%s: Received SIGQUIT.  Sending SIGUSR1 to second process - PID %d.\n", 
            ProgName, childPID[1] );

     if( kill( childPID[1], SIGUSR1 ) < 0 )
     {
         printf("%s: Error is sending signal to process - %d\n", 
                 ProgName, childPID[1] );
     }
}

/* 
 * SIGTSTP handler (Ctrl-Z) 
 * Works similiar to onSigQuit
 */
void onSigTSTP( int signum )
{
    int i;
    signal( SIGTSTP, onSigTSTP );

    printf("%s: Received SIGSTSP. Sending SIGUSR2 to all children.\n", 
            ProgName );

    for( i = 0; i < NUMCHILD; i++ )
    {
        if( kill( childPID[i], SIGUSR2 ) < 0 )
        {
            printf( "%s: Error sending SIGUSR2 to PID %d\n", ProgName, 
                    childPID[i] );
        }
    }
}

/* 
 * SIGINT Handler (Ctrl-C)
 * Works similiar to onSigQuit except that this one kills all children not dead
 * yet.
 */
void onSigInt( int signum )
{
    int i;
    

    printf("%s: Received SIGUSR1.  Sending SIGUSR1 to all alive processes.\n",
            ProgName );

    for( i = 0; i < NUMCHILD; i++ )
    {
        if( kill( childPID[i], SIGUSR1 ) < 0 )
        {
            printf( "%s: Error sending signal to %d.\n", ProgName, 
                    childPID[i] );
        }
    }

    signal( SIGINT, onSigInt );

}

int main( int argc, char *argv[], char *env[] )
{
    /* 
     * childStatus - Stores the returned statuses of the children
     * Buffer - we need a buffer to hold the converted child number
     */
    int childStatus[2] = { 0,0 };
    char Buffer[5], Buffer2[5];
    int i;
    int RandomNum = 0;

    srand( time(NULL) );

    printf("%s: Started.  My PID is %d and my parent's PID is %d.\n", 
            argv[0], getpid(), getppid() );

    /* Set up FILE-scope ProgName */
    ProgName = argv[0];
    
    /* Loop to fork the NUMCHILD children */
    for( i = 0; i < NUMCHILD; i++ )
    {
        if( (childPID[i] = fork() ) < 0 )
        {
            /*
             * If a fork fails then we need to clean up our other processes.
             * To do this we check the stored PIDs of the children.  If they
             * are non-zero then we need to kill them.
             *
             * We use SIGKILL because that signal can never be blocked.
             */
            printf( "Fork #%d failed.  Cleaning up.\n", i );
            for( i = 0; i < NUMCHILD; i++ )
            {
                if( childPID[i] != 0 )
                {
                    kill( childPID[i], SIGKILL );
                }
            }

            exit(5);
        }

        /* 
         * We are in the Child process.
         * A side effect (bad?) is that the second and third child also know
         * about the ones made before it.
         */
        if( childPID[i] == 0 )
        {
            printf("Child %d: I've been created.\n", i );
            printf("Child %d: My pid is %d and my parent is %d.\n", 
                    i, getpid(), getppid() );
            printf("Child %d: Executing \"%s\".", i, EXEC );
           /* Converting the integer to a string */
            sprintf( Buffer,"%d", i );
            sprintf( Buffer2, "%d", 1 + (int)(10.0*rand()/(RAND_MAX+1.0)) );
            execl(EXEC, EXEC, Buffer, Buffer2, NULL );

            printf("Child %d: Execution did not take place!\n", childPID[i] );
            perror(EXEC);
            exit(-2);
        }
   }

    /* Setup the signal handlers */
   signal( SIGQUIT, onSigQuit );
   signal( SIGTSTP, onSigTSTP );
   signal( SIGINT, onSigInt );

   /* Now we wait for each child to die */
   for( i = 0; i < 3; i++ )
   {
       waitpid( childPID[i], &childStatus[i], 0 );
       
   }

   /* If the children died successfully, then we output their exit status */
   for( i = 0;i < NUMCHILD; i++ )
   {
       if( WIFEXITED(childStatus[i]) )
       {
           printf("%s: Child %d exited with status - %d\n", argv[0],
                   i, WEXITSTATUS(childStatus[i]) );
       }
   }

   printf( "%s:  I'm done.  Going away now.\n", argv[0] );

    return 0;
}
