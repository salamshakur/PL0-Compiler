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

void printSource(FILE * fp);
void scanner(FILE * fp);

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
    char c;
    int i = 0;
    int j = 0;
    int count = 100;
    char name[maxChar];
    token * tkList = malloc(sizeof(token) * count);

    while(!feof(fp))
    {
        memset(name, 0, sizeof(name));
        c = fgetc(fp);

        if(c == EOF)
            break;

        if(isspace(c))
            continue;
        
        if(isalpha(c))
        {
            name[i] = c;
            i++;
            c = fgetc(fp);

            while(isalpha(c) || isdigit(c))
            {
                name[i] = c;
                i++;
                c = fgetc(fp);
            }

            token tk;
            strcpy(tk.name, name);
            //tk.tokenType = ?;
            tkList[j] = tk;
            i = 0;
            j++;
        } 
        
          
    }
}   