// Natalia Pavlovic
// CPSC 411
// Milestone 2
// March 2020
// Code modified from EX Compiler from tutorial

#ifndef _UTIL_H_
#define _UTIL_H_
#include "globals.h"

//Prints Token Lexeme
void printToken( TokenType token, const char* tokenString);
void printOperators( TokenType token, const char* tokenString, TreeNode *tree );

//Creates new Statement Node for AST
TreeNode * newStmtNode(StmtKind);
//Creates new Expression Node for AST
TreeNode * newExpNode(ExpKind);
//Creates new Declaration Node for AST
TreeNode *newDecNode(DecKind);
//Creates new Label Node for AST
TreeNode *newLabelNode(LabelKind);

//Makes copy of a string
char * copyString( char * );

//Prints AST
void printTree( TreeNode * );

#endif
