;***********************************************************************;
;                         Chapter 3: Problem 29				;
;                 Create a 83.3 kHz square wave on P1.0			;
;***********************************************************************;

	CSEG AT 0	;Create code segment at address 0

	LJMP START	;Jump beginning of code

	CSEG AT 100H	;Create code segment at address 100H

START:	SETB P1.0		;Set P1.0 high

	MOV R1, #02H		;
WAIT1:	DJNZ R1, WAIT1		;

	CLR P1.0		;Set P1.0 Low
	NOP			;1 cycle
	NOP			;1 cycle
	NOP			;1 cycle
	SJMP START		;Loop to beginning (2 cycles)
	END
