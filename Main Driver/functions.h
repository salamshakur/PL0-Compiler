/* for main.c */
void    fileReader(int argc, char ** argv);

/* for lex.c */
void    scanner();
void    printSource();
int     getReserved(char * name);
int     getSpecial(char * name);
void    printTable();
void    printList();
void    error(int val);

/* for vm.c */
void    virtual();
void    fetch();
char  * getOperationName(int op);
void    initialize();
void    execute(instr ir);
void    printInstructions(int n, instr * ir);
void    printRun(instr ir);
void    printStack();
void    printRegisters();
int     base(int l, int base);
void    ERROR_StackOverflow();

/* for syn.c */
void parser(table * lexemes);