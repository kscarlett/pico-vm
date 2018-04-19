# Pico VM Assembly
This file is currently not automatically generated, so during these early stages of development, it may be out of date (it probably is).
For the latest information, look at the comments in the code.

## Opcodes
* `HLT` - Halts execution.
* `NOP` - Nothing.
* `PUSH <val>` - Pushes value onto stack.
* `POP` - Pops value from stack (use smov to pop into a register).
* `ADD` - Pops two values of the stack, adds b to a and pushes the result onto the stack.
* `SUB` - Pops two values of the stack, subtracts b from a and pushes the result onto the stack.
* `MUL` - Pops two values of the stack, multiplies b by a and pushes the result onto the stack.
* `DIV` - Pops two values of the stack, divides b by a and pushes the result onto the stack.
* `MOV <val> <reg>` - Moves value to the given register.
* `SMOV <reg>` - Pops the top value of the stack into the given register.
* `JMP <dest>` - Unconditional jump to dest.
* `JE <val a> <val b> <dest>` - Jump to dest if a == b.
* `JNE <val a> <val b> <dest>` - Jump to dest if a != b.
* `JLE <val a> <val b> <dest>` - Jump to dest if a <= b.
* `JL <val a> <val b> <dest>` - Jump to dest if a < b.
* `JGE <val a> <val b> <dest>` - Jump to dest if a >= b.
* `JG <val a> <val b> <dest>` - Jump to dest if a > b.
* `JNZ <val> <dest>` - Jump to dest if a != 0.
* `JZ <val> <dest>` - Jump to dest if a == 0.
* `INT` - Interrupts the CPU with the interrupt code in register IC.

## Registers
* `A`, `B`, `C`, `D`, `E`, `F` - General purpose registers.
* `IP` - Instruction pointer.
* `SP` - Stack pointer.
* `IC` - Interrupt control. The interrupt code in this register will determine what happens when `INT` is called.
* `REGISTER_SIZE` - Hack to enable us to easily get the amount of registers.

## Interrupt Codes
* `INT_INVALID` - invalid interrupt.
* `INT_READCHAR` - reads a single character from STDIN (to stack).
* `INT_WRITECHAR` - writes a single character to STDIN (pop from stack).
* `INT_WRITESTR` - writes characters to STDOUT until NULL (0x00) is encountered (pop from stack).
* `INT_REAFBUFF` - reads string from STDIN until ENTER or EOF (buffered read onto stack) - NOTE: string has to be prepended with a NULL to indicate where reading should stop.
