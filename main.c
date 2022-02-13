#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h> 
#include <assert.h>

#include "flags.h"
#include "types.h"
#include "decode.c"

REG pc = 0;
REG flags = 0;
size_t vm_size = 0;


void init_vm(REG** regs, uint8_t** vm_data){

	setvbuf(stdin, 0, _IONBF, 0);
	
	*regs = calloc(9 * sizeof(void *), 1);
	
	FILE* fd = fopen("vm_data.bin", "r");
	int len;

	if (fd == NULL){
		perror("Missing vm_data.bin file\n");
		exit(-1);
	}


	
	fseek(fd, 0, SEEK_END);
	len = ftell(fd);
	
	vm_size = len;

	*vm_data = calloc(vm_size + STACK_SIZE, 1);
	if (*vm_data == NULL){
		perror("Error allocating memory, contact an admin\n");
		exit(-1);
	} 
	fseek(fd, 0, SEEK_SET);
	fread(*vm_data, 1, vm_size, fd);

	(*regs)[SP] = ALIGN(vm_size, 8);

}

opcode64 fetch_instruction_32(void* addr){
	opcode32 instruction;
	memcpy(&instruction, addr, sizeof(instruction));
	return (opcode64)instruction;
}

opcode64 fetch_instruction_64(void* addr){
	opcode64 instruction;
	memcpy(&instruction, addr, sizeof(instruction));
	return instruction;
}


opcode64 fetch_instruction(void* addr){
	if (flags & FLAG_THUMB){
		return (opcode64)fetch_instruction_32(addr);
	} else {
		return fetch_instruction_64(addr);
	}

}






int main(){
	uint8_t* vm_data;
	REG* registers;
	
	init_vm(&registers, &vm_data);

	flags |= FLAG_THUMB; // A CHANGER ou pas ? 	
	opcode64 current_instruction;


	while (1){

		current_instruction = fetch_instruction(vm_data + pc);
		if(decode_and_execute(current_instruction, registers, vm_data) == -1){
			_exit(-1);
		};

	}

	

	exit(0);
}
