/****************************************************/
/* File: analyze.c                                  */
/* Semantic analyzer                                */
/* For EX Compiler                                  */
/*                                                  */
/****************************************************/

#include "globals.h"
#include "symtab.h"
#include "analyze.h"


static int scope_a = 0;

/* counter for variable memory locations */
static int location[MAX_SCOPE] = {0,0,0};

static int No_change = 0; 
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
{ switch (t->nodekind)
    {case StmtK:
      switch (t->kind.stmt)
      { case CallK:
          if (st_lookup(t->attr.name, scope_a) == -1)
            st_insert(t->attr.name, t->lineno, -1, scope_a, FALSE);
          else
            st_insert(t->attr.name, t->lineno, 0, scope_a, FALSE);
          if (t->child[0] != NULL) {
            if (t->child[0]->type == Integer) {
              if (st_lookup(t->child[0]->attr.name, scope_a) == -1) {
                t->child[0]->scope = No_change;
                t = t->child[0];
                while (t->sibling != NULL) {
                  t = t->sibling;
                  t->scope = No_change;
                }
              }
            }
          }
          break; 
        case CompoundK:
          if (t->child[0] != NULL) {
            No_change++;
            t->child[0]->scope = No_change;
            t = t->child[0];
            while (t->sibling != NULL) {
              t = t->sibling;
              t->scope = No_change;
            }
          }
          HighScope++;
          break;
        case ReturnK:
          if (t->child[0]->child[0] != NULL) {
            t->child[0]->child[0]->scope = No_change;
            if (t->child[0]->child[1] != NULL) 
              t->child[0]->child[1]->scope = No_change;
          }
        default:
          break;
      }
      break;
    case ExpK:
      switch (t->kind.exp)
      { case IdK:
          if (t->scope > scope_a) {
            if (var_lookup(t->attr.name, t->scope) == NULL)
              st_insert(t->attr.name, t->lineno, location[t->scope]++, t->scope, FALSE);
            else
              st_insert(t->attr.name, t->lineno, 0, t->scope, FALSE);
          }
          else {
            if (var_lookup(t->attr.name, scope_a) == NULL)
              st_insert(t->attr.name, t->lineno, location[scope_a]++, scope_a, FALSE);
            else
              st_insert(t->attr.name, t->lineno, 0, scope_a, FALSE);
          }
          break;
        default:
          break;
      }
      break;
    case DecK:
      switch (t->kind.dec)
      { case VarK:
          if (t->isParameter == 1) {
            if (var_lookup(t->attr.name, t->scope) == NULL) {
              st_insert(t->attr.name, t->lineno, location[t->scope]++, t->scope, FALSE);
            }
            else
              st_insert(t->attr.name, t->lineno, 0, t->scope, FALSE);
          }
          else if (t->scope > scope_a) {
            if (var_lookup(t->attr.name, t->scope) == NULL) {
              st_insert(t->attr.name, t->lineno, location[t->scope]++, t->scope, FALSE);
            }
            else
              st_insert(t->attr.name, t->lineno, 0, t->scope, FALSE);
          }
          else {
            if (var_lookup(t->attr.name, scope_a) == NULL)
              st_insert(t->attr.name, t->lineno, location[scope_a]++, scope_a, FALSE);
            else
              st_insert(t->attr.name, t->lineno, 0, scope_a, FALSE);
          }
          break;
        case ArrayK:
          if (t->isParameter == 1) {
            if (var_lookup(t->attr.name, t->scope) == NULL) {
              st_insert(t->attr.name, t->lineno, location[t->scope]++, t->scope, FALSE);
            }
            else
              st_insert(t->attr.name, t->lineno, 0, t->scope, FALSE);
          }
          else if (t->scope > scope_a) {
            if (var_lookup(t->attr.name, t->scope) == NULL) {
              st_insert(t->attr.name, t->lineno, location[t->scope]++, t->scope, FALSE);
              location[t->scope] = location[t->scope] + t->local_size - 1;
            }
            else
              st_insert(t->attr.name, t->lineno, 0, t->scope, FALSE);
          }
          else {
            if (var_lookup(t->attr.name, scope_a) == NULL) {
              st_insert(t->attr.name, t->lineno, location[scope_a]++, scope_a, FALSE);
              location[scope_a] = location[scope_a] + t->local_size - 1;
            }
            else
              st_insert(t->attr.name, t->lineno, 0, scope_a, FALSE);
          }
          break;
        case FunK:
          if (st_lookup(t->attr.name, scope_a) == -1) {
            st_insert(t->attr.name, t->lineno, -1, scope_a, FALSE);
          }
          else
            st_insert(t->attr.name, t->lineno, -1, scope_a, FALSE);
          
          if (t->child[0] != NULL) {
            No_change++;
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
    default:
      break;
  }


}

/* Function buildSymtab constructs the symbol 
 * table by preorder traversal of the syntax tree
 */
void buildSymtab(TreeNode * syntaxTree)
{ traverse(syntaxTree,insertNode,nullProc);
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
          if ((t->child[0]->type != Integer) || (t->child[1]->type != Integer))
            typeError(t,"Op applied to non-integer");
          if ((t->attr.op == LE) || (t->attr.op == LT) || (t->attr.op == GT) || (t->attr.op == GE) || (t->attr.op == EQ) || (t->attr.op == NQ))
            t->type = Boolean;
          else
            t->type = Integer;
          break;
        case ConstK:
        case IdK:
          t->type = Integer;
          break;
        case AssignK:
          if ((t->child[1]->attr.op == LE) || (t->child[1]->attr.op == LT) || (t->child[1]->attr.op == GT) || (t->child[1]->attr.op == GE))
            typeError(t->child[1], "Cannot assign boolean to int variable");
          break;
        default:
          break;
      }
      break;
    case StmtK:
      switch (t->kind.stmt)
      { case IfK:
          if (t->child[0]->type == Integer)
            typeError(t->child[0],"if test is not Boolean");
          break;
        case WhileK:
          if (t->child[0]->type == Integer)
            typeError(t->child[0],"while test is not Boolean");
          break;
        case CallK:
          if (t->child[0] != NULL) {
            if (t->child[0]->type != Integer)
              typeError(t->child[0],"Call parameter is not Integer");
            t = t->child[0];
            while (t->sibling != NULL) {
              if (t->type != Integer)
                typeError(t,"Call parameter is not Integer");
              t = t->sibling;
            }
          }
          break;
        case ReturnK:
          if (t->child[0] != NULL) {
            if (t->child[0]->type != Integer)
              typeError(t->child[0],"Return value is not Integer");
          }          
          break;
        case CompoundK:
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
