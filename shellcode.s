JMPt PC


CALL #print_welcome
CALL #get_input

label fini
PUSH #34
POP R7
SYSCALL



label get_input
POP R4
PUSH #*check_pass
MOV R4, SP

JMP #*init_get_input
label init_get_input
XOR R0, R0, R0
ADD R0, R0, #10
XOR R1, R1, R1
ADD R1, R1, #8
XOR R2, R2, R2
XOR R5, R5, R5
JMPt PC


label start_loop_get_input
JMP #*get_input_thumb
label get_input_thumb
XOR R7, R7, R7
ADD R7, R7, #33
JMPt PC
SYSCALL
CMP R7, R0
JEQ #end_loop_get_input

CALL #shift_and_add
CALL #*inc_r2
CMP R2, R1
JEQ #save_r3

JMP #start_loop_get_input

label save_r3
PUSH R3
CALL #*reset
JMP #start_loop_get_input


label end_loop_get_input
PUSH R3
MOV R6, R4
JMP #*print_get_input
label print_get_input
ADD R0, R5, #8
ADD R5, R5, R2
XOR R7, R7, R7
ADD R7, R7 #32
JMPt PC
SYSCALL
JMP #*reset_sp
label reset_sp
SUB SP, SP, R0
JMPt PC
RET


label reset
ADD R5, R5, #8
XOR R2, R2, R2
XOR R3, R3, R3
JMPt PC
RET

label shift_and_add
PUSH R2, R7
JMP #*shift_and_add_thumb
label shift_and_add_thumb
SHL R2, R2, #3
SHL R7, R7, R2
ADD R3, R7, R3
JMPt PC
POP R7, R2
RET


label inc_r2
ADD R2, R2, #1
JMPt PC
RET


label print_welcome
MOV R6, SP
PUSH #69408608444752
PUSH #32
POP R7
SYSCALL
JMP #*clear_sp_1
label clear_sp_1
SUB SP, SP, #8
JMPt PC
RET


label print_gg
MOV R6, SP
PUSH #2180935
PUSH #32
POP R7
SYSCALL
JMP #*clear_sp_2
label clear_sp_2
SUB SP, SP, #8
JMPt PC
RET

label check_pass
XOR R5, R5, #24
SUB R2, R2, R2
ADD SP, SP, #32
JMPt PC
CMP R5, R2
JEQ #length_ok
CALL #print_nop
CALL #fini
RET

label length_ok
POP R0, R1, R2
JMP #*init_check
label init_check
XOR R3, R2, R2
XOR R4, R3, #8
JMPt PC

label loop_init
CMP R4, #0
JEQ #*loop_fin
JMP #*loop_thumb_init
label loop_thumb_init
SHL R3, R3, #8
ADD R3, R3, #171
SUB R4, R4, #1
JMPt PC
JMP #loop_init


label loop_fin
XOR R3, R3, R2
XOR R4, R1, R1
JMPt PC
PUSH #4107836099
POP R5
JMP #*shift_stored_value
label shift_stored_value
ADD R4, R4, R5
SHL R4, R4, #32
JMPt PC
PUSH #4294236386
POP R5
JMP #*add_low_bytes
label add_low_bytes
ADD R4, R5, R4
JMPt PC

CMP R4, R3
JEQ #step_2

CALL #print_nop
CALL #fini
RET

label step_2
PUSH #3737905085
PUSH #3420956130
POP R6, R7
JMP #*calc_step2
label calc_step2

SHL R6, R6, #32
ADD R6, R6, R7
XOR R5, R6, R4
JMPt PC

CMP R0, R5
MOV R3, R1
JEQ #*step_3

CALL #print_nop
CALL #fini
RET

label step_3
SUB R7, R6, R6
ADD R7, R7, #17
SHL R7, R7, #1
ADD R7, R7, #1
XOR R0, R0, R0
XOR R1, R2, R2
XOR R2, R1, R1
JMPt PC
SYSCALL

JMP #*loop_3
label loop_3
SHL R2, R2, #8
ADD R1, R1, #17
ADD R2, R1, R2
ADD R0, R0, #1

JMPt PC
CMP R0, #8
JB #*loop_3

JMP #*check_3
label check_3
ADD R3, R3, R2
XOR R4, R4, R4
AND R1, R3, R7
SUB R1, R1, R7

JMPt PC
CMP R1, #0
JEQ #owi
CALL #print_nop
CALL #fini
RET

label owi
CALL #print_gg
CALL #fini
RET

label print_nop
MOV R6, SP
PUSH #172773896014
PUSH #32
POP R7
SYSCALL
JMP #*clear_sp_3
label clear_sp_3
SUB SP, SP, #8
JMPt PC
RET






