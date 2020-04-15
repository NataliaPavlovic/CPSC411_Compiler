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

// Counter for number of current nested while loops
static int count_while = 0;

static int total_func_loops = 0;
static int func_return_counter = 0;

// Counter for number of main function declarations
int count_main = 0;

// Return type of function declaration
static int return_type = -1;

// Total number of functions in array
int totalFuncs = 0;

int getchar_redefined = 0;
int halt_redefined = 0;
int printb_redefined = 0;
int printc_redefined = 0;
int printi_redefined = 0;
int prints_redefined = 0;

int main_replacement_index;
int main_replacement_counter;

// print an error message and a line number
static void printError(TreeNode * t, char * message, int print_line_no)
{ 
  if(print_line_no)
  {
    fprintf(listing,"Error: %s at line %d\n",message, t->lineno);
  }
  else
  {
    fprintf(listing,"Error: %s\n",message);
  }
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
    {
    case LabelK:
      switch (t->kind.stmt)
      {
        case FctnArgsK:
          if (t->child[0] != NULL) {
            t->child[0]->scope = No_change;
            t = t->child[0];
            while (t->sibling != NULL) {
              t = t->sibling;
              t->scope = No_change;
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
        case CallK:
          // Check if main function was called
          if(!strcmp(t->attr.name, "main"))
          {
            printError(t, "main function cannot be called", 1);
          }
          if (st_lookup(t->attr.name, scope_a) == -1)
            st_insert(t->attr.name, t->lineno, -1, scope_a, FALSE, -1);
          else
            st_insert(t->attr.name, t->lineno, 0, scope_a, FALSE, -1);

          t->loc = -1;
          t->scope = scope_a;

          // Set scope of function call parameters
          if (t->child[0] != NULL && t->child[0]->child[0] != NULL) {
            t = t->child[0]->child[0];
            while(t != NULL && (t->attr.name == NULL))
            {
              t = t->sibling;
            }
            if (t != NULL && st_lookup(t->attr.name, scope_a) == -1) {
              t->scope = No_change;
              t-> output_return_value = 1;
              while (t->sibling != NULL) {
                t = t->sibling;
                t->scope = No_change;
                t-> output_return_value = 1;
              }
            } 
        }
        break; 
        case ReturnK:
        {
          // Set type of return to return type of function declaration
          t->type = return_type;

          if(t->child[0] != NULL)
          {
            int not_RTS = 1;
            if(t->child[0]->attr.name != NULL)
            {
              not_RTS = (strcmp(t->child[0]->attr.name, "getchar")) && (strcmp(t->child[0]->attr.name, "halt")) && strcmp(t->child[0]->attr.name, "printb") && strcmp(t->child[0]->attr.name, "printc") && strcmp(t->child[0]->attr.name, "printi") && strcmp(t->child[0]->attr.name, "prints");
            }
            if(!not_RTS)
            {
              if(!strcmp(t->child[0]->attr.name, "getchar"))
                {
                  if(!getchar_redefined)
                  {
                    t->child[0]->type = Integer;
                    t->type = Integer;
                  }
                }
              else if(!strcmp(t->child[0]->attr.name, "halt"))
                {
                  if(!halt_redefined)
                  {
                    t->child[0]->type = Void;
                    t->type = Void;
                  }

                }
              else if(!strcmp(t->child[0]->attr.name, "printc"))
                {
                  if(!printc_redefined)
                  {
                    t->child[0]->type = Void;
                    t->type = Void;
                  }
                }
              else if(!strcmp(t->child[0]->attr.name, "printb"))
                {
                  if(!printb_redefined)
                  {
                    t->child[0]->type = Void;
                    t->type = Void;
                  }
                }
              else if(!strcmp(t->child[0]->attr.name, "printi"))
                {
                  if(!printi_redefined)
                  {
                    t->child[0]->type = Void;
                    t->type = Void;
                  }
                }
              else if(!strcmp(t->child[0]->attr.name, "prints"))
                {
                  if(!prints_redefined)
                  {
                    t->child[0]->type = Void;
                    t->type = Void;
                  }
                }
            }
          }

          // Set scope of child
          if (t->child[0] != NULL) {
            t->child[0]->scope = t->scope;
            t->child[0] -> output_return_value = 1;
          }
          else if(return_type != Void)
          {
            printError(t, "No value returned from non-void function", 1);
          }
          break;
        }
        case WhileK:
          // Set scope of child
          if (t->child[0] != NULL) {
            t->child[0] -> scope = t->scope;
            t->child[0] -> output_return_value = 1;
          }         
          count_while++;
          break;
        case IfK:
          // Set scope of child
          if (t->child[0] != NULL) {
            t->child[0]->scope = t->scope;
            t->child[0] -> output_return_value = 1;
          }         
          break;
        case IfElseK:
          // Set scope of child
          if (t->child[0] != NULL) {
            t->child[0]->scope = t->scope;
            t->child[0] -> output_return_value = 1;
          }         
          break;
        case IfElseIfK:
          // Set scope of child
          if (t->child[0] != NULL) {
            t->child[0]->scope = t->scope;
            t->child[0] -> output_return_value = 1;
          }    
          if (t->child[2] != NULL) {
            t->child[2]->scope = t->scope;
            t->child[2] -> output_return_value = 1;
            t = t->child[2];
            while(t->sibling != NULL)
            {
              t->sibling->scope = t->scope;
              t->sibling-> output_return_value = 1;
              t = t->sibling;
            }
          }      
          break;
        case IfElseIfElseK:
          // Set scope of child
          if (t->child[0] != NULL) {
            t->child[0]->scope = t->scope;
            t->child[0] -> output_return_value = 1;
          } 
          if (t->child[2] != NULL) {
            t->child[2]->scope = t->scope;
            t->child[2] -> output_return_value = 1;
            t = t->child[2];
            while(t->sibling != NULL)
            {
              t->sibling->scope = t->scope;
              t->sibling-> output_return_value = 1;
              t = t->sibling;
            }
          } 
          break;
        case ElseIfK:
          // Set scope of child
          if (t->child[0] != NULL) {
            t->child[0]->scope = t->scope;
            t->child[0] -> output_return_value = 1;
          }         
          break;
        case BreakK:
          if(count_while == 0)
          {
            printError(t,"break must be inside while loop", 1);
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
          // Check if op will lead to a boolean expression
          if ((t->attr.op == LE) || (t->attr.op == '!') || (t->attr.op == '<') || (t->attr.op == '>') || (t->attr.op == GE) || (t->attr.op == EQ) || (t->attr.op == NQ) || (t->attr.op == AND) || (t->attr.op == OR))
            {
              t->type = Boolean;
            }
          else
            t->type = Integer;

          // Set scope for all children
          if (t->child[0] != NULL) {
            t->child[0]->scope = t->scope;
            t-> child[0] -> output_return_value = 1;
            if(t->child[1] != NULL)
            {
              t->child[1]->scope = t->scope;
              t-> child[1]->output_return_value = 1;
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
                  printError(t, strcat(t->attr.name, " variable used without being declared"), 1);
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
              printf("%s %d\n", t->attr.name, t->scope);
              // ID cannot be found in either current scope or global scope
              printError(t, strcat(t->attr.name, " variable used without being declared"), 1);
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
            printError(t, "Local declaration not in outermost block", 1);
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
                printError(t, "Variable redeclared in same scope", 1);
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
          return_type = -1;
          if(!strcmp(t->attr.name, "main"))
          {
            count_main++;
          }
          if(!strcmp(t->attr.name, "getchar"))
          {
            getchar_redefined = 1;
          }
          if(!strcmp(t->attr.name, "halt"))
          {
            halt_redefined = 1;
          }
          if(!strcmp(t->attr.name, "printb"))
          {
            printb_redefined = 1;
          }
          if(!strcmp(t->attr.name, "printc"))
          {
            printc_redefined = 1;
          }
          if(!strcmp(t->attr.name, "printi"))
          {
            printi_redefined = 1;
          }
          if(!strcmp(t->attr.name, "prints"))
          {
            prints_redefined = 1;
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

              printError(t, strcat(t->attr.name," function redefined"), 1);
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
            printError(t, "main declaration can't have parameters", 1);
          }

          if(t->type == Void && t->param_size == 0 && strcmp(t->attr.name, "main") && main_replacement_counter == 0)
          {
            main_replacement_index = i;
            main_replacement_counter++;
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


static void global_vars_first( TreeNode * tree)
{ 
  if (tree != NULL)
  { switch (tree->nodekind) {
      case DecK:
      {
        if( tree->kind.dec == VarK && tree->scope == 0)
        {
            // Declare variable in global scope
            if (var_lookup(tree->attr.name, scope_a) == NULL)
            {
              tree->loc = location[scope_a];
              st_insert(tree->attr.name, tree->lineno, location[scope_a]++, scope_a, FALSE, tree->type);
              tree->scope = scope_a;
            }
            else
            {
              printError(tree, "Variable redeclared in global scope", 1);
            }
        }
        global_vars_first(tree->sibling);
        break;
      }
      default:
        break;
    }
  }
}




/* Function buildSymtab constructs the symbol 
 * table by preorder traversal of the syntax tree
 */
void buildSymtab(TreeNode * syntaxTree)
{ 
  global_vars_first(syntaxTree);
  traverse(syntaxTree,insertNode,nullProc);
  if (count_main == 0 && main_replacement_counter == 0)
  {
    printError(syntaxTree, "No main declaration found", 0);
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
  { 
    case ExpK:
      switch (t->kind.exp)
      { case OpK:
        {
          // Check if op will lead to a boolean expression
          if ((t->attr.op == AND) || (t->attr.op == OR))
            {
              if (t->child[1] != NULL)
              {
                if ((t->child[0]->type != Boolean) || (t->child[1]->type != Boolean))
                  typeError(t,"Op applied to non-integer");
              }
            }
          else
          {
            // Check if children of op are not Integers
            if (t->child[1] != NULL)
            {
              if ((t->child[0]->type != Integer) || (t->child[1]->type != Integer))
                typeError(t,"Op applied to non-integer");
            }
            else
            {
              if (t->child[0]->type != Integer && t->attr.op != '!')
                typeError(t,"Op applied to non-integer");
            }
          }

          break;
        }

        case AssignK:
        {
          if(t->child[0] != NULL)
          {
            int not_RTS = 1;
            if(t->child[0]->attr.name != NULL)
            {
              not_RTS = (strcmp(t->child[0]->attr.name, "getchar")) && (strcmp(t->child[0]->attr.name, "halt")) && strcmp(t->child[0]->attr.name, "printb") && strcmp(t->child[0]->attr.name, "printc") && strcmp(t->child[0]->attr.name, "printi") && strcmp(t->child[0]->attr.name, "prints");
            }
            if(!not_RTS)
            {
              if(!strcmp(t->child[0]->attr.name, "getchar"))
                {
                  if(!getchar_redefined)
                    t->child[0]->type = Integer;
                }
              else if(!strcmp(t->child[0]->attr.name, "halt"))
                {
                  if(!halt_redefined)
                    t->child[0]->type = Void;
                }
              else if(!strcmp(t->child[0]->attr.name, "printc"))
                {
                  if(!printc_redefined)
                    t->child[0]->type = Void;
                }
              else if(!strcmp(t->child[0]->attr.name, "printb"))
                {
                  if(!printb_redefined)
                    t->child[0]->type = Void;
                }
              else if(!strcmp(t->child[0]->attr.name, "printi"))
                {
                  if(!printi_redefined)
                    t->child[0]->type = Void;
                }
              else if(!strcmp(t->child[0]->attr.name, "prints"))
                {
                  if(!prints_redefined)
                    t->child[0]->type = Void;
                }
            }
            
            if(t->child[0]->child[0] == NULL)
            {
              // Check if op will lead to a boolean expression
              if (t->type == Integer && ((t->child[0]->attr.op == LE) || (t->child[0]->attr.op == '<') || (t->child[0]->attr.op == '>') || (t->child[0]->attr.op == GE) || (t->child[0]->attr.op == AND) || (t->child[0]->attr.op == OR) || (t->child[0]->attr.op == '!') || (t->child[0]->attr.op == EQ) || (t->child[0]->attr.op == NQ)))
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
              // Check if op will lead to a boolean expression
              if (t->type == Integer && ((t->child[0]->attr.op == LE) || (t->child[0]->attr.op == '<') || (t->child[0]->attr.op == '>') || (t->child[0]->attr.op == GE) || (t->child[0]->attr.op == AND) || (t->child[0]->attr.op == OR) || (t->child[0]->attr.op == '!') || (t->child[0]->attr.op == EQ) || (t->child[0]->attr.op == NQ)))
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
        }
        default:
          break;
      }
      break;
    case StmtK:
      switch (t->kind.stmt)
      { 
        case IfK:
          if (t->child[0]->type == Integer)
            typeError(t->child[0],"need a boolean expression for if condition");
          break;
        case IfElseK:
          if (t->child[0]->type == Integer)
            typeError(t->child[0],"need a boolean expression for ifelse condition");
          break;
        case IfElseIfK:
          if (t->child[0]->type == Integer)
            typeError(t->child[0],"need a boolean expression for ifelse condition");
          break;
        case IfElseIfElseK:
          if (t->child[0]->type == Integer)
            typeError(t->child[0],"need a boolean expression for ifelse condition");
          break;
        case ElseIfK:
          if (t->child[0]->type == Integer)
            typeError(t->child[0],"need a boolean expression for ifelse condition");
          break;
        case WhileK:
          total_func_loops++;
          if (t->child[0]->type == Integer)
            typeError(t->child[0],"need a boolean expression for while condition");
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

          t->type = functionDeclarations[i].return_type;

          int not_RTS = (strcmp(t->attr.name, "getchar")) && (strcmp(t->attr.name, "halt")) && strcmp(t->attr.name, "printb") && strcmp(t->attr.name, "printc") && strcmp(t->attr.name, "printi") && strcmp(t->attr.name, "prints");
          int redef = 0;
          if (i== totalFuncs && not_RTS)
          {
            printError(t, "function was used but never declared", 1);
          }

          if(!not_RTS)
          {
            if(strcmp(t->attr.name, "getchar")==0 && !getchar_redefined)
            {
              if(t->child[0] != NULL)
              {
                printError(t, "number of arguments doesn't match getchar RTS function declaration", 1);
              }
              t->type = Integer;
              break;
            }
            else if(strcmp(t->attr.name, "halt")==0 && !halt_redefined)
            {
              if(t->child[0] != NULL)
              {
                printError(t, "number of arguments doesn't match halt RTS function declaration", 1);
              }
              t->type = Void;
            }
            else if(strcmp(t->attr.name, "printb")==0 && !printb_redefined)
            {
              if(t->child[0] == NULL || t->child[0]->param_size != 1)
              {
                printError(t, "number of arguments doesn't match printb RTS function declaration", 1);
              }
              t->type = Void;
              if(t->child[0]->child[0] != NULL)
              {
                t = t->child[0];
                if (t->child[0]->type != Boolean)
                  typeError(t->child[0],"type of arguments doesn't match printb RTS function declaration");
              }
            }
            else if(strcmp(t->attr.name, "printc")==0 && !printc_redefined)
            {
              if(t->child[0] == NULL || t->child[0]->param_size != 1)
              {
                printError(t, "number of arguments doesn't match printc RTS function declaration", 1);
              }
              t->type = Void;
              if(t->child[0]->child[0] != NULL)
              {
                t = t->child[0];
                if (t->child[0]->type != Integer)
                  typeError(t->child[0],"type of arguments doesn't match printc RTS function declaration");
              }
            }
            else if(strcmp(t->attr.name, "printi")==0 && !printi_redefined)
            {
              if(t->child[0] == NULL || t->child[0]->param_size != 1)
              {
                printError(t, "number of arguments doesn't match printi RTS function declaration", 1);
              }
              t->type = Void;
              if(t->child[0]->child[0]!= NULL)
              {
                t = t->child[0];
                if (t->child[0]->type != Integer)
                  typeError(t->child[0],"type of arguments doesn't match printi RTS function declaration");
              }
            }
            else if(strcmp(t->attr.name, "prints")==0 && !prints_redefined)
            {
              if(t->child[0] == NULL || t->child[0]->param_size != 1)
              {
                printError(t, "number of arguments doesn't match prints RTS function declaration", 1);
              }
              t->type = Void;
              if(t->child[0]->child[0] != NULL)
              {
                t = t->child[0];
                if (t->child[0]->type == Integer || t->child[0]->type == Boolean)
                  typeError(t->child[0],"type of arguments doesn't match prints RTS function declaration");
              }
            }
            else
            {
              redef = 1;
            }
          }

          // Check the types of arguments passed into the function call
          if ( (not_RTS || redef==1) && t->child[0] != NULL) {
            redef = 0;
            if(t->child[0]->param_size != functionDeclarations[i].param_size)
            {
              printError(t, "number of arguments doesn't match function declaration", 1);
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
          else if( (not_RTS || redef == 1) && t->child[0] == NULL && functionDeclarations[i].param_size != 0)
          {
              redef = 0;
              printError(t, "number of arguments doesn't match function declaration", 1);
          }
          break;
        }
        case ReturnK:
        {
          func_return_counter++;
          // if (t->child[0] != NULL) {
          //   if (t->child[0]->type != t->type)
          //     if(t->type == Void)
          //     {
          //       typeError(t->child[0], "void function can't return a value");
          //     }
          //     else
          //     {
          //       typeError(t->child[0],"type of return value doesn't match function declaration");
          //     }
          // }  
          if (t->child[0] != NULL) {
            if (t->child[0]->type != t->type)
            {
              if(t->type == Void)
              {
                typeError(t->child[0], "void function can't return a value");
              }
              else
              {
                printf("%d %d\n", t->child[0]->type, t->type);
                typeError(t->child[0],"type of return value doesn't match function declaration");
              }
            }
          }        
          break;
        }
        default:
          break;
      }
      break;
      case DecK:
        switch(t->kind.dec)
        {
          case FunK:
            {
              if(func_return_counter == 0 && t->type != Void)
              {
                char * str = (char *)malloc(42+1);
                strcpy(str, "No return statement for non-void function ");
                printError(t, strcat(str, t->attr.name), 1);
              }
              func_return_counter = 0;
              break;
          default:
            break;
        }
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
  