$NOMOD51 
$NOCOND
;------------------------------------------------------------------------------
;  This file is part of the BL51 / L251 Banked Linker/Locater package
;  Copyright (c) 1988 - 2000 Keil Elektronik GmbH and Keil Software, Inc.
;  Version 2.03 (Code and Variable Banking for 8051 based Derivatives)
;------------------------------------------------------------------------------
;************************ Configuration Section *******************************
?B_NBANKS       EQU  4    ; Define max. Number of Banks                       *
;                         ; The following values are allowed: 2, 4, 8, 16, 32 *
;                         ; the max. value for ?B_BANKS is 32                 *
;                                                                             *
?B_MODE         EQU  1    ; 0 for Bank-Switching via 8051 Port                *
;                         ; 1 for Bank-Switching via XDATA Port               *
;                         ; 4 for user-provided bank switch code              *
;                                                                             *
?B_RTX          EQU  0    ; 0 for applications without RTX-51 FULL            *
;                         ; 1 for applications using RTX-51 FULL              *
;                                                                             *
?B_VAR_BANKING  EQU  0    ; Enable Variable Banking in XDATA and CODE memory  *
;                         ; 0 Variable Banking is disabled                    *
;                         ; 1 XDATA and CODE banking with same address lines  *
;                         ; 2 XDATA uses a different banking port             *
;                                                                             *
IF  ?B_VAR_BANKING <> 0;                                                      *
;-----------------------------------------------------------------------------*
; if ?B_VAR_BANKING is enabled define the following values                    *
;                                                                             *
?B_COMMON_XRAM  EQU  0    ; Specify if your hardware has uses XDATA RAM       *
;                         ; 0 no common RAM: complete 64KB XDATA is banked    *
;                         ; 1 all XDATA variables are located to common RAM   *
;                                                                             *
?B_INTR_ACCESS  EQU  0    ; 0 unlimited access to XDATA memory in interrupts  *
;                         ; 1 interupts access to XDATA variables is allowed  *
;                         ;   after call to  ToDo                             *
;                                                                             *
;-----------------------------------------------------------------------------*
ENDIF;                                                                        *
;                                                                             *
IF  ?B_MODE = 0;                                                              *
;-----------------------------------------------------------------------------*
; if ?BANK?MODE is 0 define the following values                              *
; For Bank-Switching via 8051 Port define Port Address / Bits                 *
;                                                                             *
P1              DATA    90H      ; I/O Port Address                           *
;                                                                             *
?B_PORT         EQU     P1       ; default is P1                              *
?B_FIRSTBIT     EQU     3        ; default is Bit 3                           *
;-----------------------------------------------------------------------------*
ENDIF;                                                                        *
;                                                                             *
IF  ?B_MODE = 1;                                                              *
;-----------------------------------------------------------------------------*
; if ?BANK?MODE is 1 define the following values                              *
; For Bank-Switching via XDATA Port define XDATA Port Address / Bits          *
?B_XDATAPORT    EQU     0FFFFH   ; default is XDATA Port Address 0FFFFH       *
?B_FIRSTBIT     EQU     0        ; default is Bit 0                           *
;-----------------------------------------------------------------------------*
ENDIF;                                                                        *
;                                                                             *
IF  ?B_MODE = 4;                                                              *
;-----------------------------------------------------------------------------*
; if ?BANK?MODE is 4 define the following switch macros                       *
; For bank switching via user-provided bank switch code you must define for   *
; each memory bank a own macro which contains the bank switch code.  The      *
; following example shows how to use the I/O lines P1.4 and P1.7 for bank     *
; switching.  Since you can select just 4 banks with two address lines, just  *
; four macros are defined.  The number of macros must conform with the number *
; ?B_NBANKS number, i.e. for an application with 16 memory banks you must     *
; define 16 macros.                                                           *
;                                                                             *
; IMPORTANT NOTES:                                                            *
; 1.  Eeach SWITCH macro must generate the same code size, otherwise the      *
;     BANKSWITCH code does not work correctly.                                *
; 2.  You must ensure that your bankswitch logic has a defined stated after   *
;     CPU reset.  We recommend that the following code is insert at the end   *
;     of the STARTUP.A51 file:                                                *
;                :                                                            *
;         EXTRN DATA (?B_CURRENTBANK)                                         *
;               MOV     ?B_CURRENTBANK,#0    ; select code bank 0             *
;               SWITCH0                      ; the code of your SWITCH0 macro *
;        		LJMP	?C_START                                              *
;                :                                                            *
; 3.  If you are using the RTX-51 real-time operating system this banking     *
;     mode cannot be used.                                                    *
;                                                                             *
P1              DATA    90H      ; I/O Port Address                           *
;                                                                             *
SWITCH0         MACRO            ; Switch to Memory Bank #0                   *
                CLR     P1.4     ; Clear Port 1 Bit 4                         *
                CLR     P1.7     ; Clear Port 1 Bit 7                         *
                ENDM                                                          *
