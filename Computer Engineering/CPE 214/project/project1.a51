;AUTHORS: Adrein Seguy and Brent Powers
;DATE: NOV 10, 2005
;DESCRIPTION: Code for Project 1 of COMPE 213
;FILE: project1.a51


#include <reg932.inc>  ;include file to define registers


	MOV P0M1, #00H	;Set the port modes to push-pull (standard 8051 I/O configuration)
	MOV P0M2, #0FFH  ;Set the port modes to push-pull (standard 8051 I/O configuration)
	SETB P0.0   ;Set switch pin as an input pin
	SETB P0.1   ;Make sure the light is set to off
	CLR P0.2     ; Make sure that the Buzzer is off
	MOV TMOD, #10H  ;Set timer to the correct mode
	MOV R0, #00H    ;Initialize button press counter
	MOV R1, #00H    ;Initialize timer counter

button:	JB P0.0, button  ;Checks to see if button is pressed, loops until pressed
	SJMP check

check:	MOV TL1, #0F0H    ;Delay sequence, generating a delays of a few milliseconds
	MOV TH1, #0D8H
	SETB TR1
	SJMP again

again:	JNB TF1, again   ;counter running
	INC R1		;increment timer counter
	CLR TR1		;reset counter
	CLR TF1    	;clear timmer overflow flag
	CJNE R1,#077H,check ;jump is the counter has ran 77H times
	JNB P0.0, button   ;jump if button released
	INC R0		;number of button presses
	MOV R1,#00H	;reset the counter timer
	SETB P0.2	;turn buzzer on
buzzcounter:SETB TR1	;start timer for buzzer	
	
buzzer:	JNB TF1, buzzer	   ;run buzzer for counter
	inc R1		;increaes timer counter
	CLR TR1		;reset counter
	CLR TF1	;clear timmer overflow flag
	CJNE R1,#0FH,buzzcounter  ;run until timer counter has reached 0FH
	CLR P0.2     ;turn the buzzer off
	SJMP light1a

light1a: CJNE R0,#01h,light2a ;enter loop if one button press
light1b: CLR P0.1	;
	 SETB P0.1	;Sequence to provide 3 machine cycles with light off and one on 
	 JB P0.0, light1b	; stop sequence once button is pressed again
	 SETB P0.1		;turn light off
  	 SJMP button		;just to the software debounce
	
light2a: CJNE R0,#02h,light3a	;enter loop if two button press
light2b: SETB P0.1
	 NOP		;Sequence to provide 3 machine cycles with light off and 3 on
	 NOP
	 CLR P0.1
	 JB P0.0, light2b	; stop sequence once button is pressed again
	 SETB P0.1	;turn light off
	 SJMP button		;just to the software debounce

light3a: CJNE R0,#03h,light4a	;enter loop if three button press
light3b: SETB P0.1	;Sequence to provide 1 machine cycles with light off and 3 on
	 CLR P0.1
	 JB P0.0, light3b	; stop sequence once button is pressed again
	 SETB P0.1	;turn light off
	 SJMP button

light4a: CJNE R0,#04h,light5	;enter loop if four button press
light4b: CLR P0.1	;Sequence to set the light on
	 JB P0.0, light4b 	; stop sequence once button is pressed again
	 SETB P0.1	;turn light off
	 SJMP button

light5:  SETB P0.1	;enter loop if five button press ;turn light off
	 MOV R0,#00h	;reset number of button presses to zero
	 JB P0.0, light5  ;wait for button and jump again
	 SJMP button

END
