#ifndef VM_H
#define VM_H

#include <stdint.h>

#define VM_STACK_SIZE 1024 // The number of 32 bit integers the stack can store.

enum vm_opcode
{
    VM_OP_PRT,
    VM_OP_SCN,     
    VM_OP_ADD,    
    VM_OP_SUB,     
    VM_OP_MUL,     
    VM_OP_DIV,     
    VM_OP_JMP,     
    VM_OP_JEQ,     
    VM_OP_JNE,     
    VM_OP_JGT,     
    VM_OP_JLT,    
    VM_OP_HLT,         
    VM_OP_PSH,     
    VM_OP_POP,     
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

void vm_push(struct vm* vm, const int32_t value);
int32_t vm_pop(struct vm* vm);
int32_t vm_peek(struct vm* vm);

void vm_run(struct vm* vm, const struct vm_instruction* program, const uint16_t program_size);

#endif // VM_H