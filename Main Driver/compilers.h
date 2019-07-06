#include "../Lexical Analyzer/lex.c"
#include "../Virtual Machine/vm.c"

/* to read in source code to compile */
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