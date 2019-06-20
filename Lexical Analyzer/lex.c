#ifndef _GENERIC_H_
#define _GENERIC_H_
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <ctype.h>
#endif

#define maxChar 11 + 1
#define maxInt  5

typedef enum 
{ 
    nulsym = 1, identsym, numbersym, plussym, minussym,
    multsym,  slashsym, oddsym, eqsym, neqsym, lessym, leqsym,
    gtrsym, geqsym, lparentsym, rparentsym, commasym, semicolonsym,
    periodsym, becomessym, beginsym, endsym, ifsym, thensym, 
    whilesym, dosym, callsym, constsym, varsym, procsym, writesym,
    readsym , elsesym 
} token_type;

typedef struct token 
{
    char name[maxChar];
    int tokenType;    
} token;

void printSource(FILE * fp);
void scanner(FILE * fp);
int  isReserved(char * name);
int  isSpecial(char c);

void beginLEX(FILE * fp)
{
    printSource(fp);
    rewind(fp);
    scanner(fp);
}

void printSource(FILE * fp)
{
    printf("\nSource Program: \n");

    char c;
    while(!feof(fp))
    {
        c = fgetc(fp);

        if(c != EOF)
            printf("%c", c);
    }
}

void scanner(FILE * fp)
{
    
}

int isReserved(char name[maxChar])
{
    if (strcmp(name, "const")     == 0) return constsym;
    if (strcmp(name, "var")       == 0) return varsym;
    if (strcmp(name, "procedure") == 0) return procsym;
    if (strcmp(name, "call")      == 0) return callsym;
    if (strcmp(name, "begin")     == 0) return beginsym;
    if (strcmp(name, "end")       == 0) return endsym;
    if (strcmp(name, "if")        == 0) return ifsym;
    if (strcmp(name, "then")      == 0) return thensym;
    if (strcmp(name, "else")      == 0) return elsesym;
    if (strcmp(name, "while")     == 0) return whilesym;
    if (strcmp(name, "do")        == 0) return dosym;
    if (strcmp(name, "read")      == 0) return readsym;
    if (strcmp(name, "write")     == 0) return writesym;
    return identsym;
}

int isSpecial(char c)
{
    // TODO: add nested if for => <= etc...
    // -1 is invalid
    // * should be lead by /
    // = should follow other symbols or :
    // remember these and fix it...
    if (c == '+') return plussym;
    if (c == '-') return minussym;
    if (c == '*') return -1;
    if (c == '/') return slashsym;
    if (c == '(') return lparentsym;
    if (c == ')') return rparentsym;
    if (c == '=') return eqsym;
    if (c == ',') return commasym;
    if (c == '.') return periodsym;
    if (c == '<') return lessym;
    if (c == '>') return gtrsym;
    if (c == ';') return semicolonsym;
    if (c == ':') return -1;
    return -1;
}
