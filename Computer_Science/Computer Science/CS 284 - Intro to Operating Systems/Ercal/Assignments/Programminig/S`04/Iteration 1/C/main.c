/*
 * Iteration I
 * 
 * Author: Brian Sea
 * Date: 12/16/03
 *
 * Description: 
 *
 * This file is the entry point of the shell.  It is to verify all arguments
 * and perform the necessary actions stipulated by those arguments.
 *
 * This iteration also implements getting the input from the user, and all exit
 * conditions.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define MAXSIZE 512
#define VERSION 0.1 

/* FILE-scope used to identify the program */
char *PROGNAME;

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

    /* Restart the prompt */
    Prompt[0] = '\0';

    /* 
     * Find the proper environment variables and construct the prompt
     */
    for( searcher = find; *searcher != NULL; searcher++ )
    {
        finder = getenv( *searcher );
        curLen = maxLen - strlen( Prompt );

        /*
         * We were able to get an environmental variable
         */
        if( finder != NULL )
        {
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

int main( int argc, char *argv[], char *env[] )
{
    char Prompt[MAXSIZE];
    char Input[MAXSIZE];
    int i;
    
    /* Point to our name */
    PROGNAME = argv[0];

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

    /* 
     * Infinite loop to read in from the user 
     * If the user presses Ctrl-D then the loop exits
     */
    for( printf("%s", Prompt); fgets( Input, MAXSIZE, stdin) != NULL; 
            printf("%s", Prompt) )
    {
        fprintf(stdout,"Input from user: %s\n", Input );
        
        /*
         * The user has typed in quit all by itself
         */
        if( !strncmp( Input, "quit\n", 5 ) )
        {
            break;
        }
    }

    printf("\nProgram exit.\n");

    return 0;
}
