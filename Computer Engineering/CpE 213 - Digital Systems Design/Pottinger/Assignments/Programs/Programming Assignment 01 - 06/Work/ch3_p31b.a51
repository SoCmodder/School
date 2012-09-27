;********************************************************************;
;                      Chapter 3: Problem 31b                        ;
;                     Create 8 input NAND gate                       ;
;%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%;

CSEG AT 0	;Create code segment at address 0

LJMP START	;Jump beginning of code

CSEG AT 100H	;Create code segment at address 100H

START:	MOV R0,P1		;Move data on P1 to R0

	CJNE R0, #0FFH, NOT_EQ	;If there are any 0's, then the nand
	CLR P2.7		;output will be a 1, otherwise if all
	SJMP START		;1's, output is 0

NOT_EQ:	SETB P2.7		;Set output to 1 since there was at
	SJMP START		;least one 0
	END
