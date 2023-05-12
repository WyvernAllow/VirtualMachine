#include "vm.h"

#include <stdio.h>
#include <stdlib.h>

struct vm* vm_create()
{
    struct vm* new_vm = malloc(sizeof(struct vm));
    if(!new_vm)
    {
        fprintf(stderr, "Failed to allocate memory for vm\n");
        exit(EXIT_FAILURE);
    }

    new_vm->instruction_pointer = 0;
    new_vm->stack_pointer = -1;

    new_vm->stack = calloc(VM_STACK_SIZE, sizeof(int32_t));
    if(!new_vm->stack)
    {
        fprintf(stderr, "Failed to allocate memory for vm stack\n");
        exit(EXIT_FAILURE);
    }

    return new_vm;
}

void vm_destroy(struct vm* vm)
{
    free(vm->stack);
    free(vm);
}

void vm_push(struct vm* vm, const int32_t value)
{
    if(vm->stack_pointer == VM_STACK_SIZE - 1)
    {
        fprintf(stderr, "Stack overflow.\n");
        exit(EXIT_FAILURE);
    }

    vm->stack_pointer++;
    vm->stack[vm->stack_pointer] = value;
}

int32_t vm_pop(struct vm* vm)
{
    if(vm->stack_pointer == -1)
    {
        fprintf(stderr, "Stack underflow.\n");
        exit(EXIT_FAILURE);
    }

    int32_t value = vm->stack[vm->stack_pointer];
    vm->stack_pointer--;
    return value;
}

int32_t vm_peek(struct vm* vm)
{
    if(vm->stack_pointer == -1)
    {
        printf("Stack is empty.\n");
        return 0;
    }
    
    return vm->stack[vm->stack_pointer];
}

void vm_run(struct vm* vm, const struct vm_instruction* program, const uint16_t program_size)
{
    while(vm->instruction_pointer < program_size)
    {
        struct vm_instruction instruction = program[vm->instruction_pointer];
        vm->instruction_pointer++;

        int32_t a;
        int32_t b;
    
        switch (instruction.opcode)
        {
            case VM_OP_PRT:
                printf("%d\n", vm_peek(vm));
                break;

            case VM_OP_SCN:

                int32_t input;
                scanf("%i", &input);
                vm_push(vm, input);

                break;

            case VM_OP_ADD:
                a = vm_pop(vm);
                b = vm_pop(vm);

                vm_push(vm, b + a);
                break;

            case VM_OP_SUB:
                a = vm_pop(vm);
                b = vm_pop(vm);

                vm_push(vm, b - a);
                break;

            case VM_OP_MUL:
                a = vm_pop(vm);
                b = vm_pop(vm);

                vm_push(vm, b * a);
                break;

            case VM_OP_DIV:
                a = vm_pop(vm);
                b = vm_pop(vm);

                // Check for division by zero
                if(a == 0)
                {
                    fprintf(stderr, "Division by zero.\n");
                    exit(EXIT_FAILURE);
                }

                vm_push(vm, b / a);
                break;

            case VM_OP_JMP:
                // Set the instruction pointer to the address specified in the instruction.
                vm->instruction_pointer = instruction.operand;
                break;

            case VM_OP_JEQ:
                a = vm_pop(vm);
                b = vm_pop(vm);

                // If they are equal, set the instruction pointer to the address specified in the instruction.
                if(a == b)
                {
                    vm->instruction_pointer = instruction.operand;
                }


                break;

            case VM_OP_JNE:
                a = vm_pop(vm);
                b = vm_pop(vm);

                // If they are not equal, set the instruction pointer to the address specified in the instruction.
                if(a != b)
                {
                    vm->instruction_pointer = instruction.operand;
                }

                break;

            case VM_OP_JGT:
                a = vm_pop(vm);
                b = vm_pop(vm);

                // If the second value is greater than the first, set the instruction pointer to the address specified in the instruction.
                if(b > a)
                {
                    vm->instruction_pointer = instruction.operand;
                }

                break;

            case VM_OP_JLT:
                a = vm_pop(vm);
                b = vm_pop(vm);

                // If the second value is less than the first, set the instruction pointer to the address specified in the instruction.
                if(b < a)
                {
                    vm->instruction_pointer = instruction.operand;
                }

                break;

            case VM_OP_HLT:
                // Exit the program.
                return;

            case VM_OP_PSH:
                vm_push(vm, instruction.operand);
                break;

            case VM_OP_POP:
                vm_pop(vm);
                break;

            default:
                fprintf(stderr, "Unknown Opcode.\n");
                exit(EXIT_FAILURE);
                break;
        }
    }
}