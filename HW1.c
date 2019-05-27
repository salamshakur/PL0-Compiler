#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_STACK_HEIGHT 23
#define MAX_CODE_LENGTH  500
#define MAX_LEXI_LEVELS  3

int *sp = MAX_STACK_HEIGHT;
int *gp = -1;
int *bp =  0, 
int pc  =  0;
int stack[MAX_STACK_HEIGHT];


int instructions (int op);

typedef struct
{
    int * FV;  // functional value
    int * SL;  // static linker
    int * DL;  // dynamic linker
    int * RA;  // return address
    int * Par; // parameters 
} ActivationRecord;

typedef struct
{
    int op;   // opcode
    int r;    // register
    int l;    // lexographical level
    int m;    // modifier
} InstructionRegister;



int main(int * args){
    
    InstructionRegister IR;
    while(TRUE)
    {
        scanf("%d %d %d %d", &IR.op, &IR.r, &IR.l, &IR.m); // for testing
        instructions(IR)
    }
    
    return 0;
}


int instructions (InstructionRegister IR)
{
    switch (IR.op) {
        case 01: // LIT
            break;
        case 02: // RTN
            SP = BP + 1;
            BP = stack[SP-3];        
            PC = stack[SP-4];       
            break;

        case 03: // LOD
            if (base(IR.l, BP)==0) 
            R[IR.r] = stack[base(IR.l, BP)+IR.m];
                    else 
            R[IR.r] = stack[base(IR.l, BP)-IR.m];
            break;

        case 04: // STO
            if (base(IR.l, BP)==0) 
            stack[base(IR.l, BP)+IR.m] = R[IR.r];
                    else 
            stack[base(IR.l, BP)-IR.m] = R[IR.r];
            break;

        case 05: // CAL
            if (SP-4<=GP) ERROR_StackOverflow();
            stack[SP-1] = 0;                    
            stack[SP-2] = base(IR.l, BP);       
            stack[SP-3] = BP;                   
            stack[SP-4] = PC; 
            BP = SP-1;
            PC = IR.m;
            break;

        case 06: // INC
            break;
        case 07: // JMP
            break;
        case 08: // JPC
            break;
        case 09: // SIO (Case 1, 2, 3)
            switch(m)
            {
                case 01:
                    break;
                case 02:
                    break;
                case 03:
                    break;
                default:
                    printf("Invalid M! \n");
                    break;
            }
            break;
        case 12: // NEG
            break;
        case 13: // ADD
            break;
        case 14: // SUB
            break;
        case 15: // MUL
            break;
        case 16: // DIV
            break;
        case 17: // ODD
            break;
        case 18: // MOD
            break;
        case 19: // EQL
            break;
        case 20: // NEQ
            break;
        case 21: // LSS
            break;
        case 22: // LEQ
            break;
        case 23: // GTR
            break;
        case 24: // GEQ
            break;
        default: // Invalid OP
            printf("Invalid OP!\n");
            break;
    }
}










