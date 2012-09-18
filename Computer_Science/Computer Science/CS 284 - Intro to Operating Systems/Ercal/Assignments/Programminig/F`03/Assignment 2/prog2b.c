/*
 * CS284 Program 2b
 * Author: Brian Sea
 * Date: 9/04/03
 *
 * This program is called by an external program.
 * It's main purpose is to print out all arguments given to it.
 */

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h> /* getpid() */

int main( int argc, char *argv[], char *env[] )
{
    char *Name = *argv;
    int counter;

    printf( "%s: Starting to execute.\n", Name );
    printf( "%s: My PID is %d and my Parent's PID is %d\n", Name, getpid(),
            getppid() );
    
    /* Loop through argv array and print them out.  If the first character is
     * an integer than output the whole string as an integer.
     */
    for( counter = 0; counter < argc; counter++ )
    {
        printf( "Argument %d is: %s\n", counter + 1, argv[counter] );
    }

    printf( "%s: I'm ending execution.\n", Name );
    return 0;
}

        
