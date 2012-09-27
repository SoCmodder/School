// keypad.c
//
// D. Beetner 
//
// A program SEGMENT to scan in the current state of a 16-key keypad
// and track new key pushes and releases.  This segment would likely
// be used as part of a larger program (that does something with the
// information).

// include 8051 SFR declarations
#include <reg51.h>

main(){
	// local variable declaration
	unsigned int old, new, pushes, rels; // track state of 16 keys
	unsigned char pat; // write a specific pattern to keypad

	old = 0xFFFF;
	while(1){		// read keypad over and over, "forever"

		// read state of keypad switches
		for (pat = 0x80; pat>0x08; pat>>=1){
			P3 = ~pat;
			new = (new<<4)|(P3&0x0F);
		}

		// find pushes are releases
		pushes = (new^old)&old;
		rels = (new^old)&new;

		// get ready for next scan
		old = new;

		//
		// lots of other code here -- do something with key states!
		//
	}
}
