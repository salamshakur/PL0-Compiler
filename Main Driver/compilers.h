#include "../Lexical Analyzer/lex.c"
#include "../Virtual Machine/vm.c"
#include "../Syntatic Analyzer/syn.c"

/* to read in source code to compile */
void fileReader(int argc, char ** argv)
{
    if(argc < 2)
    {
        printf("Error: No input file found.\n");
        exit(1);
    }
    else if(argc >= 2)
        fp = fopen(argv[1], "r");
    else
        fp = fopen(argv[0], "r");
}