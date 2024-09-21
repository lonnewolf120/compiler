MOV a, 10

MOV c, 5

MOV ax, c
MOV bx, 2
MUL bx
MOV t1, ax
MOV ax, a
MOV bx, t1
ADD ax, bx
MOV t2, ax
MOV ax, t2
MOV bx, 12
SUB ax, bx
MOV t3, ax
MOV d, t3

MOV ax, a
MOV bx, c
SUB ax, bx
MOV t1, ax
MOV ax, 2
MOV bx, 3
SUB ax, bx
MOV t2, ax
MOV ax, t2
MOV ax, t3
MOV bx, 5
MUL bx
MOV t4, ax
MOV ax, t1
MOV bx, t4
SUB ax, bx
MOV t5, ax
MOV d, t5


