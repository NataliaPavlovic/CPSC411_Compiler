/****************************************************/
/* File: analyze.c                                  */
/* Semantic analyzer                                */
/* For EX Compiler                                  */
/*                                                  */
/****************************************************/

#include "globals.h"
#include "symtab.h"
#include "analyze.h"

#include <stdlib.h>
#include <string.h>

static int scope_a = 0;

/* counter for variable memory locations */
static int location[MAX_SCOPE] = {0,0,0};

static int No_change = 0; 

static int count_while = 0;
static int count_main = 0;

static int return_type = -1;

struct Funk_decls
{
  char function_name[20];
  int return_type;
  int param_size;
  int arg_list[20];
} ;

struct Funk_decls functionDeclarations [100];
int totalFuncs = 0;

static void printError(TreeNode * t, char * message)
{ fprintf(listing,"Error: %s at line %d\n",message, t->lineno);
  Error = TRUE;
}

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
      { case CallK:
          if(!strcmp(t->attr.name, "main"))
          {
            printError(t, "Main function is called");
          }
          if (st_lookup(t->attr.name, scope_a) == -1)
            st_insert(t->attr.name, t->lineno, -1, scope_a, FALSE, t->type);
          else
            st_insert(t->attr.name, t->lineno, 0, scope_a, FALSE, t->type);

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
         
          break; 
        }
        case ReturnK:
          t->type = return_type;
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
            printError(t,"Break statement not in a while loop");
          }
          else
          {
            count_while--;
          }
          break;
        case CompoundK:
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
          if (t->child[0] != NULL) {
            t->child[0]->scope = t->scope;
            if(t->child[1] != NULL)
            {
              t->child[1]->scope = t->scope;
            }
          }
        case IdK:
            if(t->attr.name != NULL)
            {
              BucketList lookup_inner = var_lookup(t->attr.name, t->scope);
              BucketList lookup_outer = var_lookup(t->attr.name, scope_a);
              if (lookup_inner!=NULL)
              {
                t->type = lookup_inner->type;
              }
              else if (lookup_outer!=NULL)
              {
                t->type = lookup_outer->type;
              }

              if (t->scope > scope_a) {
                if(lookup_inner == NULL && lookup_outer == NULL)
                {
                  printError(t, strcat(t->attr.name, " variable used without being declared"));
                }
                else if (lookup_inner == NULL)
                {
                  st_insert(t->attr.name, t->lineno, 0, scope_a, FALSE, t->type);
                }
                else
                {
                  st_insert(t->attr.name, t->lineno, 0, t->scope, FALSE, t->type);
                }
              }
              else {
                st_insert(t->attr.name, t->lineno, 0, scope_a, FALSE, t->type);
              }
            }
          break;
        case AssignK:
          if (t->child[0] != NULL) {
            t->child[0]->scope = t->scope;
          }
          BucketList lookup_inner = var_lookup(t->attr.name, t->scope);
          BucketList lookup_outer = var_lookup(t->attr.name, scope_a);
          if (lookup_inner!=NULL)
          {
            t->type = lookup_inner->type;
          }
          else if (lookup_outer!=NULL)
          {
            t->type = lookup_outer->type;
          }

          if (t->scope > scope_a) {
            if(lookup_inner == NULL && lookup_outer== NULL)
            {
              printError(t, strcat(t->attr.name, " variable used without being declared"));
            }
            else if (lookup_inner == NULL)
            {
              st_insert(t->attr.name, t->lineno, 0, scope_a, FALSE, t->type);
            }
            else
            {
              st_insert(t->attr.name, t->lineno, 0, t->scope, FALSE, t->type);
            }
          }
          else {
            st_insert(t->attr.name, t->lineno, 0, scope_a, FALSE, t->type);
          }
          break;
        default:
          break;
      }
      break;
    case DecK:
      switch (t->kind.dec)
      { case VarK:
          if(t->in_compound == 1)
          {
            printError(t, "Variable declared in compound statament");
          }
          else
          {
            if (t->scope > scope_a) {
              if (var_lookup(t->attr.name, t->scope) == NULL) {
                st_insert(t->attr.name, t->lineno, location[t->scope]++, t->scope, FALSE, t->type);
              }
              else
                {
                  printError(t, "Variable redeclared in same scope");
                }
            }
            else {
              if (var_lookup(t->attr.name, scope_a) == NULL)
                st_insert(t->attr.name, t->lineno, location[scope_a]++, scope_a, FALSE, t->type);
              else
                {
                  printError(t, "Variable redeclared in global scope");
                }
            }
          }
          break;
        case ParameterK:
            if (var_lookup(t->attr.name, t->scope) == NULL) {
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
          if (count_main > 1)
          {
            printError(t, "Second main declaration");
          }

          return_type = t->type;

          st_insert(t->attr.name, t->lineno, -1, scope_a, FALSE, t->type);

          int i;
          for(i = 0; i < totalFuncs; i++)
          {
            if(!strcmp(t->attr.name, functionDeclarations[i].function_name))
            {
              printError(t, "Function redefined");
              break;
            }
          }
          if (i == totalFuncs)
          {
            strcpy(functionDeclarations[i].function_name, t->attr.name);
            functionDeclarations[i].param_size = t->param_size;
            functionDeclarations[i].return_type = return_type;
          }
          totalFuncs++;

          if(!strcmp(t->attr.name, "main") && t->param_size != 0)
          {
            printError(t, "Main declaration has parameters");
          }

          No_change++;

          TreeNode * temp = t;

          int j = 0;
          // Function arguments
          if (t->child[0] != NULL && t->child[0]->child[0] != NULL) {
            t = t->child[0];
            t->child[0]->scope = No_change;
            t = t->child[0];
            functionDeclarations[i].arg_list[j] = t->type;
            while (t->sibling != NULL) {
              t = t->sibling;
              t->scope = No_change;
              j++;
              functionDeclarations[i].arg_list[j] = t->type;
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

              if (count_return == 0)
              {
                printError(t, "No Return statement for non-void function");
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
          else if (return_type != Void)
          {
            printError(t, "No Return statement for non-void function");
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
    printNoMainError(syntaxTree, "No main declaration");
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

          if ((t->attr.op == LE) || (t->attr.op == '<') || (t->attr.op == '>') || (t->attr.op == GE) || (t->attr.op == EQ) || (t->attr.op == NQ) || (t->attr.op == AND) || (t->attr.op == OR))
            {
              t->type = Boolean;
            }
          else
            t->type = Integer;
          break;
        case AssignK:
          if(t->child[0] != NULL)
          {
            if(t->child[0]->child[0] == NULL)
            {
              if ((t->child[0]->attr.op == LE) || (t->child[0]->attr.op == '<') || (t->child[0]->attr.op == '>') || (t->child[0]->attr.op == GE) || (t->child[0]->attr.op == AND) || (t->child[0]->attr.op == OR) || (t->child[0]->attr.op == '!'))
              typeError(t->child[0], "Cannot assign boolean to int variable");
              else if (t->child[0]->type != t->type)
              {
                typeError(t->child[0], "Cannot assign this type to variable");
              }
            }
            else
            {
              t = t->child[0];
              if ((t->child[0]->attr.op == LE) || (t->child[0]->attr.op == '<') || (t->child[0]->attr.op == '>') || (t->child[0]->attr.op == GE) || (t->child[0]->attr.op == AND) || (t->child[0]->attr.op == OR) || (t->child[0]->attr.op == '!'))
              typeError(t->child[0], "Cannot assign boolean to int variable");
              else if (t->child[0]->type != t->type)
              {
                typeError(t->child[0], "Cannot assign this type to variable");
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
              typeError(t->child[0],"if condition is not Boolean");
          }
          else
          {
            if (t->child[0]->child[0]->type == Integer)
              typeError(t->child[0]->child[0],"if condition is not Boolean");
          }
          break;
        case IfElseK:
          if(t->child[0]->child[0] == NULL)
          {
            if (t->child[0]->type == Integer)
              typeError(t->child[0],"ifelse condition is not Boolean");
          }
          else
          {
            if (t->child[0]->child[0]->type == Integer)
              typeError(t->child[0]->child[0],"ifelse condition is not Boolean");
          }
          break;
        case WhileK:
          if(t->child[0]->child[0] == NULL)
          {
            if (t->child[0]->type == Integer)
              typeError(t->child[0],"while condition is not Boolean");
          }
          else
          {
            if (t->child[0]->child[0]->type == Integer)
              typeError(t->child[0]->child[0],"while condition is not Boolean");
          }

          break;
        case CallK:
        {
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
            printError(t, "The function was not declared");
          }

          if (t->child[0] != NULL && t->child[0]->child[0]) {
            if(t->child[0]->param_size != functionDeclarations[i].param_size)
            {
              printError(t, "Function called with wrong number of arguments");
            }
            t = t->child[0];
            int j = 0;
            if (t->child[0]->type != functionDeclarations[i].arg_list[j])
              typeError(t->child[0],"Call parameter is not correct type");
            j++;
            t = t->child[0];
            while (t->sibling != NULL && j < functionDeclarations[i].param_size) {
              if (t->type != functionDeclarations[i].arg_list[j])
                typeError(t,"Call parameter is not correct type");
              t = t->sibling;
              j++;
            }
          }
          break;
        }
        case ReturnK:
          if (t->child[0] != NULL) {
            if (t->child[0]->type != t->type)
              typeError(t->child[0],"Return value is of wrong type");
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
