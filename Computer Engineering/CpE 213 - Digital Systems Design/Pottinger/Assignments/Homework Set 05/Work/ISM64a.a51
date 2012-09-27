CSEG AT 0	;Create code segment at address 0

LJMP START	;Jump beginning of code

CSEG AT 100H	;Create code segment at address 100H

START:	MOV A,#0x80
	MOV R7,#8
LOOP:	RLC A
	XCH A, 0F0H
	RRC A
	XCH A,0F0H
	DJNZ R7, LOOP
	XCH A, 0F0H
	END
