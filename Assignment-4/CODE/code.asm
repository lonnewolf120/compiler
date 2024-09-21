.MODEL SMALL
.STACK 100H
.DATA
a DW ?
c DW ?
d DW ?
t1 DW ?
t2 DW ?
t3 DW ?
t4 DW ?
t5 DW ?
t6 DW ?
t7 DW ?
.CODE
MAIN PROC
	MOV AX, @DATA
	MOV DS, AX
	MOV AX, 2
	MOV a, AX

	MOV AX, 1
	MOV c, AX

	XOR DX, DX ;need to clear DX first
	MOV AX, c
	MOV BX, 2
	MUL BX
	MOV c, AX

	MOV AX, a
	MOV BX, t1
	ADD AX, BX
	MOV a, AX

	MOV AX, t2
	MOV BX, 1
	SUB AX, BX
	MOV t2, AX

	MOV AX, t3
	MOV d, AX

	MOV AX, a
	MOV BX, c
	SUB AX, BX
	MOV a, AX

	MOV AX, 2
	MOV BX, 3
	SUB AX, BX
	MOV 2, AX

	MOV AX, t5
	MOV c, AX

	XOR DX, DX ;need to clear DX first
	MOV AX, c
	MOV BX, 1
	MUL BX
	MOV c, AX

	MOV AX, t4
	MOV BX, t6
	SUB AX, BX
	MOV t4, AX

	MOV AX, t7
	MOV d, AX

	MOV AH, 02H
	MOV DX, a
	INT 21H
	MOV AH, 02H
	MOV DX, c
	INT 21H
	MOV AH, 02H
	MOV DX, d
	INT 21H
	MOV AH, 4CH
	INT 21H
MAIN ENDP
END MAIN
