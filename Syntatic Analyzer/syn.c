void parser()
{
    code = malloc(sizeof(instr)  * MAX_CODE_LENGTH); 
    symTable = malloc(sizeof(symbol) * 100000); 

    program(); 
}

void program()
{
    block();
    
    lexCount++;

    if(lexemes->arr[lexCount].tokenType != periodsym)
        ERROR_Syn(13);
        
    printf("No errors, program is syntactically correct\n\n");

    emit(SIO, 0, 0, 3);
}

void block()
{
    emit(JMP, 0, 0, 0);

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

    // adding in procedures
    if(lexemes->arr[lexCount].tokenType == procsym)
    {

        procDeclaration();
        
        lexCount++;
    }

    code[0].m = codeCount;

    emit(INC, 0, 0, addrCount);

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

        insert(1, name, val, 0, 0, 0); 

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
            ERROR_Syn(1);
        
        int i = lookUp(lexemes->arr[lexCount].name);

        if(i != -1 && symTable[i].lvl == lvlCount) 
            ERROR_Syn(2); 

        strcpy(name, lexemes->arr[lexCount].name);

        insert(2, name, 0, lvlCount, addrCount, 0); 

        addrCount++; 

        lexCount++; 

    } while (lexemes->arr[lexCount].tokenType == commasym); 
    
    if(lexemes->arr[lexCount].tokenType != semicolonsym) 
        ERROR_Syn(5);  
}

// added procedure declaration function
void procDeclaration()
{
    name = malloc(sizeof(char) * (maxChar + 1));
    
    lexCount++;

    if(lexemes->arr[lexCount].tokenType != identsym)
        ERROR_Syn(1);
    
    (lookUp(lexemes->arr[lexCount].name) == -1)? strcpy(name, lexemes->arr[lexCount].name) : ERROR_Syn(2); 

    lexCount++;

    if(lexemes->arr[lexCount].tokenType != semicolonsym)
        ERROR_Syn(5);
    
    lexCount++;

    lvlCount++;
    
    insert(3, name, 0, lvlCount, codeCount, 0);

    block();

    lexCount++;

    if(lexemes->arr[lexCount].tokenType != semicolonsym)
        ERROR_Syn(5);

    emit(RTN, 0, 0, 0);
    int tempIndex = symCount -1;

    while(symTable[tempIndex].lvl >= lvlCount)
    {
        symTable[tempIndex].mark = 1;
        tempIndex--;
    }

    lvlCount--;
}

