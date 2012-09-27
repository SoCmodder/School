/********************************************************************/
/*					  Programming Assignment 8						*/
/* 				Direct Calculation - Restricted Input				*/
/*																	*/
/* This program calculates the tangent of an angle input on P1 and  */
/* outputs the result on P2.  The input angle is limited from -45   */
/* to 45 degrees.  The input 0x00 corresponds to -45 degrees and    */
/* 0xFF corresponds to 45 degrees.  The output of tangent in this   */
/* range is -1 to 1.  The output 0x00 corresponds to -1 and 0xFF    */
/* corresponds to 1.												*/
/********************************************************************/


#include <reg51.h>	//Include register definitions
#include <math.h>	//Include math libraries

/* Global Definitions */
#define DEG2RAD 3.14159265358979/180.
#define HEX2DEG 90/255.

void main(void) {
	while(1) {
		P2=(unsigned char)((float) (127.5*(1.0 + tan((P1*HEX2DEG-45.0)*DEG2RAD))));
	}
}

