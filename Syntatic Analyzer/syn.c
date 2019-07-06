void parser()
{
    symCount = 1;
    lexCount = 0;
    symTable = malloc(sizeof(symbol) * 100000);

    program();
}

void program()
{
    block();

    if(lexemes->arr[lexCount].tokenType != periodsym)
        exit(1);
}

void block()
{
    if(lexemes->arr[lexCount].tokenType == constsym)
        constDeclaration();
    if(lexemes->arr[lexCount].tokenType == varsym)
        varDeclaration();
}

void constDeclaration()
{
    do
    {
        lexCount++;

        if(lexemes->arr[lexCount].tokenType != identsym)
            exit(1);
        
        char * name = lexemes->arr[lexCount].name;
        lexCount++;

        if(lexemes->arr[lexCount].tokenType != eqsym)
            exit(1);
        
        lexCount++;

        if(lexemes->arr[lexCount].tokenType != numbersym)
            exit(1);
        
        int val = atoi(lexemes->arr[lexCount].name);
        lexCount++;

        insert(1, name, val, 0, 0, NA, 0);

    } while (lexemes->arr[lexCount].tokenType == commasym);
    
    if(lexemes->arr[lexCount].tokenType != semicolonsym)
        exit(1);
    
    lexCount++;
}


void varDeclaration()
{

}







void insert(int kind, char name[], int val, int lvl, int addr, int mark)
{
    symTable[symCount].kind  = kind;
    symTable[symCount].val   = val;
    symTable[symCount].lvl = lvl;
    symTable[symCount].addr  = addr;
    symTable[symCount].mark  = mark;
    strcpy(symTable[symCount].name, name);
    symCount++;
}