;                                                                             *
SWITCH1         MACRO            ; Switch to Memory Bank #0                   *
                SETB    P1.4     ; Set   Port 1 Bit 4                         *
                CLR     P1.7     ; Clear Port 1 Bit 7                         *
                ENDM                                                          *
;                                                                             *
SWITCH2         MACRO            ; Switch to Memory Bank #0                   *
                CLR     P1.4     ; Clear Port 1 Bit 4                         *
                SETB    P1.7     ; Set   Port 1 Bit 7                         *
                ENDM                                                          *
;                                                                             *
SWITCH3         MACRO            ; Switch to Memory Bank #0                   *
                SETB    P1.4     ; Set   Port 1 Bit 4                         *
                SETB    P1.7     ; Set   Port 1 Bit 7                         *
                ENDM                                                          *
;                                                                             *
;-----------------------------------------------------------------------------*
ENDIF;                                                                        *
;                                                                             *
;******************************************************************************
;                                                                             *
; THEORY OF OPERATION                                                         *
; -------------------                                                         *
; The section below describes the code generated by BL51 or L251 and the      *
; operation of the L51_BANK.A51 module.  BL51/L251 generates for each         *
; function that is located in a code memory bank and called from the common   *
; area or a different code bank and entry into the INTRABANK CALL TABLE.  The *
; INTRABANK CALL TABLE is located in the SEGMENT ?BANK?SELECT and listed in   *
; the Linker MAP file. The entries in that TABLE have the following format:   *
;                                                                             *
;   ?FCT?1:  MOV  DPTR,#FCT     ; Load Address of target FCT                  *
;            JMP  ?B_BANKn      ; Switch to Bank and Jump to Target Code      *
;                                                                             *
; Instead of directly calling the function FCT, the Linker changes the entry  *
; to ?FCT?1.  This entry selects the bank where the function FCT is located   *
; and calls that function via the routines defined in this L51_BANK.A51 file. *
; The L51_BANK.A51 file contains two sets of functions for each bank:         *
;                                                                             *
; ?B_BANKn    is a routine which saves the entry of the ?B_SWITCHn function   *
;             for the current active bank on the STACK and switches to the    *
;             bank 'n'.  Then it jumps to the address specified by the DPTR   *
;             register.  It is allowed to modify the following registers in   *
;             the ?B_BANKn routine:  A, B, R0, DPTR, PSW                      *
;                                                                             *
; ?B_SWITCHn  is a function which selects the bank 'n'.  This function is     *
;             used at the end of a user function to return to the calling     *
;             code bank.  Only the following registers may be altered in the  *
;             ?B_SWITCHn function:  R0, DPTR                                  *
;                                                                             *
; The current active bank is stored in ?B_CURRENTBANK.  RTX-51 uses this      *
; variable to restore the code bank after a task switch.  To get correct      *
; results, ?B_CURRENTBANK must be set to the code bank before the hardware    *
; switch is done, or the code banking sequences must be interrupt protected.  *
;******************************************************************************

                NAME    ?BANK?SWITCHING

                PUBLIC  ?B_NBANKS, ?B_MODE, ?B_CURRENTBANK, ?B_MASK
                PUBLIC  ?B_FACTOR

