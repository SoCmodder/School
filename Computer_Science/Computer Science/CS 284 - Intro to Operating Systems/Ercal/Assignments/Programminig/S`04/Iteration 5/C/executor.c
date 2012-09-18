/*
 * Author: Brian Sea
 * Date: 12/30/03
 *
 * This file contains the implementation of the Executor object
 *
 * The purpose of the executor is to take the tokens from a Parser and execute
 * the next complete command sequence held by it.
 */

#include <stdlib.h>
#include <stdio.h>

#include "executor.h"

/*
 * Executor structure
 *
 * execDelimiters - the delimiters that symbolize the end of a command
 *                     structure.
 *
 */

struct executor_t
{
    char *execDelimiters;
};

#define DEFAULT_DELIMITERS "|<>^&"
#define DLT_DELIMITS_SIZE 4

/*
 * Creates a new Executor object with defaults
 */
Executor *Executor_new()
{
    Executor *e;

    e = (Executor *)malloc( sizeof(Executor) );
    e->execDelimiters = (char *)calloc( DLT_DELIMITS_SIZE+1, sizeof(char));

    strncpy( e->execDelimiters, DEFAULT_DELIMITERS, DLT_DELIMITS_SIZE );
    e->execDelimiters[DLT_DELIMITS_SIZE] = '\0';

    return e;
}

/*
 * Frees up the executor
 */
void Executor_free( Executor *e )
{
    if( e )
    {
        if( e->execDelimiters)
        {
            free(e->execDelimiters);
        }

        free( e );
    }

    e = NULL;
}

/*
 * Sets the executor's special chars to delimits
 */
int Executor_setExecDelimiters( Executor *e, char *delimits )
{
    int len;
    
    /*
     * You passed in NULL pointers!
     */
    if( delimits == NULL || e == NULL)
    {
        return -1;
    }
    
    len = strlen( delimits );
    
    if( e )
    {
        /* 
         * Free up the last set of delimiters and copy the new ones over
         */
        if( e->execDelimiters )
        {
            free( e->execDelimiters );
            e->execDelimiters = malloc( len * sizeof(char) + 1 );
            strncpy( e->execDelimiters, delimits, len );
            e->execDelimiters[len] = '\0';
        }
    }
}

/*
 * Gets the current set of delimits
 */
char *Executor_getExecDelimiters( Executor *e )
{
    return e->execDelimiters;
}

/*
 * Searches the parser p for a command sequence and executes it
 */
Process *Executor_execute( Executor *e, Parser *p )
{
    Process *proc;

    char *look = NULL;
    int len = 0;
    
    int Execute = 0;
    int childPID;

    /*
     * We're at the end of the list in the parser
     * So we return 0 to indicate this
     */
    if( Parser_end(p) )
    {
        return NULL;
    }

    proc = Process_new();

    while( (look = Parser_next(p)) != NULL )
    {

        /*
        * We've got a command.  Check to see if we are at a "special" 
        * token.  If we are then we treat them accordingly.
        */
        if( strchr( e->execDelimiters, *look ) != NULL )
        {
            switch( *look )
            {
                /*
                * Normal execution end
                */
                case '|':
                    Execute = 1;
                    break;

                default:
                    printf("Special Character not assigned\n");
                    break;
            }
        }

        /*
        * We've got a command sequence, we need to break out and run the
        * executable
        */
        if( Execute )
        {
            break;
        }

        /*
        * We got here, so we know we have an argument.  Increase the size 
        * of the argument table and copy the argument in.
        */

        Process_addArgument( proc, look );
    }

    /*
    * Print out the command and the associated table
    */
    Process_printTable( proc, stdout );
    
    return proc;
}
