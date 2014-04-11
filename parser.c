/*

********
BATCH 62
********

************************
ANUJ PAHUJA 2011A7PS028P
SIDHARTH CHATURVEDI 2011A7PS126P
********************************
*/

#include <stdio.h>
#include "parser.h"
#include "lexerDef.h"
#include <string.h>
#include <stdlib.h>

char* grammarSymbols[] = {"mainFunction", "stmtsAndFunctionDefs", "functionChoice", "stmtOrFunctionDef", "stmt", "functionDef", "declarationStmt", "assignmentStmt_type1", "assignmentStmt_type2", "ifStmt", "ioStmt", "funCallStmt", "parameter_list", "type", "remainingList", "var_list", "more_ids", "leftHandSide_singleVar", "rightHandSide_type1", "leftHandSide_listVar", "rightHandSide_type2", "sizeExpression", "elsePart", "booleanExpression", "otherStmts", "inputParameterList", "var", "listVar", "arithmeticExpression", "precedenceChoice", "arithmeticTerm", "precedenceChoice2", "operator_lowPrecedence", "factor", "operator_highPrecedence", "logicalOp", "constrainedVars", "relationalOp", "matrixElement", "matrix", "rows", "row", "extraRow", "extraColumn", "remainingColElements", "MAIN", "SQO", "SQC", "END", "FUNCTION", "ASSIGNOP", "FUNID", "SEMICOLON", "ID", "INT", "REAL", "STRING", "MATRIX", "COMMA", "SIZE", "IF", "OP", "CL", "ELSE", "ENDIF", "READ", "PRINT", "PLUS", "MINUS", "MUL", "DIV", "NUM", "RNUM", "STR", "AND", "OR", "NOT", "LT", "LE", "EQ", "GT", "GE", "NE", "EPSILON"};

char *nonTerminals[] = {"mainFunction", "stmtsAndFunctionDefs", "functionChoice", "stmtOrFunctionDef", "stmt", "functionDef", "declarationStmt", "assignmentStmt_type1", "assignmentStmt_type2", "ifStmt", "ioStmt", "funCallStmt", "parameter_list", "type", "remainingList", "var_list", "more_ids", "leftHandSide_singleVar", "rightHandSide_type1", "leftHandSide_listVar", "rightHandSide_type2", "sizeExpression", "elsePart", "booleanExpression", "otherStmts", "inputParameterList", "var", "listVar", "arithmeticExpression", "precedenceChoice", "arithmeticTerm", "precedenceChoice2", "operator_lowPrecedence", "factor", "operator_highPrecedence", "logicalOp", "constrainedVars", "relationalOp", "matrixElement", "matrix", "rows", "row", "extraRow", "extraColumn", "remainingColElements"};

char* terminals[] = {"MAIN", "SQO", "SQC", "END", "FUNCTION", "ASSIGNOP", "FUNID", "SEMICOLON", "ID", "INT", "REAL", "STRING", "MATRIX", "COMMA", "SIZE", "IF", "OP", "CL", "ELSE", "ENDIF", "READ", "PRINT", "PLUS", "MINUS", "MUL", "DIV", "NUM", "RNUM", "STR", "AND", "OR", "NOT", "LT", "LE", "EQ", "GT", "GE", "NE", "EPSILON"};

int convert(char* str)
{
    int i;
    for(i = 0; i < sizeof(grammarSymbols)/sizeof(char*); i++)
    {
        if(strcmp(str,grammarSymbols[i]) == 0)
            return i;
    }
    return -1;
}