; Standard SFR Symbols required in L51_BANK.A51
ACC     DATA    0E0H
B       DATA    0F0H
DPL     DATA    82H
DPH     DATA    83H
IE      DATA    0A8H
EA      BIT     IE.7


; generate Mask and Bank Number Information
IF      ?B_NBANKS <= 2
  MASK          EQU     00000001B
ELSEIF  ?B_NBANKS <= 4
  MASK          EQU     00000011B
ELSEIF  ?B_NBANKS <= 8
  MASK          EQU     00000111B
ELSEIF  ?B_NBANKS <= 16
  MASK          EQU     00001111B
ELSE
  MASK          EQU     00011111B
ENDIF     

IF  ?B_MODE = 0 ;**************************************************************

?B_FACTOR       EQU     1 SHL ?B_FIRSTBIT

?B_MASK         EQU     MASK SHL ?B_FIRSTBIT

BANKN           MACRO   N
BANK&N           EQU     N SHL ?B_FIRSTBIT
                ENDM

CNT             SET     0

                REPT    ?B_NBANKS
                BANKN   %CNT
CNT             SET     CNT+1
                ENDM


?B_CURRENTBANK  EQU     ?B_PORT

  ; Convert Bank No in Accu to Address * 8

  IF  ?B_FIRSTBIT = 0
  CONVBANKNO    MACRO
                SWAP    A
                RR      A
                ENDM
  ENDIF

  IF  ?B_FIRSTBIT = 1
  CONVBANKNO    MACRO
                RL      A
                RL      A
                ENDM
  ENDIF

  IF  ?B_FIRSTBIT = 2
  CONVBANKNO    MACRO
                RL      A
                ENDM
  ENDIF

  IF  ?B_FIRSTBIT = 3
  CONVBANKNO    MACRO
                ENDM
  ENDIF

  IF  ?B_FIRSTBIT = 4
  CONVBANKNO    MACRO
                RR      A
                ENDM
  ENDIF

  IF  ?B_FIRSTBIT = 5
  CONVBANKNO    MACRO
                RR      A
                RR      A
                ENDM
  ENDIF

  IF  ?B_FIRSTBIT = 6
  CONVBANKNO    MACRO
                SWAP    A
                RL      A
                ENDM
  ENDIF

  IF  ?B_FIRSTBIT = 7
  CONVBANKNO    MACRO
                SWAP    A
                ENDM
  ENDIF


SELECT          MACRO   N
LOCAL           XLABEL, YLABEL

                PUBLIC  ?B_BANK&N
?B_BANK&N:      
                MOV     A,?B_CURRENTBANK
                ANL     A,#?B_MASK
;;               CJNE    A,#BANK&N,XLABEL
;;               CLR     A
;;               JMP     @A+DPTR
;;
;;XLABEL:
                CONVBANKNO         ; Convert Bank Number to Address
                PUSH    ACC
                MOV     A,#HIGH ?BANK?SWITCH
                PUSH    ACC
;;YLABEL:
                PUSH    DPL
                PUSH    DPH
                LJMP    ?B_SWITCH&N
                ENDM


?BANK?SELECT    SEGMENT  CODE

                RSEG    ?BANK?SELECT
CNT             SET     0

                REPT    ?B_NBANKS
                SELECT  %CNT
CNT             SET     CNT+1

                ENDM



SWITCH          MACRO   N
                ORG     N * 8
                PUBLIC  ?B_SWITCH&N
  ?B_SWITCH&N:
  IF ?B_RTX = 0
    IF  N <> 0
                ORL     ?B_CURRENTBANK,#?B_MASK
    ENDIF
    IF  N <> (?B_NBANKS-1)
                ANL     ?B_CURRENTBANK,#(BANK&N OR NOT ?B_MASK) 
    ENDIF
                RET
  ELSE
    IF  N = 0
                ANL     ?B_CURRENTBANK,#(BANK&N OR NOT ?B_MASK) 
    ELSEIF  N <> (?B_NBANKS-1)
                MOV     R0,A
                MOV     A,#(BANK&N OR NOT ?B_MASK) 
                LJMP    SWITCHBNK
    ELSE
                ORL     ?B_CURRENTBANK,#?B_MASK
                RET
    ENDIF
  ENDIF                
                ENDM


