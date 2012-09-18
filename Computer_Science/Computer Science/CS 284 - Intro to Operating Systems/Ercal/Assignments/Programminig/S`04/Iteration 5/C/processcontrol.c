/*
 * Author: Brian Sea
 * Date: 1/2/04
 *
 * This file implements the process control for the shell
 */

#include "processcontrol.h"

/*
 * List of processes
 */

Process **LIST = NULL;
int numProcs = 0;

/*
 * Move a process to the background list
 */
void ProcControl_add( Process *p )
{
    if( LIST != NULL )
    {
        LIST = realloc( LIST, sizeof(Process*) * (numProcs + 2) );
    }
    else
    {
        LIST = calloc( 2, sizeof( Process *) );
    }

    LIST[ numProcs ] = p;
    LIST[ numProcs + 1] = NULL;

    numProcs++;
}

/*
 * Take a process out of the list and return it
 */
Process *ProcControl_remove( int Num )
{
    Process *p;
    
    if( Num > numProcs || Num < 1 )
    {
        return NULL;
    }

    p = LIST[Num-1];

    memmove( &LIST[Num-1], &LIST[Num], (numProcs - Num+1)*sizeof(Process *) );
    numProcs--;

    return p;
}

/*
 * Take a process that has the PID of Num out of the list and return it
 */
Process *ProcControl_removePID( int Num )
{
    Process *p = NULL;
    int i;
    
    for( i = 0; i < numProcs; i++ )
    {
        if( Process_getPID(LIST[i]) == Num )
        {
            p = LIST[i];
            memmove( &LIST[i], &LIST[i+1], (numProcs - i + 1)*sizeof(Process *) );
            numProcs--;
            break;
        }
    }

    return p;
}

/*
 * Returns a process at Num
 */
Process *ProcControl_get( int Num )
{
    return (Num > 0) ? LIST[Num - 1] : NULL;
}

/*
 * Returns a process with PID Num
 */
Process *ProcControl_getPID( int Num )
{
    Process *p = NULL;
    int i;
    
    for( i = 0; i < numProcs; i++ )
    {
        if( Process_getPID(LIST[i]) == Num )
        {
            p = LIST[i];
            break;
        }
    }
    
    return p;
}

/*
 * Print out a table to out
 */
void ProcControl_printTable( FILE *out )
{
    int i;

    for( i = 0; i < numProcs; i++ )
    {
        fprintf( out, "[%d] %d ", i, Process_getPID( LIST[i]) );
        Process_printCommand( LIST[i], out );
        fprintf( out, "\n" );
    }

    fprintf( out, "\n" );
}

/*
 * Number of process in the list
 */

int ProcControl_numProcs()
{
    return numProcs;
}

/*
 * Free the table
 */

void ProcControl_free()
{
    Process **p;

    if( LIST == NULL )
        return;
    
    for( p = LIST; *p != NULL; p++ )
    {
        Process_kill(*p);
        Process_wait(*p, PROCESS_NOWAIT);
        Process_free(*p);
    }

    free( LIST );
}
