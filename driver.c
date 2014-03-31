/*

********
BATCH 62
********

************************
ANUJ PAHUJA 2011A7PS028P
SIDHARTH CHATURVEDI 2011A7PS126P
********************************

**********
driver.c
**********

*/

#include "lexer.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
  int i;
  tokenInfo t;
  FILE *fp;
  grammar G;
	table T;
	parseTree pt;

  printf("(a) FIRST and FOLLOW sets automated\n");
  printf("(c) Both lexical and syntax analysis modules implemented\n\n");

  printf("Enter your choice: \n");
  printf(" 1. Print the token list \n");
  printf(" 2. Parse the input source code \n");
  printf(" 3. Create parse tree and print it \n");

  scanf("%d", &i);

  switch(i)
  {
    case 1:
      fp = fopen(argv[1],"r");

      t = getNextToken(fp);

      while(t->sym != EPSILON)
      {
				if (t != NULL)
				{
					printf("%s\n",grammarSymbols[t->sym]);
					t = getNextToken(fp);
				}
				else
					t = getNextToken(fp);

      }

      fclose(fp);
      break;

		case 2:
			G = storeGrammar("grammar.txt");
			createParseTable(G, &T);
			pt = parseInputSourceCode(argv[1], &T, G);
      break;

		case 3:
			G = storeGrammar("grammar.txt");
			createParseTable(G, &T);
			pt = parseInputSourceCode(argv[1], &T, G);
			printParseTree(pt, argv[2]);
      break;

		default:
      printf("Wrong choice entered. \n");


  }

}