void statementDeclaration()
{
    if(lexemes->arr[lexCount].tokenType == identsym) 
    {
        int i = lookUp(lexemes->arr[lexCount].name); 
            
        if(i == -1){
            printf("state name - %s \n", lexemes->arr[lexCount].name);
            ERROR_Syn(6); 
        }

        lexCount++; 

        if(lexemes->arr[lexCount].tokenType != becomessym) 
            ERROR_Syn(7); 
        
        lexCount++; 

        expressionDeclaration(); 

        emit(STO, --regPointer, 0, symTable[i].addr);
    }

    else if(lexemes->arr[lexCount].tokenType == beginsym)
    {
        do
        {
            lexCount++; 

            statementDeclaration(); 

            lexCount++; 

        } while (lexemes->arr[lexCount].tokenType == semicolonsym); 
        
        if(lexemes->arr[lexCount].tokenType != endsym) 
            ERROR_Syn(9);
    }

    else if(lexemes->arr[lexCount].tokenType == ifsym) 
    {   
        lexCount++; 

        conditionDeclaration(); 

        lexCount++; 

        if(lexemes->arr[lexCount].tokenType != thensym) 
            ERROR_Syn(10);

        int tempIndex = codeCount;

        emit(JPC, regPointer, 0, 0);

        lexCount++; 

        statementDeclaration(); 

        code[tempIndex].m = codeCount;
    }
    
    else if(lexemes->arr[lexCount].tokenType == whilesym) 
    {
        int tempIndex = codeCount;

        lexCount++; 

        conditionDeclaration(); 

        int tempIndex2 = codeCount;

        emit(JPC, regPointer, 0, 0);

        lexCount++; 

        if(lexemes->arr[lexCount].tokenType != dosym) 
            ERROR_Syn(11);

        lexCount++; 

        statementDeclaration(); 

        emit(JMP, 0, 0, tempIndex);

        code[tempIndex2].m = codeCount;
    }
    
    else if(lexemes->arr[lexCount].tokenType == readsym) 
    {
        lexCount++; 

        if(lexemes->arr[lexCount].tokenType != identsym) 
            ERROR_Syn(1);

        int i = lookUp(lexemes->arr[lexCount].name);

        if(i == -1){
            printf("read name - %s \n", lexemes->arr[lexCount].name);
            ERROR_Syn(6); 
        }

        if(symTable[i].kind != 2) ERROR_Syn(15);

        emit(SIO, 0, 0, 2);

        emit(STO, 0, 0, symTable[i].addr);

        if(regPointer < 0)
            regPointer = 0;
    }

    
    else if(lexemes->arr[lexCount].tokenType == writesym) 
    {
        lexCount++; 

        if(lexemes->arr[lexCount].tokenType != identsym) 
            ERROR_Syn(1);

        int i = lookUp(lexemes->arr[lexCount].name);

        if(i == -1){
            printf("write name - %s \n", lexemes->arr[lexCount].name);
            ERROR_Syn(6); 
        }
        
        if(symTable[i].kind == 2)
            emit(LOD, 0, 0, symTable[i].addr);
        else
            emit(LIT, 0, 0, symTable[i].val);

        emit(SIO, 0, 0, 1);
    }

    else if(lexemes->arr[lexCount].tokenType == callsym)
    {
        lexCount++;

        if(lexemes->arr[lexCount].tokenType != identsym)
            ERROR_Syn(1);
        
        int i = lookUp(lexemes->arr[lexCount].name);
        printf("i - %d, name - %s \n", i, lexemes->arr[lexCount].name);
        if(i == -1){
            printf("call name - %s \n", lexemes->arr[lexCount].name);
            ERROR_Syn(6); 
        }
        
        if(symTable[i].kind != 3)
            ERROR_Syn(18);
        
        emit(CAL, 0, (lvlCount - symTable[i].lvl), symTable[i].addr);
    }

    else 
    {
        lexCount--;

        return;
    }
}

void conditionDeclaration()
{
    if(lexemes->arr[lexCount].tokenType == oddsym)
    {
        lexCount++;

        expressionDeclaration();

        emit(ODD, regPointer, 0, 0);
    }
    else
    {
        expressionDeclaration();

        lexCount++;

        int op = rel_opDeclaration(lexemes->arr[lexCount].tokenType);

        lexCount++;

        expressionDeclaration();

        emit(op, regPointer-2, regPointer-2, regPointer-1);

        regPointer -= 2;
    }
}

void expressionDeclaration()
{
    int tempType;

    if(lexemes->arr[lexCount].tokenType == plussym || lexemes->arr[lexCount].tokenType == minussym)
    {
        tempType = lexemes->arr[lexCount].tokenType;

        lexCount++;

        termDeclaration();

        if(tempType == minussym)
            emit(NEG, regPointer-1, --regPointer, 0);
    }
    else
        termDeclaration();
    
    lexCount++;

    while(lexemes->arr[lexCount].tokenType == plussym || lexemes->arr[lexCount].tokenType == minussym)
    {
        tempType = lexemes->arr[lexCount].tokenType;

        lexCount++;

        termDeclaration();

        if(tempType == plussym)
        {
            emit(ADD, regPointer-2, regPointer-1, regPointer-2);
            regPointer--;
        }
        else
        {
            emit(SUB, regPointer-2, regPointer-2, regPointer-1);
            regPointer--;
        }

        lexCount++;
    } 

    lexCount--;
}

