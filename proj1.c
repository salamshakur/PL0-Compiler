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
void    getOperationName(int op);
void    ERROR_StackOverflow();
void    fileReader(int argc, char ** argv);
void    initialize();
int     base(int l, int base);
void    printInstructions(Instr * ir);
void    printRun();
void    printStack();
int     halt = 1;
int     init = 1;
char *  operationName;
FILE *  fp;
int     count;

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

    // print out instructions
    printInstructions(ir);

    // execute instructions
    while(halt)
    {
        printRun();
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
        count++;
    }
    fclose(fp);
}

void execute(Instr * ir)
{
    Instr IR = ir[*PC];
    switch(IR.op)
    {
        case 1:         
            break;
        case 2:         
            break;      
        case 3:         
            if(base(IR.l, *BP) == 0)
                RF[IR.r] = DS[base(IR.l, *BP) + IR.m];
            else
                RF[IR.r] = DS[base(IR.l, *BP) - IR.m];
            break;
        case 4:         
            break;
        case 5:         
            break;
        case 6:         
            if(*SP - IR.m <= *GP) 
                ERROR_StackOverflow();
            if(*BP == 0)
                *GP = *GP + IR.m;
            else
                *SP = *SP - IR.m;
            break;
        case 7:         
            *PC = IR.m;
            break;
        case 8:         
            break;
        case 9:          
            break;
        case 10:         
            break;
        case 11:         
            halt = 0;     
            break;
        case 12:        
            break;
        case 13:        
            break;
        case 14:        
            break;
        case 15:        
            break;
        case 16:        
            break;
        case 17:        
            break;
        case 18:        
            break;
        case 19:        
            break;
        case 20:        
            break;
        case 21:        
            break;
        case 22:
            break;
        case 23:  
            break;
        case 24:
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

void getOperationName(int op)
{
    switch(op)
    {
        case 1:         
            operationName = "lit";
            break;
        case 2:         
            operationName = "rtn";
            break;
        case 3:         
            operationName = "lod";
            break;
        case 4:         
            operationName = "sto";
            break;
        case 5:         
            operationName = "cal";
            break;
        case 6:         
            operationName = "inc";
            break;
        case 7:         
            operationName = "jmp";
            break;
        case 8:         
            operationName = "jpc";
            break;
        case 9:          
            operationName = "sio";
            break;
        case 10:         
            operationName = "sio";
            break;
        case 11:         
            operationName = "sio";
            break;
        case 12:        
            operationName = "neg";
            break;
        case 13:        
            operationName = "add";
            break;
        case 14:        
            operationName = "sub";
            break;
        case 15:        
            operationName = "mul";
            break;
        case 16:        
            operationName = "div";
            break;
        case 17:        
            operationName = "odd";
            break;
        case 18:        
            operationName = "mod";
            break;
        case 19:        
            operationName = "eql";
            break;
        case 20:        
            operationName = "neq";
            break;
        case 21:        
            operationName = "lss";
            break;
        case 22:
            operationName = "leq";
            break;
        case 23:  
            operationName = "gtr";
            break;
        case 24:
            operationName = "geq";
            break;
    }
}

void printInstructions(Instr * ir)
{
    printf("\nLine\tOP\tR\tL\tM\n");
    for(int i = 0; i < count; i++)
    {
        int op = ir[i].op;
        int r = ir[i].r;
        int l = ir[i].l;
        int m = ir[i].m;
        getOperationName(op);
        printf("%d\t%s\t%d\t%d\t%d\n", i, operationName, r, l, m);
    }
    printf("\n");
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