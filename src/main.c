#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// TODO: add guards and errors for stack over- and underflow
#define STACK_SIZE 512
static int stack[STACK_SIZE];

// TODO: Add parsing of symbols to find syntax errors and match with opcodes

/** Instructions */
typedef enum {
    HLT,    // hlt                          0  - halts execution
    NOP,    // nop                          1  - nothing
    PUSH,   // push <val>                   2  - pushes value onto stack
    POP,    // pop                          3  - pops value from stack (use smov to pop into a register)
    ADD,    // add                          4  - pops two values of the stack, adds b to a and pushes the result onto the stack
    SUB,    // sub                          5  - pops two values of the stack, subtracts b from a and pushes the result onto the stack
    MUL,    // mul                          6  - pops two values of the stack, multiplies b by a and pushes the result onto the stack
    DIV,    // div                          7  - pops two values of the stack, divides b by a and pushes the result onto the stack
    MOV,    // mov <val> <reg>              8  - moves value to the given register
    SMOV,   // smov <reg>                   9  - pops the top value of the stack into the given register
    JMP,    // jmp <dest>                   10 - unconditional jump to dest
    JE,     // je <val a> <val b> <dest>    11 - jump to dest if a == b
    JNE,    // jne <val a> <val b> <dest>   12 - jump to dest if a != b
    JLE,    // jle <val a> <val b> <dest>   13 - jump to dest if a <= b
    JL,     // jl <val a> <val b> <dest>    14 - jump to dest if a < b
    JGE,    // jge <val a> <val b> <dest>   15 - jump to dest if a >= b
    JG,     // jg <val a> <val b> <dest>    16 - jump to dest if a > b
    JNZ,    // jnz <val> <dest>             17 - jump to dest if a != 0
    JZ,     // jz <val> <dest>              18 - jump to dest if a == 0
    INT,    // int                          19 - interrupts the CPU with the interrupt code in register IC
    HCF     //                              20
} InstructionSet;

/** Registers */
typedef enum {
    A, B, C, D, E, F, // General purpose registers
    IP, // Instruction pointer
    SP, // Stack pointer
    IC, // Interrupt control
    REGISTER_SIZE
} Registers;

/** Interrupt Control Codes */
typedef enum {
    INT_INVALID,    // invalid interrupt
    INT_READCHAR,   // reads a single character from STDIN (to stack)
    INT_WRITECHAR,  // writes a single character to STDIN (pop from stack)
    INT_WRITESTR,   // writes characters until NULL (0x00) is encountered (pop from stack)
    INT_REAFBUFF    // reads string from STDIN until ENTER or EOF (buffered read onto stack) - NOTE: string has to be prepended with a NULL to indicate where reading should stop.
} Interrupts;

static int registers[REGISTER_SIZE];

// instructions array
int *instructions;

// how many instructions to do
int instruction_count = 0;

// how much space is allocated for the instructions
// 4 instructions by default
int instruction_space = 4;

/** if the program is running */
static bool running = true;

/** if the IP is assigned by jmp instructions(such as IF,IFN),it should not increase 1 any more **/
bool is_jmp = false;

/** quick ways to get SP and IP */
#define SP (registers[SP])
#define IP (registers[IP])

/** fetch current instruction set */
#define FETCH (instructions[IP]) // TODO: refactor this into something nicer

void eval(int instr) {
    is_jmp = false;
    switch (instr) {
        case HLT: {
            running = false;
            printf("Finished execution with exit code %d\n", F);
            break;
        }
        case NOP:
            break;
        case PUSH: {
            SP = SP + 1;
            IP = IP + 1;
            // TODO: check for errors
            stack[SP] = instructions[IP];
            break;
        }
        case POP: {
            int val_popped = stack[SP];
            SP = SP - 1;
            // TODO: make this sprint statement enabled only when in debug mode
            printf("< %d\n", val_popped);
            break;
        }
        case ADD: {
            // pop the stack and store value in register A
            registers[A] = stack[SP];
            SP = SP - 1;

            // pop the stack and store value in register B
            registers[B] = stack[SP];

            // add the values and and push the result to the stack
            registers[C] = registers[B] + registers[A];
            stack[SP] = registers[C];

            break;
        }
        case SUB: {
            // pop the stack and store value in register A
            registers[A] = stack[SP];
            SP = SP - 1;

            // pop the stack and store value in register B
            registers[B] = stack[SP];

            // subtract the values and and push the result to the stack
            registers[C] = registers[B] - registers[A];
            stack[SP] = registers[C];

            break;
        }
        case MUL: {
            // pop the stack and store value in register A
            registers[A] = stack[SP];
            SP = SP - 1;

            // pop the stack and store value in register B
            registers[B] = stack[SP];

            // multiply the values and and push the result to the stack
            registers[C] = registers[B] * registers[A];
            stack[SP] = registers[C];

            break;
        }
        case DIV: {
            // pop the stack and store value in register A
            registers[A] = stack[SP];
            SP = SP - 1;

            // pop the stack and store value in register B
            registers[B] = stack[SP];

            // divide the values and and push the result to the stack
            registers[C] = registers[B] / registers[A];
            stack[SP] = registers[C];

            break;
        }
        case HCF: {
            for(int i = 0; i < 37; i++) {
                printf("%d\n", registers[59 * i]);
            }
            exit(-999);
        }
    }
}

// TODO: customise some more. This is mainly to test right now.
int main(int argc, char** argv) {
    if (argc <= 1) {
        printf("error: no input files\n");
        return -1;
    }

    // filename
    char *filename = argv[1];

    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("error: could not read file `%s`\n", filename);
        return -1;
    }

    // allocate space for instructions
    instructions = malloc(sizeof(*instructions) * instruction_space); // 4 instructions

    // read the "binary" file
    int num;
    int i = 0;
    while (fscanf(file, "%d", &num) > 0) {
        instructions[i] = num;
        printf("%d\n", instructions[i]);
        i++;
        if (i >= instruction_space) {
            instruction_space *= 2;
            instructions = realloc(instructions, sizeof(*instructions) * instruction_space); // double size
        }
    }
    
    // set 'instruction_count' to number of instructions read
    instruction_count = i;

    // close the file
    fclose(file);

    // initialize stack pointer
    SP = -1;

    // loop through program, but don't
    // go out of the programs bounds
    while (running && IP < instruction_count) {
        eval(FETCH);
        if(!is_jmp){
            IP = IP + 1;
        }
    }

    // clean up instructions
    free(instructions);

    return 0;
}