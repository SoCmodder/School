/*
 * Iteration V
 * 
 * Author: Brian Sea
 * Date: 12/16/03
 *
 * Description: 
 *
 * This file is the entry point of the shell.  It is to verify all arguments
 * and perform the necessary actions stipulated by those arguments.
 *
 * This file also implements getting the input from the user, and all exit
 * conditions.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>

#include "parser.h"
#include "executor.h"
#include "process.h"
#include "signals.h"
#include "processcontrol.h"

#define MAXSIZE 512
#define VERSION 0.5

/* FILE-scope used to identify the program */
char *PROGNAME;

/*
 * Signals that are specially handled by the shell
 */
#define NUM_SIGS 4
int SIGNUMS[4] = { SIGCHLD, SIGINT, SIGTSTP };
static int gotSignal = 0;

/*
 * Usage() - this function prints, to stderr, how to use this program. It then 
 * exits.
 */
void Usage()
{
   fprintf( stderr, "\n\nUsage: %s [--help|--version]\n", PROGNAME);
   fprintf( stderr, "--help\t\tShows this message.\n" );
   fprintf( stderr, "--version\tShows the version of this program.\n\n");

   exit( 0 );
}

/*
 * Version() - this function prints, to stderr, the version of the program.
 * It then exits.
 */

void Version()
{
    fprintf( stderr, "\n\n%s: Version %f\n\n", PROGNAME, VERSION );
    exit(0);
}
   
/* 
 * constructPrompt() - this function constructs the prompt using the 
 * data obtained from the environment.
 */

char *constructPrompt( char *Prompt, int maxLen )
{
    /*
     * We will use the current user's name, the current host and the current
     * directory to construct the prompt
     */

    /* An array of environment variable to search */
    char *find[] = { "USER", "HOSTNAME", "PWD", NULL };

    char **searcher, *finder;
    int curLen = 0;

    Parser *p;
    int count;

    /* Restart the prompt */
    Prompt[0] = '\0';

    /* Create a new parser for the PWD */
    p = Parser_new();
    Parser_setDelimiters(p, "/");
    
    /* 
     * Find the proper environment variables and construct the prompt
     */
    for( searcher = find; *searcher != NULL; searcher++ )
    {
        finder = getenv( *searcher );
        curLen = maxLen - strlen( Prompt );
    
        if( finder != NULL )
        {
            /* We are now messing with the PWD */
            if( !strncmp( *searcher, "PWD", 3 ) )
            {
                /* Parse the directory */
                Parser_parse(p, finder );
                count = Parser_numTokens(p);

                /* 
                 * There are more than two direcories in the Path
                 * so we need to some more work
                 */
                if( count > 2 )
                {
                    /*
                     * Forget all but the last two tokens
                     */
                    for( count = Parser_numTokens(p) - 2; count > 0; 
                                                                count-- )
                    {
                        Parser_next(p);
                    }

                    /* 
                     * Add the last two tokens to our prompt 
                     */
                    strncat( Prompt, Parser_next(p), strlen(Prompt) - 1 );
                    strncat( Prompt, "/", 1 );
                    strncat( Prompt, Parser_next(p), strlen(Prompt) - 1 );
                    strncat( Prompt, ":", 1 );

                    continue;
                }
            }

            strncat( Prompt, finder, --curLen );
        }
        else
        {
            strncat( Prompt, "(null)", --curLen );
        }

        strncat( Prompt, ":", curLen - 1 );
    }

    strncat( Prompt, ">", curLen );
    
    return Prompt;
}


/*
 * Our big signal handler.  It should be noted that this function takes a
 * Signal object that we created.
 *
 * The rest must be captured and forwarded to the running process
 */

void sigHandler( Signal *s )
{
    int PID;
    Process *p = NULL;
    Signal *t;
    
    gotSignal = 1;

    /*
     * Switch that takes care of the signal that was caught
     */
    switch( Signal_getNum(s) )
    {
        /*
         * Message from the child
         */
        case SIGCHLD:

            PID = Signal_getCaller(s);

            switch( Signal_getCode(s) )
            {
                /*
                 * Child exited
                 */
                case CLD_EXITED:
                    printf("\nCHILD exited: PID %d\n", PID );
                    p = ProcControl_removePID( PID );
                    if( p != NULL )
                    {
                        Process_wait( p, PROCESS_NOWAIT );
                        Process_free( p );
                    }
                    else
                    {
                        if( RUNNING )
                        {
                            Process_free( RUNNING );
                        }
                    }

                    if( p == RUNNING )
                        RUNNING = NULL;

                    break;

                /*
                 * Child got killed
                 */
                case CLD_KILLED:
                    printf("\nCHILD killed: PID %d\n", PID );
                    p = ProcControl_removePID( PID );
                    if( p != NULL )
                    {
                        Process_wait( p, PROCESS_NOWAIT );
                        Process_free( p );
                    }

                    if( p == RUNNING )
                        RUNNING = NULL;

                    break;

                /*
                 * Child got suspended
                 */
                case CLD_STOPPED:

                        p = ProcControl_getPID( PID );
                        if( p != NULL )
                        {
                            printf("\nSuspended %d ", Process_getPID(p) );
                            Process_printCommand( p, stdout );
                            printf("\n");
                        }
                        else
                        {
                            fprintf( stderr, "Process stopped that wasn't in"
                                    "List: %d\n", PID );
                        }
                        break;

                case CLD_CONTINUED:

                        fprintf(stderr, "LOOOOOOO\n");
                        break;

            }

            break;

            /* 
             * Caught the Cntrol-Z 
             * 
             * We need to suspend the child
             */
       case SIGTSTP:

                if( RUNNING != NULL )
                {
                    Process_suspend( RUNNING );
                    RUNNING = NULL;
                }
                else
                {
                    printf("\n");
                }

            break;

            /*
             * Ctrl-C - we need to kill the current child
             */

       case SIGINT:
            if( RUNNING != NULL )
            {
                Process_kill( RUNNING );
            }
            else
            {
                printf("\n");
            }

            break;

            /*
             * Seg fault handler
             */
       case SIGSEGV:
            fprintf(stderr, "\nSeg fault!!!\n");
            exit(-1);
    }
}

