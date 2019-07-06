#ifndef _GENERIC_H_
#define _GENERIC_H_
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <ctype.h>
#endif

typedef struct symbol
{
    int  kind;                // const = 1, var = 2, proc = 3
    char name[maxChar + 1];   // name up to 11 chars
    int  val;                 // numbers (ASCII value)
    int  level;               // L level
    int  addr;                // M address
    int  mark;                // to indicate that code has been generated already for a block
} symbol;

void insert(symbol * symTable, int symCount, int kind, char name[], int val, int level, int addr, int mark);
void block(symbol * symTable, table * lexemes);
void constCheck();
void varCheck();
void statementCheck();


void parser(table * lexemes)
{
    int symCount = 1; // 0 is reserved for undeclared variables
    symbol * symTable = malloc(sizeof(symbol) * 100000);

    block(symTable, lexemes);

}

void insert(symbol * symTable, int symCount, int kind, char name[], int val, int level, int addr, int mark)
{
    symTable[symCount].kind  = kind;
    symTable[symCount].val   = val;
    symTable[symCount].level = level;
    symTable[symCount].addr  = addr;
    symTable[symCount].mark  = mark;
    strcpy(symTable[symCount].name, name);
}

void block(symbol * symTable, table * lexemes)
{
    constCheck();
    varCheck();
    statementCheck();
}

void constCheck()
{

}

void varCheck()
{

}

void statementCheck()
{
    
}