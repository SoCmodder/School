;------------------------------------------------------------------------------
;  This file is part of the C51 Compiler package
;  Copyright (c) 1988-1999 Keil Elektronik GmbH and Keil Software, Inc.
;------------------------------------------------------------------------------
;  INIT751.A51:  This code is executed, if the application program contains
;                initialized variables at file level.
;
;  To translate this file use A51 with the following invocation:
;
;     A51 INIT751.A51
;
;  To link the modified INIT.OBJ file to your application use the following
;  BL51 invocation:
;
;     BL51 <your object file list>, INIT751.OBJ <controls>
;
;------------------------------------------------------------------------------
;
;  User-defined Watch-Dog Refresh.
;
;  If the C application contains many initialized variables uses a watchdog
;  it might be possible that the user has to include a watchdog refresh into
;  the initialization process. The watchdog refresh routine can be included
;  in the following MACRO and can alter all CPU registers except
;  DPTR.
;
WATCHDOG	MACRO
				; Include any Watchdog refresh code here
		ENDM
;------------------------------------------------------------------------------

		NAME	?C_INIT


?C_C51STARTUP	SEGMENT   CODE
?C_INITSEG	SEGMENT   CODE		; Segment with Initializing Data


		EXTRN CODE (MAIN)
		PUBLIC	?C_START

		RSEG	?C_C51STARTUP
INITEND:	AJMP	MAIN

IorPData:				; If CY=1 PData Values
		CLR	A
		MOVC	A,@A+DPTR
		INC	DPTR
		MOV	R0,A		; Start Address
IorPLoop:	CLR	A
		MOVC	A,@A+DPTR
		INC	DPTR
		MOV	@R0,A
Common:		INC	R0
		DJNZ	R7,IorPLoop
		SJMP	Loop

Bits:		CLR	A
		MOVC	A,@A+DPTR
		INC	DPTR
		MOV	R0,A
		ANL	A,#007H
		ADD	A,#Table-LoadTab
		XCH	A,R0
		CLR	C	
		RLC	A		; Bit Condition to Carry
		SWAP	A
		ANL	A,#00FH
		ORL	A,#20H		; Bit Address
		XCH	A,R0		; convert to Byte Addressen
		MOVC	A,@A+PC
LoadTab:	JC	Setzen
		CPL	A
		ANL	A,@R0
		SJMP	BitReady
Setzen:		ORL	A,@R0
BitReady:	MOV	@R0,A
		DJNZ	R7,Bits
		SJMP	Loop

Table:		DB	00000001B
		DB	00000010B
		DB	00000100B
		DB	00001000B
		DB	00010000B
		DB	00100000B
		DB	01000000B
		DB	10000000B
		

?C_START:	
		MOV	DPTR,#?C_INITSEG
LOOP:		CLR	A
		MOV	R6,#1
		MOVC	A,@A+DPTR
		JZ	INITEND
		INC	DPTR
		MOV	R7,A
		ANL	A,#3FH
		JNB	ACC.5,NOBIG
		ANL	A,#01FH
		MOV	R6,A
		CLR	A
		MOVC	A,@A+DPTR
		INC	DPTR
		JZ	NOBIG
		INC	R6
NOBIG:		XCH	A,R7
		ANL	A,#0C0H		; Typ is in Bit 6 and Bit 7
		ADD	A,ACC
		JZ	IorPDATA
		JC	Bits
		SJMP	$

		RSEG	?C_INITSEG
		DB	0

		END