grammar storeGrammar(char* fileName)
{
    grammar G = (grammar)calloc(1,sizeof(grammar_t));
    FILE *fp;
    char str[1000];
    fp = fopen(fileName,"r");
    int i = 0;
    while(fgets(str,1000,fp) != NULL)
    {
        char *str2 = strtok(str," =\n\r");
        G->rules[i] = (ruleptr)calloc(1,sizeof(rule));
        G->rules[i]->lhs = (symbol_name)convert(str2);
        G->rules[i]->rhs = NULL;

        node2ptr temp2 = (node2ptr)calloc(1,sizeof(node2));
        temp2->rule_num = i;
        temp2->next = G->nonTerminalLHS[G->rules[i]->lhs];
        G->nonTerminalLHS[G->rules[i]->lhs] = temp2;

        str2 = strtok(NULL," =\n\r");
        nodeptr temp = (nodeptr)calloc(1,sizeof(node));
        temp->sym = (symbol_name)convert(str2);
        if(temp->sym == EPSILON)
            G->epsilon_array[G->rules[i]->lhs] = 1;
        temp->next = NULL;
        temp->prev = NULL;
        if(temp->sym < nNonTerminals)
        {
            node3ptr temp3 = (node3ptr)calloc(1,sizeof(node3));
            temp3->pt = temp;
            temp3->next = G->nonTerminalOccurence[temp->sym];
            temp3->ruleNum = i;
            G->nonTerminalOccurence[temp->sym] = temp3;
        }
        G->rules[i]->rhs = temp;
        str2 = strtok(NULL," =\n\r");
        while(str2 != NULL)
        {
            temp->next = (nodeptr)calloc(1,sizeof(node));
            temp->next->prev = temp;
            temp = temp->next;
            temp->sym = (symbol_name)convert(str2);
            temp->next = NULL;
            if(temp->sym < nNonTerminals)
            {
                node3ptr temp3 = (node3ptr)calloc(1,sizeof(node3));
                temp3->pt = temp;
                temp3->next = G->nonTerminalOccurence[temp->sym];
                temp3->ruleNum = i;
                G->nonTerminalOccurence[temp->sym] = temp3;
            }
            str2 = strtok(NULL," =\n\r");
        }
        i++;
    }

    calculateFirstSets(G);
    calculateFollowSets(G);
    return G;
}

void first(grammar G, symbol_name symbol)
{
    visitedNonTerminal[symbol] = 1;
    node2ptr n1 = G->nonTerminalLHS[symbol];
    while(n1 != NULL)
    {
        int i = n1->rule_num;
        nodeptr n2 = G->rules[i]->rhs;
        while(n2 != NULL)
        {
            if(n2->sym >= nNonTerminals)
            {
                G->ffSets[symbol].first[(int)n2->sym - nNonTerminals] = 1;
                G->ffSets[symbol].first_rule[(int)n2->sym - nNonTerminals] = i;
                break;
            }
            else
            {
                if(!visitedNonTerminal[n2->sym])
                    first(G, n2->sym);
                int j;
                for(j = 0;j<nTerminals;j++)
                {
                    G->ffSets[symbol].first[j] = G->ffSets[symbol].first[j] | G->ffSets[n2->sym].first[j];
                    if(G->ffSets[n2->sym].first[j])
                        G->ffSets[symbol].first_rule[j] = i;
                }
                if(!G->epsilon_array[n2->sym])
                    break;
            }
            n2 = n2->next;
        }
        n1 = n1->next;
    }
}

void calculateFirstSets(grammar G)
{
    int i;
    for(i=0;i<nNonTerminals;i++)
    {
        if(!visitedNonTerminal[i])
            first(G,(symbol_name)i);
    }
}

void follow(grammar G, symbol_name symbol)
{
    visitedNonTerminal2[symbol] = 1;
    node3ptr n1 = G->nonTerminalOccurence[symbol];
    while(n1!=NULL)
    {
        nodeptr n2 = n1->pt->next;
        while(n2 != NULL)
        {
            if(n2->sym >= nNonTerminals)
            {
                G->ffSets[symbol].follow[n2->sym - nNonTerminals] = 1;
                break;
            }
            else
            {
                int j;
                for(j=0;j<nTerminals-1;j++)
                {
                    G->ffSets[symbol].follow[j] = G->ffSets[symbol].follow[j] | G->ffSets[n2->sym].first[j];
                }
                if(!G->epsilon_array[n2->sym])
                    break;
                n2 = n2->next;
            }
        }
        if(n2 == NULL)
        {
            if(!visitedNonTerminal2[G->rules[n1->ruleNum]->lhs])
                follow(G, G->rules[n1->ruleNum]->lhs);
            int j;
            for(j=0;j<nTerminals;j++)
            {
                G->ffSets[symbol].follow[j] = G->ffSets[symbol].follow[j] | G->ffSets[G->rules[n1->ruleNum]->lhs].follow[j];
            }
        }
        n1 = n1->next;
    }
}

void calculateFollowSets(grammar G)
{
    int i;
    for(i=0;i<nNonTerminals;i++)
    {
        //if(!visitedNonTerminal2[i])
            follow(G, (symbol_name)i);
        /*printf("%s ",nonTerminals[i]);
        int j;
        for(j = 0;j<nTerminals;j++)
        {
            if(G->ffSets[i].follow[j] == 1)
                printf("%s ",terminals[j]);
        }
        printf("\n");
        */
    }
}

