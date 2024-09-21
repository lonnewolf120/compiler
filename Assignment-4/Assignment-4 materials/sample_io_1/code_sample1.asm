MOV ax, 1
MOV bx, 2
ADD ax, bx
MOV t1, ax

MOV ax, 5
MOV bx, 9
MUL bx
MOV t1, ax
MOV ax, t1
MOV bx, 2
SUB ax, bx
MOV t2, ax
MOV ax, t2
MOV bx, 4
ADD ax, bx
MOV t3, ax
MOV a, t3

MOV ax, z
MOV bx, 5
SUB ax, bx
MOV t1, ax
MOV ax, t1
MOV ax, u
MOV bx, t2
ADD ax, bx
MOV t3, ax
MOV x, t3


