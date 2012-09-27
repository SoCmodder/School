// Example. c 
/* A program (segment) to read values from P0 and store these values in
an array */

// include statements
	#include <reg51.h>

// definition of constants
	#define ARRAYSIZE 42	// note: no semicolon!
	#define DELAYCYCLES 5280

// function declarations (not definitions)
	void delay (int cycles);         //a typical function prototype

// global variables (note: I haven't used any -- bad programming practice!)

/* Start main function */
void main ( void) {        // pass and return nothing

	// local variables
	int i ;
	unsigned char array [ARRAYSIZE] ;

	/* clear array */	
	i = 0;
	do{
		array[i] = 0;   // initialize to 0 
	} while (i++<ARRAYSIZE) ;

	/* read values from P0 */
	i = 0;
	while(i<42) {
		array [i] = P0 ;	// put value in array
		i++;	// increment by 1     
		delay (DELAYCYCLES) ;     // wait before adding another value to array
	}
} // end function main	

/* Function delay: Do nothing for a given number of loops */ 

void delay(int cycles) {         // return nothing, passed int number of cycles

	// local variables (note: cycles is local too)	
	int i ;
	
	// local code	
	//Do nothing for given number of cycles 

	for (i=0 ; i<cycles ; i++) { ; }
} // end function delay (and return nothing)