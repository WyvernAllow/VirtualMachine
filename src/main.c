#include "vm.h"

int main()
{
    struct vm* vm = vm_create();
    
    // Simple program to demonstrate arithmetic and conditional branching.
    // Asks the user to input two numbers and subtracts them.
    // If the answer is 10, it prints 1, otherwise it prints 0.
    // Note: Some instructions do not require an operand, in which case the operand passed is ignored. Here we pass 0 as a placeholder.
    struct vm_instruction program[] = 
    {
        { VM_OP_SCN, 0  },  
        { VM_OP_SCN, 0  },  
        { VM_OP_SUB, 0  },  
        { VM_OP_PSH, 10 },  
        { VM_OP_JEQ, 8  },

        // Program continues to here if the answer is not 10.
        { VM_OP_PSH, 0  },
        { VM_OP_PRT, 0  },
        { VM_OP_HLT, 0  },


        // Jumps here if the answer is 10.
        { VM_OP_PSH, 1  }, 
        { VM_OP_PRT, 0  },
        { VM_OP_HLT, 0  }
    };
    
    vm_run(vm, program, sizeof(program) / sizeof(struct vm_instruction));

    vm_destroy(vm);
}