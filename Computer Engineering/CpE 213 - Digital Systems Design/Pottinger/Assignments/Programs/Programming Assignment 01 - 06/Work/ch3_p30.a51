;***********************************************************************;
;                        Chapter 3: Problem 30				;
;         Create a 4 us active-high pulse on P1.7 every 200 us		;
;***********************************************************************;

CSEG AT 0	;Create code segment at address 0

LJMP START	;Jump beginning of code

CSEG AT 100H	;Create code segment at address 100H

START:	SETB P1.7	;Set P1.7 high
	NOP		;1 cycle
	NOP		;1 cycle
	NOP		;1 cycle

	CLR P1.7	;Clear P1.7

	MOV R1, #60H	;Wait 193 cycles
WAIT2:	DJNZ R1, WAIT2	;

	SJMP START	;Loop to beginning (2 cycles)

	END
