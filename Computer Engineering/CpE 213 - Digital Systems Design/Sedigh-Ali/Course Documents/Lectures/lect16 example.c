/*****************************************
lect16_example.c
D. Beetner

A quick bit of code to show how to do a
few things in C for the 8051.  This program
isn't really useful for anything else
(maybe as a template?).

*****************************************/

// include special function register defs
// -- note: commented out for this example (so don't
// -------- redefine some SFRs
// #include <reg51.h>

// include mem-access functions (XBYTE[], etc)
#include <absacc.h>

// Declare some SFRs -- MUST BE GLOBAL!
	sfr P0 = 0x80;		//sfr named P0 located at addr 0x80
	sfr P1 = 0x90;

	sfr16 DPTR = 0x82;	// 16-bit sfr named DPTR at addr 0x82

	sbit z = P0^3;		// z is bit 3 of P0
	sbit carry = 0xD7;	// carry is at bit addr 0xD7

// Declare bit-addressable memory
// (must use sbits to access individual bits, hence global)
	unsigned char bdata bits; 	// a byte in bit-mem
	sbit bit4 = bits^4;			// bit4 is bit 4 of bits

// Declare some variables located _at_ a particular address
// MUST BE GLOBAL to use _at_
	char data myabs _at_ 0x42; // located at data addr 42H
	char xdata seven_seg _at_ 0x5280;	// at xdata addr 5280H

// function prototypes (declarations)
	char myfun(char);
	void afun(void);
	
// main routine
void main(void){

	//local variables
	bit y;				// a bit variable
	unsigned char bdata x = 0x2A;	// a byte located in bit mem
					// initialized as 0x2A
	int data aword;			// in data mem
	char code emsg[] = "ERROR";	// in code mem
	unsigned char xdata	xsensor;	// in xdata

	char blah;			// mem space SPEC'D BY COMPILER!
	int blab;				// MUCH EASIER ON PROGRAMMER!
	float blob;

//	sfr P2 = 0xA0;	// NOT ALLOWED

	// Some bit operations
	P0 = 0x00;	// clear sfr P0
	y = 1;		// set bit y
	z = y;		// set sbit z equal to bit y

	bits = 0;	// set variable bits (in bit mem) to 0
	bit4 = 1;	// set bit bit4 to 1


	// play with some variables at known locations
	myabs = 0x2A;	// set location 42 (myabs) to 0x2A
	DBYTE[0x42] = 0;

	// call a function
	myabs = myfun(blah);

}


// Define contents of function myfun
char myfun(char x) small{	// runs using a small memory model
	return x--;
}

// Define afun as a function responding to interrupt 0
// and using register bank 3
void afun(void) interrupt 0 using 3{
	static char x;

	x++;
}

