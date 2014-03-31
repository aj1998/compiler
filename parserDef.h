/*

********
BATCH 62
********

************************
ANUJ PAHUJA 2011A7PS028P
SIDHARTH CHATURVEDI 2011A7PS126P
********************************
*/

#ifndef PARSERDEF_H_INCLUDED
#define PARSERDEF_H_INCLUDED

#include "lexerDef.h"
#include "stack.h"

#define nRules 88
#define nNonTerminals 45
#define nTerminals 39

extern char* grammarSymbols[];
extern char* nonTerminals[];
extern char* terminals[];

typedef struct node_t node;
typedef node* nodeptr;
typedef struct rule_t rule;
typedef rule* ruleptr;
typedef struct node2_t node2;
typedef node2* node2ptr;
typedef struct node3_t node3;
typedef node3* node3ptr;
typedef struct grammar_struc grammar_t;
typedef grammar_t* grammar;
typedef struct table_t table_t;
typedef table_t** table;
typedef struct parseTree_t parseTree_t;
typedef parseTree_t* parseTree;

int visitedNonTerminal[nNonTerminals];
int visitedNonTerminal2[nNonTerminals];

typedef struct node_t
{
    symbol_name sym;
    nodeptr next;
    nodeptr prev;
}node;

typedef struct rule_t
{
    symbol_name lhs;
    nodeptr rhs;
}rule;

typedef struct node2_t
{
    int rule_num;
    node2ptr next;
}node2;

typedef struct node3_t
{
    int ruleNum;
    nodeptr pt;
    node3ptr next;
}node3;

typedef struct
{
    int first[nTerminals];
    int first_rule[nTerminals];
    int follow[nTerminals];
}ff;

typedef struct grammar_struc
{
    ruleptr rules[nRules];
    node2ptr nonTerminalLHS[nNonTerminals];
    node3ptr nonTerminalOccurence[nNonTerminals];
    ff ffSets[nNonTerminals];
    int epsilon_array[nNonTerminals];
}grammar_t;

typedef struct table_t
{
    int array[nNonTerminals][nTerminals];
}table_t;

typedef struct parseTree_t
{
    tokenInfo tk;
    parseTree parent;
    parseTree child;
    parseTree left;
    parseTree right;
}parseTree_t;



#endif // PARSERDEF_H_INCLUDED
