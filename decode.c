#include "instructions.c"
#include "opcodes.h"

extern REG flags;
extern REG sp;


int decode_and_execute_32(opcode32 instruction, REG* registers){
	// Opcodes dans le .h (operations sur registres)

	uint8_t op1, op2, op3;
	uint8_t OPCODE = (instruction & 0x00ff0000) >> 16;
	uint8_t is_imm = (instruction & 0x0f000000) >> 24;

	op2 = (instruction & 0xf0000000) >> 28;
	op3 = (instruction & 0x0000ff00) >> 8;
	op1 = (instruction & 0x000000ff);

	pc += 4;	

	switch (OPCODE){
		case ADD:
			if (is_imm){
				add_imm(registers, op1, op2, op3);
			} else {
				add_reg(registers, op1, op2, op3);
			}
			break;
		case XOR:
			if (is_imm){
				xor_imm(registers, op1, op2, op3);
			} else {
				xor_reg(registers, op1, op2, op3);
			}
			break;
		case SUB:
			if (is_imm){
				sub_imm(registers, op1, op2, op3);
			} else {
				sub_reg(registers, op1, op2, op3);
			}
			break;
		case OR:
			if (is_imm){
				or_imm(registers, op1, op2, op3);
			} else {
				or_reg(registers, op1, op2, op3);
			}
			break;
		case JMP:
			if (op1 == PC){
				jmp(pc);
			} else if (op1 <= 8){
				jmp(registers[op1]);
			}
			break;
		case AND:
			if (is_imm){
				and_imm(registers, op1, op2, op3);
			} else {
				and_reg(registers, op1, op2, op3);
			}
			break;
		case SHL:
			if (is_imm){
				shl_imm(registers, op1, op2, op3);
			} else {
				shl_reg(registers, op1, op2, op3);
			}
			break;
		case SHR:
			if (is_imm){
				shr_imm(registers, op1, op2, op3);
			} else {
				shr_reg(registers, op1, op2, op3);
			}
			break;
		default:
			return -1;
	}
	
	return 0;
}

int decode_and_execute_64(opcode64 instruction, REG* registers, uint8_t* vm_data){
	
	uint8_t is_imm 	= (instruction & 0x000000000000000f);
	uint8_t nb_regs = (instruction & 0x00000000000000f0) >> 4;
	uint8_t OPCODE 	= (instruction & 0x000000000000ff00) >> 8;
	uint64_t imm 	= (instruction & 0xffffffffffff0000) >> 16;

	pc += 8;

	switch (OPCODE){
		case PUSH:
			if (is_imm){
				push_imm(registers, vm_data, imm);
			} else {
				push_regs(registers, vm_data, imm, nb_regs);
			}
			break;
		case POP:
			pop(registers, vm_data, imm, nb_regs);
			break;
		case RET:
			ret(registers, vm_data);
			break;
		
		case JMP:
			if (is_imm && nb_regs){
				jeq(imm);
			} else if (is_imm){
				jb(imm);
			} else if (nb_regs){
				ja(imm);
			} else {
				jmp(imm);
			}
			break;

		case CALL:
			if (is_imm){
				call_imm(registers, vm_data, imm);
			} else {
				call_reg(registers, vm_data, imm);
			}
			break;
		case MOV:
			mov(registers, is_imm, nb_regs);
			break;
		case CMP:
			if (is_imm){
				cmp_imm(registers, nb_regs, imm);
			} else {
				cmp_reg(registers, nb_regs, imm);
			}
			break;
		case SYSCALL:
			sys_call(registers, vm_data);
			break;
		default:
			return -1;
	}

	return 0;
}


int decode_and_execute(opcode64 instruction, REG* registers, uint8_t* vm_data){

	if (flags & FLAG_THUMB){
		return decode_and_execute_32((opcode32)instruction, registers);
	} else {
		return decode_and_execute_64(instruction, registers, vm_data);
	}

	return -1;
}




