;sigcur segment bit
;sigprev segment bit

	SETB P1.0

	MOV C,P1.0
	MOV 0x20.0,C

LOOP:	MOV C,0x20.0
	MOV 0x20.1,C
	MOV C,P1.0
	MOV 0x20.0,C

;	MOV C, 0x20.0
;	ANL C,/0x20.1
;	JNC LOOP
	MOV C,0x20.0
	JNC LOOP
	JB 0x20.1, LOOP


END
