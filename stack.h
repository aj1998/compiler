/*

********
BATCH 62
********

************************
ANUJ PAHUJA 2011A7PS028P
SIDHARTH CHATURVEDI 2011A7PS126P
********************************
*/

#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include "lexerDef.h"

typedef struct singleElement_t singleElement_t;
typedef singleElement_t* singleElement;
typedef struct stack_t stack_t;
typedef stack_t* stack;

typedef struct singleElement_t
{
    symbol_name sym;
    singleElement next;
}singleElement_t;

typedef struct stack_t
{
    int size;
    singleElement head;
}stack_t;

stack push(symbol_name sym, stack st);

symbol_name top(stack st);

stack pop(stack st);

#endif // STACK_H_INCLUDED
