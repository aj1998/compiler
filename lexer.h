/*

********
BATCH 62
********

************************
ANUJ PAHUJA 2011A7PS028P
SIDHARTH CHATURVEDI 2011A7PS126P
********************************

**********
lexer.h
**********

*/

#ifndef LEXER_H_INCLUDED
#define LEXER_H_INCLUDED

#include <stdio.h>
#include "lexerDef.h"

FILE *getStream(FILE *fp, buffer B, buffersize k);
tokenInfo getNextToken(FILE *fp);
boolean checkKeyword(char* s);
int hashFunction(char* str);
void addSymbol(int hashValue, tokenInfo token);
void errorFunc(char c, char* str, boolean length, FILE *fp);

#endif
