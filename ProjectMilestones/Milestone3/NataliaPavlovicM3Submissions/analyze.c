// Natalia Pavlovic
// CPSC 411
// Milestone 3
// March 2020
// Code modified from EX Compiler from tutorial

// Semantic analyzer for EX Compiler

#include "globals.h"
#include "symtab.h"
#include "analyze.h"
#include "util.h"

#include <stdlib.h>
#include <string.h>

static int scope_a = 0;

/* counter for variable memory locations */
static int location[MAX_SCOPE] = {0,0,0};

static int No_change = 0; 

// Counter for number oof current nested while loops
static int count_while = 0;

// Counter for number of main function declarations
static int count_main = 0;

// Return type of function declaration
static int return_type = -1;

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
int totalFuncs = 0;

// print an error message and a line number
static void printError(TreeNode * t, char * message)
{ fprintf(listing,"Error: %s at line %d\n",message, t->lineno);
  Error = TRUE;
}

// Print an error if there is no main declaration
static void printNoMainError(TreeNode * t, char * message)
{ fprintf(listing,"Error: %s\n",message);
  Error = TRUE;
}

/* Procedure traverse is a generic recursive 
 * syntax tree traversal routine:
 * it applies preProc in preorder and postProc 
 * in postorder to tree pointed to by t
 */
static void traverse( TreeNode * t,
               void (* preProc) (TreeNode *),
               void (* postProc) (TreeNode *) )
{ if (t != NULL)
  { preProc(t);
    int i;
    for (i=0; i < MAXCHILDREN; i++)
        traverse(t->child[i],preProc,postProc);

    postProc(t);
    traverse(t->sibling,preProc,postProc);
  }
}

/* nullProc is a do-nothing procedure to 
 * generate preorder-only or postorder-only
 * traversals from traverse
 */
static void nullProc(TreeNode * t)
{ if (t==NULL) return;
  else return;
}

/* Procedure insertNode inserts 
 * identifiers stored in t into 
 * the symbol table 
 */
