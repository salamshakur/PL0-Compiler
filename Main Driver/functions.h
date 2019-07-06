/* for main.c */
FILE * fileReader(int argc, char ** argv);

/* for lex.c */
void    printSource(FILE * fp);
table * scanner(FILE * fp);
int     getReserved(char * name);
int     getSpecial(char * name);
void    printTable(table * lexemes);
void    printList(table * lexemes);
void    error(int val);
void    beginVM(FILE * fp);
instr * fetch(FILE * fp);

/* for vm.c */
char  * getOperationName(int op);
void    initialize();
void    execute(instr ir);
void    printInstructions(int n, instr * ir);
void    printRun(instr ir);
void    printStack();
void    printRegisters();
int     base(int l, int base);
void    ERROR_StackOverflow();