# Virtual Machine

A simple stack based virtual machine. 

# Opcodes
All the opcodes that can be used to program the VM.

## IO
PRT - Prints the value at the top of the stack to the standard output stream. Does not require any operands.
SCN - Reads a 32 bit integer from the standard input stream, and pushes it to the stack. Does not require any operands.

## Arithmetic
ADD - Adds the top two values on the stack and pushes the result onto the stack. Does not require any operands.
SUB - Subtracts the top two values on the stack and pushes the result onto the stack. Does not require any operands.
MUL - Multiplies the top two values on the stack and pushes the result onto the stack. Does not require any operands.
DIV - Divides the top two values on the stack and pushes the result onto the stack. Does not require any operands.

## Control Flow
JMP - Jumps to the address specified in the operand.
JEQ - Jumps to the address specified in the operand if the top two values on the stack are equal.
JNE - Jumps to the address specified in the operand if the top two values on the stack are not equal.
JGT - Jumps to the address specified in the operand if the top value on the stack is greater than the second value on the stack.
JLT - Jumps to the address specified in the operand if the top value on the stack is less than the second value on the stack.
HLT - Halts the program. 

## Stack
PSH - Pushes the value specified in the opcode onto the stack. 
POP - Pops the top value off the stack.
