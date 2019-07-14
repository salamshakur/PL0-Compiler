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

typedef enum opcodes
{
    LIT = 1, RTN = 2, LOD = 3, STO = 4, 
    CAL = 5, INC = 6, JMP = 7, JPC = 8, SIO = 9, 
    NEG = 12, ADD = 13, SUB = 14, MUL = 15, DIV = 16, 
    ODD = 17, MOD = 18, EQL = 19, NEQ = 20, 
    LSS = 21, LEQ = 22, GTR = 23, GEQ = 24
} opcodes;