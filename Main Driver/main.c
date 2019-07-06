#include "headers.h"
#include "defines.h"
#include "structs.h"
#include "functions.h"
#include "globals.h"
#include "compilers.h"

void main(int argc, char ** argv)
{
    FILE * fp = fileReader(argc, argv);

    //beginVM(fp);
    table * lexemes = beginLEX(fp);
    fclose(fp);
}

