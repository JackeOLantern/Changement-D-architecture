#define R0 0 
#define R1 1
#define R2 2
#define R3 3
#define R4 4
#define R5 5
#define R6 6
#define R7 7

#define SP 8
#define PC 9
#define FLAGS 10

#define STACK_SIZE 0x1000

#define ALIGN(value, alignement)	value % alignement ? value + (alignement - (value % alignement)) : value

typedef uint64_t REG;

typedef uint64_t opcode64;
typedef uint32_t opcode32;

