;
; Demonstrate a few basics for ASM programs
;********************************************

;Declare some constants
	TheAnswer	EQU	42

;********************************************
mydata 	segment data	; declare mydata as segment of internal direct data
	rseg mydata	; start relocatable segment 
			; (contents defined immediately below)

mybyte:	DS	1	; declare 1-byte variable mybyte
mystack: DS	42	; set aside 42 byte (array) for an internal stack

;********************************************
myconst segment code	; declare myconst as segment of type code
	rseg myconst	; start relocatable segment
			; (contents defined immediately below)

lookup: DB	1,2,3,4,5	; define table of constants

;********************************************
mybits	segment bit	; declare mybits as segment of bit memory
	rseg mybits	; start relocatable segment
			; (contents defined immediately below)

mybitvar: DBIT	1	; define 1-bit variable mybitvar

;********************************************
myxdata	segment xdata	; declare mybits as segment of external memory
	rseg myxdata	; start relocatable segment
			; (contents defined immediately below)

xstuff: DS	1	; define 1 byte variable xstuff


;******************************************** 
; create variables "outside" of a segment
	anothervar DATA 7FH	; declare variable anothervar located at 7FH in datamem
	anxvar XDATA 5280H	; declare variable anxvar located at 5280H in external datamem

;********************************************
CSEG at 0000H		; begin definition of a code segment located at 0000H
			; (contents defined immediately below)

	mov mybyte,#42H	; intialize mybyte with 42H
	mov A, mybyte	; load A with contents of mybyte
	mov R0,#mybyte	; mov address of mybyte into R0
	mov @R0, #0FFH	; mov FF into location pointed to by R0
	xch A,mybyte	; exchange bytes

	mov mybyte, #TheAnswer	; use constant TheAnswer
	
	mov SP,#mystack	; initialize SP
	push mybyte	; push mybyte onto stack
	mov A, mystack+1	; assembler increments address of mystack by 1

	mov DPTR, #xstuff	; load DPTR with location of variable xstuff
	movx @DPTR, A	; load external var xstuff (DPTR)  with contents of A

	setb PSW.7	; set carry flag
	clr CY		; clear carry flag
	setb 0D0H.7	; set carry flag

	JBC CY,arith	; jump to arith and clear CY if CY=1

	NOP		; do nothing
	NOP		; do nothing
	NOP		; do nothing

arith:	MOV B, #10D	; load B with 10 decimal
	MUL AB		; multiply A and B

	call blah	; call function blah

stop:	JMP stop	; end, for all practical purposes

;********************************************
; function blah, in its own code segment
;********************************************
blahfunc segment code	; declare blahfunc as a segment of type code
	rseg blahfunc	; begin relocatable code segment blahfunc

blah:	MOV A, #01111111B ; pre-load ACC
	ANL A, PSW	; clear ....
	MOV PSW, A	; carry bit using byte inst.
	ret		; return to calling location