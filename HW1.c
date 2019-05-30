/* libararies */
#include <stdio.h>
#include <stdlib.h>


/* definitions */
#define MAX_STACK_HEIGHT 23
#define MAX_CODE_LENGTH  500
#define MAX_LEXI_LEVELS  3


/* registers & stack */
int  * RF;                  // register file (0-7) 
int  * PC;                  // program counter
int  * BP;                  // base pointer
int  * GP;                  // global pointer
int  * SP;                  // stack pointer
int *  DS;                  // datastack (0-22)


/* instruction register */
typedef struct IR
{
    int op;                  // operation code
    int r;                   // register 
    int l;                   // lexicographical level
    int m;                   // modifier
} IR;


/* cycles */
void fetch(IR * IR);
void execute(IR * IR);

/* helpers */
int  base(int l, int base);
void print();

/* main driver */
int main()
{

    // allocate variables
    DS    = calloc(sizeof(int), 23);
    RF    = calloc(sizeof(int), 8);
    PC    = calloc(sizeof(int), 1);
    BP    = calloc(sizeof(int), 1);
    GP    = calloc(sizeof(int), 1);
    SP    = calloc(sizeof(int), 1);
   
    // initialize variables
    *PC =  0;
    *BP =  0;
    *GP = -1;
    *SP = MAX_STACK_HEIGHT;

    // allocate structs
    IR * IR = calloc(sizeof(IR), 1);

    // testing
    for(int i = 0; i < 23; i++)
    {
        printf("stack[%d] = %d\n", i, DS[i]);
    }
     for(int i = 0; i < 8; i++)
    {
        printf("rf[%d] = %d\n", i, RF[i]);
    }
    printf("pc = %d\n", *PC);
    printf("bp = %d\n", *BP);
    printf("gp = %d\n", *GP);
    printf("sp = %d\n", *SP);
    
    // fetch instruction
    fetch(IR);

    // execute instruction
    execute(IR);

    return EXIT_SUCCESS;
}


void fetch(IR * IR)
{
    scanf("%d", &IR->op);
    scanf("%d", &IR->r);
    scanf("%d", &IR->l);
    scanf("%d", &IR->m);
    return;
}


void execute(IR * IR)
{

    // testing
    printf("\n");
    printf("op - %d \n", IR->op);
    printf("r  - %d \n", IR->r);
    printf("l  - %d \n", IR->l);
    printf("m  - %d \n", IR->m);

    switch(IR->op)
    {
        case 1:         // LIT
            break;
        case 2:         // RTN
            break;      
        case 3:         // LOD
            break;
        case 4:         // STO
            break;
        case 5:         // CAL
            break;
        case 6:         // INC
            break;
        case 7:         // JMP
            break;
        case 8:         // JPC
            break;
        case 9:         // SIO
            break;
        case 10:        //
            break;
        case 11:        //
            break;
        case 12:        // NEG
            break;
        case 13:        // ADD
            break;
        case 14:        // SUB
            break;
        case 15:        // MUL
            break;
        case 16:        // DIV
            break;
        case 17:        // ODD
            break;
        case 18:        // MOD
            break;
        case 19:        // EQL
            break;
        case 20:        // NEQ
            break;
        case 21:        // LSS
            break;
        case 22:        // LEQ
            break;
        case 23:        // GTR
            break;
        case 24:        // GEQ
            break;
        default:        // DEFAULT CASE
            break;
    }

    return;
}