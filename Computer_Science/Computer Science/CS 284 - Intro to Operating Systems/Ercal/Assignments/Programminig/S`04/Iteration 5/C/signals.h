/*
 * Author: Brian Sea
 * Date: 1/1/04
 *
 * This file attempts to declare an OS independant signal system
 */

#ifndef SIGNALS_H_
#define SIGNALS_H_

typedef struct Signal_t Signal;


/* Some definitions for setting handlers */
#define SIGNAL_DFLT (void(*)(Signal*))-1
#define SIGNAL_IGN  (void(*)(Signal*))-2


/*
 * This isused to help us return a function pointer
 */
typedef void(*SIGHANDLE)(Signal *s);
/*
 * Creates a new signal object
 *
 * returns NULL on failure or a new Signal object on success
 *
 * The signal will be filled with the current signal setting if such a setting
 * can be retreived.
 */
Signal *Signal_new();

/*
 * Frees up a signal object
 *
 * s will be set to NULL
 */
void Signal_free( Signal *s );

/*
 * Installs the signal.
 *
 * A signal must be installed for it to work.  In order to be installed, a
 * signal MUST have a valid number and handler
 *
 * p becomes the old signal (NULL was never set before).  If p is NULL then the
 * old signal is lost.
 * 
 * returns:
 *
 * 0 on success
 * -1 on failure
 */
int Signal_install( Signal *s, Signal *p );

/*
 * Sets the handler for a signal object
 *
 * This handler is ANY function.   The function used should take a Signal as
 * its only argument
 */
void Signal_setHandler( Signal *s, void (*Handler)(Signal *s) );

/*
 * Gets the handler for a signal object
 */
SIGHANDLE Signal_getHandler( Signal *s );

/*
 * Gets the handler we want to go to
 */
SIGHANDLE Signal_getFutureHandler( Signal *s );

/*
 * Sets the signal to deal with
 */
void Signal_setNum( Signal *s, int SigNum );

/*
 * Gets the signal the object is dealing with
 */
int Signal_getNum( Signal *s );

/*
 * Gets the signal that we want to go to
 */
int Signal_getFutureNum( Signal *s );

/*
 * Returns the process ID that caused the signal to happen
 *
 * returns -1 if no process caused a signal
 * returns 0 if the causing process is the process itself
 */
int Signal_getCaller( Signal *s );

/*
 * Returns the Code of the signal - This code is signal type specific
 */
int Signal_getCode( Signal *s );

/*
 * Resets a signal to its Default setting
 */
void Signal_reset( Signal *s );

/*
 * Ignores a signal for this process
 */
void Signal_ignore( Signal *s );

/*
 * Clears ALL set signals
 */
void Signal_clear();

/*
 * Wait on a signal
 *
 * This is a BLOCKING call!
 *
 * returns:
 * 1 on success
 * 0 is the signal is being ignored
 * -1 on a failure
 */
int Signal_wait( Signal *s );

#endif
