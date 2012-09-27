#include <reg51.h>
#define DELAY (1000-10) //Delay time in microseconds

void output_freq( void )
{
	P0=TL1;
	P1=TH1;
}

void main( void )
{
	unsigned char j;
	TMOD=0x51; //Timer 1=16 Counter; Timer 0=16 Timer
	while (1) {
		TH1=0;
		TL1=0;
		for (j=100; j>0; j--) {
			TH0=-DELAY>>8;
			TL0=-DELAY&0xFF;
			TR0=1;
			TR1=1;
			while(!TF0);
			TR0=0;
			TF0=0;
		}
		TR1=0;

		output_freq();
	}
}
