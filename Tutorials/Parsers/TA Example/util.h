/****************************************************/
/* File: util.h                                     */
/* Utility functions for EX Compiler                */
/****************************************************/

#ifndef _UTIL_H_
#define _UTIL_H_
#include "globals.h"

//Prints Token Lexeme
void printToken( TokenType token, const char* tokenString);

//Creates new Statement Node for AST
TreeNode * newStmtNode(StmtKind);
//Creates new Expression Node for AST
TreeNode * newExpNode(ExpKind);
//Creates new Declaration Node for AST
TreeNode *newDecNode(DecKind);

//Makes copy of a string
char * copyString( char * );

//Prints AST
void printTree( TreeNode * );

#endif
