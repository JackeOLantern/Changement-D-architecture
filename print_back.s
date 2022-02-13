ADD R2, R2, #8
ADD R3, R3, #10
JMPt PC

label start
PUSH SP
POP R5

label loop
PUSH #33
POP R7
SYSCALL

CMP R7, R3
JEQ #fin

CALL #*shift
CALL #*inc

CMP R1, R2
JEQ #save
label return
JMP #loop

label save
PUSH R4
CALL #*reset
JMP #return

label inc
ADD R1, R1, #1
JMPt PC
RET

label shift
SHL R0, R1, #3
SHL R7, R7, R0
ADD R4, R4, R7
JMPt PC
RET

label reset
XOR R4, R4, R4
XOR R1, R1, R1
JMPt PC
RET

label fin
PUSH R4
PUSH #0
PUSH #32
POP R7
PUSH R5
POP R6
SYSCALL

PUSH #34
POP R7
SYSCALL
