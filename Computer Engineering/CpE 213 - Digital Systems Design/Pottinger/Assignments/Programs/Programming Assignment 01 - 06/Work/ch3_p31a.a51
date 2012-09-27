;********************************************************************;
;                      Chapter 3: Problem 31A                        ;
;                     Create 3 input NOR gate                        ;
;%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%;

CSEG AT 0	;Create code segment at address 0

LJMP START	;Jump beginning of code

CSEG AT 100H	;Create code segment at address 100H

START:	MOV C, P1.4	;Or bits 4, 5, 6 of P1
	ORL C, P1.5
	ORL C, P1.6
	CPL C		;Complement the result
	MOV P1.7, C	;Output the result to P1.7
	SJMP START	;Loop to beginning
	END
