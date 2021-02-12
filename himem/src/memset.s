@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@                             neopolitan himem                             @@
@@                                                                          @@
@@                      Copyright © 2019-2021 Aquefir                       @@
@@                       Released under BSD-2-Clause.                       @@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

.section .text
.balign 4, 0
.globl memset
.code 32

@ memset
@ A fast memfill implementation in ARM assembly for the GBA.
@
@ R0: address to start fill at.
@ R1: u8 to fill memory with.
@ R2: number of bytes to fill, in total.

memset:
	PUSH    {R4-R12,LR}
	@ duplicate bytes into the whole register
	AND     R1, R1, #0xFF
	LSL     R3, R1, #8
	LSL     R4, R1, #16
	LSL     R5, R1, #24
	ORR     R1, R1, R3
	ORR     R1, R1, R4
	ORR     R1, R1, R5
	CMP     R2, #40
	BLT     .Lfillbyword
	MOV     R3, R1
	MOV     R4, R1
	MOV     R5, R1
	MOV     R6, R1
	MOV     R7, R1
	MOV     R8, R1
	MOV     R9, R1
	MOV     R10, R1
	MOV     R11, R1
	MOV     R12, R1

.Lfillby40:
	STMIA   R0!, {R3-R12}
	SUB     R2, R2, #40
	BGE     .Lfillby40

	CMP     R2, #4
	BLT     .Lfillbyhword

.Lfillbyword:
	CMP     R2, #4
	BLT     .Lfillbyhword

.Lwordloop:
	STR     R1, [R0]
	ADD     R0, R0, #4
	SUB     R2, R2, #4
	BGE     .Lwordloop

.Lfillbyhword:
	CMP     R2, #2
	BLT     .Lfillbybyte

.Lhwordloop:
	STRH    R1, [R0]
	ADD     R0, R0, #2
	SUB     R2, R2, #2
	BGE     .Lhwordloop

.Lfillbybyte:
	STRB    R1, [R0]
	ADD     R0, R0, #1
	SUB     R2, R2, #1
	BGE     .Lfillbybyte

.Lfill_end:
	POP     {R4-R12,LR}
	BX      LR

.size memset, .-memset
