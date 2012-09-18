/*
 * Author: Brian Sea
 * Date: 12/31/03
 *
 * The file implements the Process object.  This object is used to manipulate
 * each process.
 */

#include "process.h"
#include "signals.h"

#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>

/*
 * Process Structure
 *
 * Command - a pointer to the command being run - usually argv[0]
 *
 * argTable - the argument table for the process
 * numArgs - how many args we are going to use
 * 
 * PID - the Process ID of the current process
 * ProcessGroup - the group that this process belongs to
 * State - the current state of the process (running, suspend)
 * rtnStatus - the status returned from running the process
 */

struct process_t
{
    char *Command;
    
    char **argTable;
    int numArgs;

    int PID;
    int ProcessGroup;
    int State;
    int rtnStatus;
};

/*
 * Makes a new process
 */

Process *Process_new()
{
    Process *p;

    p = malloc( sizeof(Process) );

    p->Command = NULL;
    p->argTable = NULL;

    p->PID = -1;
    p->ProcessGroup = -1;
    p->numArgs = 0;
    p->State = PROCESS_NONE;

    return p;
}

/*
 * Free up the process
 * 
 * p is set to NULL
 */
void Process_free( Process *p )
{
    char **arg;
    
    if( p == NULL )
        return;

    for( arg = p->argTable; *arg != NULL; arg++ )
    {
        free( *arg );
    }

    free( p->argTable );
    free(p);

    p = NULL;
}

/*
 * Sets the command to run
 */
void Process_setCommand( Process *p, char *Command )
{
    int len = strlen( Command );

    if( p->argTable == NULL )
    {
        p->argTable = (char **)calloc( 2, sizeof( char *) );
    }

    p->argTable[0] = (char *)calloc( len + 1, sizeof(char) );
    strncpy( p->argTable[0], Command, len );
    p->argTable[0][len] = '\0';

    p->Command = p->argTable[0];

    if( p->numArgs == 0 )
    {
        p->numArgs++;
        p->argTable[1] = NULL;
    }
}

/*
 * Adds an argument to the processes argument table
 */
void Process_addArgument( Process *p, char *Argument )
{
    int len;
    if( p->Command == NULL )
    {
        Process_setCommand( p, Argument );
        return;
    }

    len = strlen( Argument );
    p->numArgs++;
    p->argTable = realloc( p->argTable, (p->numArgs+1) * sizeof(char *) );
    p->argTable[p->numArgs-1] = calloc( len + 1, sizeof(char) );
    strncpy( p->argTable[p->numArgs-1], Argument, len );
    p->argTable[p->numArgs-1][len] = '\0';
    p->argTable[p->numArgs] = NULL;
}

/*
 * Clears the argument table - not thæ command though
 */
void Process_clearArguments( Process *p )
{
    char **arg;

    for( arg = &p->argTable[ p->numArgs-1]; p->numArgs > 1; p->numArgs-- )
    {
        free( *arg );
    }

    p->argTable = realloc( p->argTable, 2 * sizeof(char *) );
    p->argTable[1] = NULL;
}

/*
 * Start the process
 *
 * We will fork off a process and start it up
 */
int Process_start( Process *p )
{

   /* Process is already started */
   if( p->State == PROCESS_RUNNING )
   {
       return 0;
   }


   if( (p->PID = fork() ) < 0 )
   {
        return 0;
   }

   /*
    * Set up the state and a group for this process
    */
   p->State = PROCESS_RUNNING;
   p->ProcessGroup = setpgid( p->PID, 0);

   if( !p->PID )
   {
       /*
        * Ensure that the parent can finish their work
        */
       sched_yield();
       Signal_clear();
       execvp( p->argTable[0], p->argTable );
       perror( "Child could not start" );
       exit( -1 );
   }

   
   return p->PID;
}

/* 
 * Sends a signal to the Process p 
 */
int Process_sendSig( Process *p, int SigNum )
{
    return kill(p->PID, SigNum );
}

/*
 * Sends a SIGSTOP to the process
 */
int Process_suspend( Process *p )
{

    if( p->State != PROCESS_RUNNING )
    {
        return -1;
    }

    if( Process_sendSig(p, SIGTSTP) < 0 )
    {
        return -1;
    }

    p->State = PROCESS_SUSPEND;
    return 0;
}

/*
 * Sends a SIGCONT to a suspended process
 */
int Process_resume( Process *p )
{
    if( Process_sendSig( p, SIGCONT) < 0 )
    {
        return -1;
    }

    p->State = PROCESS_RUNNING;
    return 0;
}

/*
 * Sends a SIGKILL to a process - it dies
 */
int Process_kill( Process *p )
{
    if( Process_sendSig( p, SIGKILL ) < 0 )
    {
        return -1;
    }

    p->State = PROCESS_DONE;
    return 0;
}

/*
 * Returns the process ID of p
 */
int Process_getPID( Process *p )
{
    return p->PID;
}

/*
 * Waits on the process to end
 */
int Process_wait( Process *p, int wait )
{
    int option = 0;

    if( wait == PROCESS_NOWAIT )
    {
        option = WNOHANG;
    }

    return (p->State != PROCESS_NONE) ? 
                waitpid( p->PID, &p->rtnStatus, option ) : -1;
}

/*
 * How the process exited
 */
int Process_howExit( Process *p )
{
    if( (p->State != PROCESS_REAP) && (p->State != PROCESS_DONE) )
    {
        return -1;
    }

    if( WIFEXITED(p->rtnStatus) )
    {
        return 0;
    }

    if( WIFSIGNALED(p->rtnStatus) )
    {
        return 1;
    }

    return -1;
}

/*
 * returns the exit status of the process depending on the return value of
 * Process_howExit()
 */
int Process_getExitState( Process *p )
{
    int getStatus = Process_howExit(p);

    if( getStatus < 0 )
    {
        return 0;
    }

    if( getStatus == 0 )
    {
        return WEXITSTATUS(p->rtnStatus);
    }

    return WTERMSIG(p->rtnStatus);
}

/*
 * Print out the argument table to "out"
 */
void Process_printTable( Process *p, FILE *out )
{
    char *look;
    int numArgs;
    
    look = p->argTable[0];
    printf("\nCOMMAND EXEC: %s\n", look );

    numArgs = 0;
    fprintf( out, "Argument Table:\n");
    while( look != NULL )
    {
        fprintf(out,"\tEntry %d: %s\n", numArgs, look );
        numArgs++;
        look = p->argTable[numArgs];
    }

    fprintf(out, "Entry %d: NULL - End of Table\n\n", numArgs );
}

void Process_printCommand( Process *p, FILE *out )
{
    fprintf(out, "%s", p->argTable[0] );
}

/*
 * Return current known state
 */
int Process_getState( Process *p )
{
    return p->State;
}
                    
