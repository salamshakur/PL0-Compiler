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
int    base(int l, int base);
void   printRun();
void   printStack();
int    halt = 1;
int    init = 1;
char * operation;


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
    // for(int i = 0; i < 23; i++)
    // {
    //     printf("stack[%d] = %d\n", i, DS[i]);
    // }
    //  for(int i = 0; i < 8; i++)
    // {
    //     printf("rf[%d] = %d\n", i, RF[i]);
    // }
    // printf("pc = %d\n", *PC);
    // printf("bp = %d\n", *BP);
    // printf("gp = %d\n", *GP);
    // printf("sp = %d\n", *SP);
    
    while(halt)
    {
        // print run
        printRun();

        // fetch instruction
        fetch(IR);

        // execute instruction
        execute(IR);
    }

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
    // printf("\n");
    // printf("op - %d \n", IR->op);
    // printf("r  - %d \n", IR->r);
    // printf("l  - %d \n", IR->l);
    // printf("m  - %d \n", IR->m);

    switch(IR->op)
    {
        case 1:         // LIT
            printf("LIT \n");            
            break;
        case 2:         // RTN
            printf("RTN \n");
            break;      
        case 3:         // LOD
            printf("LOD \n");
            break;
        case 4:         // STO
            printf("STO \n");
            break;
        case 5:         // CAL
            printf("CAL \n");
            break;
        case 6:         // INC
            printf("INC \n");
            break;
        case 7:         // JMP
            printf("JMP \n");
            break;
        case 8:         // JPC
            printf("JPC \n");
            break;
        case 9:         // SIO (1)
            if(IR->m != 1)
                printf("Invalid M \n");
            else
                printf("SIO 1 \n");            
            break;
        case 10:        // SIO (2)
            if(IR->m != 2)
                printf("Invalid M \n");
            else
                printf("SIO 2 \n");            
            break;
        case 11:        // SIO (3)
            if(IR->m != 3)
                printf("Invalid M \n");
            else{
                printf("SIO 3");
                halt = 0;
            }           
            break;
        case 12:        // NEG
        printf("NEG \n");        
            break;
        case 13:        // ADD
        printf("ADD \n");        
            break;
        case 14:        // SUB
        printf("SUB \n");        
            break;
        case 15:        // MUL
        printf("MUL \n");                
            break;
        case 16:        // DIV
        printf("DIV \n");        
            break;
        case 17:        // ODD
        printf("ODD \n");        
            break;
        case 18:        // MOD
        printf("MOD \n");        
            break;
        case 19:        // EQL
        printf("EQL \n");        
            break;
        case 20:        // NEQ
        printf("NEQ \n");        
            break;
        case 21:        // LSS
        printf("LSS \n");        
            break;
        case 22:        // LEQ
        printf("LEQ \n");        
            break;
        case 23:        // GTR
        printf("GTR \n");
            break;
        case 24:        // GEQ
        printf("GEQ \n");
            break;
        default:        // DEFAULT CASE
        printf("INVALID OP \n");
            break;
    }

    return;
}


int base(int l, int base)
{
    int bl;
    bl = base;

    while(l > 0)
    {
        bl = DS[bl - 1];
        l--;
    }
    return bl;
}

void printRun()
{
    if(init)
    {
        printf("              \t\t\t gp \t pc \t bp \t sp \t data \t\t stack \n");
        printf("InitialValues \t\t\t %d \t %d \t %d \t %d \t ", *GP, *PC, *BP, *SP);
        printStack();
    }
    else
    {

    }
}

void printStack()
{
    for(int i = 0; i < 23; i++)
    {
        printf("%d ", DS[i]);
    }
    printf("\n");
}