void createParseTable(grammar G, table T)
{
    *T = (table_t*)calloc(1,sizeof(table_t));
    int i;
    for(i = 0;i<nNonTerminals;i++)
    {
        int j;
        for(j=0;j<nTerminals;j++)
            (*T)->array[i][j] = -1;
    }

    for(i = 0;i < nNonTerminals;i++)
    {
        int j;
        for(j = 0;j < nTerminals;j++)
        {
            if(G->ffSets[i].first[j])
                (*T)->array[i][j] = G->ffSets[i].first_rule[j];
        }
        if(G->epsilon_array[i])
        {
            for(j = 0;j < nTerminals - 1;j++)
            {
                if(G->ffSets[i].follow[j])
                    (*T)->array[i][j] = G->ffSets[i].first_rule[nTerminals-1];
            }
        }
    }
    /*for(i = 0;i < nNonTerminals;i++)
    {
        int j;
        for(j = 0;j < nTerminals;j++)
            printf("%d ",(*T)->array[i][j]);
        printf("\n");
    }*/
}

parseTree parseInputSourceCode(char *testcaseFile, table T, grammar G)
{
    FILE *fp = fopen(testcaseFile,"r");
    parseTree pt = (parseTree)calloc(1,sizeof(parseTree_t));
    pt->parent = NULL;
    stack st = (stack)calloc(1,sizeof(stack_t));
    st->size = 0;
    st = push(DOLLAR,st);
    pt->tk = (tokenInfo)calloc(1,sizeof(token_struct));
    st = push(mainFunction,st);
    pt->tk->sym = mainFunction;

    parseTree curNode = pt;
    tokenInfo tk = getNextToken(fp);
    int t;
    while(st->size != 1)
    {

        if(tk == NULL)
        {
            tk = getNextToken(fp);
            while(tk == NULL || tk->sym != EPSILON)
                tk = getNextToken(fp);
            return NULL;
        }
        symbol_name symbol = tk->sym;
        t = (int)symbol - nNonTerminals;
        if(st->head->sym == symbol)
        {
            curNode->tk = tk;
            while(curNode->right == NULL && curNode->parent != NULL)
                curNode = curNode->parent;
            curNode = curNode->right;
            st = pop(st);
            tk = getNextToken(fp);
        }
        else if(st->head->sym == EPSILON)
        {
        	st = pop(st);
        	while(curNode->right == NULL)
        		curNode = curNode->parent;
            curNode = curNode->right;
        }
        else if(st->head->sym >= nNonTerminals)
        {
            parseError(tk, st, G, &T);
            return NULL;
        }
        else if((*T)->array[st->head->sym][t] == -1)
        {
            parseError(tk, st, G, &T);
            return NULL;
        }
        else
        {
            int i = (*T)->array[st->head->sym][t];
            nodeptr n1 = G->rules[i]->rhs;
            while(n1->next != NULL)
            {
                n1 = n1->next;
            }
            st = pop(st);
            curNode->child = (parseTree)calloc(1,sizeof(parseTree_t));
            curNode->child->parent = curNode;
            curNode = curNode->child;
            curNode->tk = (tokenInfo)calloc(1,sizeof(token_struct));
            curNode->tk->sym = n1->sym;
            st = push(n1->sym,st);
            n1 = n1->prev;
            while(n1!=NULL)
            {
                curNode->left = (parseTree)calloc(1,sizeof(parseTree_t));
                curNode->left->right = curNode;
                curNode->left->parent = curNode->parent;
                curNode = curNode->left;
                curNode->tk = (tokenInfo)calloc(1,sizeof(token_struct));
                curNode->tk->sym = n1->sym;
                //strcpy(curNode->tk->stringValue, "----");
                st = push(n1->sym,st);
                n1 = n1->prev;
            }
        }
    }
    if((tk = getNextToken(fp))->sym != EPSILON)
    {
        parseError(tk, st, G, &T);
        return NULL;
    }
    printf("Compiled Successfully: Input source code is syntactically correct!!\n");
    return pt;
}

