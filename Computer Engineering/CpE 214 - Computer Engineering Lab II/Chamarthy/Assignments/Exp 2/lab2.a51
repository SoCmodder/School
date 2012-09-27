MOV A, #0
MOV R0, A
MOV A, #3
MOV R1, A
Loop:
MOV A, #5
CLR C
ADDC A, R0
MOV R0, A
MOV A, R1
CLR C
ADDC A, #0FFh
MOV R1, A
JZ Stop
SJMP Loop
Stop:
SJMP Stop
END
