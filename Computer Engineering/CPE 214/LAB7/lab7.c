/* Serial Port Usage Example */
#include <reg51.h>
#define uchar unsigned char
uchar incoming,outgoing,lastinchar; 		/* received/transmited messages */
bit newin,gone; 		/* These are global flags */


/* Serial port interrupt-service routine. Interrupt 4 is generated
by RI or TI, the serial-port interrupt */


void serint(void) interrupt 4 using 1{
	if(RI){ 							/* Has a byte been received */
		incoming=SBUF;						 /* read the received byte */
		RI=0; 										/* reset the interrupt flag */
		newin=1;								 /* notify the main function */
	}else if (TI){ 							/* have we just finished sending a byte */
		SBUF=outgoing;							/* send the next byte */
		TI=0; 								/* reset the interrupt flag */
		gone=1; 							/* notify the main function */
	}
}



/* The main function */
void main(void){
			/* INITIALIZE THE UART */
	TMOD=0x20; 			/* use timer1, mode 2 */
	TH1=0xfd; 			/* 9600 baud with a 11.059mHz clock */
	TCON=0x40; 			/* start baud clock*/
	SCON=0x50; 			/* enable receive */
	IE=0x90; 			/* enable serial int */
						/* start by sending the character 'x' */
	lastinchar=outgoing='X';
						/* initialize the flags */
	gone=0;
	newin=0;
						/* Initiate the serial interrupt */
	TI=1; 				/* Since the interrupt occurs when TI=1,
							this command will cause an interrupt which
							will initiate execution of function
							serint */
	/* Main loop (do forever) */
	for(;;){
							/* if the last character is "gone", put the
								lastcharacter read into the output buffer, outgoing */
	if (gone){
		outgoing=lastinchar;
		gone=0; /* reset the flag */
	}

							/* If a new character has been read in, read it
								from the incoming buffer, incoming */
	if(newin){
		lastinchar=incoming;
		newin=0; /* reset the flag */
	}
	} // end for
} // end main