/*
 * Setup the signals for the main program
 */
void setupSignals()
{
    int i;

    Signal *s;

    for( i = 0; i < NUM_SIGS; i++ )
    {
        s = Signal_new();

        Signal_setNum( s, SIGNUMS[i] );
        Signal_setHandler( s, sigHandler );
        Signal_install( s, NULL );
    }
}


int main( int argc, char *argv[], char *env[] )
{
    char Prompt[MAXSIZE];
    char Input[MAXSIZE];
    int i;
    int count;

    char *look;
    
    Process *child;
    Parser *p; 
    Executor *e;
    
    /* Point to our name */
    PROGNAME = argv[0];

    /*
     * Construct a parser to handle the input
     *
     * We delimit on the space and "|" for now, but need to keep the 
     * "|" so we need to it as a Special Delimiter
     */
    p = Parser_new();
    Parser_setDelimiters( p, " |" );
    Parser_setSpecialDelimiters( p, "|" );

    /*
     * Construct an executor to run the commands
     *
     * We delimit on the "|" for now
     */
    e = Executor_new();
    Executor_setExecDelimiters( e, "|" );

    /*
     * Setup the signals
     */
    setupSignals();

    /* 
     * Starting from the first true argument, scan the argument table
     */
    for( i = 1; i < argc; i++ )
    {
        if( !strncmp( argv[i], "--version", 10 ) )
        {
            Version();
        }

        if( !strncmp( argv[i], "--help", 7 ) )
        {
            Usage();
        }
    }

    /* Construct the prompt */
    constructPrompt( Prompt, MAXSIZE );

    do
    {
        gotSignal = 0;
        /* Infinite loop to read in from the user */
        for( printf("%s ", Prompt); fgets( Input, MAXSIZE, stdin) != NULL; 
                                                printf("%s ", Prompt) )
        {

            /* They just pressed Enter */
            if( *Input == '\n' )
            {
                continue;
            }

            /* Quit */
            if( !strncmp( Input, "exit\n", 5 ) )
            {
                gotSignal = 0;
                break;
            }

            /* 
             * Background the process */
            if( !strncmp( Input, "bg\n", 3 ) )
            {
                child = ProcControl_get(ProcControl_numProcs());
                
                if( child != NULL )
                {
                    printf("Backgrounded %d ", Process_getPID(child));
                    Process_printCommand( child, stdout );
                    printf("\n");

                    Process_resume(child);
                    Parser_clear( p );
                    gotSignal = 0;
                }
                else
                {
                    fprintf( stderr, "\n!!! There is no child to background.\n" );
                }

                ProcControl_printTable( stdout );

                continue;
            }

            /*
             * List current jobs
             */
            if( !strncmp( Input, "jobs\n", 5 ) )
            {
                ProcControl_printTable( stdout );
                Parser_clear(p);
                gotSignal = 0;
                continue;
            }

            /*
             * Foreground the last process
             */
            if( !strncmp( Input, "fg\n", 3 ) )
            {
                child = ProcControl_get(ProcControl_numProcs());
                RUNNING = child;
                if( child != NULL )
                {
                    Process_resume( RUNNING );
                    printf("Forground process %d ", Process_getPID(RUNNING) );
                    Process_printCommand( RUNNING, stdout );
                    printf("\n");
                    Process_wait( RUNNING, PROCESS_WAIT );
                    Parser_clear(p);
                    gotSignal = 0;
                }
                else
                {
                    fprintf(stderr, "\n!!! There are no backgrounded children to "
                                    "bring to the fore.\n\n");
                }
                continue;
            }

            /* Parse the input */
            Parser_parse( p, Input );

            while( (RUNNING = Executor_execute( e, p ) ) != NULL)
            {
                
                ProcControl_add(RUNNING);
                Process_start( RUNNING );
                
                if( RUNNING != NULL )
                {
                    Process_wait( RUNNING, PROCESS_WAIT);
                }
            }

            /* Clear the parser's token list */
            Parser_clear( p );
            gotSignal = 0;
        }
    }while( gotSignal );

    printf("\nProgram exit.\n");

    /* Clean up children that haven't finished */
    ProcControl_free();

    /* Free our parser and executor */
    Parser_free( p );
    Executor_free( e );
    Signal_clear();

    return 0;
}
