;********************************************************************;
;                      Chapter 3: Problem 31c                        ;
;         Create logic circuit in Problem 31.c, pg 78 ISM            ;
;%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%;

	CSEG AT 0	;Create code segment at address 0

	LJMP START	;Jump beginning of code

	CSEG AT 100H	;Create code segment at address 100H

START:	MOV C, P1.4	;Move P1.4 to carry bit
	ORL C, /P1.5	;Or carry with /P1.5
	ORL C, P1.6	;Or carry with P1.6
	MOV P1.7, C	;Output result on P1.7
	SJMP START	;Loop to beginning
	END

