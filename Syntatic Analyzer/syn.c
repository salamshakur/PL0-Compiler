void parser()
{
    asmTable = malloc(sizeof(instr)  * MAX_CODE_LENGTH);
    symTable = malloc(sizeof(symbol) * 100000);
    program();
}

void program()
{
    block();

    lexCount++;

    if(lexemes->arr[lexCount].tokenType != periodsym)
        ERROR_Syn(13);
    printf("No errors, program is syntactically correct\n");
}

void block()
{
    if(lexemes->arr[lexCount].tokenType == constsym)
    {
        constDeclaration();
        lexCount++;
    }

    if(lexemes->arr[lexCount].tokenType == varsym)
    {
        varDeclaration();
        lexCount++;
    }

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

        insert(1, name, val, 0, 0, 0, NA);

        lexCount++;

        memset(name, 0, sizeof(name));

    } while (lexemes->arr[lexCount].tokenType == commasym);

    if(lexemes->arr[lexCount].tokenType != semicolonsym)
        ERROR_Syn(5);
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

        insert(2, name, 0, 0, addrCount, 0);
        addrCount++;

        lexCount++;

    } while (lexemes->arr[lexCount].tokenType == commasym);
    
    if(lexemes->arr[lexCount].tokenType != semicolonsym)
        exit(1);    
}

void statementDeclaration()
{
    if(lexemes->arr[lexCount].tokenType == identsym)
    {
        int i = lookUp(lexemes->arr[lexCount].name);

        if(i == -1) ERROR_Syn(6);

        lexCount++;

        if(lexemes->arr[lexCount].tokenType != becomessym) ERROR_Syn(7);
        
        lexCount++;

        expressionDeclaration();
    }

    else if(lexemes->arr[lexCount].tokenType == beginsym)
    {
        do
        {
            lexCount++;

            statementDeclaration();

            lexCount++;

        } while (lexemes->arr[lexCount].tokenType == semicolonsym);
        
        if(lexemes->arr[lexCount].tokenType != endsym) ERROR_Syn(9);
    }

    else if(lexemes->arr[lexCount].tokenType == ifsym)
    {   
        lexCount++;

        conditionDeclaration();

        lexCount++;

        if(lexemes->arr[lexCount].tokenType != thensym) ERROR_Syn(10);

        lexCount++;

        statementDeclaration();

    }
    
    else if(lexemes->arr[lexCount].tokenType == whilesym)
    {
        lexCount++;

        conditionDeclaration();

        lexCount++;

        if(lexemes->arr[lexCount].tokenType != dosym) ERROR_Syn(11);

        lexCount++;

        statementDeclaration();
    }
    
    else if(lexemes->arr[lexCount].tokenType == readsym)
    {
        lexCount++;

        if(lexemes->arr[lexCount].tokenType != identsym) ERROR_Syn(1);
    }

    
    else if(lexemes->arr[lexCount].tokenType == writesym)
    {
        lexCount++;

        if(lexemes->arr[lexCount].tokenType != identsym) ERROR_Syn(1);
    }

    else
    {
        lexCount--; // test
        return;
    }
}

void conditionDeclaration()
{
    if(lexemes->arr[lexCount].tokenType == oddsym)
    {
        lexCount++;
        expressionDeclaration();
    }
    else
    {
        expressionDeclaration();

        lexCount++;

        rel_opDeclaration();

        lexCount++;

        expressionDeclaration();
    }
}

void expressionDeclaration()
{
    if(lexemes->arr[lexCount].tokenType == plussym || lexemes->arr[lexCount].tokenType == minussym)
        lexCount++;

    termDeclaration();
    
    lexCount++;

    while(lexemes->arr[lexCount].tokenType == plussym || lexemes->arr[lexCount].tokenType == minussym)
    {
        lexCount++;

        termDeclaration();

        lexCount++;
    } 

    lexCount--;
}

void rel_opDeclaration()
{
    if(lexemes->arr[lexCount].tokenType == eqsym)
    {

    }
    
    else if(lexemes->arr[lexCount].tokenType == neqsym)
    {

    }
        
    else if(lexemes->arr[lexCount].tokenType == lessym)
    {
        
    }
        
    else if(lexemes->arr[lexCount].tokenType == leqsym)
    {
        
    }
        
    else if(lexemes->arr[lexCount].tokenType == gtrsym)
    {
        
    }
        
    else if(lexemes->arr[lexCount].tokenType == geqsym)
    {
        
    }
    
    else
    {
        ERROR_Syn(12);
    }
}

void termDeclaration()
{
    factorDeclaration();

    lexCount++;

    while (lexemes->arr[lexCount].tokenType == multsym || lexemes->arr[lexCount].tokenType == slashsym)
    {
        lexCount++;

        factorDeclaration();

        lexCount++;
    }
    
    lexCount--;
}

void factorDeclaration()
{
    if(lexemes->arr[lexCount].tokenType == identsym)
    {
        int i = lookUp(lexemes->arr[lexCount].name);

        if(i == -1)
            ERROR_Syn(6);
        
    }

    if(lexemes->arr[lexCount].tokenType == numbersym)
    {
        // use later for object code
    }

    if(lexemes->arr[lexCount].tokenType == lparentsym)
    {
        lexCount++;

        expressionDeclaration();

        lexCount++;

        if(lexemes->arr[lexCount].tokenType != rparentsym)
            ERROR_Syn(8);
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

void createAssembly(int op, int r, int l, int m)
{
    asmTable[asmCount].op = op;
    asmTable[asmCount].r  = r;
    asmTable[asmCount].l  = l;
    asmTable[asmCount].m  = m;
    asmCount++;
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
        case 6: message = "Undeclared identifier"; break;
        case 7: message = "Become symbol not found."; break;
        case 8: message = "Right paranthesis not found."; break;
        case 9: message = "End symbol not found."; break;
        case 10: message = "Then symbol not found."; break;
        case 11: message = "Do symbol not found."; break;
        case 12: message = "Relational Operation not found."; break;
        case 13: message = "Period symbol not found."; break;
    }
    printf("Error hit! %s \n", message);
    exit(1);
}