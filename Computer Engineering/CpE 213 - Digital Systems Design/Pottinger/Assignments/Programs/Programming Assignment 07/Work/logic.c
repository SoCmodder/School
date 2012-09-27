/************************************************************************************/
/*      					Program Assignment 7									*/
/*																					*/
/*            Create a controller logic circuit for a DC motor						*/
/************************************************************************************/

#include <reg51.h>		//Include register definitions

sbit A1=P1^0;			//Define Input and Output bits
sbit B1=P1^1;
sbit C1=P1^2;
sbit Motor_on=P1^3;

void main(void) {

	A1=B1=C1=1;			//Initialize input ports
	while(1) {			//Repeat forever
		Motor_on = ~A1 | (B1 ^ C1);	//Compute output
	}
}
