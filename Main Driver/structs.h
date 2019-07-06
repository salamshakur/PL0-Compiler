/* enumerated token type values */
typedef enum 
{ 
    nulsym = 1, identsym, numbersym, plussym, minussym,
    multsym,  slashsym, oddsym, eqsym, neqsym, lessym, leqsym,
    gtrsym, geqsym, lparentsym, rparentsym, commasym, semicolonsym,
    periodsym, becomessym, beginsym, endsym, ifsym, thensym, 
    whilesym, dosym, callsym, constsym, varsym, procsym, writesym,
    readsym, elsesym
} token_type;

/* token */
typedef struct token 
{
    char name[maxChar + 1];
    int tokenType;    
} token;

/* token table */
typedef struct table
{
    struct token * arr;
    int size;
} table;

/* instruction register */
typedef struct instr
{
    int op;  // operation code
    int r;   // register
    int l;   // lexicographical level 
    int m;   // modifier
} instr;