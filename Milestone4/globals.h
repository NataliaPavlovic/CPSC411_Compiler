// Natalia Pavlovic
// CPSC 411
// Milestone 3
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

extern FILE * source; //Input Source File
extern FILE * listing; //Output (stdout or file)
extern FILE * code;

extern int lineno; //Line counter
int HighScope;

//Types of Nodes
typedef enum {StmtK,ExpK,DecK,LabelK} NodeKind;
//Types of Statements
typedef enum {IfK,IfElseK,BreakK,WhileK,CallK,ReturnK,CompoundK,EmptyK,SemicolonK} StmtKind;
//Types of Expressions
typedef enum {OpK,ConstK,IdK,AssignK} ExpKind;
//Types of Declarations
typedef enum {VarK,FunK,ParameterK} DecKind;
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
  //Set if in compound statement
  int in_compound;   
  //Location in symbol table
  int loc;  
  int if_block_counter;
  int ifelse_block_counter;
  int loop_counter;
} TreeNode;

extern int EchoSource;
extern int TraceScan;
extern int TraceParse;
extern int TraceAnalyze;
extern int TraceCode;

//If TRUE, prevents further passes
extern int Error; 
#endif
