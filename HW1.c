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
char * operationName;


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
    switch(IR->op)
    {
        case 1:         
            operationName = "LIT";
            break;
        case 2:         
            operationName = "RTN";
            break;      
        case 3:         
            operationName = "LOD";
            break;
        case 4:         
            operationName = "STO";
            break;
        case 5:         
            operationName = "CAL";
            break;
        case 6:         
            operationName = "INC";
            break;
        case 7:         
            operationName = "JMP";
            break;
        case 8:         
            operationName = "JPC";
            break;
        case 9:          
            operationName = "SIO";
            if(IR->m == 1)
                //
            break;
        case 10:         
            operationName = "SIO";
            if(IR->m == 2)
                //
            break;
        case 11:         
            operationName = "SIO";
            if(IR->m == 3)
                halt = 0;       
            break;
        case 12:        
            operationName = "NEG";
            break;
        case 13:        
            operationName = "ADD";
            break;
        case 14:        
            operationName = "SUB";
            break;
        case 15:        
            operationName = "MUL";
            break;
        case 16:        
            operationName = "DIV";
            break;
        case 17:        
            operationName = "ODD";
            break;
        case 18:        
            operationName = "MOD";
            break;
        case 19:        
            operationName = "EQL";
            break;
        case 20:        
            operationName = "NEQ";
            break;
        case 21:        
            operationName = "LSS";
            break;
        case 22:
            operationName = "LEQ";
            break;
        case 23:  
            operationName = "GTR";
            break;
        case 24:
            operationName = "GEQ";
            break;
        default:
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
        init = 0;
    }
    else
    {
        // TODO
        printf("%s\n", operationName);
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