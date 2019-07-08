#include "headers.h"
#include "defines.h"
#include "structs.h"
#include "functions.h"
#include "globals.h"
#include "compilers.h"

void main(int argc, char ** argv)
{
    fileReader(argc, argv);
    
    scanner();
    parser();
    //virtual();
    fclose(fp);
}

