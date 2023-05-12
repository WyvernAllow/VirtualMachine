#ifndef VM_H
#define VM_H

#include <stdint.h>

#define VM_STACK_SIZE 1024 // The number of 32 bit integers the stack can store.

enum vm_opcode
{
    // IO opcodes
    
    VM_OP_PRT,     // Prints the value at the top of the stack
    VM_OP_SCN,     // Pushes user input taken from the console onto the stack.
    
    // Arithmetic opcodes

    VM_OP_ADD,     // Adds the top two values on the stack and pushes the result onto the stack
    VM_OP_SUB,     // Subtracts the top two values on the stack and pushes the result onto the stack
    VM_OP_MUL,     // Multiplies the top two values on the stack and pushes the result onto the stack
    VM_OP_DIV,     // Divides the top two values on the stack and pushes the result onto the stack

    // Control flow opcodes

    VM_OP_JMP,     // Jumps to the address specified.
    VM_OP_JEQ,     // Jumps to the address specified if the top two values on the stack are equal
    VM_OP_JNE,     // Jumps to the address specified if the top two values on the stack are not equal
    VM_OP_JGT,     // Jumps to the address specified if the top value on the stack is greater than the second value on the stack
    VM_OP_JLT,     // Jumps to the address specified if the top value on the stack is less than the second value on the stack
    VM_OP_HLT,     // Halts the program

    // Stack opcodes

    VM_OP_PSH,     // Pushes the value specified onto the stack
    VM_OP_POP,     // Pops the top value off the stack
};

struct vm_instruction
{
    enum vm_opcode opcode;
    int32_t operand;
};

struct vm
{
    uint16_t stack_pointer;
    uint16_t instruction_pointer;

    int32_t* stack;
};

struct vm* vm_create();
void vm_destroy(struct vm* vm);

void vm_run(struct vm* vm, const struct vm_instruction* program, const uint16_t program_size);

#endif // VM_H