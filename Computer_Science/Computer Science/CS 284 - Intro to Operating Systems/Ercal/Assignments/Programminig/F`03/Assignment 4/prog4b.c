/*
 * Programming Assignment #4 (Part II)
 * Author: Brian Sea
 * Date: 9/13/03
 *
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
int creatThreads = 0;
pthread_t *ThreadPool;
int Number = 0;

/* SIGUSR1 Handler */
void onSIGUSR1( int signum )
{
    printf( "%s-%d: Received SIGUSR1. Incrementing Number by 2.\n", ProgName,
            ChildNum );

    Number+=2;
}

/* SIGUSR2 Handler */
void onSIGUSR2( int signum )
{
    int i;
    int Status[10];
    printf( "%s-%d: Received SIGUSR2. I'm gonna die now.\n", ProgName,
            ChildNum );

    for( i = 0; i < creatThreads; i++ )
    {
        pthread_join( ThreadPool[i], &Status[i] );
        printf("%s-%d: joined Thread %d - return %d.\n", ProgName,
                ChildNum, i, Status[i] );
    }
    
    exit(creatThreads);
}

/* Thread Routine */

int thread_routine( int arg )
{
    printf("%s-%d: I am a new thread - TID = %d\n", ProgName, ChildNum,
            pthread_self() );
    printf("%s-%d Thread %d: PID = %d.  Parent PID = %d\n", ProgName, ChildNum,
            pthread_self(), getpid(), getppid() );

    printf( "%s-%d Thread %d: I will sleep for %d\n", ProgName, ChildNum,
            pthread_self(), arg );

    usleep( arg);

    Number+=arg;

    pthread_exit(Number);
}

/*  Function to free Thread pool at exit */
void exit_function(void)
{
    free(ThreadPool);
}

int main( int argc, char *argv[], char *env[] )
{
 
    int i, RandNum;
    /* Setup ProgName and verify that at least one arg was passed in */
    ProgName = argv[0];
    
    if( argc < 3 )
    {
        printf( "Two arguments were not passed to the program!\n" );
        exit(-5);
    }

    /* Setup ChildNum and begin the execution of the program */
    ChildNum = atoi(argv[1]);

    /* Setup the number threads to create */
    creatThreads = atoi( argv[2] );
    ThreadPool = (pthread_t*)malloc( sizeof(pthread_t) *creatThreads);

    atexit(exit_function);
    srand( time(NULL));

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
    
    /* Create my threads */
    for( i = 0; i < creatThreads; i++ )
    {
        RandNum = rand() % 1000 + 1;
        pthread_create( &ThreadPool[i], NULL, (void*(*)(void*))thread_routine, 
                (void*)RandNum );
    }

    
    /* Loop indefinitely, waiting for interrupts to kill us */
    for(;;)
        sleep(1);

    /* We should never get past here */
    return 0;
}
