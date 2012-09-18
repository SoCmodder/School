/*
 * Author: Brian Sea
 * Date: 12/30/03
 *
 * This file contains the object used the execute commands.  This "executor" is
 * fashioned in an object-oriented fashion.
 */

#ifndef EXECUTOR_H_
#define EXECUTOR_H_

#include "parser.h"

/*
 * Opaque Executor structure
 *
 * NORE:  You cannot create this structure outright, you must use a pointer to
 * it.
 */

typedef struct exector_t Executor;

/*
 * Creates a new executor
 *
 * returns NULL on failure
 *
 * A new executor object is return on success
 */
Executor *Executor_new();

/*
 * Frees up the executor
 *
 * e is set to NULL
 */
void Executor_free( Executor *e );

/*
 * Executes the next command sequence in the parser
 *
 * returns:
 *
 * The child PID on success
 * 0 if no executable was run
 * -1 on error
 */
int Executor_execute( Executor *e, Parser *p );

/*
 * Adds the "special" characters to the Executor, e.
 * The characters are used to indicate the end of a complete command sequence.
 *
 * returns:
 *  0 on sucess
 *  -1 on failure
 */
int Executor_setSpecialDelimiters( Executor *e, char *delimits );

/* 
 * Returns the delimiters used by the executor, e
 *
 * returns:
 *  The string of special characters on sucess
 *  NULL on failure
 */
char *Executor_getSpecialDelimiters( Executor *e );

#endif


