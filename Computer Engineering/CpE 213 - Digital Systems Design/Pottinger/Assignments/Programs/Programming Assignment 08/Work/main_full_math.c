/********************************************************************/
/*					  Programming Assignment 8						*/
/* 				Direct Calculation - Restricted Output				*/
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
#include <math.h>	//Include math libraries

/* Global Definitions */
#define DEG2RAD 3.14159265358979/180	//Convert Degrees to Radians
#define HEX2DEG 89*2/255.				//Convert Hex to Degrees
#define CUTOFF tan(70*DEG2RAD)			//Cutoff output
#define SCALE 255/(2.0 * CUTOFF)		//Scaling factor

float angle;	//Angle variable

void main(void) {
	while(1) {
		angle=P1*HEX2DEG-89.0;	//Calculate angle

		if (angle < -70.0)		//Case 1: angle < -70
			{
			P2=0x00;
			}
		else if (angle > 70.0)	//Case 2: angle > 70
			{
			P2=0xFF;
			}
			else				//Case 3: -70 < angle < 70
				{
				P2=(unsigned char)((float) (SCALE*(CUTOFF + tan(angle*DEG2RAD))));
				}
	}
}

