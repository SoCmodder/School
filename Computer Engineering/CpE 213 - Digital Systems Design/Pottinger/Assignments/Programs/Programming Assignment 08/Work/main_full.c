/********************************************************************/
/*					  Programming Assignment 8						*/
/*				Table Lookup - Restricted Output					*/
/*																	*/
/* This program calculates the tangent of an angle input on P1 and  */
/* outputs the result on P2.  The input angle is limited from -89   */
/* to 89 degrees.  The input 0x00 corresponds to -89 degrees and    */
/* 0xFF corresponds to 89 degrees.  Values of tangent at angles		*/
/* less than -70 degrees are made equal to 0x00.  Values of tangent	*/
/* at angles greater than 70 degrees are made equal to 0xFF.  The   */
/* value at tan(-70)=-2.747477 which corresponds to the output 0x00.*/
/* The value at tan(70)=2.747477 which corresponds to the output    */
/* 0xFF.															*/
/********************************************************************/


#include <reg51.h>	//Include register definitions

void main(void) {

	//Create lookup table
	code unsigned char tan[]={
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,8,12,16,
	19,23,26,29,32,35,38,41,43,45,48,50,52,54,56,58,59,61,63,65,66,68,69,
	70,72,73,75,76,77,78,79,81,82,83,84,85,86,87,88,89,90,91,92,92,93,94,
	95,96,97,97,98,99,100,101,101,102,103,103,104,105,106,106,107,108,108,
	109,110,110,111,111,112,113,113,114,115,115,116,116,117,118,118,119,
	119,120,120,121,122,122,123,123,124,124,125,126,126,127,127,128,128,
	129,130,130,131,131,132,132,133,134,134,135,135,136,136,137,138,138,
	139,139,140,141,141,142,143,143,144,144,145,146,146,147,148,148,149,
	150,151,151,152,153,153,154,155,156,157,157,158,159,160,161,162,162,
	163,164,165,166,167,168,169,170,171,172,173,175,176,177,178,179,181,
	182,184,185,186,188,189,191,193,195,196,198,200,202,204,206,209,211,
	213,216,219,222,225,228,231,235,238,242,246,251,255,255,255,255,255,
	255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
	255,255,255,255,255,255
	};

	while(1) {			//Repeat forever
		P2=tan[P1];		//Lookup output
	}
}