?BANK?SWITCH    SEGMENT  CODE  PAGE

                RSEG    ?BANK?SWITCH
CNT             SET     0

                REPT    ?B_NBANKS
                SWITCH  %CNT

CNT             SET     CNT+1
                ENDM


  IF ?B_RTX = 1
    SWITCHBNK:  PUSH    IE
                CLR     EA
                ORL     ?B_CURRENTBANK, #?B_MASK
                ANL     ?B_CURRENTBANK, A
                POP     IE
                MOV     A,R0
                RET
  ENDIF

ENDIF  ; close block IF ?B_MODE = 0 *******************************************


IF ?B_MODE = 1 ;***************************************************************

?B_FACTOR       EQU     1 SHL ?B_FIRSTBIT

?B_MASK         EQU     MASK SHL ?B_FIRSTBIT

BANKN           MACRO   N
BANK&N           EQU     N SHL ?B_FIRSTBIT
                ENDM

CNT             SET     0

                REPT    ?B_NBANKS
                BANKN   %CNT
CNT             SET     CNT+1
                ENDM


?C_INITSEG      SEGMENT   CODE          ; Segment for Variable Initialization
                RSEG    ?C_INITSEG
                DB      01H             ; IData
                DB      ?B_CURRENTBANK  ; Init Current Bank
                DB      0               ; Set to Zero
                DB      41H             ; XData
                DW      ?B_XDATAPORT    ; Init XDATA Port
                DB      0               ; Set to Zero

                PUBLIC  ?B_XDATAPORT

?BANK?DATA      SEGMENT DATA
                RSEG    ?BANK?DATA
?B_CURRENTBANK: DS      1


IF ?B_RTX = 1 OR ?B_NBANKS > 16
  ; Convert Bank No in Accu to Address * 8

  IF  ?B_FIRSTBIT = 0
  CONVBANKNO    MACRO
                SWAP    A
                RR      A
                ENDM
  ENDIF

  IF  ?B_FIRSTBIT = 1
  CONVBANKNO    MACRO
                RL      A
                RL      A
                ENDM
  ENDIF

  IF  ?B_FIRSTBIT = 2
  CONVBANKNO    MACRO
                RL      A
                ENDM
  ENDIF

  IF  ?B_FIRSTBIT = 3
  CONVBANKNO    MACRO
                ENDM
  ENDIF

  IF  ?B_FIRSTBIT = 4
  CONVBANKNO    MACRO
                RR      A
                ENDM
  ENDIF

  IF  ?B_FIRSTBIT = 5
  CONVBANKNO    MACRO
                RR      A
                RR      A
                ENDM
  ENDIF

  IF  ?B_FIRSTBIT = 6
  CONVBANKNO    MACRO
                SWAP    A
                RL      A
                ENDM
  ENDIF

  IF  ?B_FIRSTBIT = 7
  CONVBANKNO    MACRO
                SWAP    A
                ENDM
  ENDIF
ENDIF


IF ?B_RTX = 0 AND ?B_NBANKS <= 16
  ; Convert Bank No in Accu to Address * 16
  IF  ?B_FIRSTBIT = 0
  CONVBANKNO    MACRO
                SWAP    A
                ENDM
  ENDIF

  IF  ?B_FIRSTBIT = 1
  CONVBANKNO    MACRO
                SWAP    A
                RR      A
                ENDM
  ENDIF

  IF  ?B_FIRSTBIT = 2
  CONVBANKNO    MACRO
                RL      A
                RL      A
                ENDM
  ENDIF

  IF  ?B_FIRSTBIT = 3
  CONVBANKNO    MACRO
                RL      A
                ENDM
  ENDIF

  IF  ?B_FIRSTBIT = 4
  CONVBANKNO    MACRO
                ENDM
  ENDIF

  IF  ?B_FIRSTBIT = 5
  CONVBANKNO    MACRO
                RR      A
                ENDM
  ENDIF

  IF  ?B_FIRSTBIT = 6
  CONVBANKNO    MACRO
                RR      A
                RR      A
                ENDM
  ENDIF

  IF  ?B_FIRSTBIT = 7
  CONVBANKNO    MACRO
                SWAP    A
                RL      A
                ENDM
  ENDIF
