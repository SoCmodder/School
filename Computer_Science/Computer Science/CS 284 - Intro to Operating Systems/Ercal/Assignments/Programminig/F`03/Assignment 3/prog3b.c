/*
 * Programming Assignment #3 (Part II)
 * Author: Brian Sea
 * Date: 9/13/03
 *
 * This program helps illistrate signals as an IPC (Inter-Process
 * Communication) device.
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <signal.h>  /* for signal */

/* FILE-scoped variable for the signal handlers
 *
 * ProgName - The name of the program
 * ChildNum - Variable to store the number that uniquely IDs this program
 */
char *ProgName;
int ChildNum;

/* SIGUSR1 Handler */
void onSIGUSR1( int signum )
{
    printf( "%s-%d: Received SIGUSR1. I'm gonna die now.\n", ProgName,
            ChildNum );
    exit(2);
}

/* SIGUSR2 Handler */
void onSIGUSR2( int signum )
{
    printf( "%s-%d: Received SIGUSR2. I'm gonna die now.\n", ProgName,
            ChildNum );
    exit(1);
}

int main( int argc, char *argv[], char *env[] )
{
 
    /* Setup ProgName and verify that at least one arg was passed in */
    ProgName = argv[0];
    
    if( argc < 2 )
    {
        printf( "One Argument were not passed to the program!\n" );
        exit(-5);
    }

    /* Setup ChildNum and begin the execution of the program */
    ChildNum = atoi(argv[1]);

    printf("%s-%d: Starting Execution.\n", ProgName, ChildNum );

    /* Setup signal handlers.  We need to make sure that we ignore all signal
     * handlers that are used in the parent.  Otherwise we'll try to handle
     * them ourself and die.
     *
     * We really should get the interrupts needed to be ignored differently,
     * but since this is such a small program we'll just hardcode them
     */
    signal( SIGTSTP, SIG_IGN );
    signal( SIGQUIT, SIG_IGN );
    signal( SIGINT, SIG_IGN );
    signal( SIGUSR1, onSIGUSR1 );
    signal( SIGUSR2, onSIGUSR2 );
    
    /* Loop indefinitely, waiting for interrupts to kill us */
    for(;;)
        sleep(1);

    /* We should never get past here */
    return 0;
}
