/*

********
BATCH 62
********

************************
ANUJ PAHUJA 2011A7PS028P
SIDHARTH CHATURVEDI 2011A7PS126P
********************************
*/

#include "stack.h"
#include <stdlib.h>

stack push(symbol_name sym, stack st)
{
    singleElement sin = (singleElement)calloc(1,sizeof(singleElement));
    sin->sym = sym;
    sin->next = st->head;
    st->head = sin;
    st->size++;
    return st;
}

symbol_name top(stack st)
{
    return st->head->sym;
}

stack pop(stack st)
{
    singleElement sin = st->head;
    st->head = st->head->next;
    st->size--;
    //free(sin);
    return st;
}
