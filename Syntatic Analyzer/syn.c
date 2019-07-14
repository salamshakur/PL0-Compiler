void parser()
{
    code = malloc(sizeof(instr)  * MAX_CODE_LENGTH); // create array to hold PL0 assembly
    symTable = malloc(sizeof(symbol) * 100000); // create symbol table to store const, var, procedures

    program(); // check EBNF program

    for(int i = 0; i < codeCount; i++)
        printf("%d %d %d %d \n", code[i].op, code[i].r, code[i].l, code[i].m);
}

void program()
{
    block(); // check EBNF block

    lexCount++;

    if(lexemes->arr[lexCount].tokenType != periodsym)
        ERROR_Syn(13);
        
    printf("No errors, program is syntactically correct\n\n");

    emit(SIO, 0, 0, 3);
}

void block()
{
    emit(JMP, 0, 0, 0);

    if(lexemes->arr[lexCount].tokenType == constsym) // check if token is a const
    {
        constDeclaration(); // check EBNF const

        lexCount++; // get next token
    }

    if(lexemes->arr[lexCount].tokenType == varsym) // check if token is a var
    {
        varDeclaration(); // check EBNF var

        lexCount++; // get next token
    }

    code[0].m = codeCount;

    emit(INC, 0, 0, addrCount);

    statementDeclaration(); // check EBNF statement
}

void constDeclaration()
{
    name = malloc(sizeof(char) * (maxChar + 1)); // create a string to hold const name
    do
    {
        lexCount++; // get next token

        if(lexemes->arr[lexCount].tokenType != identsym) // check if token is an identifier
            ERROR_Syn(1);

        (lookUp(lexemes->arr[lexCount].name) == -1)? strcpy(name, lexemes->arr[lexCount].name) : ERROR_Syn(2); // check if identifier already exist

        lexCount++; // get next token

        if(lexemes->arr[lexCount].tokenType != eqsym) // check if token is an equal symbol
            ERROR_Syn(3);
        
        lexCount++; // get next token

        if(lexemes->arr[lexCount].tokenType != numbersym) // check if token is a number
            ERROR_Syn(4);
        
        int val = atoi(lexemes->arr[lexCount].name); // convert the number from string into an int

        insert(1, name, val, 0, 0, 0, NA); // insert const into the symbol table

        lexCount++; // get next token

        memset(name, 0, sizeof(name)); // reset name string to reuse again

    } while (lexemes->arr[lexCount].tokenType == commasym); // continue logic as long as there is a comma to be found

    if(lexemes->arr[lexCount].tokenType != semicolonsym) // check if the end of the const line is a semicolon
        ERROR_Syn(5);
}

void varDeclaration()
{
    name = malloc(sizeof(char) * (maxChar + 1)); // create a string to hold var name
    do
    {
        lexCount++; // get next token

        if(lexemes->arr[lexCount].tokenType != identsym) // check if token is an identifier
            ERROR_Syn(1);
        
        (lookUp(lexemes->arr[lexCount].name) == -1)? strcpy(name, lexemes->arr[lexCount].name) : ERROR_Syn(2); // check if identifier already exist

        insert(2, name, 0, 0, addrCount, 0); // insert var into the symbol table

        addrCount++; // increment the address for the next var

        lexCount++; // get next token

    } while (lexemes->arr[lexCount].tokenType == commasym); // continue logic as long as there is a comma to be found
    
    if(lexemes->arr[lexCount].tokenType != semicolonsym) // check if the end of the var line is a semicolon
        ERROR_Syn(5);  
}

void statementDeclaration()
{
    if(lexemes->arr[lexCount].tokenType == identsym) // check if token is an identifier
    {
        int i = lookUp(lexemes->arr[lexCount].name); // check if identifier has been declared
            
        if(i == -1) ERROR_Syn(6); 

        lexCount++; // get next token

        if(lexemes->arr[lexCount].tokenType != becomessym) // check if token is a become symbol
            ERROR_Syn(7); 
        
        lexCount++; // get next token

        expressionDeclaration(); // check EBNF expression

        emit(STO, --regPointer, 0, symTable[i].addr);
    }

    else if(lexemes->arr[lexCount].tokenType == beginsym) // or if it's a begin 
    {
        do
        {
            lexCount++; // get next token

            statementDeclaration(); // recurse EBNF statement

            lexCount++; // get next token

        } while (lexemes->arr[lexCount].tokenType == semicolonsym); // continue logic as long as there is a semicolon to be found
        
        if(lexemes->arr[lexCount].tokenType != endsym) // check if begin block ended with end token
            ERROR_Syn(9);
    }

    else if(lexemes->arr[lexCount].tokenType == ifsym) // or if it's an if statement
    {   
        lexCount++; // get next token

        conditionDeclaration(); // check EBNF condition

        lexCount++; // get next token

        if(lexemes->arr[lexCount].tokenType != thensym) // check if token is a then symbol
            ERROR_Syn(10);

        int tempIndex = codeCount;

        emit(JPC, regPointer, 0, 0);

        lexCount++; // get next token

        statementDeclaration(); // recurse statement

        code[tempIndex].m = codeCount;
    }
    
    else if(lexemes->arr[lexCount].tokenType == whilesym) // or if it's a while loop
    {
        int tempIndex = codeCount;

        lexCount++; // get next token

        conditionDeclaration(); // check EBNF condition

        int tempIndex2 = codeCount;

        emit(JPC, regPointer, 0, 0);

        lexCount++; // get next token

        if(lexemes->arr[lexCount].tokenType != dosym) // check if token is a do symbol
            ERROR_Syn(11);

        lexCount++; // get next token

        statementDeclaration(); // recurse statement

        emit(JMP, 0, 0, tempIndex);

        code[tempIndex2].m = codeCount;
    }
    
    else if(lexemes->arr[lexCount].tokenType == readsym) // or if it's a read
    {
        lexCount++; // get next token

        if(lexemes->arr[lexCount].tokenType != identsym) // check if token is a identifier
            ERROR_Syn(1);

        int i = lookUp(lexemes->arr[lexCount].name);

        if(i == -1) ERROR_Syn(6);

        if(symTable[i].kind != 2) ERROR_Syn(15);

        emit(SIO, 0, 0, 2);

        emit(STO, 0, 0, symTable[i].addr);

        if(regPointer < 0)
            regPointer = 0;
    }

    
    else if(lexemes->arr[lexCount].tokenType == writesym) // or if it's a write
    {
        lexCount++; // get next token

        if(lexemes->arr[lexCount].tokenType != identsym) // check if token is an identifier
            ERROR_Syn(1);

        int i = lookUp(lexemes->arr[lexCount].name);

        if(i == -1)
            ERROR_Syn(6);
        
        if(symTable[i].kind == 2)
            emit(LOD, 0, 0, symTable[i].addr);
        else
            emit(LIT, 0, 0, symTable[i].val);

        emit(SIO, 0, 0, 1);
    }

    else // else put back token and return
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

        if(i == -1)
            ERROR_Syn(6);
        
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

void emit(int op, int r, int l, int m)
{
    if(codeCount > MAX_CODE_LENGTH)
        ERROR_Syn(14);
    
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
    }
    printf("Error hit! %s \n", message);
    exit(1);
}