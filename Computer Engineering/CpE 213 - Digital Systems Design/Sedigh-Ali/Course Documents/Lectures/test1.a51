	mov 2AH, #042H
	mov A, #0F6H
label:	inc A
	jmp label
stop:	jmp stop
	end