void parseError(tokenInfo tk, stack st, grammar G, table T)
{
    symbol_name sym = st->head->sym;
    printf("The token %s for lexeme %s does not match at line %d. The expected token/s here is/are\n",grammarSymbols[tk->sym], tk->stringValue, tk->currentLine);
    int i;
    if(sym >= nNonTerminals)
    	printf("%s\n", grammarSymbols[sym]);
    else
    {
    	for(i = 0;i<nTerminals-1;i++)
    	{
    		if((*T)->array[sym][i] != -1)
    			printf("%s\n", terminals[i]);
    	}
    }
}

void printSpaces(int x, FILE* fp)
{
    int i = 0;
    for(i=0;i<x;i++)
        fprintf(fp," ");
}

void printNonTerminal(parseTree curNode, FILE *fp)
{
    if(curNode->parent == NULL)
    {
        fprintf(fp, "-----------------        ------        -----        -------------        ROOT                    no                <%s>\n",grammarSymbols[curNode->tk->sym]);
        return;
    }
    fprintf(fp, "-----------------        ------        -----        -------------        <%s>",grammarSymbols[curNode->parent->tk->sym]);
    printSpaces(22-strlen(grammarSymbols[curNode->parent->tk->sym]),fp);
    fprintf(fp,"no                ");
    fprintf(fp,"<%s>\n",grammarSymbols[curNode->tk->sym]);

}

void printNumber(parseTree curNode, FILE* fp)
{
    fprintf(fp, "-----------------        %d",curNode->tk->currentLine);
    printSpaces(14 - (curNode->tk->currentLine / 10 + 1),fp);
    fprintf(fp,"%s",grammarSymbols[curNode->tk->sym]);
    printSpaces(13 - strlen(grammarSymbols[curNode->tk->sym]),fp);
    fprintf(fp,"%s",curNode->tk->stringValue);
    printSpaces(21 - strlen(curNode->tk->stringValue),fp);
    fprintf(fp,"<%s>",grammarSymbols[curNode->parent->tk->sym]);
    printSpaces(22 - strlen(grammarSymbols[curNode->parent->tk->sym]),fp);
    fprintf(fp, "yes               ----------\n");
}

void printTerminal(parseTree curNode, FILE* fp)
{
    fprintf(fp,"%s",curNode->tk->stringValue);
    printSpaces(25-strlen(curNode->tk->stringValue),fp);
    fprintf(fp, "%d", curNode->tk->currentLine);
    printSpaces(14 - (curNode->tk->currentLine / 10 + 1),fp);
    fprintf(fp,"%s",grammarSymbols[curNode->tk->sym]);
    printSpaces(13 - strlen(grammarSymbols[curNode->tk->sym]),fp);
    fprintf(fp, "-------------        ");
    fprintf(fp,"<%s>",grammarSymbols[curNode->parent->tk->sym]);
    printSpaces(22 - strlen(grammarSymbols[curNode->parent->tk->sym]),fp);
    fprintf(fp, "yes               ----------\n");
}

void printGeneral(parseTree curNode, FILE* fp)
{
    if(curNode->tk->sym < nNonTerminals)
        printNonTerminal(curNode, fp);
    else if(curNode->tk->sym == NUM || curNode->tk->sym == RNUM )
        printNumber(curNode, fp);
    else
        printTerminal(curNode, fp);
}


void printRecursive(parseTree curNode, FILE* fp)
{
    printGeneral(curNode, fp);
    if(curNode->child == NULL)
    {
        return;
    }
    curNode = curNode->child;
    while(curNode->left != NULL)
        curNode = curNode->left;
    while(curNode != NULL)
    {
        printRecursive(curNode, fp);
        curNode = curNode->right;
    }
}


void printParseTree(parseTree PT, char *outfile)
{
    if(PT == NULL)
    {
    	printf("The source file contains errors and hence parse tree cannot be printed.\n");
    	return;
    }
	FILE *fp = fopen(outfile, "w");
    fprintf(fp,"lexemeCurrentNode        lineno        token        valueIfNumber        parentNodeSymbol        isLeafNode        NodeSymbol\n");
    printRecursive(PT, fp);
    /*parseTree curNode = PT;
    fprintf(fp, "-----------------        -         ----              -                  ROOT                       no            <%s>\n",grammarSymbols[curNode->tk->sym]);
    do
    {
        curNode = curNode->child;
        while(curNode->left != NULL)
            curNode = curNode->left;
        printGeneral(curNode, fp);
    }
    while(curNode->child != NULL);
    while(curNode->right != NULL)
    {
        curNode = curNode->right;

    }
    fclose(fp);
*/
}