int rel_opDeclaration(int tokenType)
{
	if(tokenType == eqsym)  return EQL;
	if(tokenType == neqsym) return NEQ;
	if(tokenType == lessym) return LSS;
	if(tokenType == leqsym) return LEQ;
	if(tokenType == gtrsym) return GTR;
	if(tokenType == geqsym) return GEQ;
	ERROR_Syn(12);
}

void termDeclaration()
{
    factorDeclaration();

    lexCount++;

    int tempType;

    while (lexemes->arr[lexCount].tokenType == multsym || lexemes->arr[lexCount].tokenType == slashsym)
    {
        tempType = lexemes->arr[lexCount].tokenType;

        lexCount++;

        factorDeclaration();

        lexCount++;

        if(tempType == multsym)
        {
            emit(MUL, regPointer-2, regPointer-1, regPointer-2);
            regPointer--;
        }
        else
        {
            emit(DIV, regPointer-2, regPointer-1, regPointer-2);
            regPointer--;
        }
    }
    
    lexCount--;
}

void factorDeclaration()
{
    if(lexemes->arr[lexCount].tokenType == identsym)
    {
        int i = lookUp(lexemes->arr[lexCount].name);

        if(i == -1){
            printf("factor name - %s \n", lexemes->arr[lexCount].name);
            ERROR_Syn(6); 
        }
        
        if(symTable[i].kind == 2)
            emit(LOD, regPointer++, 0, symTable[i].addr);
        else if(symTable[i].kind == 1)
            emit(LIT, regPointer++, 0, symTable[i].val);
        else
            ERROR_Syn(16);
    }

    else if(lexemes->arr[lexCount].tokenType == numbersym)
    {
        emit(LIT, regPointer++, 0, atoi(lexemes->arr[lexCount].name));
    }

    else if(lexemes->arr[lexCount].tokenType == lparentsym)
    {
        lexCount++;

        expressionDeclaration();

        lexCount++;

        if(lexemes->arr[lexCount].tokenType != rparentsym)
            ERROR_Syn(8);
    }

    else
    {
        ERROR_Syn(17);
    }
}

int lookUp(char name[])
{
    int n = symCount;
    for(int i = 0; i < n; n--)
    {
        if(strcmp(name, symTable[n].name) == 0){
            if(symTable[n].mark == 1) 
                continue;
            return n;
        }
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

void emit(int op, int r, int l, int m)
{
    if(codeCount > MAX_CODE_LENGTH)
        ERROR_Syn(14);
    
    if(op == SIO)
    {
        if(m == 1)
            op = 9;
        if(m == 2)
            op = 10;
        if(m == 3)
            op = 11;
    }

    code[codeCount].op = op;
    code[codeCount].r  = r;
    code[codeCount].l  = l;
    code[codeCount].m  = m;
    codeCount++;
}

void ERROR_Syn(int val)
{
    char * message;
    switch(val)
    {
        case 1: message  = "An identifier was not found.";  break;
        case 2: message  = "Name has already been declared."; break;
        case 3: message  = "Equal symbol not found."; break;
        case 4: message  = "Number not found."; break;
        case 5: message  = "Semicolon not found."; break;
        case 6: message  = "Undeclared identifier"; break;
        case 7: message  = "Become symbol not found."; break;
        case 8: message  = "Right paranthesis not found."; break;
        case 9: message  = "End symbol not found."; break;
        case 10: message = "Then symbol not found."; break;
        case 11: message = "Do symbol not found."; break;
        case 12: message = "Relational Operation not found."; break;
        case 13: message = "Period symbol not found."; break;
        case 14: message = "Exceeded max code size"; break;
        case 15: message = "Variable not found"; break;
        case 16: message = "Constant/Variable not found."; break;
        case 17: message = "Identifier/Number/Expression not found."; break;
        case 18: message = "Procedure not found"; break;
    }
    printf("***** Error number %d, %s \n", val, message);
    exit(1);
}