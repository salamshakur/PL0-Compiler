void parser()
{
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
    
    statementDeclaration();
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
    int addrCount = 4;
    do
    {
        lexCount++;

        if(lexemes->arr[lexCount].tokenType != identsym)
            exit(1);
        
        char * name = lexemes->arr[lexCount].name;
        lexCount++;

        insert(2, name, 0, 0, addrCount, 0);

        addrCount++;

    } while (lexemes->arr[lexCount].tokenType == commasym);
    
    if(lexemes->arr[lexCount].tokenType != semicolonsym)
        exit(1);
    
    lexCount++;
}

void statementDeclaration()
{
    if(lexemes->arr[lexCount].tokenType == identsym)
    {
        if(lexemes->arr[lexCount].tokenType != eqsym)
            exit(1);
        
        lexCount++;

        if(!checkExpression())
            exit(1);
    }

    
}




int checkExpression()
{
    if(lexemes->arr[lexCount].tokenType == plussym || lexemes->arr[lexCount].tokenType == minussym)
        checkTerm();
    
    return 1;
}

void checkTerm()
{
    do
    {
        checkFactor();
    } while (1);
    
}

void checkFactor()
{

}


void insert(int kind, char name[], int val, int lvl, int addr, int mark)
{
    symTable[symCount].kind  = kind;
    symTable[symCount].val   = val;
    symTable[symCount].lvl   = lvl;
    symTable[symCount].addr  = addr;
    symTable[symCount].mark  = mark;
    strcpy(symTable[symCount].name, name);
    printf("kind - %d \t name - %s \t addr - %d\n", kind, name, addr);
    symCount++;
}