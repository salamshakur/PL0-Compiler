#ifndef _GENERIC_H_
#define _GENERIC_H_
    #include <stdio.h>
    #include <stdlib.h>
#endif

#define maxChar 11
#define maxInt  5

// Symbol Table Record
typedef struct namerecord_t
{
    int kind;            // const = 1, var = 2, proc = 3
    char name[maxChar];  // name up to 11 chars
    int val;             // ASCII value
    int level;           // L level
    int adr;             // M address
} namerecord_t;

void beginLEX(FILE * fp)
{

}