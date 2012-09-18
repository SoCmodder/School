/*
 * Author: Brian Sea
 * Date: 1/1/04
 *
 * This file is the implementation of the signal object
 *
 * The file uses POSIX signals.  It is VERY dependænt on the OS
 */

#include "signals.h"

#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>


/*
 * INTERNAL OS DEPENDANT functions!!!
 *
 * DO NO USE EXTERNAL TO THIS FILE!
 */
static void _signal_internal_setup_list_();
static void _signal_internal_handler_(int signo,siginfo_t *si,void *context);

static int gotInt = -1;

/*
 * Signal Structure
 *
 * sigNum -     the signal this object deals with
 * tmpsigNum - the signal number this object is meant to use (before
 *              installation of the signal)
 *
 * CausedBy -   the PID of the process that caused this signal to happen
 * ignore   -   if this signal is being ignored
 * code     -   signal specific code
 *
 * Handler  -   the handler of the INSTALLED signal
 * tmpHandler - the handler of the signal BEFORE installation
 *
 * Action   -   an attempt to increase speed by getting a sigaction ready
 * Set      -   an attempt to increase speed by getting a sigset ready
 * oldSet   -   an attempt to increase speed by getting a sigset ready
 */
struct Signal_t
{
    int sigNum;
    int tmpsigNum;
    
    int causedBy;
    int ignore;
    int code;

    void (*Handler)(struct Signal_t *s);
    void (*tmpHandler)(struct Signal_t *s);

    struct sigaction Action;
    sigset_t Set, oldSet;
};

/*
 * static list of signals;  There is a list of signals for each OS supported
 * signal that can be changed.
 *
 */

#define SIGNAL_NUM_OS_SIGNALS 33
static Signal **SIGNALLIST = NULL;

/*
 * Creates a new signal object
 */
Signal *Signal_new()
{

    if( SIGNALLIST == NULL )
    {
        _signal_internal_setup_list_();
    }

    Signal *s;

    s = malloc( sizeof( Signal ) );

    s->sigNum = -1;
    s->tmpsigNum = -1;

    s->ignore = 0;
    s->code = 0;
    
    s->causedBy = -1;

    s->Handler = SIGNAL_DFLT;
    s->tmpHandler = SIGNAL_DFLT;

    s->Action.sa_sigaction = _signal_internal_handler_;
    s->Action.sa_flags |= SA_SIGINFO;
    
    return s;
}

/* 
 * Frees up a signal
 */
void Signal_free( Signal *s )
{
    if( s )
    {
        free( s );
    }

    s = NULL;
}


/*
 * Sets the signal we're messing with
 */
void Signal_setNum( Signal *s, int sigNum )
{
    s->tmpsigNum = sigNum;
}

/*
 * Gets the signal we're messing with
 */
int Signal_getNum( Signal *s )
{
    return s->sigNum;
}

/*
 * Gets the signal we want to move to
 */
int Signal_getFutureNum( Signal *s )
{
    return s->tmpsigNum;
}

/*
 * Returns the PID that caused this signal
 */
int Signal_getCaller( Signal *s )
{
    return s->causedBy;
}

/* 
 * Returns the code of the signal
 */
int Signal_getCode( Signal *s )
{
    return s->code;
}

/*
 * Setup the handler
 */
void Signal_setHandler( Signal *s, void (*Handler)(Signal *s) )
{
    s->tmpHandler = Handler;
    s->Action.sa_flags |= SA_SIGINFO;
}

/*
 * returns the handler for the signal
 */
SIGHANDLE Signal_getHandler( Signal *s )
{
    return s->Handler;
}

/*
 * Returns future installer
 */
SIGHANDLE Signal_getFutureHandler( Signal *s)
{
    return s->tmpHandler;
}

/*
 * Install the signal that has already been setup
 */
int Signal_install( Signal *s, Signal *p )
{
    int rtn = -1;

    if( p != NULL )
    {
        p = SIGNALLIST[ s->tmpsigNum];
    }

    if( s->tmpHandler != NULL && s->tmpsigNum > 0 )
    {
        rtn = sigaction( s->tmpsigNum, &s->Action, NULL );
    }
        

    /*
     * RACE CONDITION!!
     *
     * We have a race condition here.  I'm not quite sure how we would get
     * around this short of ignoring the signal for a short time.. but that
     * would create a nastier race condition, so I'll take this one for now.
     */
    if( !rtn )
    {
        s->Handler = s->tmpHandler;
        s->sigNum = s->tmpsigNum;
        SIGNALLIST[s->sigNum] = s;
    }

    return rtn;
}

/*
 * Resets the signal
 *
 * TODO:  Add the ability to reverse this call
 */

void Signal_reset( Signal *s )
{
    s->Action.sa_handler = SIG_DFL;
    s->Action.sa_flags = 0;

    sigaction( s->sigNum, &s->Action, NULL );
    
    SIGNALLIST[ s->sigNum ] = NULL;
    
    s->ignore = 0;
}

/*
 * Clears all set signals
 */
void Signal_clear()
{
    int i;
    Signal *s;

    for( i = 0; i < SIGNAL_NUM_OS_SIGNALS; i++ )
    {
        s = SIGNALLIST[i];
        if( s != NULL )
        {
            Signal_reset( s );
        }
    }
}
    
/*
 * Set a signal to ignore
 *
 * TODO:  Add the ability to reverse this call
 */
void Signal_ignore( Signal *s )
{
    s->Action.sa_handler = SIG_IGN;
    s->Action.sa_flags = 0;

    sigaction( s->sigNum, &s->Action, NULL );
    s->ignore = 1;
}

/*
 * Wait on a signal.. if we can
 */
int Signal_wait( Signal *s )
{
    if( s->ignore )
    {
        return 0;
    }
    
    /*
     * Block the signal we want to listen for
     */
    sigemptyset( &s->Set );
    sigaddset( &s->Set, s->sigNum );

    sigprocmask( SIG_BLOCK, &s->Set, &s->oldSet );
    
    /*
     * The signal isn't the one we want so we keep waiting
     */
    while( gotInt != s->sigNum )
    {
        sigsuspend( &s->oldSet );
    }

    sigprocmask( SIG_UNBLOCK, &s->Set, NULL );
    
    return 1;
}


/*
 * INTERNAL function
 *
 * This function is meant to setup the signal lookup table for the OS.
 *
 * This function IS OS DEPENDANT!!!
 */
void _signal_internal_setup_list_()
{
    int i = 0;
    Signal **s;

    SIGNALLIST = calloc( SIGNAL_NUM_OS_SIGNALS, sizeof( Signal *) );

    for( s = SIGNALLIST; i < SIGNAL_NUM_OS_SIGNALS; i++ )
    {
        *s=NULL;
        s++;
    }
}

/*
 * INTERNAL function
 *
 * This function is ALWAYS called by all but the default and ignored signals.
 * This function is meant to setup all the fields of the Signal object prior to
 * the "real" signal handler is called.
 *
 * It is quit important that this function is optimized.  Therefore, more work
 * may need to be done if this becomes a problem.
 *
 * This function IS OS DEPENDANT!!!
 */
void _signal_internal_handler_( int signo, siginfo_t *si, void *context )
{
    Signal *s = SIGNALLIST[signo];
    
    s->causedBy = 0;
    s->code = si->si_code;

    gotInt = signo;

    switch( si->si_signo )
    {
        case SIGCHLD:
                s->causedBy = si->si_pid;
                break;

    }

    s->Handler(s);
    gotInt = -1;
}
