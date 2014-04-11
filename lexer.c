/*

********
BATCH 62
********

************************
ANUJ PAHUJA 2011A7PS028P
SIDHARTH CHATURVEDI 2011A7PS126P
********************************

**********
lexer.c
**********

*/

#include "lexerDef.h"
//#include "lexer.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int lineNo = 1;
int currentBuffer = -1;
int k = 50;
buffer buffer1;
buffer buffer2;
char* backward = NULL;
char* forward = NULL;


// Function to fill and re-fill buffers 
FILE *getStream(FILE *fp, buffer B, buffersize k)
{
  size_t bytesRead;
  *B = (buffer)calloc(k+2,sizeof(char));

  if(*B == NULL)
    printf("error\n");

  bytesRead = fread(*B, sizeof(char), k, fp);
  if (bytesRead < k)
    (*B)[bytesRead] = '^';

  (*B)[k] = '~';
  //printf("%s\n",*B);
  return fp;
}


// Checks if a string is keyword or not
boolean checkKeyword(char* s)
{
  if (strcmp("end", s) == 0)
  {
    keyword = END;
    return TRUE;
  }

  else if (strcmp("int", s) == 0)
  {
    keyword = INT;
    return TRUE;
  }

  else if (strcmp("real", s) == 0)
  {
    keyword = REAL;
    return TRUE;
  }

  else if (strcmp("string", s) == 0)
  {
    keyword = STRING;
    return TRUE;
  }

  else if (strcmp("matrix", s) == 0)
  {
    keyword = MATRIX;
    return TRUE;
  }

  else if (strcmp("if", s) == 0)
  {
    keyword = IF;
    return TRUE;
  }

  else if (strcmp("else", s) == 0)
  {
    keyword = ELSE;
    return TRUE;
  }

  else if (strcmp("endif", s) == 0)
  {
    keyword = ENDIF;
    return TRUE;
  }

  else if (strcmp("read", s) == 0)
  {
    keyword = READ;
    return TRUE;
  }

  else if (strcmp("print", s) == 0)
  {
    keyword = PRINT;
    return TRUE;
  }

  else if (strcmp("function", s) == 0)
  {
      keyword = FUNCTION;
      return TRUE;
  }
  else
    return FALSE;

}


// A hashing function which generates a hash value for adding symbols in Symbol Table
int hashFunction(char* str)
{
  int hash = 0;
  int i = 0;
  while (str[i] != '\0')
  {
    hash = (hash*3 + str[i])%101;
    i++;
  }
  return hash;
}


// Function that adds a symbol to Symbol Table
void addSymbol(int hashValue, tokenInfo token)
{
  while (symbolTable[hashValue] != NULL)
    hashValue++;

  symbolTable[hashValue] = token;
}


