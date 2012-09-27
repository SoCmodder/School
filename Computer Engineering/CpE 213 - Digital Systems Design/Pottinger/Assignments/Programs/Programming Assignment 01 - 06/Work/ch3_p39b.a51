;***********************************************************************;
;                         Chapter 3: Problem 39                		;
;		         Create 7 segment decoder			;
;***********************************************************************;

	CSEG AT 0

	LJMP START

TABLE:	db 3FH, 06H, 5BH, 4FH, 66H, 6DH, 7DH, 07H, 7FH, 67H, 77H, 7CH, 39H, 5EH, 79H, 71H

	CSEG AT 100H

START:	MOV P3, #0FH		;Allow bits 0 - 3 to be inputs

LOOP:	MOV A, P3		;Read P3

	ANL A, #0FH		;Mask input bits
	MOV DPTR, #TABLE	;Get table address
	MOVC A,@A+DPTR		;Get ith entry in table

	MOV P1, A		;Output to P1
	SJMP LOOP		;Repeat forever

	END
