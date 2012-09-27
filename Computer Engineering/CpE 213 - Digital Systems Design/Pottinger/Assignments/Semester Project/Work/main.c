#include <reg51.h>
#include <stdlib.h>
#include <project.h>

void main( void )
{
	char button;

	EA=1; 
	TMOD = 0x11;	//Set Timer 0 and Timer 1 into 16 bit Timer mode

	RESTART:	//Label to restart if player wins

	win();		//Flash lights and sound speaker

	/* Setup Powerdown Timer */
	ET0=1;
	TH0=(-50000)>>8;
	TL0=(-50000)&0xFF;
	TR0=1;
	
	initial();	//Set random initial light pattern

	while(1)	//Repeat forever
	{

		button=input();	//Read switches to get input
		press(button);	//Change LED's according to switch pressed

		if( led_read() == 0 )	//Check for winning state
		{
			goto RESTART;		//If player won, then restart
		}
	}
}