ENDIF


SELECT          MACRO   N
LOCAL           XLABEL, YLABEL

                PUBLIC  ?B_BANK&N
?B_BANK&N:      
                MOV     A,?B_CURRENTBANK
                ANL     A,#?B_MASK
;;              CJNE    A,#BANK&N,XLABEL
;;              SJMP    YLABEL
;;XLABEL:
                CONVBANKNO         ; Convert Bank Number to Address
                PUSH    ACC
                MOV     A,#HIGH ?BANK?SWITCH
                PUSH    ACC
;;YLABEL:
                PUSH    DPL
                PUSH    DPH
                LJMP    ?B_SWITCH&N

                ENDM


?BANK?SELECT    SEGMENT  CODE

                RSEG    ?BANK?SELECT
CNT             SET     0

                REPT    ?B_NBANKS
                SELECT  %CNT
CNT             SET     CNT+1

                ENDM


SWITCH          MACRO   N
  IF  ?B_RTX = 0 AND ?B_NBANKS <= 16
                ORG     N * 16
                PUBLIC  ?B_SWITCH&N
    ?B_SWITCH&N:
                MOV     R0,A
                MOV     A,#BANK&N
                MOV     DPTR,#?B_XDATAPORT
                MOV     ?B_CURRENTBANK,A
                MOVX    @DPTR,A
                MOV     A,R0
                RET
  ENDIF

  IF  ?B_RTX = 1 OR ?B_NBANKS > 16
                ORG     N * 8
                PUBLIC  ?B_SWITCH&N
    ?B_SWITCH&N:
                MOV     R0,A
                MOV     A,#BANK&N
                LJMP    SWITCHNOW
  ENDIF

                ENDM


?BANK?SWITCH    SEGMENT  CODE  PAGE

                RSEG    ?BANK?SWITCH
CNT             SET     0

                REPT    ?B_NBANKS
                SWITCH  %CNT

CNT             SET     CNT+1
                ENDM


  IF  ?B_RTX = 1 OR ?B_NBANKS > 16
    SWITCHNOW:  MOV     DPTR,#?B_XDATAPORT
    IF ?B_RTX = 0
                MOV     ?B_CURRENTBANK,A
                MOVX    @DPTR,A
    ELSE
;;;             PUSH    IE
;;;             CLR     EA
                MOV     ?B_CURRENTBANK,A
                MOVX    @DPTR,A
;;;             POP     IE
    ENDIF
                MOV     A,R0
                RET
  ENDIF

ENDIF  ; close block IF ?B_MODE = 1 *******************************************


IF  ?B_MODE = 4 ;**************************************************************

?B_FACTOR       EQU     0               ; Dummy Declarations
?B_FIRSTBIT     EQU     0
?B_MASK         EQU     MASK

?BANK?SELECT	SEGMENT CODE
?BANK?DATA      SEGMENT DATA
                RSEG    ?BANK?DATA
?B_CURRENTBANK: DS      1

BANK            MACRO   N
                PUBLIC  ?B_BANK&N
?B_BANK&N:
                PUSH    ?B_CURRENTBANK
                MOV     A,#HIGH ?BANK?SWITCH
                PUSH    ACC
                PUSH    DPL
                PUSH    DPH
                ENDM

SWITCH          MACRO   N
                PUBLIC  ?B_SWITCH&N
?B_SWITCH&N:
                MOV     ?B_CURRENTBANK,#LOW ?B_SWITCH&N
                SWITCH&N
                RET
                ENDM

?BANK?SWITCH    SEGMENT CODE PAGE

                RSEG    ?BANK?SWITCH
; Generate ?B_SWITCHn functions
CNT             SET     0

                REPT    ?B_NBANKS
                BANK    %CNT
                SWITCH  %CNT
CNT             SET     CNT+1
                ENDM

