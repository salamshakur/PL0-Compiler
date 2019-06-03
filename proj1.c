/* Libraries */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Definitions */
#define MAX_STACK_HEIGHT 23
#define MAX_CODE_LENGTH  500
#define MAX_LEXI_LEVELS  3

/* Registers & Stack */
int  * RF;                  // register file (0-7) 
int  * PC;                  // program counter
int  * BP;                  // base pointer
int  * GP;                  // global pointer
int  * SP;                  // stack pointer
int  * DS;                  // datastack (0-22)

/* Instruction Register Struct*/
typedef struct Instr
{
    int op;                  // operation code
    int r;                   // register 
    int l;                   // lexicographical level
    int m;                   // modifier
} Instr;

/* Cycles*/
void fetch(Instr * ir);
void execute(Instr * ir);

/* Helpers */
void    ERROR_StackOverflow();
void    fileReader(int argc, char ** argv);
void    initialize();
int     base(int l, int base);
void    printRun();
void    printStack();
int     halt = 1;
int     init = 1;
char *  operationName;
FILE *  fp;

/* Main Driver */
void main(int argc, char ** argv)
{
    // read in instructions from text file
    fileReader(argc, argv);

    // initialize registers & stack
    initialize();

    // create struct
    Instr * ir = calloc(sizeof(Instr), MAX_CODE_LENGTH);

    // fetch instructions
    fetch(ir);

    while(halt)
    {
        // print run
        printRun();

        // execute instructions
        execute(ir);
    }
}

void fileReader(int argc, char ** argv)
{	
	if(argc < 2)
	{
		printf("Error: No input file found. \n");
        exit(1);
	}
		
	if(argc >= 2)
		fp = fopen(argv[1], "r");
	else
		fp = fopen(argv[0], "r");
}

void initialize()
{
    DS    = calloc(sizeof(int), 23);
    RF    = calloc(sizeof(int), 8);
    PC    = calloc(sizeof(int), 1);
    BP    = calloc(sizeof(int), 1);
    GP    = calloc(sizeof(int), 1);
    SP    = calloc(sizeof(int), 1);
   
    *PC   =  0;
    *BP   =  0;
    *GP   = -1;
    *SP   = MAX_STACK_HEIGHT;
}

void fetch(Instr * ir)
{
    int op, r, l, m;
    
    int i = 0;
    while(fscanf(fp, "%d %d %d %d", &op, &r, &l, &m) != EOF)
    {
        ir[i].op = op;
        ir[i].r = r;
        ir[i].l = l;
        ir[i].m = m;
        i++;
    }
    fclose(fp);
}

void execute(Instr * ir)
{
    Instr IR = ir[*PC];
    switch(IR.op)
    {
        case 1:         
            operationName = "LIT";
            break;
        case 2:         
            operationName = "RTN";
            break;      
        case 3:         
            operationName = "LOD";
            if(base(IR.l, *BP) == 0)
                RF[IR.r] = DS[base(IR.l, *BP) + IR.m];
            else
                RF[IR.r] = DS[base(IR.l, *BP) - IR.m];
            break;
        case 4:         
            operationName = "STO";
            break;
        case 5:         
            operationName = "CAL";
            break;
        case 6:         
            operationName = "INC";
            if(*SP - IR.m <= *GP) 
                ERROR_StackOverflow();
            if(*BP == 0)
                *GP = *GP + IR.m;
            else
                *SP = *SP - IR.m;
            break;
        case 7:         
            operationName = "JMP";
            *PC = IR.m;
            break;
        case 8:         
            operationName = "JPC";
            break;
        case 9:          
            operationName = "SIO";
            break;
        case 10:         
            operationName = "SIO";
            break;
        case 11:         
            operationName = "SIO";
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
    }

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

void ERROR_StackOverflow()
{
    printf("Error: Stack Overflow. \n");
    exit(1);
}