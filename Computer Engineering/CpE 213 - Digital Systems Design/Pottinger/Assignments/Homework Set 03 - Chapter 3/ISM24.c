#include <reg51.h>

#define uchar unsigned char
char code msg[]="Pump on";
bit b_Pump_On;
uchar bdata flags;
sbit flag0=flags^0;
uchar xdata buf[10] _at_ 0x8000;
uchar idata ivar;
uchar pdata pvar;
uchar i;

void main(void) {
	b_Pump_On=1;
	i=0;
	do buf[i]=msg[i]; while(msg[i++]!='\0');
	flag0=b_Pump_On;
	ivar=25;
	pvar=33;
	while(1);
	}


