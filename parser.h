/*

********
BATCH 62
********

************************
ANUJ PAHUJA 2011A7PS028P
SIDHARTH CHATURVEDI 2011A7PS126P
********************************
*/

#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include "parserDef.h"

grammar storeGrammar(char* fileName);
void createParseTable(grammar G, table T);
void calculateFirstSets(grammar G);
void calculateFollowSets(grammar G);
parseTree parseInputSourceCode(char *testcaseFile, table T, grammar G);
void parseError(tokenInfo tk, stack st, grammar G, table T);
void printParseTree(parseTree PT, char *outfile);

#endif // PARSER_H_INCLUDED
