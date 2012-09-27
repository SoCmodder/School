xseg at 14A0H
myseg: DS 1

xseg at 5280H
theseg: DS 1

mydata segment data
	rseg mydata
mystack: DS 42
mybyte: DS 1

mycode segment code
	rseg mycode
	mov p1, #00H
	mov dptr, #14A0H
	mov a, #42h
	movx @dptr, A
	setb psw.4
	setb psw.3
	mov R4, #42h
	clr psw.4
	mov R6, #2AH
	mov 13H, #13
	mov 00H, #01110101B
	mov SP, #mystack
	mov mybyte, #12H
	push DPL
	push DPH
	pop DPL
	pop DPH
	jnb p1.2, next
	mov A, #42H
next:	JB p1.2, NEXT2
	mov A, P1
	mov dptr, #5280h
	movx @dptr, A
NEXT2:	mov A, P1
	Anl A, #00000100B
	JZ next1
	mov A, #42H
next1:	jnz NEXT3
	mov dptr, #5280h
	mov A, #42H
	movx @dptr, A
	CLR A
NEXT3:
	END;
