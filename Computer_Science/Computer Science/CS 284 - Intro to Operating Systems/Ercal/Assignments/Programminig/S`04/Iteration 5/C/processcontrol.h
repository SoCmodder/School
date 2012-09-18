/*
 * Author: Brian Sea
 * Date: 1/2/04
 *
 * This file implements a list that can be generically
 */

#ifndef LIST_H_
#define LIST_H_

#include <stdlib.h>
#include <stdio.h>
#include "process.h"

static Process *RUNNING = NULL;

/*
 * Add a process to the end of the background list
 */
void ProcControl_add( Process *p );

/*
 * Returns, but does not remove the process at Num
 */
Process *ProcControl_get( int Num );

/*
 * Retuns, but not remove the process with PID Num 
 */
Process *ProcControl_getPID( int Num );

/*
 * returns the process p that is in the background list at Num
 */
Process *ProcControl_remove( int Num );

/*
 * return the process p that has the PID Num
 */
Process *ProcControl_removePID( int Num );

/*
 * Get the number of process in the list
 */
int ProcControl_numProcs();

/*
 * Prints a table of backgrounded Processes to "out" 
 */
void ProcControl_printTable( FILE *out );


#endif
