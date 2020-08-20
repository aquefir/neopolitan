
.ifdef CFG_GBA

.section .text
.balign 4, 0
.globl memcpy
.code 32

@ memcpy
@ A fast memcpy implementation in ARM assembly for the GBA.
@
@ R0: destination address.
@ R1: source address.
@ R2: number of bytes to fill, in total.

memcpy:
	PUSH    {R4-R12,LR}
	CMP     R2, #40
	BLT     .Lcpybyword

.Lcpyby40:
	LDMIA   R1!, {R3-R12}
	STMIA   R0!, {R3-R12}
	SUB     R2, R2, #40
	BGE     .Lcpyby40

.Lcpybyword:
	CMP     R2, #4
	BLT     .Lcpybyhword

.Lwordloop:
	LDR     R3, [R1]
	STR     R3, [R0]
	ADD     R0, R0, #4
	SUB     R2, R2, #4
	BGE     .Lwordloop

.Lcpybyhword:
	CMP     R2, #2
	BLT     .Lcpybybyte

.Lhwordloop:
	LDRH    R3, [R1]
	STRH    R3, [R0]
	ADD     R0, R0, #2
	SUB     R2, R2, #2
	BGE     .Lhwordloop

.Lcpybybyte:
	LDRB    R3, [R1]
	STRB    R3, [R0]
	ADD     R0, R0, #1
	SUB     R2, R2, #1
	BGE     .Lcpybybyte

.Lcpy_end:
	POP     {R4-R12,LR}
	BX      LR

.size memcpy, .-memcpy

.endif
