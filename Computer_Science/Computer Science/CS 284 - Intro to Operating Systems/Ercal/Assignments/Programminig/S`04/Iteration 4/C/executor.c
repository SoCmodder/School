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
#include "parser.h"

/*
 * Executor structure
 *
 * execDelimiters - the delimiters that symbolize the end of a command
 *                     structure.
 *
 */

typedef struct executor_t
{
    char *execDelimiters;
} Executor;

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
int Executor_execute( Executor *e, Parser *p )
{
    char *Command = NULL;
    char **argTable = NULL;

    char *look = NULL;
    int len = 0;
    int numArgs = 0;
    
    int Execute = 0;
    int childPID;

    if( Parser_end( p ) )
    {
        return -1;
    }

    while( (look = Parser_next(p)) != NULL )
    {

        /*
        * We haven't set a command yet.
        * We start up the argument table, copy the command as the first 
        * entry into the table.
        * 
        * We then continue to the next iteration of the loop
        */
        if( Command == NULL )
        {
            /*
             * Not a valid command 
             */
            if( strchr( e->execDelimiters, *look ) != NULL )
            {
                continue;
            }

            len = strlen( look );
            argTable = (char **)malloc( sizeof(char *) );
            argTable[0] = (char *)calloc( len + 1, sizeof(char) );
            strncpy( argTable[0], look, len );
            argTable[0][len] = '\0';

            Command = argTable[0];
            numArgs++;
            continue;
        }


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

        numArgs++;
        len = strlen( look );

        argTable = (char **)realloc( argTable, numArgs * sizeof(char*) );
        argTable[numArgs-1] = (char *)calloc( len + 1, sizeof(char) );
        strncpy( argTable[numArgs-1], look, len );
        argTable[numArgs-1][len] = '\0';
    }

    /* 
     * Command was not set
     */
    if( Command == NULL )
    {
        return -1;
    }

    /*
    * End of the table, increase the table by one and point it to NULL
    */
    numArgs++;
    argTable = (char **)realloc( argTable, numArgs * sizeof(char*) );
    argTable[numArgs-1] = NULL;

    /*
    * Print out the command and the associated table
    */
    look = argTable[0];
    printf("\nCOMMAND EXEC: %s\n", look );

    numArgs = 0;
    printf( "Argument Table:\n");
    while( look != NULL )
    {
        printf("\tEntry %d: %s\n", numArgs, look );
        numArgs++;
        look = argTable[numArgs];
    }

    printf("Entry %d: NULL - End of Table\n\n", numArgs );
    
    /* RUN! */
    if( (childPID = fork()) < 0 )
    {
        perror( "Fork error");
        return -1;
    }

    if( !childPID )
    {
        execvp( argTable[0], argTable );
        perror( "Exec error");
        exit(-1);
    }

    return childPID;
}
