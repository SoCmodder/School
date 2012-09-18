/*
 * This Program demeonstrates the use of:
 *  scanf(...) function.
 *  printf(...) function.
 *  the three arguments passed to main(...) by the Operating System
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main( int argc, char *argv[], char *env[] )
{
    int anInt, manyInts[10];
    float aFloat;
    char aChar, aString[30];
    
    int counter = 0;
    int envCounter;
    char Buffer[20];
    
    /* Reading in the inputs */
    scanf( "%d %f %c %s", &anInt, &aFloat, &aChar, aString );
   
    for( counter = 0; counter < 5; counter++ )
    {
        scanf( "%d", manyInts + counter );

    }

    /* Outputting them */
    printf( "An Int: %d\nA Float: %f\nA Character: %c\nA String: %s\n", 
            anInt, aFloat, aChar, aString );
    for( counter = 0; counter < 5; counter++ )
    {
        printf( "Int #%d from Array: %d\n", counter + 1, manyInts[counter] );
    }

    /* Loop through argv array and print them out.  If the first character is
     * an integer than output the whole string as an integer.
     */

    for( counter = 0; counter < argc; counter++ )
    {
        if( isdigit( argv[counter][0] ) )
        {
            /* first character is an integer */
            printf( "Argument %d has first character as an integer: %d\n",
                    counter + 1, atoi( argv[counter] ) );

            /* since we've dealt with this argument we need to restart the
             * loop
             */
            continue;
        }

        printf( "Argument %d is a string: %s\n", counter + 1, argv[counter] );
    }

    /* Deal with the environment variable
     * set up a counter to count them
     */

    printf( "First environment string: %s\n", env[0] );
    for( envCounter = 1; env[envCounter] != NULL; envCounter++ )
    {
        strcpy( Buffer, strtok( env[envCounter], "=" ) );

        if( !strcmp( Buffer, "HOSTNAME" ) )
        {
            printf( "The value of HOSTNAME is: %s\n", strtok( NULL, "="  ) );
        }
        else
        {
            if( !strcmp( Buffer, "USER" ) )
            {
                printf( "The value of USER is: %s\n", strtok( NULL, "=" ) );
            }
        }

    }

    printf( "The last environment string is: %s\n", env[envCounter -1 ] );
    printf( "The total number of environment variable is: %d\n", --envCounter);

    return 0;
}

        