static void insertNode( TreeNode * t)
{ 
  switch (t->nodekind)
    {case StmtK:
      switch (t->kind.stmt)
      { 
        case CallK:
          // Check if main function was called
          if(!strcmp(t->attr.name, "main"))
          {
            printError(t, "main function cannot be called");
          }
          if (st_lookup(t->attr.name, scope_a) == -1)
            st_insert(t->attr.name, t->lineno, -1, scope_a, FALSE, -1);
          else
            st_insert(t->attr.name, t->lineno, 0, scope_a, FALSE, -1);

          t->loc = -1;
          t->scope = scope_a;

          // Set scope of function call parameters
          if (t->child[0] != NULL && t->child[0]->child[0] != NULL) {
            t = t->child[0];
              if (st_lookup(t->child[0]->attr.name, scope_a) == -1) {
                t->child[0]->scope = No_change;
                t = t->child[0];
                while (t->sibling != NULL) {
                  t = t->sibling;
                  t->scope = No_change;
                }
              } 
        }
        break; 
        case ReturnK:
          // Set type of return to return type of function declaration
          t->type = return_type;
          // Set scope of child
          if (t->child[0] != NULL) {
            t->child[0]->scope = t->scope;
          }
          else if(return_type != Void)
          {
            printError(t, "No value returned from non-void function");
          }
          return_type = -1;
          break;
        case WhileK:
          count_while++;
          break;
        case BreakK:
          if(count_while == 0)
          {
            printError(t,"break must be inside while loop");
          }
          else
          {
            count_while--;
          }
          break;
        case CompoundK:
          // Set scope for all children and set in_compound to 1 for all children
          if (t->child[0] != NULL) {
            t->child[0]->scope = No_change;
            t->child[0]->in_compound = 1;
            t = t->child[0];
            while (t->sibling != NULL) {
              t = t->sibling;
              t->scope = No_change;
              t->in_compound = 1;
            }
          }
          break;
        default:
          break;
      }
      break;
    case ExpK:
      switch (t->kind.exp)
      { case OpK:
          // Set scope for all children
          if (t->child[0] != NULL) {
            t->child[0]->scope = t->scope;
            if(t->child[1] != NULL)
            {
              t->child[1]->scope = t->scope;
            }
          }
          break;
        case IdK:
            if(t->attr.name != NULL)
            {
              BucketList lookup_inner = var_lookup(t->attr.name, t->scope);
              BucketList lookup_outer = var_lookup(t->attr.name, scope_a);

              // Get type and location information saved in symbol table
              if (lookup_inner!=NULL)
              {
                t->type = lookup_inner->type;
                t->loc = lookup_inner->memloc;
              }
              else if (lookup_outer!=NULL)
              {
                t->type = lookup_outer->type;
                t->loc = lookup_outer->memloc;
              }

              if (t->scope > scope_a) {
                if(lookup_inner == NULL && lookup_outer == NULL) 
                {
                  // ID cannot be found in either current scope or global scope
                  printError(t, strcat(t->attr.name, " variable used without being declared"));
                }
                else if (lookup_inner == NULL)
                {
                  // ID can be found in global scope
                  st_insert(t->attr.name, t->lineno, 0, scope_a, FALSE, t->type);
                  t->scope = scope_a;
                }
                else
                {
                  // ID can be found in current scope
                  st_insert(t->attr.name, t->lineno, 0, t->scope, FALSE, t->type);
                }
              }
              else {
                st_insert(t->attr.name, t->lineno, 0, scope_a, FALSE, t->type);
                t->scope = scope_a;
              }
            }
          break;
        case AssignK:
          if (t->child[0] != NULL) {
            t->child[0]->scope = t->scope;
          }
          BucketList lookup_inner = var_lookup(t->attr.name, t->scope);
          BucketList lookup_outer = var_lookup(t->attr.name, scope_a);

          // Get type information and location saved in symbol table
          if (lookup_inner!=NULL)
          {
            t->type = lookup_inner->type;
            t->loc = lookup_inner->memloc;
          }
          else if (lookup_outer!=NULL)
          {
            t->type = lookup_outer->type;
            t->loc = lookup_outer->memloc;
          }

          if (t->scope > scope_a) {
            if(lookup_inner == NULL && lookup_outer== NULL)
            {
              // ID cannot be found in either current scope or global scope
              printError(t, strcat(t->attr.name, " variable used without being declared"));
            }
            else if (lookup_inner == NULL)
            {
              // ID can be found in global scope
              st_insert(t->attr.name, t->lineno, 0, scope_a, FALSE, t->type);
              t->scope = scope_a;
            }
            else
            {
              // ID can be found in current scope
              st_insert(t->attr.name, t->lineno, 0, t->scope, FALSE, t->type);
            }
          }
          else {
            st_insert(t->attr.name, t->lineno, 0, scope_a, FALSE, t->type);
            t->scope = scope_a;
          }
          break;
        default:
          break;
      }
      break;
    case DecK:
      switch (t->kind.dec)
      { 
        case VarK:
          // check if variable declared in compound statement
          if(t->in_compound == 1)
          {
            printError(t, "Local declaration not in outermost block");
          }
          else
          {
            if (t->scope > scope_a) {
              if (var_lookup(t->attr.name, t->scope) == NULL) {
                // If variable is not declared yet, add to symbol table
                t->loc = location[t->scope];
                st_insert(t->attr.name, t->lineno, location[t->scope]++, t->scope, FALSE, t->type);
              }
              else
              {
                // Variable is already declared in scope
                printError(t, "Variable redeclared in same scope");
              }
            }
            else {
              // Declare variable in global scope
              if (var_lookup(t->attr.name, scope_a) == NULL)
              {
                t->loc = location[scope_a];
                st_insert(t->attr.name, t->lineno, location[scope_a]++, scope_a, FALSE, t->type);
                t->scope = scope_a;
              }
              else
              {
                printError(t, "Variable redeclared in global scope");
              }
            }
          }
          break;
        case ParameterK:
            // Add parameters to symbol table
            if (var_lookup(t->attr.name, t->scope) == NULL) {
              t->loc = location[t->scope];
              st_insert(t->attr.name, t->lineno, location[t->scope]++, t->scope, FALSE, t->type);
            }
            else
              st_insert(t->attr.name, t->lineno, 0, t->scope, FALSE, t->type);
            break;
        case FunK:
          if(!strcmp(t->attr.name, "main"))
          {
            count_main++;
          }

          return_type = t->type;

          st_insert(t->attr.name, t->lineno, -1, scope_a, FALSE, -1);
          t->loc = -1;
          t->scope = scope_a;

          int i;
          for(i = 0; i < totalFuncs; i++)
          {
            if(!strcmp(t->attr.name, functionDeclarations[i].function_name))
            {

              printError(t, strcat(t->attr.name," function redefined"));
              break;
            }
          }

          // Populate array entry in functionDeclarations array
          if (i == totalFuncs)
          {
            strcpy(functionDeclarations[i].function_name, t->attr.name);
            functionDeclarations[i].param_size = t->param_size;
            functionDeclarations[i].return_type = return_type;
          }
          totalFuncs++;

          // Check if main function has parameters
          if(!strcmp(t->attr.name, "main") && t->param_size != 0)
          {
            printError(t, "main declaration can't have parameters");
          }

          No_change++;

          TreeNode * temp = t;

          int j = 0;
          // Function arguments
          if (t->child[0] != NULL && t->child[0]->child[0] != NULL) {
            t = t->child[0];
            t->child[0]->scope = No_change;
            t = t->child[0];
            functionDeclarations[i].arg_list[j] = t->type; // Set function declaration parameter types
            while (t->sibling != NULL) {
              t = t->sibling;
              t->scope = No_change;
              j++;
              functionDeclarations[i].arg_list[j] = t->type; // Set function declaration parameter types
            }
          }

          t = temp;
          // Block
          if (t->child[1] != NULL && t->child[1]->child[0] != NULL) {
            t = t->child[1];

            if(return_type != Void)
            {
              int count_return = 0;

              t->child[0]->scope = No_change;
              t = t->child[0];
              t->scope = No_change;
              if(t->nodekind == StmtK && t->kind.stmt == ReturnK)
              {
                count_return++;
              }
              while (t->sibling != NULL) {
                t = t->sibling;
                t->scope = No_change;
                if(t->nodekind == StmtK && t->kind.stmt == ReturnK)
                {
                  count_return++;
                }
              }

              // No return statements in function declaration
              if (count_return == 0)
              {
                char * str = (char *)malloc(42+1);
                strcpy(str, "No return statement for non-void function ");
                printError(t, strcat(str, temp->attr.name));
              }
            }
            else{
              t->child[0]->scope = No_change;
              t = t->child[0];
              t->scope = No_change;
              while (t->sibling != NULL) {
                t = t->sibling;
                t->scope = No_change;
              }
            }
          }
          else if (return_type != Void) // Empty statement
          {
            char * str = (char *)malloc(42+1);
            strcpy(str, "No return statement for non-void function ");
            printError(t, strcat(str, temp->attr.name));
          }

          HighScope++;
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }


}

/* Function buildSymtab constructs the symbol 
 * table by preorder traversal of the syntax tree
 */
void buildSymtab(TreeNode * syntaxTree)
{ traverse(syntaxTree,insertNode,nullProc);
  if (count_main == 0)
  {
    printNoMainError(syntaxTree, "No main declaration found");
  }
  if (TraceAnalyze)
  { fprintf(listing,"\nSymbol table:\n\n");
    printSymTab(listing);
  }
}

static void typeError(TreeNode * t, char * message)
{ fprintf(listing,"Type error at line %d: %s\n",t->lineno,message);
  Error = TRUE;
}

/* Procedure checkNode performs
 * type checking at a single tree node
 */
static void checkNode(TreeNode * t)
{ switch (t->nodekind)
  { case ExpK:
      switch (t->kind.exp)
      { case OpK:
          // Check if children of op are not Integers
          if (t->child[1] != NULL)
          {
            if ((t->child[0]->type != Integer) || (t->child[1]->type != Integer))
              typeError(t,"Op applied to non-integer");
          }
          else
          {
            if (t->child[0]->type != Integer)
              typeError(t,"Op applied to non-integer");
          }

          // Check if op will lead to a boolean expression
          if ((t->attr.op == LE) || (t->attr.op == '<') || (t->attr.op == '>') || (t->attr.op == GE) || (t->attr.op == EQ) || (t->attr.op == NQ) || (t->attr.op == AND) || (t->attr.op == OR))
            {
              t->type = Boolean;
            }
          else
            t->type = Integer;
          break;
        case AssignK:
          if(t->child[0] != NULL && t->child[0]->attr.name == NULL)
          {
            if(t->child[0]->child[0] == NULL)
            {
              // Check if op will lead to a boolean expression
              if ((t->child[0]->attr.op == LE) || (t->child[0]->attr.op == '<') || (t->child[0]->attr.op == '>') || (t->child[0]->attr.op == GE) || (t->child[0]->attr.op == AND) || (t->child[0]->attr.op == OR) || (t->child[0]->attr.op == '!'))
                typeError(t->child[0], "Cannot assign boolean to int variable");
              // Check if type of children matches types of assign
              else if (t->child[0]->type != t->type)
              {
                if(t->type == Boolean)
                {
                  typeError(t->child[0], "cannot assign to boolean variable");
                }
                else if(t->type == Integer)
                {
                  typeError(t->child[0], "cannot assign to integer variable");
                }
              }
            }
            else
            {
              t = t->child[0];
              // Check if op will lead to a boolean expression
              if ((t->child[0]->attr.op == LE) || (t->child[0]->attr.op == '<') || (t->child[0]->attr.op == '>') || (t->child[0]->attr.op == GE) || (t->child[0]->attr.op == AND) || (t->child[0]->attr.op == OR) || (t->child[0]->attr.op == '!'))
                typeError(t->child[0], "Cannot assign boolean to int variable");
              // Check if type of children matches types of assign
              else if (t->child[0]->type != t->type)
              {
                if(t->type == Boolean)
                {
                  typeError(t->child[0], "cannot assign to boolean variable");
                }
                else if(t->type == Integer)
                {
                  typeError(t->child[0], "cannot assign to integer variable");
                }
              }
            }
          }
          break;
        default:
          break;
      }
      break;
    case StmtK:
      switch (t->kind.stmt)
      { 
        case IfK:
          if(t->child[0]->child[0] == NULL)
          {
            if (t->child[0]->type == Integer)
              typeError(t->child[0],"need a boolean expression for if condition");
          }
          else
          {
            if (t->child[0]->child[0]->type == Integer)
              typeError(t->child[0]->child[0],"need a boolean expression for if condition");
          }
          break;
        case IfElseK:
          if(t->child[0]->child[0] == NULL)
          {
            if (t->child[0]->type == Integer)
              typeError(t->child[0],"need a boolean expression for ifelse condition");
          }
          else
          {
            if (t->child[0]->child[0]->type == Integer)
              typeError(t->child[0]->child[0],"need a boolean expression for ifelse condition");
          }
          break;
        case WhileK:
          if(t->child[0]->child[0] == NULL)
          {
            if (t->child[0]->type == Integer)
              typeError(t->child[0],"need a boolean expression for while condition");
          }
          else
          {
            if (t->child[0]->child[0]->type == Integer)
              typeError(t->child[0]->child[0],"need a boolean expression for while condition");
          }

          break;
        case CallK:
        {
          // Find fundtionDeclaration entry for the current function call
          int i;
          for(i = 0; i < totalFuncs; i++)
          {
            if(!strcmp(functionDeclarations[i].function_name, t->attr.name))
            {
              break;
            }
          }

          if (i== totalFuncs)
          {
            printError(t, "function was used but never declared");
          }

          // Check the types of arguments passed into the function call
          if (t->child[0] != NULL) {
            if(t->child[0]->param_size != functionDeclarations[i].param_size)
            {
              printError(t, "number of arguments doesn't match function declaration");
            }
            t = t->child[0];
            int j = 0;
            if (t->child[0]->type != functionDeclarations[i].arg_list[j])
              typeError(t->child[0],"type of arguments doesn't match function declaration");
            j++;
            t = t->child[0];
            while (t->sibling != NULL && j < functionDeclarations[i].param_size) {
              if (t->sibling->type != functionDeclarations[i].arg_list[j])
                typeError(t,"type of arguments doesn't match function declaration");
              t = t->sibling;
              j++;
            }
          }

          break;
        }
        case ReturnK:
          if (t->child[0] != NULL) {
            if (t->child[0]->type != t->type)
              if(t->type == Void)
              {
                typeError(t->child[0], "void function can't return a value");
              }
              else
              {
                typeError(t->child[0],"type of return value doesn't match function declaration");
              }
          }          
          break;
        default:
          break;
      }
      break;
    default:
      break;

  }
}

/* Procedure typeCheck performs type checking 
 * by a postorder syntax tree traversal
 */
void typeCheck(TreeNode * syntaxTree)
{ traverse(syntaxTree,nullProc,checkNode);
}

//Stores Current Num of spaces for AST
static int indentno = 0;

//Increase/Cecrease Indentation
#define INDENT indentno+=2
#define UNINDENT indentno-=2

//Increases Indetation by printing spaces
void printSpaces(void) {
  int i;
  for (i=0;i<indentno;i++)
    fprintf(listing," ");
}

//Print the Annotated AST
void printAnnotatedTree(TreeNode *tree)
{
    int i;
    
    //Macro to Indent
    INDENT;

    //Loop while tree is not null (No Children)
    while (tree != NULL) {

      printSpaces();

      //Output based on Node Type
        
      if (tree->nodekind == DecK) {

        switch(tree->kind.dec) {
          case VarK:
            fprintf(listing,"[Variable declaration \"%s\" of type \"%s\" at line %d, scope %d and memory location %d]\n"
                   , tree->attr.name, tree->type==Integer?"Integer": (tree->type==Boolean?"Boolean":"Void"), tree->lineno, tree->scope, tree->loc);
            break;
            
          case FunK:
            fprintf(listing, "[Function declaration \"%s()\""
                    " of return type \"%s\" with \"%d\" arguments at line %d, scope %d and memory location %d. ", 
                    tree->attr.name, tree->type==Integer?"Integer": (tree->type==Boolean?"Boolean":"Void"), tree->param_size, tree->lineno, tree->scope, tree->loc);
            
            if(tree->param_size != 0)
            {
              fprintf(listing,  "Argument types are: ");
              int i;
              for(i = 0; i < totalFuncs; i++)
              {
                if(!strcmp(functionDeclarations[i].function_name, tree->attr.name))
                {
                  break;
                }
              }

              for(int j = 0; j < tree->param_size; j++)
              {
                fprintf(listing, "%s ", functionDeclarations[i].arg_list[j]==Integer?"Integer": (functionDeclarations[i].arg_list[j]==Boolean?"Boolean":"Void"));
              }
            }
            fprintf(listing, "]\n");
            break;

          case ParameterK:
            fprintf(listing, "[Parameter \"%s\""
                    " of type \"%s\" at line %d, scope %d and memory location %d]\n", 
                    tree->attr.name, tree->type==Integer?"Integer": (tree->type==Boolean?"Boolean":"Void"), tree->lineno, tree->scope, tree->loc);
            break;
            
          default:
            fprintf(listing, "<<<unknown declaration type>>>\n");
            break;
        }
      }
      
      else if (tree->nodekind == ExpK) {

        switch(tree->kind.exp) {          
          case OpK:
            fprintf(listing, "[Operator ");
            printOperators(tree->attr.op, "", tree);
            fprintf(listing, "of type \"%s\"]\n", tree->type==Integer?"Integer": (tree->type==Boolean?"Boolean":"Void"));
            break;
                
          case IdK:
            fprintf(listing, "[Identifier \"%s\" at line %d of type \"%s\", scope %d and memory location %d]\n", tree->attr.name, tree->lineno, tree->type==Integer?"Integer": (tree->type==Boolean?"Boolean":"Void"), tree->scope, tree->loc);
            break;
                
          case ConstK:
            fprintf(listing, "[Literal constant \"%s\" at line %d of type \"%s\"]\n", tree->attr.val, tree->lineno, tree->type==Integer?"Integer": (tree->type==Boolean?"Boolean":"Void"));
            break;
                
          case AssignK:
            fprintf(listing, "[Assignment \"%s\" at line %d of type \"%s\", scope %d and memory location %d]\n", tree->attr.name, tree->lineno, tree->type==Integer?"Integer": (tree->type==Boolean?"Boolean":"Void"), tree->scope, tree->loc);
            break;       
                
          default:
            fprintf(listing, "<<<unknown expression type>>>\n");
            break;
        }
      }
    
      else if (tree->nodekind == StmtK) {

        switch(tree->kind.stmt) {
          case CompoundK:
            fprintf(listing, "[Compound statement ending at line %d]\n", tree->lineno);
            break;

          case IfK:
            fprintf(listing, "[IF statement ending at line %d]\n", tree->lineno);
            break;

          case IfElseK:
            fprintf(listing, "[IFELSE statement ending at line %d]\n", tree->lineno);
            break;

          case BreakK:
            fprintf(listing, "[BREAK statement at line %d]\n", tree->lineno);
            break;
                
          case WhileK:
            fprintf(listing, "[WHILE statement ending at line %d]\n", tree->lineno);
            break;
                
          case ReturnK:
            fprintf(listing, "[RETURN statement at line %d of type \"%s\"]\n", tree->lineno, tree->type==Integer?"Integer": (tree->type==Boolean?"Boolean":"Void"));
            break;
                
          case CallK:
          fprintf(listing, "[Call to function \"%s()\" with \"%d\" argument(s) at line %d, scope %d and memory location %d]\n",
                  tree->attr.name,(tree->child[0])!=NULL?(tree->child[0])->param_size:0, tree->lineno, tree->scope, tree->loc);
          break;

          case EmptyK:
            fprintf(listing, "[EMPTY statement at line %d]\n", tree->lineno);
            break;

          case SemicolonK:
            fprintf(listing, "[Semicolon statement at line %d]\n", tree->lineno);
            break;
       
        default:
          fprintf(listing, "<<<unknown statement type>>>\n");
          break;
        }
      }
      else if (tree->nodekind == LabelK) {
        switch(tree->kind.stmt) {
          case FctnParamsK:
            fprintf(listing, "[Function Parameters List at line %d]\n", tree->lineno);
            break;  
          
          case FctnArgsK:
            fprintf(listing, "[Function Declaration List at line %d]\n", tree->lineno);
            break;      
          
          case BlockK:
            fprintf(listing, "[Block ending at line %d]\n", tree->lineno);
            break;

        default:
          fprintf(listing, "<<<unknown label type>>>\n");
          break;
        }
      }

      else
        fprintf(listing, "<<<unknown node kind>>>\n");

      for (i=0; i<MAXCHILDREN; ++i)
        printAnnotatedTree(tree->child[i]);
        
      tree = tree->sibling;
    }

    UNINDENT;
}