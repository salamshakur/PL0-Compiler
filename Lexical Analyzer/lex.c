#ifndef _GENERIC_H_
#define _GENERIC_H_
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <ctype.h>
#endif

#define maxChar 11
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
    char name[maxChar + 1];
    int tokenType;    
} token;

typedef struct table
{
    struct token;
    int    size;
} table;

void    printSource(FILE * fp);
token * scanner(FILE * fp);
int     getReserved(char * name);
int     getSpecial(char c);
void    printTable(token * table);

void beginLEX(FILE * fp)
{
    printSource(fp);
    rewind(fp);
    token * table = scanner(fp);
    printTable(table);
}

void printSource(FILE * fp)
{
    char c;
    printf("\nSource Program: \n");
    while(!feof(fp))
    {
        c = fgetc(fp);

        if(c != EOF)
            printf("%c", c);
    }
    printf("\n");
}

token * scanner(FILE * fp)
{
    char    c;
    int     countId  = 0;
    int     countNum = 0;
    int     countTB  = 0;
    char    tempID[maxChar + 1];
    char    tempNum[maxInt + 1];
    token * table = malloc(sizeof(token) * 3000);


    while(!feof(fp))
    {
        c = fgetc(fp);

        if(isalpha(c))
        {
            //printf("letter found! -> %c \n", c); // test
            while((isalnum(c)) && !ispunct(c) && countId <= maxChar)
            {
                tempID[countId] = c;
                countId++;
                c = fgetc(fp);
            }
            tempID[countId] = '\0';

            token tk;
            strcpy(tk.name, tempID);
            tk.tokenType = getReserved(tk.name);
            table[countTB] = tk;
            printf("token -> %s \n", table[countTB].name); // test
            memset(tempID, 0, sizeof(tempID));
            countId = 0;
            countTB++;

            continue;
        }

        if(isdigit(c))
        {
            //printf("digit found! -> %c \n", c); // test
            while(isdigit(c) && !ispunct(c) && countNum <= maxInt)
            {
                tempNum[countNum] = c;
                countNum++;
                c = fgetc(fp);
            }
            tempNum[countNum] = '\0';

            token tk;
            strcpy(tk.name, tempNum);
            tk.tokenType = numbersym;
            table[countTB] = tk;
            printf("token -> %s \n", table[countTB].name); // test
            memset(tempNum, 0, sizeof(tempNum));
            countNum = 0;
            countTB++;
            
            continue;
        }

        if(ispunct(c))
        {
            //printf("special found! -> %c \n", c); // test
            continue;
        }
    }

    return table;
}

int getReserved(char name[maxChar])
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

int getSpecial(char c)
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

void printTable(token * table)
{

}