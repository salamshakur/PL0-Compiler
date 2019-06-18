#ifndef _GENERIC_H_
#define _GENERIC_H_
    #include <stdio.h>
    #include <stdlib.h>
#endif

#include "../Virtual Machine/vm.c"
#include "../Lexical Analyzer/lex.c"
FILE * fileReader(int argc, char ** argv);

void main(int argc, char ** argv)
{
    FILE * fp = fileReader(argc, argv);

    beginVM(fp);
    beginLEX(fp);
}

FILE * fileReader(int argc, char ** argv)
{
    FILE * fp = NULL;
    if(argc < 2)
    {
        printf("Error: No input file found.\n");
        exit(1);
    }
    else if(argc >= 2)
        fp = fopen(argv[1], "r");
    else
        fp = fopen(argv[0], "r");
    return fp;
}

