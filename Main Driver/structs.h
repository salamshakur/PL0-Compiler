/* for lex.c */
typedef enum { 
    nulsym = 1, identsym, numbersym, plussym, minussym,
    multsym,  slashsym, oddsym, eqsym, neqsym, lessym, leqsym,
    gtrsym, geqsym, lparentsym, rparentsym, commasym, semicolonsym,
    periodsym, becomessym, beginsym, endsym, ifsym, thensym, 
    whilesym, dosym, callsym, constsym, varsym, procsym, writesym,
    readsym, elsesym
} token_type;

typedef struct token {
    char name[maxChar + 1];
    int tokenType;    
} token;

typedef struct table {
    struct token * arr;
    int size;
} table;

//========================================================================\\

/* for vm.c && syn.c */
typedef struct instr {
    int op;  // operation code
    int r;   // register
    int l;   // lexicographical level 
    int m;   // modifier
} instr;

//========================================================================\\

/* for syn.c */
typedef struct symbol
{
    int  kind;                // const = 1, var = 2, proc = 3
    char name[maxChar + 1];   // name up to 11 chars
    int  val;                 // numbers (ASCII value)
    int  lvl;                 // L level
    int  addr;                // M address
    int  mark;                // to indicate that code has been generated already for a block
} symbol;