/*
 * Iteration II
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

#include "parser.h"


#define MAXSIZE 512
#define VERSION 0.2

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
                    strncat( Prompt, "/", strlen(Prompt) - 1 );
                    strncat( Prompt, Parser_next(p), strlen(Prompt) - 1 );
                    strncat( Prompt, ":", strlen(Prompt) - 1 );

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

int main( int argc, char *argv[], char *env[] )
{
    char Prompt[MAXSIZE];
    char Input[MAXSIZE];
    int i;
    int count;

    char *look;
    
    Parser *p; 
    
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

    /* Infinite loop to read in from the user */
    for( printf("%s", Prompt); fgets( Input, MAXSIZE, stdin) != NULL; 
            printf("%s", Prompt) )
    {

        if( *Input == '\n' )
        {
            continue;
        }

        if( !strncmp( Input, "exit\n", 5 ) )
        {
            break;
        }

        /* Parse the input */
        Parser_parse( p, Input );

        /* Print out the tokens */
        count = 1;
        while( (look = Parser_next(p)) != NULL )
        {
            printf("Token %d: %s\n", count, look );
            count++;
        }

        /* Clear the parser's token list */
        Parser_clear( p );
    }

    printf("\nProgram exit.\n");

    /* Free our parser */
    Parser_free( p );

    return 0;
}