// Error generating function which decides which type of error it is
void errorFunc(char c, char* str, boolean length, FILE *fp)
{
  if (length == TRUE)
    printf("ERROR_1: Identifier at line %d is longer than the prescribed length of 20 characters \n", lineNo);
  else
  {
    if (((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z')) || ((c >= '0') && (c <= '9')) || (c == '"') || (c == '#') || (c == '=') || (c == '_') || (c == '[') || (c == ']') || (c == '(') || (c == ')') || (c == '#') || (c == '+') || (c == '-') || (c == '*') || (c == '/') || (c == '@') || (c == '.') || (c == '<') || (c == '>'))
      printf("ERROR_3: Unknown pattern  %s \n", str);
    else
      printf("ERROR_2: Unknown Symbol %s at line %d \n", str, lineNo);

  }

  forward++;

  while (forward[0] != '\n')
  {
    forward++;
    c = forward[0];

    if (c == '~')
    {
      if (currentBuffer == 1)
	{
	  fp = getStream(fp, &buffer2, k);
	  forward = buffer2;
	  currentBuffer = 2;
	  //c = forward[0];
	}

      else if (currentBuffer == 2)
	{
	  fp = getStream(fp, &buffer1, k);
	  forward = buffer1;
	  currentBuffer = 1;
	  
	}

    }

  }

  lineNo++;

}

// Function to generate next token from file pointer fp
tokenInfo  getNextToken(FILE *fp)
{
  int state = 0;
  int i = 0;
  tokenInfo t = (tokenInfo)malloc(sizeof(token_struct));
  int z;
  for(z = 0;z<50;z++)
	  t->stringValue[z] = '\0';
  char c;
  char lexeme[100];
  for(z = 0;z<100;z++)
  	  lexeme[z] = '\0';
  int hVal;
  int lengthID = 0;
  
  if (currentBuffer == -1)				// Checks if no buffer is being used 
  {
    fp = getStream(fp, &buffer1, k);
    backward = buffer1;
    forward = buffer1;
    currentBuffer = 1;
  }

  while(1)
  {
      
    if (c == '~')					// Checks if a buffer has reached its end
    {
      if (currentBuffer == 1)
	{
	  fp = getStream(fp, &buffer2, k);
	  forward = buffer2;
	  currentBuffer = 2;
	  c = forward[0];
	}

      else if (currentBuffer == 2)
	{
	  fp = getStream(fp, &buffer1, k);
	  forward = buffer1;
	  currentBuffer = 1;
	  c = forward[0];
	}

    }

    switch(state)
    {
      case 0:						// Starting state
	c = forward[0];

	switch(c)
	{

	  case '^':					// Checks if it is the end of file
	    t->sym = EPSILON;
	    t->currentLine = lineNo;
	    return t;

	  case '~':
	    if (currentBuffer == 1)
	    {
	      fp = getStream(fp, &buffer2, k);
	      forward = buffer2;
	      currentBuffer = 2;
	      c = forward[0];
	    }

	    else if (currentBuffer == 2)
	    {
	      fp = getStream(fp, &buffer1, k);
	      forward = buffer1;
	      currentBuffer = 1;
	      c = forward[0];
	    }
	    state = 0;
	    break;

	  case ',':
	    lexeme[i++] = c;
	    state = 1;
	    break;

	  case ';':
	    lexeme[i++] = c;
	    state = 2;
	    break;

	  case '(':
	    lexeme[i++] = c;
	    state = 3;
	    break;


	  case ')':
	    lexeme[i++] = c;
	    state = 4;
	    break;

	  case '[':
	    lexeme[i++] = c;
	    state = 5;
	    break;

	  case ']':
	    lexeme[i++] = c;
	    state = 6;
	    break;

	  case '"':
	    lexeme[i++] = c;
	    state = 7;
	    forward++;
	    c = forward[0];
	    break;

	  case '+':
	    lexeme[i++] = c;
	    state = 8;
	    break;

	  case '-':
	    lexeme[i++] = c;
	    state = 9;
	    break;

	  case '*':
	    lexeme[i++] = c;
	    state = 10;
	    break;

	  case '/':
	    lexeme[i++] = c;
	    state = 11;
	    break;

	  case '<':
	    lexeme[i++] = c;
	    state = 12;
	    forward++;
	    c = forward[0];
	    break;

	  case '=':
	    lexeme[i++] = c;
	    state = 13;
	    forward++;
	    c = forward[0];
	    break;

	  case '>':
	    lexeme[i++] = c;
	    state = 14;
	    forward++;
	    c = forward[0];
	    break;

	  case '@':
	    lexeme[i++] = c;
	    state = 15;
	    break;

	  case '#':
	    forward++;
	    c = forward[0];
	    
	    while ((c != '\n') && (c != '\r'))
	    {
	      if (c == '~')
	      {
		
		if (currentBuffer == 1)
		{
		  fp = getStream(fp, &buffer2, k);
		  forward = buffer2;
		  currentBuffer = 2;
		  c = forward[0];
		}

		else if (currentBuffer == 2)
		{
		  fp = getStream(fp, &buffer1, k);
		  forward = buffer1;
		  currentBuffer = 1;
		  c = forward[0];
		}
	      }
    
         
	      else
	      {
		forward++;
		c = forward[0];
	      }

	    }

	    lineNo++;
	    forward++;
	    backward = forward;
	    state = 0;
	    break;

	  case '_':
	    lexeme[i++] = c;
	    state = 16;
	    forward++;
	    c = forward[0];
	    break;

	  case '.':
	    lexeme[i++] = c;
	    state = 17;
	    forward++;
	    c = forward[0];
	    break;


	  default:
	    if (((c >= 'a') && (c <= 'z'))||((c >= 'A') && (c <='Z')))
	    {
	      lexeme[i++] = c;
	      state = 18;
	      lengthID++;
	      forward++;
	      c = forward[0];
	    }

	    else if ((c >= '0') && (c <= '9'))
	    {
	      lexeme[i++] = c;
	      state = 19;
	      forward++;
	      c = forward[0];
	    }

	    else if ((c == ' ') || (c == '\n') || (c == '\t') || (c == '\v') || (c == '\f') || (c == '\r'))
	    {
	      state = 20;

	      if (c == '\n')
		lineNo++;

	      forward++;
	      c = forward[0];
	    }

	    else
	    {
	      errorFunc(c, lexeme, FALSE, fp);
	      return NULL;
	    }

	    break;

	}

	break;

	  case 1:
	    t->sym = COMMA;
	    t->currentLine = lineNo;
	    strcpy(t->stringValue, lexeme);
	    backward++;
	    forward++;
	    return t;

	  case 2:
	    t->sym = SEMICOLON;
	    t->currentLine = lineNo;
	    strcpy(t->stringValue, lexeme);
	    backward++;
	    forward++;
	    return t;

	  case 3:
	    t->sym = OP;
	    t->currentLine = lineNo;
	    strcpy(t->stringValue, lexeme);
	    backward++;
	    forward++;
	    return t;

	  case 4:
	    t->sym = CL;
	    t->currentLine = lineNo;
	    strcpy(t->stringValue, lexeme);
	    backward++;
	    forward++;
	    return t;

	  case 5:
	    t->sym = SQO;
	    t->currentLine = lineNo;
	    strcpy(t->stringValue, lexeme);
	    backward++;
	    forward++;
	    return t;

	  case 6:
	    t->sym = SQC;
	    t->currentLine = lineNo;
	    strcpy(t->stringValue, lexeme);
	    backward++;
	    forward++;
	    return t;

	  case 7:

	    if (((c >= 'a') && (c <= 'z')) || (c == ' '))
	    {
	      lexeme[i++] = c;
	      state = 21;
	      forward++;
	      c = forward[0];
	    }

	    else
	    {
	      errorFunc(c, lexeme, FALSE, fp);
	      return NULL;
	    }
	    break;

	  case 8:
	    t->sym = PLUS;
	    t->currentLine = lineNo;
	    strcpy(t->stringValue, lexeme);
	    backward++;
	    forward++;
	    return t;

	  case 9:
	    t->sym = MINUS;
	    t->currentLine = lineNo;
	    strcpy(t->stringValue, lexeme);
	    backward++;
	    forward++;
	    return t;

	  case 10:
	    t->sym = MUL;
	    t->currentLine = lineNo;
	    strcpy(t->stringValue, lexeme);
	    backward++;
	    forward++;
	    return t;

	  case 11:
	    t->sym = DIV;
	    t->currentLine = lineNo;
	    strcpy(t->stringValue, lexeme);
	    backward++;
	    forward++;
	    return t;

	  case 12:

	    if (c == '=')
	    {
	      lexeme[i++] = c;
	      state = 22;
	      forward++;
	      c = forward[0];
	    }

	    else
	    {
	      t->sym = LT;
	      t->currentLine = lineNo;
	      strcpy(t->stringValue, lexeme);
	      backward = forward;
	      return t;
	    }
	    break;

	  case 13:

	    if (c == '=')
	    {
	      lexeme[i++] = c;
	      state = 23;
	      forward++;
	      c = forward[0];
	    }

	    else if (c == '/')
	    {
	      lexeme[i++] = c;
	      state = 24;
	      forward++;
	      c = forward[0];
	    }

	    else
	    {
	      t->sym = ASSIGNOP;
	      t->currentLine = lineNo;
	      strcpy(t->stringValue, lexeme);
	      backward = forward;
	      return t;
	    }

	    break;

	  case 14:

	    if (c == '=')
	    {
	      lexeme[i++] = c;
	      state = 25;
	      forward++;
	      c = forward[0];
	    }

	    else
	    {
	      t->sym = GT;
	      t->currentLine = lineNo;
	      strcpy(t->stringValue, lexeme);
	      backward = forward;
	      return t;
	    }
	    break;

	  case 15:
	    t->sym = SIZE;
	    t->currentLine = lineNo;
	    strcpy(t->stringValue, lexeme);
	    backward++;
	    forward++;
	    return t;

	  case 16:

	    if (((c >= 'a') && (c <= 'z') && (c != 'm'))||((c >= 'A') && (c <= 'Z')))
	    {
	      lexeme[i++] = c;
	      state = 26;
	      forward++;
	      c = forward[0];
	    }

	    else if (c == 'm')
	    {
	      lexeme[i++] = c;
	      state = 27;
	      forward++;
	      c = forward[0];
	    }

	    else
	    {
	      errorFunc(c, lexeme, FALSE, fp);
	      return NULL;
	    }
	    break;

	  case 17:
	    if (c == 'a')
	    {
	      lexeme[i++] = c;
	      state = 28;
	      forward++;
	      c = forward[0];
	    }

	    else if (c == 'n')
	    {
	      lexeme[i++] = c;
	      state = 29;
	      forward++;
	      c = forward[0];
	    }

	    else if (c == 'o')
	    {
	      lexeme[i++] = c;
	      state = 30;
	      forward++;
	      c = forward[0];
	    }

	    else
	    {
	      errorFunc(c, lexeme, FALSE, fp);
	      return NULL;
	    }
	    break;

	  case 18:
	    if (((c >= 'a') && (c <= 'z'))||((c >= 'A') && (c <='Z')))
	    {
	      lengthID++;
	      lexeme[i++] = c;
	      state = 18;
	      forward++;
	      c = forward[0];
	    }

	    else if ((c >= '0') && (c <= '9'))
	    {
	      lengthID++;
	      lexeme[i++] = c;
	      state = 31;
	      forward++;
	      c = forward[0];
	    }

	    else
	    {
	      lexeme[i] = '\0';
	      if (checkKeyword(lexeme) == TRUE)
		t->sym = keyword;
	      else
	      {
		if (lengthID > 20)
		{
		  errorFunc(c, lexeme, TRUE, fp);
		  return NULL;
		}
		else
		  t->sym = ID;
	      }

	      //lexeme[i] = '\0';
	      strcpy(t->stringValue, lexeme);
	      t->currentLine = lineNo;
	      backward = forward;
	      hVal = hashFunction(lexeme);
	      addSymbol(hVal, t);
	      return t;
	    }
	    break;

	  case 19:
	    if ((c >= '0') && (c <= '9'))
	    {
	      lexeme[i++] = c;
	      state = 19;
	      forward++;
	      c = forward[0];
	    }

	    else if (c == '.')
	    {
	      lexeme[i++] = c;
	      state = 32;
	      forward++;
	      c = forward[0];
	    }

	    else
	    {
	      t->sym = NUM;
	      lexeme[i] = '\0';
	      strcpy(t->stringValue, lexeme);
	      t->currentLine = lineNo;
	      backward = forward;
	      hVal = hashFunction(lexeme);
	      addSymbol(hVal, t);
	      return t;
	    }
	    break;

	  case 20:

	    if (c == '\n')
	    {
	      lineNo++;
	      state = 20;
	      forward++;
	      c = forward[0];
	    }

	    else if ((c == ' ') || (c == '\t') || (c == '\v') || (c == '\f') || (c == '\r'))
	    {
	      state = 20;
	      forward++;
	      c = forward[0];
	    }

	    else
	    {
	      backward = forward;
	      state = 0;
	      //forward++;

	    }
	    break;

	  case 21:

	    if (((c >= 'a') && (c <= 'z')) || (c == ' '))
	    {
	      lexeme[i++] = c;
	      state = 21;
	      forward++;
	      c = forward[0];
	    }

	    else if (c == '"')
	    {
	      lexeme[i++] = c;
	      state = 33;
	      forward++;
	      c = forward[0];
	    }

	    else
	    {
	      errorFunc(c, lexeme, FALSE, fp);
	      return NULL;
	    }
	    break;

	  case 22:
	    t->sym = LE;
	    t->currentLine = lineNo;
	    strcpy(t->stringValue, lexeme);
	    forward++;
	    backward = forward;
	    return t;

	  case 23:
	    t->sym = EQ;
	    t->currentLine = lineNo;
	    strcpy(t->stringValue, lexeme);
	    forward++;
	    backward = forward;
	    return t;

	  case 24:
	    if (c == '=')
	    {
	      lexeme[i++] = c;
	      state = 34;
	      forward++;
	      c = forward[0];
	    }

	    else
	    {
	      errorFunc(c, lexeme, FALSE, fp);
	      return NULL;
	    }
	    break;

	  case 25:
	    t->sym = GE;
	    t->currentLine = lineNo;
	    strcpy(t->stringValue, lexeme);
	    forward++;
	    backward = forward;
	    return t;

	  case 26:

	    if (((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z')) || ((c >= '0') && (c <= '9')))
	    {
	      lexeme[i++] = c;
	      state = 26;
	      forward++;
	      c = forward[0];
	    }

	    else
	    {
	      t->sym = FUNID;
	      lexeme[i] = '\0';
	      strcpy(t->stringValue, lexeme);
	      t->currentLine = lineNo;
	      backward = forward;
	      hVal = hashFunction(lexeme);
	      addSymbol(hVal, t);
	      return t;
	    }
	    break;

	  case 27:

	    if (c == 'a')
	    {
	      lexeme[i++] = c;
	      state = 35;
	      forward++;
	      c = forward[0];
	    }

	    else if (((c > 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z')) || ((c >= '0') && (c <= '9')))
	    {
	      lexeme[i++] = c;
	      state = 26;
	      forward++;
	      c = forward[0];
	    }

	    else
	    {
	      t->sym = FUNID;
	      lexeme[i] = '\0';
	      strcpy(t->stringValue, lexeme);
	      t->currentLine = lineNo;
	      backward = forward;
	      hVal = hashFunction(lexeme);
	      addSymbol(hVal, t);
	      return t;
	    }
	    break;

	  case 28:

	    if (c == 'n')
	    {
	      lexeme[i++] = c;
	      state = 36;
	      forward++;
	      c = forward[0];
	    }

	    else
	    {
	      errorFunc(c, lexeme, FALSE, fp);
	      return NULL;
	    }
	    break;

	  case 29:

	    if (c == 'o')
	    {
	      lexeme[i++] = c;
	      state = 37;
	      forward++;
	      c = forward[0];
	    }

	    else
	    {
	      errorFunc(c, lexeme, FALSE, fp);
	      return NULL;
	    }
	    break;

	  case 30:

	    if (c == 'r')
	    {
	      lexeme[i++] = c;
	      state = 38;
	      forward++;
	      c = forward[0];
	    }

	    else
	    {
	      errorFunc(c, lexeme, FALSE, fp);
	      return NULL;
	    }
	    break;

	  case 31:
	    if (lengthID > 20)
		{
		  errorFunc(c, lexeme, TRUE, fp);
		  return NULL;
		}

	    if (((c >= 'a') && (c <= 'z')) || ((c >='A') && (c <= 'Z')) || ((c >= '0') && (c <= '9')))
	    {
	      lexeme[i++] = c;
	      lexeme[i] = '\0';
	      errorFunc(c, lexeme, FALSE, fp);
	      return NULL;

	    }

	    if (checkKeyword(lexeme) == TRUE)
		t->sym = keyword;
	    else
		t->sym = ID;

	    lexeme[i] = '\0';
	    strcpy(t->stringValue, lexeme);
	    t->currentLine = lineNo;
	    //forward++;
	    backward = forward;
	    hVal = hashFunction(lexeme);
	    addSymbol(hVal, t);
	    return t;

	  case 32:

	    if ((c >= '0') && (c <= '9'))
	    {
	      lexeme[i++] = c;
	      state = 39;
	      forward++;
	      c = forward[0];
	    }

	    else
	    {
	      errorFunc(c, lexeme, FALSE, fp);
	      return NULL;
	    }
	    break;

	  case 33:
	    t->sym = STR;
	    lexeme[i] = '\0';
	    strcpy(t->stringValue, lexeme);
	    t->currentLine = lineNo;
	    //forward++;
	    backward = forward;
	    hVal = hashFunction(lexeme);
	    addSymbol(hVal, t);
	    return t;

	  case 34:
	    t->sym = NE;
	    t->currentLine = lineNo;
	    strcpy(t->stringValue, lexeme);
	    forward++;
	    backward = forward;
	    return t;

	  case 35:

	    if (c == 'i')
	    {
	      lexeme[i++] = c;
	      state = 40;
	      forward++;
	      c = forward[0];
	    }

	    else if (((c >= 'a') && (c <= 'z') && (c != 'i')) || ((c >= 'A') && (c <= 'Z')) || ((c >= '0') && (c <= '9')))
	    {
	      lexeme[i++] = c;
	      state = 26;
	      forward++;
	      c = forward[0];
	    }

	    else
	    {
	      t->sym = FUNID;
	      lexeme[i] = '\0';
	      strcpy(t->stringValue, lexeme);
	      t->currentLine = lineNo;
	      backward = forward;
	      hVal = hashFunction(lexeme);
	      addSymbol(hVal, t);
	      return t;
	    }
	    break;

	  case 36:

	    if (c == 'd')
	    {
	      lexeme[i++] = c;
	      state = 41;
	      forward++;
	      c = forward[0];
	    }

	    else
	    {
	      errorFunc(c, lexeme, FALSE, fp);
	      return NULL;
	    }
	    break;

	  case 37:

	    if (c == 't')
	    {
	      lexeme[i++] = c;
	      state = 42;
	      forward++;
	      c = forward[0];
	    }

	    else
	    {
	      errorFunc(c, lexeme, FALSE, fp);
	      return NULL;
	    }
	    break;

	  case 38:

	    if (c == '.')
	    {
	      lexeme[i++] = c;
	      state = 43;
	      forward++;
	      c = forward[0];
	    }

	    else
	    {
	      errorFunc(c, lexeme, FALSE, fp);
	      return NULL;
	    }
	    break;

	  case 39:

	    if ((c >= '0') && (c <= '9'))
	    {
	      lexeme[i++] = c;
	      state = 44;
	      forward++;
	      c = forward[0];
	    }

	    else
	    {
	      errorFunc(c, lexeme, FALSE, fp);
	      return NULL;
	    }
	    break;

	  case 40:

	    if (c == 'n')
	    {
	      lexeme[i++] = c;
	      state = 45;
	      forward++;
	      c = forward[0];
	    }

	    else if (((c >= 'a') && (c <= 'z') && (c != 'n')) || ((c >= 'A') && (c <= 'Z')) || ((c >= '0') && (c <= '9')))
	    {
	      lexeme[i++] = c;
	      state = 26;
	      forward++;
	      c = forward[0];
	    }

	    else
	    {
	      t->sym = FUNID;
	      lexeme[i] = '\0';
	      strcpy(t->stringValue, lexeme);
	      t->currentLine = lineNo;
	      backward = forward;
	      hVal = hashFunction(lexeme);
	      addSymbol(hVal, t);
	      return t;
	    }
	    break;

	  case 41:

	    if (c == '.')
	    {
	      lexeme[i++] = c;
	      state = 46;
	      forward++;
	      c = forward[0];
	    }

	    else
	    {
	      errorFunc(c, lexeme, FALSE, fp);
	      return NULL;
	    }
	    break;

	  case 42:

	    if (c == '.')
	    {
	      lexeme[i++] = c;
	      state = 47;
	      forward++;
	      c = forward[0];
	    }

	    else
	    {
	      errorFunc(c, lexeme, FALSE, fp);
	    }
	    break;

	  case 43:
	    t->sym = OR;
	    strcpy(t->stringValue, lexeme);
	    t->currentLine = lineNo;
	    forward++;
	    backward = forward;
	    return t;

	  case 44:
	    t->sym = RNUM;
	    lexeme[i] = '\0';
	    strcpy(t->stringValue, lexeme);
	    t->currentLine = lineNo;
	    backward = forward;
	    hVal = hashFunction(lexeme);
	    addSymbol(hVal, t);
	    return t;

	  case 45:

	    if (((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z')) || ((c >= '0') && (c <= '9')))
	    {
	      lexeme[i++] = c;
	      state = 26;
	      forward++;
	      c = forward[0];
	    }

	    else
	    {
	      t->sym = MAIN;
	      lexeme[i] = '\0';
	      strcpy(t->stringValue, lexeme);
	      t->currentLine = lineNo;
	      backward = forward;
	      return t;
	    }
	    break;

	  case 46:
	    t->sym = AND;
	    t->currentLine = lineNo;
	    strcpy(t->stringValue, lexeme);
	    forward++;
	    backward = forward;
	    return t;

	  case 47:
	    t->sym = NOT;
	    t->currentLine = lineNo;
	    strcpy(t->stringValue, lexeme);
	    forward++;
	    backward = forward;
	    return t;

	}
  }

}

/*int main()
{
  printf("%d", 1234);
  return 0;
}*/


