/*
 * Author: Brian Sea
 * Date: 12/31/03
 *
 * This file declares a process.  This structure is used to symbolize a child
 * process that is manipulated by an Executor
 */

#ifndef PROCESS_H_
#define PROCESS_H_

#include <stdio.h>


/*
 * definitions for Process_wait()
 */
#define PROCESS_NOWAIT  1
#define PROCESS_WAIT    0 

/*
 * Definitions for Process States
 */
#define PROCESS_RUNNING 1<<1
#define PROCESS_SUSPEND 1<<2
#define PROCESS_REAP    1<<3
#define PROCESS_DONE    1<<4
#define PROCESS_NONE    1<<5

/*
 * Object oriented - You need to use pointers.
 */
typedef struct process_t Process;

/*
 * Makes a process with defaults
 *
 * returns:
 * NULL on failure
 *
 * A new process object is returned on success
 */
Process *Process_new();

/*
 * Frees up a process
 *
 * p is set to NULL
 */
void Process_free( Process *p );

/*
 * Sets the Command to run
 *
 * The command will be *copied* into the process
 */
void Process_setCommand( Process *p, char *Command );

/*
 * Adds an argument to the argument table of the process
 *
 * The argument will be *copied* into the process
 */
void Process_addArgument( Process *p, char *Argument );

/*
 * Clears the argument table of the Process p
 */
void Process_clearArguments( Process *p );

/*
 * Start the process
 *
 * returns:
 *
 * the Child PID on success
 * -1 if the file was not found
 * 0 on fork failure
 */
int Process_start( Process *p );

/*
 * Suspend the process
 *
 * returns:
 * 0 on success
 * -1 on failure
 */
int Process_suspend( Process *p );

/*
 * Resume the process
 *
 * returns:
 * 0 on success
 * -1 on failure
 */
int Process_resume( Process *p );

/*
 * Kill the process
 *
 * returns:
 * 0 on success
 * -1 on failue
 */
int Process_kill( Process *p );

/*
 * Wait on the process to finish
 *
 * Set wait to 0 if this call should be non-blocking
 * returns:
 *
 * 0 on success
 * -1 on failure
 */
int Process_wait( Process *p, int wait );

/*
 * Sends a signal SigNum to the process
 * 
 * Returns:
 *  0 on sucess
 *  -1 on failure
 */
int Process_sendSig( Process *p, int SigNum );

/*
 * Returns the PID of process p
 */
int Process_getPID( Process *p );

/* 
 * Returns whether a process has exited safely
 *
 * returns:
 * -1 if the process has not returned
 * 0 if the process returned safely
 * 1 if the process was signaled to exit
 */
int Process_howExit( Process *p ); 

/*
 * Returns the status number of the process p
 *
 * returns:
 * 
 * Exit status IF AND ONLY IF Process_howExit() returned 0
 * Signal number IF AND ONLY IF Process_howExit() returned 1
 * MEANLESS if Process_howExit() returned -1
 */
int Process_getExitState( Process *p );

/*
 * Print out the argument table
 */
void Process_printTable( Process *p, FILE *out );

/*
 * Prints the command only
 */
void Process_printCommand( Process *p, FILE *out );

/*
 * Return the current known state of the process
 */
int Process_getState( Process *p );

#endif
