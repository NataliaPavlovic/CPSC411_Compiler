// Natalia Pavlovic
// CPSC 411
// Milestone 3
// March 2020
// Code modified from EX Compiler from tutorial

// Semantic analyzer interface for EX compiler

#ifndef _ANALYZE_H_
#define _ANALYZE_H_

/* Function buildSymtab constructs the symbol 
 * table by preorder traversal of the syntax tree
 */
void buildSymtab(TreeNode *);

/* Procedure typeCheck performs type checking 
 * by a postorder syntax tree traversal
 */
void typeCheck(TreeNode *);

// Struct to contain information about function declarations
struct Funk_decls
{
  char function_name[20];
  int return_type;
  int param_size;
  int arg_list[20];
} ;

// Array of all function declarations
struct Funk_decls functionDeclarations [100];

// Total number of functions in array
extern int totalFuncs;

#endif
