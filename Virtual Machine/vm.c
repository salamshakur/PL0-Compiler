#ifndef _GENERIC_H_
#define _GENERIC_H_
    #include <stdio.h>
    #include <stdlib.h>
#endif

#define MAX_STACK_HEIGHT 23
#define MAX_CODE_LENGTH  500
#define MAX_LEXI_LEVELS  3

int  * ds;   // datastack
int  * rf;   // register file
int    pc;   // program counter
int    bp;   // base pointer
int    gp;   // global pointer
int    sp;   // stack pointer
int    hlt;  // halt flag

typedef struct instr
{
    int op;  // operation code
    int r;   // register
    int l;   // lexicographical level 
    int m;   // modifier
} instr;

void    beginVM(FILE * fp);
instr * fetch(FILE * fp);
char  * getOperationName(int op);
void    initialize();
void    execute(instr ir);
void    printInstructions(int n, instr * ir);
void    printRun(instr ir);
void    printStack();
void    printRegisters();
int     base(int l, int base);
void    ERROR_StackOverflow();

void beginVM(FILE * fp)
{
    initialize();
    instr * ir = fetch(fp);

    while(hlt)
    {
        printRun(ir[pc]);
        execute(ir[pc]);
        printStack();
        printRegisters(); 
    }
}

instr * fetch(FILE * fp)
{
    int op, r, l, m;
    instr * ir = calloc(sizeof(instr), MAX_CODE_LENGTH);

    int i = 0;
    while(fscanf(fp, "%d %d %d %d", &op, &r, &l, &m) != EOF)
    {
        ir[i].op = op;
        ir[i].r  = r;
        ir[i].l  = l;
        ir[i].m  = m;
        i++;
    }
    fclose(fp);

    printInstructions(i, ir);
    return ir;
}

void printInstructions(int n, instr * ir)
{
    printf("\nLine\tOP\tR\tL\tM\n");
    for(int i = 0; i < n; i++)
    {
        int    op   = ir[i].op;
        int    r    = ir[i].r;
        int    l    = ir[i].l;
        int    m    = ir[i].m;
        char * name = getOperationName(op);
        printf("%d\t%s\t%d\t%d\t%d\n", i, name, r, l, m);
    }
    printf("\n\n");
    printf("              \t\t\t gp \t pc \t bp \t sp \t data \t\t stack \n");
    printf("InitialValues \t\t\t ");
    printStack();
    printRegisters();
}

char * getOperationName(int op)
{
    switch(op)
    {
        case 1:         
            return "lit";
        case 2:         
            return "rtn";
        case 3:         
            return "lod";
        case 4:         
            return "sto";
        case 5:         
            return "cal";
        case 6:         
            return "inc";
        case 7:         
            return "jmp";
        case 8:         
            return "jpc";
        case 9:          
            return "sio";
        case 10:         
            return "sio";
        case 11:         
            return "sio";
        case 12:        
            return "neg";
        case 13:        
            return "add";
        case 14:        
            return "sub";
        case 15:        
            return "mul";
        case 16:        
            return "div";
        case 17:        
            return "odd";
        case 18:        
            return "mod";
        case 19:        
            return "eql";
        case 20:        
            return "neq";
        case 21:        
            return "lss";
        case 22:
            return "leq";
        case 23:  
            return "gtr";
        case 24:
            return "geq";
    }
}

void initialize()
{
    ds  = calloc(sizeof(int), 23);
    rf  = calloc(sizeof(int), 8);
    sp  = MAX_STACK_HEIGHT;
    gp  = -1;
    pc  =  0;
    bp  =  0;
    hlt =  1;
}

void printRun(instr ir)
{
    printf("%d %s %d %d %d \t\t\t ", pc, getOperationName(ir.op), ir.r, ir.l, ir.m);
}

void printStack()
{
    printf("%d \t %d \t %d \t %d \t ", gp, pc, bp, sp);
    for(int i = 0; i < 23; i++)
    {
        printf("%d ", ds[i]);
    }
    printf("\n");
}

void printRegisters()
{
    printf("RF: ");
    for(int i = 0; i < 8; i++)
    {
        printf("%d ", rf[i]);
    }
    printf("\n\n");
}

void execute(instr ir)
{
    pc++;
    switch(ir.op)
    {
        case 1:
            rf[ir.r] = ir.m;
            break;
        case 2:
            sp = bp + 1;
            bp = ds[sp - 3];
            pc = ds[sp - 4];
            break;
        case 3:
            if(base(ir.l, bp) == 0)
                rf[ir.r] = ds[base(ir.l, bp) + ir.m];
            else
                rf[ir.r] = ds[base(ir.l, bp) - ir.m];
            break;
        case 4:
            if(base(ir.l, bp) == 0)
                ds[base(ir.l, bp) + ir.m] = rf[ir.r];
            else
                ds[base(ir.l, bp) - ir.m] = rf[ir.r];
            break;
        case 5:
            if(sp - 4 <= gp)
                ERROR_StackOverflow();
            ds[sp - 1] = 0;
            ds[sp - 2] = base(ir.l, bp);
            ds[sp - 3] = bp;
            ds[sp - 4] = pc;
            bp = sp - 1;
            pc = ir.m;
            break;
        case 6:
            if(sp - ir.m <= gp)
                ERROR_StackOverflow();
            if(bp == 0)
                gp = gp + ir.m;
            else
                sp = sp - ir.m;
            break;
        case 7:
            pc = ir.m;
            break;
        case 8:
            if(rf[ir.r] == 0)
                pc = ir.m;
            break;
        case 9:
            printf("%d \n", rf[ir.r]);
            break;
        case 10:
            scanf("%d", &rf[ir.r]);
            break;
        case 11:
            hlt = 0;
            break;
        case 12:
            rf[ir.r] = rf[ir.l] * -1;
            break;
        case 13:
            rf[ir.r] = rf[ir.l] + rf[ir.m];
            break;
        case 14:
            rf[ir.r] = rf[ir.l] - rf[ir.m];
            break;
        case 15:
            rf[ir.r] = rf[ir.l] * rf[ir.m];
            break;
        case 16:
            rf[ir.r] = rf[ir.l] / rf[ir.m];
            break;
        case 17:
            rf[ir.r] = rf[ir.r] % 2;
            break;
        case 18:
            rf[ir.r] = rf[ir.l] % rf[ir.m];
            break;
        case 19:
            rf[ir.r] = (rf[ir.l] == rf[ir.m]) ? 1 : 0;
            break;
        case 20:
            rf[ir.r] = (rf[ir.l] != rf[ir.m]) ? 1 : 0;
            break;
        case 21:
            rf[ir.r] = (rf[ir.l] < rf[ir.m]) ? 1 : 0;
            break;
        case 22:
            rf[ir.r] = (rf[ir.l] <= rf[ir.m]) ? 1 : 0;
            break;
        case 23:
            rf[ir.r] = (rf[ir.l] > rf[ir.m]) ? 1 : 0;
            break;
        case 24:
            rf[ir.r] = (rf[ir.l] >= rf[ir.m]) ? 1 : 0;
            break;
    }
}

int base(int l, int base)
{
    int bl;
    bl = base;

    while(l > 0)
    {
        bl = ds[bl - 1];
        l--;
    }
    return bl;
}

void ERROR_StackOverflow()
{
    printf("Error: Stack Overflow. \n");
    exit(1);
}