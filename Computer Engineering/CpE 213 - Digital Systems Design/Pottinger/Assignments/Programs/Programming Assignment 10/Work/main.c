#include <reg51.h>

sbit P0_0=P0^0;
sbit D=P0^1;
sbit Q=P0^2;
void Ex0Isr(void) interrupt 0 {
	P0_0= ~P0_0;
}

void Ex1Isr( void ) interrupt 2 {
	Q=D;
}

void main( void ) {
	IT0=1;  //enable negative edge triggered Int0
	IT1=1;  //enable negative edge triggered Int1
	EX0=1;  //enable external interrupt 0
	EX1=1;  //enable external interrupt 1
	EA=1;	//enable global interrupts
	while(1) P1=5*P2;
}
