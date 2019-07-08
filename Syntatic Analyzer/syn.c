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
    name = malloc(sizeof(char) * (maxChar + 1));
    do
    {
        lexCount++;

        if(lexemes->arr[lexCount].tokenType != identsym)
            ERROR_Syn(1);

        (lookUp(lexemes->arr[lexCount].name) == -1)? strcpy(name, lexemes->arr[lexCount].name) : ERROR_Syn(2);

        lexCount++;

        if(lexemes->arr[lexCount].tokenType != eqsym)
            ERROR_Syn(3);
        
        lexCount++;

        if(lexemes->arr[lexCount].tokenType != numbersym)
            ERROR_Syn(4);
        
        int val = atoi(lexemes->arr[lexCount].name);
        lexCount++;

        insert(1, name, val, 0, 0, 0, NA);

        memset(name, 0, sizeof(name));

    } while (lexemes->arr[lexCount].tokenType == commasym);

    if(lexemes->arr[lexCount].tokenType != semicolonsym)
        ERROR_Syn(5);
    
    lexCount++;
}


void varDeclaration()
{
    name = malloc(sizeof(char) * (maxChar + 1));
    do
    {
        lexCount++;

        if(lexemes->arr[lexCount].tokenType != identsym)
            exit(1);
        
        (lookUp(lexemes->arr[lexCount].name) == -1)? strcpy(name, lexemes->arr[lexCount].name) : ERROR_Syn(2);
        
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
        int n = lookUp(lexemes->arr[lexCount].name);

        if(n == -1)
            exit(1); // doesn't exist

        lexCount++;

        if(lexemes->arr[lexCount].tokenType != becomessym)
            exit(1);
        
        lexCount++;

        expressionDeclaration();
    }

    
}




void expressionDeclaration()
{
    if(lexemes->arr[lexCount].tokenType == plussym || lexemes->arr[lexCount].tokenType == minussym)
    {
        lexCount++;
        termDeclaration();
    }
    
}

void termDeclaration()
{
    do
    {
        factorDeclaration();
    } while (1);
    
}

void factorDeclaration()
{
    if(lexemes->arr[lexCount].tokenType == identsym)
    {

    }

    if(lexemes->arr[lexCount].tokenType == numbersym)
    {

    }

    if(lexemes->arr[lexCount].tokenType == lparentsym)
    {
        
    }
}


int lookUp(char name[])
{
    int n = symCount;
    for(int i = 0; i < n; n--)
    {
        if(strcmp(name, symTable[n].name) == 0)
            return n;
    }
    return -1;
}

void insert(int kind, char name[], int val, int lvl, int addr, int mark)
{
    symTable[symCount].kind  = kind;
    symTable[symCount].val   = val;
    symTable[symCount].lvl   = lvl;
    symTable[symCount].addr  = addr;
    symTable[symCount].mark  = mark;
    strcpy(symTable[symCount].name, name);
    symCount++;
}

void ERROR_Syn(int val)
{
    char * message;
    switch(val)
    {
        case 1: message = "An identifier was not found.";  break;
        case 2: message = "Name has already been declared."; break;
        case 3: message = "Equal symbol not found."; break;
        case 4: message = "Number not found."; break;
        case 5: message = "Semicolon not found."; break;
    }
    printf("Error hit! %s \n", message);
    exit(1);
}