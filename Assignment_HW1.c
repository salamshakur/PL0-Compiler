#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_HEIGHT 23
#define MAX_CODE_LENGTH  500
#define MAX_LEXI_LEVELS  3

int PC   = 0;
int * BP = NULL;
int * GP = NULL;
int * SP = NULL;

typedef struct IR
{
    int op;
    int r;
    int l;
    int m;
} IR;

void fetch();
void execute(IR ir);

void main()
{

    return 0;
}