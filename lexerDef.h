/*

********
BATCH 62
********

************************
ANUJ PAHUJA 2011A7PS028P
SIDHARTH CHATURVEDI 2011A7PS126P
********************************

**********
lexerDef.h
**********

*/


#ifndef LEXERDEF_H_INCLUDED
#define LEXERDEF_H_INCLUDED


typedef char** buffer;
typedef int buffersize;

typedef enum { FALSE, TRUE } boolean;


typedef enum
{
  mainFunction, stmtsAndFunctionDefs, functionChoice, stmtOrFunctionDef, stmt, functionDef, declarationStmt, assignmentStmt_type1, assignmentStmt_type2, ifStmt, ioStmt, funCallStmt, parameter_list, type, remainingList, var_list, more_ids, leftHandSide_singleVar, rightHandSide_type1, leftHandSide_listVar, rightHandSide_type2, sizeExpression, elsePart, booleanExpression, otherStmts, inputParameterList, var, listVar, arithmeticExpression, precedenceChoice, arithmeticTerm, precedenceChoice2, operator_lowPrecedence, factor, operator_highPrecedence, logicalOp, constrainedVars, relationalOp, matrixElement, matrix, rows, row, extraRow, extraColumn,remainingColElements, MAIN, SQO, SQC, END, FUNCTION, ASSIGNOP, FUNID, SEMICOLON, ID, INT, REAL, STRING, MATRIX, COMMA, SIZE, IF, OP, CL, ELSE, ENDIF, READ, PRINT, PLUS, MINUS, MUL, DIV, NUM, RNUM, STR, AND, OR, NOT, LT, LE, EQ, GT, GE, NE, EPSILON, DOLLAR

} symbol_name;


extern buffer buffer1, buffer2;
extern char* forward;
extern char* backward;
symbol_name keyword;
extern int currentBuffer;
extern int lineNo;
extern int k;

typedef struct
{
  char stringValue[50];
  symbol_name sym;
  int currentLine;

} token_struct;

typedef token_struct* tokenInfo;
tokenInfo symbolTable[101];


#endif

