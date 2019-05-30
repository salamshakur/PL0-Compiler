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
int *  Stack;               // stack (0-22)

/* instruction register */
typedef struct IR
{
    int op;                  // operation code
    int r;                   // register 
    int l;                   // lexicographical level
    int m;                   // modifier
} IR;

/* cycles */
void fetch();
void execute(IR ir);

/* main driver */
int main()
{

    // allocate variables
    Stack = calloc(sizeof(int), 23);
    RF    = calloc(sizeof(int), 8);
    PC    = calloc(sizeof(int), 1);
    BP    = calloc(sizeof(int), 1);
    GP    = calloc(sizeof(int), 1);
    SP    = calloc(sizeof(int), 1);
   
    // initialize variables
    PC =  0;
    BP =  0;
    GP = -1;
    SP = MAX_STACK_HEIGHT;

    // allocate structs
    IR * IR = calloc(sizeof(IR), 1);


    return EXIT_SUCCESS;
}
