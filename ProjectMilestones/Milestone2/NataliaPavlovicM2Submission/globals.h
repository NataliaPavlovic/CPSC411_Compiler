// Natalia Pavlovic
// CPSC 411
// Milestone 2
// March 2020
// Code modified from EX Compiler from tutorial

#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#ifndef YYPARSER
//Change name of following to your parser's
#include "parser.tab.h"
#define ENDFILE 0
#endif


/* MAXRESERVED = the number of reserved words */
#define MAXRESERVED 10

typedef int TokenType;

extern FILE* source; //Input Source File
extern FILE* output; //Output (stdout or file)

extern int lineno; //Line counter

//Types of Nodes
typedef enum {StmtK,ExpK,DecK,LabelK} NodeKind;
//Types of Statements
typedef enum {IfK,ElseK,BreakK,WhileK,CallK,ReturnK,CompoundK,EmptyK,SemicolonK} StmtKind;
//Types of Expressions
typedef enum {OpK,ConstK,IdK,AssignK} ExpKind;
//Types of Declarations
typedef enum {VarK,ArrayK,FunK,ParameterK} DecKind;
//Types of Labels that provide additional information
typedef enum {FctnParamsK,FctnArgsK,BlockK} LabelKind;
//Type Checking
typedef enum {Void,Integer,Boolean} ExpType;

#define MAXCHILDREN 3

//Struct for Tree Nodes
typedef struct treeNode {
  struct treeNode * child[MAXCHILDREN];
  struct treeNode * sibling;
  int lineno;
  NodeKind nodekind;
  union { StmtKind stmt; ExpKind exp; DecKind dec;} kind;
  struct { TokenType op;
          char * val;
          char * name; } attr;
  //Array Index
  int value;
  //If Object is Array  
  int isArray;       
  //If Object is a Parameter
  int isParameter;
  //If Object is a global variable
  int isGlobal;
  //Parameter Count
  int param_size;
  //Local variable count 
  int local_size;
  //Scope of node
  int scope;
  //Type Checking Expressions
  ExpType type;
     
} TreeNode;

extern int TraceScan;
extern int TraceParse;

//If TRUE, prevents further passes
extern int Error; 
#endif