IF (HIGH ?BANK?SWITCH) <> (HIGH $)
ERROR BANK SWITCH CODE EXCEEDS 256 BYTES
ENDIF


;---- Initialization of ?B_CURRENTBANK and execution of SWITCH0:
;?C_C51STARTUP?1 SEGMENT CODE  
;                RSEG    ?C_C51STARTUP?1
;                CLR     A
;                MOV     ?B_CURRENTBANK,A       ; Init Current Bank
;                SWITCH0                        ; Execute SWITCH0 Macro


COMMON_XDATA	MACRO     ; Switch back to common XDATA bank
                SWITCH1			       ; Switch to XDATA Bank 1
		ENDM


ENDIF  ; close block IF ?B_MODE = 4 *******************************************
;?BANK?SELECT	SEGMENT CODE

                RSEG    ?BANK?SELECT

;************************  SWITCHBANK FUNCTION  *******************************
;                                                                             *
; SWITCHBANK allows use of bank-switching for C programs                      *
;                                                                             *
; prototype:   extern switchbank (unsigned char bank_number);                 *
;                                                                             *
;******************************************************************************
                PUBLIC  _SWITCHBANK

_SWITCHBANK:    MOV     A,R7

IF  ?B_VAR_BANKING <> 0 ;******************************************************

		SJMP	_SWITCHBANK_A

PUBLIC ?C_VBANKING
PUBLIC ?B_VAR_BANKING
PUBLIC ?B_COMMON_XRAM
PUBLIC ?B_INTR_ACCESS

C_VBANKING:
IF ?B_COMMON_XRAM = 0 
  IF ?B_INTR_ACCESS = 0
	        JBC	EA,ENA_Intr     ; Check EA and disable interrupts
 		CALL	SWITCH_VBANK    ; Switch to XDATA bank and make access
		COMMON_XDATA            ; Switch back to common XDATA bank
		RET

ENA_Intr:	CALL	SWITCH_VBANK    ; Switch to XDATA bank and make access
		COMMON_XDATA            ; Switch back to common XDATA bank
                BSET    EA              ; If EA was 1 enable interrupts again
		RET
  ELSE
                CALL	SWITCH_VBANK    ; Switch to XDATA bank and make access
		COMMON_XDATA            ; Switch back to common XDATA bank
		RET
  ENDIF
ENDIF

SWITCH_VBANK:	PUSH	DPL
		PUSH	DPH
		PUSH	ACC
		MOV	A,R3

IF  ?B_VARBANKING = 2

		JB	ACC.7,CONST_BANKING


ENDIF

CONST_BANKING:	ANL	A,#MASK

ENDIF  ; close block IF ?B_VAR_BANKING <> 0 ***********************************

IF  ?B_MODE = 0 ;**************************************************************

_SWITCHBANK_A:  SWAP    A
                RR      A
                MOV     DPTR,#?BANK?SWITCH
                JMP     @A+DPTR

ENDIF  ; close block IF ?B_MODE = 0 *******************************************

IF ?B_MODE = 1 ;***************************************************************

_SWITCHBANK_A:
IF ?B_NBANKS > 16 OR ?B_RTX = 1
                SWAP    A
                RR      A
ENDIF

IF ?B_NBANKS <= 16 AND ?B_RTX = 0
                SWAP    A
ENDIF
                MOV     DPTR,#?BANK?SWITCH
                JMP     @A+DPTR

ENDIF  ; close block IF ?B_MODE = 1 *******************************************


IF  ?B_MODE = 4 ;**************************************************************

S_ENTRY         MACRO   N
                DB      LOW ?B_SWITCH&N
                ENDM

_SWITCHBANK_A:
                ADD     A,#switch_tab+3-$
                MOVC    A,@A+PC
                MOV     DPTR,#?BANK?SWITCH
                JMP     @A+DPTR

switch_tab:     
CNT             SET     0

                REPT    ?B_NBANKS
                S_ENTRY %CNT
CNT             SET     CNT+1
                ENDM
ENDIF  ; close block IF ?B_MODE = 4 *******************************************


                END
