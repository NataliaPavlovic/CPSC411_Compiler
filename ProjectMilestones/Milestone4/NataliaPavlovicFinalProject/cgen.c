// Natalia Pavlovic
// CPSC 411
// Milestone 4
// April 2020
// Code modified from EX Compiler from tutorial

// Code generator

#include "globals.h"
#include "symtab.h"
#include "code.h"
#include "cgen.h"
#include "analyze.h"

/* to store local var of main 
*/
static int main_locals = 0;

/* getValue:
 * 1 - store value in ax
 * 0 - store address in bx
 */
static int getValue=1;

/* prototype for internal recursive code generator */
static void cGen (TreeNode * tree, int output);

static void cGen_globalvars (TreeNode * tree, int output);

static int tmp;

/* isRecursive:
 * 1 - cGen will recurse on sibling
 * 0 - cGen won't recurse on sibling
 */
static int isRecursive = 1;

static int dataSize = 11;
static int memorySize = 1;

static int indentation = 4;
static int block_counter = 0;
static int loop_counter = 0;
static int current_loop_counter = 0;

/* stack used for call */
TreeNode* paramStack[10];
int top = 0;

/* stack routines*/
int pushParam(TreeNode* param)
{
    if(top == SIZE) 
      return 1;

    paramStack[top++] = param;
    return 0;
}

TreeNode* popParam()
{
  if(top == 0)
    return NULL;

  return paramStack[--top];
}  

/* Procedure genDec generates code at an declaration node */
static void genDec( TreeNode * tree, int output)
{ /* Complete this function */
  switch (tree->kind.dec)
  { 
    case VarK:
    {
      if(output)
      {
        if(tree->scope == 0)
        {
          char * s = (char *) malloc(strlen(tree->attr.name)+36);
          strcpy(s, "(global $G");
          strcat(s, tree->attr.name);
          strcat(s, " (mut i32) (i32.const 0))");
          emitInstruction(s, indentation, NULL, 1);
        }
        else
        {
          char * s = (char *) malloc(strlen(tree->attr.name)+15);
          strcpy(s, "(local $I");
          strcat(s, tree->attr.name);
          strcat(s," i32)");
          emitInstruction(s, indentation, NULL, 1);
        }
      }
      break;
    }
    case ParameterK:
    {
      if (output)
      {
        char * s = (char *) malloc(strlen(tree->attr.name)+16);
        strcpy(s," (param $I");
        strcat(s, tree->attr.name);
        strcat(s, " i32)");
        emitInstruction(s, 1, NULL, 0);
      }

      cGen(tree->child[0], output);
      break;
    }
    case FunK:
    {
      if (output)
      {
        block_counter = 0;
        loop_counter = 0;
        char * s = (char *) malloc(strlen(tree->attr.name)+8);
        strcpy(s,"(func $");
        strcat(s, tree->attr.name);
        emitInstruction(s, indentation, NULL, 0);
      }

      // int i;

      cGen(tree->child[0], output);

      if(output)
      {
        if(tree->type != Void)
        {
          emitInstruction("(result i32)", 1, NULL, 0);
        }
        indentation += 4;
        emitInstruction("\n", indentation, NULL, 0);
        emitInstruction("(local $T0 i32)", indentation, NULL, 1);
        emitInstruction("(local $T1 i32)", indentation, NULL, 1);
      }

      cGen(tree->child[1], output);

      if (output)
      {
        if(tree->type != Void)
        {
          emitInstruction("i32.const -1", indentation, NULL, 1);
          emitInstruction("return", indentation, NULL, 1);
        }
        indentation -= 4;
        emitInstruction(")", indentation, NULL, 1);
      }

      cGen(tree->sibling, output);
      break;
    }
  }
} /* genDec */

/* Procedure genStmt generates code at a statement node */
static void genStmt( TreeNode * tree, int output)
{/* Complete this function */
  switch (tree->kind.stmt)
  {
    case CallK:
    {
      cGen(tree->child[0], output);
      if(output)
      {
        char * s = (char *) malloc(strlen(tree->attr.name)+7);
        strcpy(s,"call $");
        strcat(s, tree->attr.name);
        emitInstruction(s, indentation, NULL, 1);
        if(tree->type != Void)
        {
          emitInstruction("local.set $T0", indentation, NULL, 1);
        }
        if(tree->output_return_value)
        {
          emitInstruction("local.get $T0", indentation, NULL, 1);
        }
      }
      break;
    }
    case ReturnK:
      cGen(tree->child[0], output);
      if (output)
      {
        emitInstruction("return", indentation, NULL, 1);
      }
      break;
    case WhileK:
    {
      if (output)
      {
        char * s = (char *) malloc(10);
        strcpy(s,"(block $B");
        emitNumberedLabel(s, indentation, block_counter, NULL, 1);
        indentation+=4;
        tree->if_block_counter = block_counter;
        block_counter++;
        char * l = (char *) malloc(9);
        strcpy(l,"(loop $L");
        emitNumberedLabel(l, indentation, loop_counter, NULL, 1);
        indentation+=4;
        tree->while_loop_counter = loop_counter;
        loop_counter++;
      }

      cGen(tree->child[0], output);

      if (output)
      {
        emitInstruction("i32.eqz", indentation, NULL, 1); 
        emitNumberedLabel("br_if $B", indentation, tree->if_block_counter, NULL, 1);
      }
      int restore_loop_counter = current_loop_counter;
      current_loop_counter = tree->if_block_counter;

      cGen(tree->child[1], output);

      if (output)
      {
        emitNumberedLabel("br $L", indentation, tree->while_loop_counter, NULL, 1);

        indentation-=4;
        emitInstruction(")", indentation, NULL, 1);
        indentation-=4;
        emitInstruction(")", indentation, NULL, 1);

        current_loop_counter = restore_loop_counter;
      }

      break;
    }
    case IfK:
    {
      if (output)
      {
        char * s = (char *) malloc(10);
        strcpy(s,"(block $B");
        emitNumberedLabel(s, indentation, block_counter, NULL, 1);
        indentation+=4;
        tree->if_block_counter = block_counter;
        block_counter++;
        cGen(tree->child[0], output);
        emitInstruction("i32.eqz", indentation, NULL, 1); 
        emitNumberedLabel("br_if $B", indentation, tree->if_block_counter, NULL, 1);
      }

      cGen(tree->child[1], output);

      if (output)
      {
        indentation-=4;
        emitInstruction(")", indentation, NULL, 1);
      }

      break;
    }
    case IfElseK:
    {
      if (output)
      {
        char * s = (char *) malloc(10);
        strcpy(s,"(block $B");
        emitNumberedLabel(s, indentation, block_counter, NULL, 1);
        indentation+=4;
        tree->ifelse_block_counter = block_counter;
        block_counter++;
        strcpy(s,"(block $B");
        emitNumberedLabel(s, indentation, block_counter, NULL, 1);
        indentation+=4;
        tree->if_block_counter = block_counter; 
        block_counter++;     
      }

      cGen(tree->child[0], output);

      if (output)
      {
        emitInstruction("i32.eqz", indentation, NULL, 1); 
        emitNumberedLabel("br_if $B", indentation, tree->if_block_counter, NULL, 1);
      }

      if(tree->child[2] != NULL)
      {
        cGen(tree->child[1], output);

        if (output)
        {
          emitNumberedLabel("br $B", indentation, tree->ifelse_block_counter, NULL, 1);
          indentation-=4;
          emitInstruction(")", indentation, NULL, 1);
        }

        cGen(tree->child[2], output);

        if(output)
        {
          indentation-=4;
          emitInstruction(")", indentation, NULL, 1);
        }
      }
      else
      {
        if (output)
        {
          emitNumberedLabel("br $B", indentation, tree->ifelse_block_counter, NULL, 1);
          indentation-=4;
          emitInstruction(")", indentation, NULL, 1);         
        }

        cGen(tree->child[1], output);

        if (output)
        {
          indentation-=4;
          emitInstruction(")", indentation, NULL, 1);
        }
      }
      break;
    }
    case IfElseIfK:
    {
      if(output)
      {
        char * s = (char *) malloc(10);
        strcpy(s,"(block $B");
        emitNumberedLabel(s, indentation, block_counter, NULL, 1);
        indentation+=4;;
        tree->ifelseif_block_counter = block_counter;
        block_counter++;

        TreeNode * temp = tree;

        // Set block counter for outer block for all elseif nodes
        if (tree->child[2] != NULL) {
          tree->child[2]->ifelseif_block_counter = tree->ifelseif_block_counter;
          tree = tree->child[2];
          while(tree->sibling != NULL)
          {
            tree->sibling->ifelseif_block_counter = tree->ifelseif_block_counter;
            tree = tree->sibling;
          }
        }

        tree = temp;

        // if block
        strcpy(s,"(block $B");
        emitNumberedLabel(s, indentation, block_counter, NULL, 1);
        indentation+=4;
        tree->if_block_counter = block_counter;
        block_counter++;     
      }

      cGen(tree->child[0], output);

      if (output)
      {
        emitInstruction("i32.eqz", indentation, NULL, 1); 
        emitNumberedLabel("br_if $B", indentation, tree->if_block_counter, NULL, 1);
      }

      cGen(tree->child[1], output);

      if (output)
      {
        emitNumberedLabel("br $B", indentation, tree->ifelseif_block_counter, NULL, 1);

        indentation-=4;
        emitInstruction(")", indentation, NULL, 1);
      }

      cGen(tree->child[2], output);

      if(output)
      {
        indentation-=4;
        emitInstruction(")", indentation, NULL, 1);
      }
      break;
    }
    case IfElseIfElseK:
    {
      if (output)
      {
        char * s = (char *) malloc(10);
        strcpy(s,"(block $B");
        emitNumberedLabel(s, indentation, block_counter, NULL, 1);
        indentation+=4;;
        tree->ifelseif_block_counter = block_counter;
        block_counter++;

        TreeNode * temp = tree;

        // Set block counter for outer block for all elseif nodes
        if (tree->child[2] != NULL) {
          tree->child[2]->ifelseif_block_counter = tree->ifelseif_block_counter;
          tree = tree->child[2];
          while(tree->sibling != NULL)
          {
            tree->sibling->ifelseif_block_counter = tree->ifelseif_block_counter;
            tree = tree->sibling;
          }
        }

        tree = temp;

        // if block
        strcpy(s,"(block $B");
        emitNumberedLabel(s, indentation, block_counter, NULL, 1);
        indentation+=4;
        tree->if_block_counter = block_counter; 
        block_counter++;           
      }

      cGen(tree->child[0], output);

      if (output)
      {
        emitInstruction("i32.eqz", indentation, NULL, 1); 
        emitNumberedLabel("br_if $B", indentation, tree->if_block_counter, NULL, 1);
      }

      cGen(tree->child[1], output);

      if (output)
      {
        emitNumberedLabel("br $B", indentation, tree->ifelseif_block_counter, NULL, 1);

        indentation-=4;
        emitInstruction(")", indentation, NULL, 1); 
      }

      cGen(tree->child[2], output);
      cGen(tree->child[3], output);

      if (output)
      {
        indentation-=4;
        emitInstruction(")", indentation, NULL, 1);      
      }

      break;
    }
    case ElseIfK:
    {
      if (output)
      {
        char * s = (char *) malloc(10);
        strcpy(s,"(block $B");
        emitNumberedLabel(s, indentation, block_counter, NULL, 1);
        indentation+=4;
        tree->if_block_counter = block_counter;
        block_counter++;
      }
      
      cGen(tree->child[0], output);

      if (output)
      {
        emitInstruction("i32.eqz", indentation, NULL, 1); 
        emitNumberedLabel("br_if $B", indentation, tree->if_block_counter, NULL, 1);      
      }

      cGen(tree->child[1], output);

      if (output)
      {
        emitNumberedLabel("br $B", indentation, tree->ifelseif_block_counter, NULL, 1);
        
        indentation-=4;
        emitInstruction(")", indentation, NULL, 1);        
      }

      cGen(tree->sibling, output);
      break;
    }
    case BreakK:
      if(output)
      {
        emitNumberedLabel("br $B", indentation, current_loop_counter, NULL, 1);
      }
      break;
    case CompoundK:
    {
      if(tree->child[0] != NULL)
      {
        cGen(tree->child[0], output);
        tree=tree->child[0], output;
        while(tree->sibling != NULL)
        {
          cGen(tree->sibling, output);
          tree=tree->sibling;
        }
      }

      break;
    }
    default:
      break;
  }

} /* genStmt */

/* Procedure genExp generates code at an expression node */
static void genExp( TreeNode * tree, int output)
{ /* Complete this function */
  switch (tree->kind.exp)
  {
    case OpK:
    {
      switch(tree -> attr.op)
      {
        case '+':
          cGen(tree->child[0], output);
          cGen(tree->child[1], output);
          if(output)
          {
            emitInstruction("i32.add", indentation, NULL, 1);          
          }
          break;
        case '-':
          if(tree->child[1] == NULL)
          {
            if(output)
            {
              emitInstruction("i32.const 0", indentation, NULL, 1);
            }
            cGen(tree->child[0], output);  
          }
          else
          {
            cGen(tree->child[0], output);
            cGen(tree->child[1], output);
          }
          if (output)
          {
            emitInstruction("i32.sub", indentation, NULL, 1);              
          }
          break;
        case '*':
          cGen(tree->child[0], output);
          cGen(tree->child[1], output);
          if (output)
          {
            emitInstruction("i32.mul", indentation, NULL, 1);            
          }
          break;
        case '/':
          cGen(tree->child[0], output);
          cGen(tree->child[1], output);
          if (output)
          {
            emitInstruction("i32.div_s", indentation, NULL, 1);             
          }
          break;
        case '%':
          cGen(tree->child[0], output);
          cGen(tree->child[1], output);
          if (output)
          {
            emitInstruction("i32.rem_u", indentation, NULL, 1);             
          }
          break;
        case '!':
          cGen(tree->child[0], output);
          if (output)
          {
            emitInstruction("i32.const 1", indentation, NULL, 1); 
            emitInstruction("i32.xor", indentation, NULL, 1);            
          }
          break;
        case '>':
          cGen(tree->child[0], output);
          cGen(tree->child[1], output); 
          if (output)
          {
            emitInstruction("i32.gt_s", indentation, NULL, 1);
          }         
          break;
        case '<':
          cGen(tree->child[0], output);
          cGen(tree->child[1], output); 
          if (output)
          {
            emitInstruction("i32.lt_s", indentation, NULL, 1);             
          }         
          break;
        case AND:
        {
          if (output)
          {
            char * s = (char *) malloc(10);
            strcpy(s,"(block $B");
            emitNumberedLabel(s, indentation, block_counter, NULL, 1);
            indentation+=4;
            tree->logic_block = block_counter;
            block_counter++; 
          }
          cGen(tree->child[0], output);
          if (output)
          {
            emitInstruction("local.set $T1", indentation, NULL, 1);
            emitInstruction("local.get $T1", indentation, NULL, 1);
            emitInstruction("i32.eqz", indentation, NULL, 1);   
            emitNumberedLabel("br_if $B", indentation, tree->logic_block, NULL, 1);                                         
            emitInstruction("local.get $T1", indentation, NULL, 1);                      
          }
          cGen(tree->child[1], output);
          if (output)
          {
            emitInstruction("i32.and", indentation, NULL, 1); 
            emitInstruction("local.set $T1", indentation, NULL, 1);
            indentation-=4;
            emitInstruction(")", indentation, NULL, 1);  
            emitInstruction("local.get $T1", indentation, NULL, 1);                       
          }
          break;
        }
        case OR:
        {
          if (output)
          {
            char * s = (char *) malloc(10);
            strcpy(s,"(block $B");
            emitNumberedLabel(s, indentation, block_counter, NULL, 1);
            indentation+=4;
            tree->logic_block = block_counter;
            block_counter++; 
          }
          cGen(tree->child[0], output);
          if (output)
          {
            emitInstruction("local.set $T1", indentation, NULL, 1);
            emitInstruction("local.get $T1", indentation, NULL, 1);       
            emitInstruction("i32.const 1", indentation, NULL, 1);
            emitInstruction("i32.eq", indentation, NULL, 1);   
            emitNumberedLabel("br_if $B", indentation, tree->logic_block, NULL, 1);                                         
            emitInstruction("local.get $T1", indentation, NULL, 1);                      
          }
          cGen(tree->child[1], output);
          if (output)
          {
            emitInstruction("i32.or", indentation, NULL, 1);   
            emitInstruction("local.set $T1", indentation, NULL, 1);
            indentation-=4;
            emitInstruction(")", indentation, NULL, 1);  
            emitInstruction("local.get $T1", indentation, NULL, 1);       
          }
          break;
        }
        case LE:
          cGen(tree->child[0], output);
          cGen(tree->child[1], output); 
          if (output)
          {
            emitInstruction("i32.le_s", indentation, NULL, 1);             
          }         
          break;
        case GE:
          cGen(tree->child[0], output);
          cGen(tree->child[1], output);
          if (output)
          {
            emitInstruction("i32.ge_s", indentation, NULL, 1);             
          }          
          break;
        case EQ:
          cGen(tree->child[0], output);
          cGen(tree->child[1], output); 
          if (output)
          {
            emitInstruction("i32.eq", indentation, NULL, 1);             
          }         
          break;
        case NQ:
          cGen(tree->child[0], output);
          cGen(tree->child[1], output);
          if (output)
          {
            emitInstruction("i32.ne", indentation, NULL, 1);             
          }          
          break;
      }
      break;
    }
    case IdK:
    {
      if (output)
      {
        if(tree->scope == 0)
        {
          char * s = (char *) malloc(strlen(tree->attr.name)+14);
          strcpy(s,"global.get $G");
          strcat(s, tree->attr.name);
          emitInstruction(s, indentation, NULL, 1);
        }
        else
        {
          char * s = (char *) malloc(strlen(tree->attr.name)+13);
          strcpy(s,"local.get $I");
          strcat(s, tree->attr.name);
          emitInstruction(s, indentation, NULL, 1);
        }
      }
      break;
    }
    case ConstK:
    {
      if(tree->type == Integer)
      {
        if(output)
        {
          char * s = (char *) malloc(strlen(tree->attr.val)+11);
          strcpy(s,"i32.const ");
          strcat(s, tree->attr.val);
          emitInstruction(s, indentation, NULL, 1);
        }
      }
      else if(tree->type == Boolean)
      {
        if(output)
        {
          if(!strcmp(tree->attr.val,"true"))
          {
            emitInstruction("i32.const 1", indentation, NULL, 1);
          }
          else if(!strcmp(tree->attr.val,"false"))
          {
            emitInstruction("i32.const 0", indentation, NULL, 1);
          }         
        }
      }
      // String
      else
      {
        if(output)
        {
          emitNumberedLabel("i32.const ", indentation, dataSize, NULL, 1);
          emitNumberedLabel("i32.const ", indentation, strlen(tree->attr.val), NULL, 1);
          tree->string_offset = dataSize;
          dataSize += strlen(tree->attr.val) + 4;
        }
        else
        {
          char * s = (char *) malloc(strlen(tree->attr.val)+3);
          strcpy(s, "\"");
          strcat(s, tree->attr.val);
          strcat(s, "\"");
          emitData(s, tree->string_offset, NULL);
        }
      }
      break;
    }
    case AssignK:
    {
      cGen(tree->child[0], output);
      if (output)
      {
        if(tree->child[0] != NULL && tree->child[0]->nodekind == ExpK && tree->child[0]->kind.exp == ConstK )
        {
          ;
        } 
        else if(tree->child[0] != NULL && tree->child[0]->nodekind == StmtK && tree->child[0]->kind.stmt == CallK )
        {
          emitInstruction("local.get $T0", indentation, NULL, 1); 
        } 
        else if(tree->child[0] != NULL && tree->child[0]->nodekind == ExpK && tree->child[0]->kind.exp == AssignK )
        {
          char * s2 = (char *) malloc(strlen(tree->attr.name)+14);
          if(tree->child[0]->scope == 0)
          {
            strcpy(s2,"global.get $G");       
          }
          else
          {
            strcpy(s2,"local.get $I");       
          }
          strcat(s2, tree->child[0]->attr.name);
          emitInstruction(s2, indentation, NULL, 1); 
        }

        if(tree->scope == 0)
        {
          char * s = (char *) malloc(strlen(tree->attr.name)+14);
          strcpy(s,"global.set $G");
          strcat(s, tree->attr.name);
          emitInstruction(s, indentation, NULL, 1);
          if(tree->output_return_value == 1)
          {
            char * s2 = (char *) malloc(strlen(tree->attr.name)+14);
            strcpy(s2,"global.get $G");
            strcat(s2, tree->attr.name);
            emitInstruction(s2, indentation, NULL, 1);          
          }
        } 
        else
        {
          char * s = (char *) malloc(strlen(tree->attr.name)+13);
          strcpy(s,"local.set $I");
          strcat(s, tree->attr.name);
          emitInstruction(s, indentation, NULL, 1);
          if(tree->output_return_value == 1)
          {
            char * s2 = (char *) malloc(strlen(tree->attr.name)+13);
            strcpy(s2,"local.get $I");
            strcat(s2, tree->attr.name);
            emitInstruction(s2, indentation, NULL, 1);
          }
        } 
      }
      break;   
    }
  }
} /* genExp */

static void genLabel( TreeNode * tree, int output )
{
  TreeNode * temp = tree;
  if( tree->kind.stmt == BlockK && tree->child[0] != NULL)
  {
    tree=tree->child[0], output;
    if(tree->nodekind == DecK && tree->kind.dec == VarK)
    {
      cGen(tree, output);
    }
    while(tree->sibling != NULL)
    {
      tree = tree->sibling;
      if(tree->nodekind == DecK && tree->kind.dec == VarK)
      {
        cGen(tree, output);
      }
    }
  }
  tree = temp;
  if( tree->child[0] != NULL)
  {
    tree=tree->child[0], output;
    if(tree->nodekind == DecK && tree->kind.dec == VarK)
    {
      ;
    }
    else
    {
      cGen(tree, output);
    }
    while(tree->sibling != NULL)
    {
      tree = tree->sibling;
      if(tree->nodekind == DecK && tree->kind.dec == VarK)
      {
        ;
      }
      else
      {
        cGen(tree, output);
      }
    }
  }
}

/* Procedure cGen recursively generates code by
 * tree traversal
 */
static void cGen( TreeNode * tree, int output)
{ 
  if (tree != NULL)
  { switch (tree->nodekind) {
      case StmtK:
        genStmt(tree, output);
        break;
      case ExpK:
        genExp(tree, output);
        break;
      case DecK:
      {
        if( tree->kind.dec == VarK && tree->scope == 0)
        {
          cGen(tree->sibling, output);
        }
        else
        {
          genDec(tree, output);
        }
        break;
      }
      case LabelK:
        genLabel(tree, output);
        break;
      default:
        break;
    }
  }
}

static void cGen_globalvars( TreeNode * tree, int output)
{ 
  if (tree != NULL)
  { switch (tree->nodekind) {
      case DecK:
      {
        if( tree->kind.dec == VarK && tree->scope == 0)
        {
          genDec(tree, output);
        }
        cGen_globalvars(tree->sibling, output);
        break;
      }
      default:
        break;
    }
  }
}

static void outputStringData( TreeNode * tree, int output)
{ 
  if (tree != NULL)
  { switch (tree->nodekind) {
      case StmtK:
        genStmt(tree, output);
        break;
      case ExpK:
        genExp(tree, output);
        break;
      case DecK:
      {
        if( tree->kind.dec == VarK && tree->scope == 0)
        {
          cGen(tree->sibling, output);
        }
        else
        {
          genDec(tree, output);
        }
        break;
      }
      case LabelK:
        genLabel(tree, output);
        break;
      default:
        break;
    }
  }
}

int originalStringLength(char * c)
{
   int len = strlen(c);
   int addedCharacters = 0;
   for (int i = 0; i < len; i++)
   {
      if(c[i] == '\"' || c[i] == '\\')
      {
        addedCharacters++;
      }
   }

   return (len - addedCharacters);
}

/**********************************************/
/* the primary function of the code generator */
/**********************************************/
/* Procedure codeGen generates code to a code
 * file by traversal of the syntax tree. The
 * second parameter (codefile) is the file name
 * of the code file, and is used to print the
 * file name as a comment in the code file
 *
 * Edit this to output code in WAT instead
 * The code in the function below may be useful
 * to understand how to start off but will need
 * to be replaced with instructions to generate WAT code
 */
void codeGen(TreeNode * syntaxTree, char * codefile)
{  
   char * s = malloc(strlen(codefile)+7);
   BucketList fun;  /*function bucket */

   strcpy(s,"File: ");
   strcat(s,codefile);
   emitComment("C Compilation to J-- Code", 0);
   emitComment(s, 0);

   /* generate standard prelude */
   emitComment("Standard prelude:", 0);
   emitInstruction("(module", 0, NULL, 1);
   // exit
   if(!halt_redefined)
   {
     emitInstruction("(import \"host\" \"exit\" (func $exit))", 4, NULL, 1);
   }
   // getchar
   if(!getchar_redefined)
   {
     emitInstruction("(import \"host\" \"getchar\" (func $getchar (result i32)))", 4, NULL, 1);
   }

   // putchar
   if(!printc_redefined)
   {
     emitInstruction("(import \"host\" \"putchar\" (func $putchar (param i32)))", 4, NULL, 1);
   }

   // halt
   if(!halt_redefined)
   {
     emitInstruction("(func $halt", 4, NULL, 1);
     emitInstruction("call $exit", 8, NULL, 1);
     emitInstruction(")", 4, NULL, 1);
   }
  
   // printc
   if(!printc_redefined)
   {
     emitInstruction("(func $printc (param $char i32)", 4, NULL, 1);
     emitInstruction("local.get $char", 8, NULL, 1); 
     emitInstruction("call $putchar", 8, NULL, 1); 
     emitInstruction(")", 4, NULL, 1);
   }

   // prints
   if(!prints_redefined)
   {
     emitInstruction("(func $prints (param $offset i32) (param $length i32)", 4, NULL, 1);
     emitInstruction("(local $I0 i32)", 8, NULL, 1);
     emitInstruction("i32.const 0", 8, NULL, 1);
     emitInstruction("local.set $I0", 8, NULL, 1);
     emitInstruction("(block $B1", 8, NULL, 1);
     emitInstruction("(loop $L1", 12, NULL, 1);
     emitInstruction("local.get $length", 16, NULL, 1);
     emitInstruction("local.get $I0", 16, NULL, 1);
     emitInstruction("i32.le_s", 16, NULL, 1);
     emitInstruction("br_if $B1", 16, NULL, 1);
     emitInstruction("local.get $offset", 16, NULL, 1);
     emitInstruction("local.get $I0", 16, NULL, 1);
     emitInstruction("i32.add", 16, NULL, 1);
     emitInstruction("i32.load", 16, NULL, 1);
     emitInstruction("call $printc", 16, NULL, 1);
     emitInstruction("local.get $I0", 16, NULL, 1);
     emitInstruction("i32.const 1", 16, NULL, 1);
     emitInstruction("i32.add", 16, NULL, 1);
     emitInstruction("local.set $I0", 16, NULL, 1);
     emitInstruction("br $L1", 16, NULL, 1);
     emitInstruction(")", 12, NULL, 1);
     emitInstruction(")", 8, NULL, 1);
     emitInstruction(")", 4, NULL, 1);
   }

   // print b
   if(!printb_redefined)
   {
     emitInstruction("(func $printb (param $b i32)", 4, NULL, 1);
     emitComment("select with 3rd operand 0 selects 2nd operand", 4);
     emitComment("select with 3rd operand 1 selects 1st operand", 4);
     emitInstruction("(local $I0 i32)", 8, NULL, 1);
     emitInstruction("i32.const 5", 8, NULL, 1);
     emitInstruction("i32.const 6", 8, NULL, 1);
     emitInstruction("local.get $b", 8, NULL, 1);
     emitInstruction("select", 8, NULL, 1);
     emitInstruction("local.set $I0", 8, NULL, 1);
     emitInstruction("i32.const 0", 8, NULL, 1);
     emitInstruction("i32.const 5", 8, NULL, 1);
     emitInstruction("local.get $b", 8, NULL, 1);
     emitInstruction("select", 8, NULL, 1);
     emitInstruction("local.get $I0", 8, NULL, 1);
     emitInstruction("call $prints", 8, NULL, 1);
     emitInstruction(")", 4, NULL, 1);
   }

   // printi
   if(!printi_redefined)
   {
     emitInstruction("(func $printi (param $n i32)", 4, NULL, 1); 
     emitInstruction("(local $I0 i32)", 8, NULL, 1);
     emitInstruction("(local $I1 i32)", 8, NULL, 1);
     emitInstruction("(block $B5", 8, NULL, 1);
     emitInstruction("local.get $n", 12, NULL, 1);
     emitInstruction("i32.const 0", 12, NULL, 1);
     emitInstruction("i32.ne", 12, NULL, 1);
     emitInstruction("br_if $B5", 12, NULL, 1);
     emitInstruction("i32.const 48", 12, NULL, 1);
     emitInstruction("call $printc", 12, NULL, 1);
     emitInstruction("return", 12, NULL, 1);
     emitInstruction(")", 8, NULL, 1);
     emitInstruction("i32.const 1000000000", 12, NULL, 1);
     emitInstruction("local.set $I0", 12, NULL, 1);
     emitInstruction("(block $B0", 12, NULL, 1);
     emitInstruction("(loop $L0", 12, NULL, 1);
     emitInstruction("local.get $n", 16, NULL, 1);
     emitInstruction("local.get $I0", 16, NULL, 1);
     emitInstruction("i32.div_s", 16, NULL, 1);
     emitInstruction("i32.const 0", 16, NULL, 1);
     emitInstruction("i32.gt_u", 16, NULL, 1);
     emitInstruction("br_if $B0", 16, NULL, 1);
     emitInstruction("local.get $I0", 16, NULL, 1);
     emitInstruction("i32.const 10", 16, NULL, 1);
     emitInstruction("i32.div_s", 16, NULL, 1);
     emitInstruction("local.set $I0", 16, NULL, 1);
     emitInstruction("br $L0", 16, NULL, 1);
     emitInstruction(")", 12, NULL, 1);
     emitInstruction(")", 8, NULL, 1);

     emitInstruction("(block $B2", 8, NULL, 1); 
     emitInstruction("(loop $L2", 12, NULL, 1);
     emitInstruction("local.get $n", 16, NULL, 1);
     emitInstruction("i32.const 0", 16, NULL, 1);
     emitInstruction("i32.ge_s", 16, NULL, 1); 
     emitInstruction("br_if $B2", 16, NULL, 1);
     emitInstruction("i32.const 45", 16, NULL, 1);
     emitInstruction("call $printc", 16, NULL, 1);
     emitInstruction(")", 12, NULL, 1);
     emitInstruction(")", 8, NULL, 1);
     emitInstruction("(block $B1", 8, NULL, 1);
     emitInstruction("(loop $L1", 12, NULL, 1);
     emitInstruction("local.get $I0", 16, NULL, 1);
     emitInstruction("i32.eqz", 16, NULL, 1);
     emitInstruction("br_if $B1", 16, NULL, 1);
     emitInstruction("local.get $n", 16, NULL, 1);
     emitInstruction("local.get $I0", 16, NULL, 1);
     emitInstruction("i32.div_s", 16, NULL, 1);
     emitInstruction("local.set $I1", 16, NULL, 1);
     emitInstruction("(block $B3", 16, NULL, 1);
     emitInstruction("local.get $I1", 20, NULL, 1);
     emitInstruction("i32.const 0", 20, NULL, 1);
     emitInstruction("i32.gt_s", 20, NULL, 1);
     emitInstruction("br_if $B3", 20, NULL, 1);
     emitInstruction("i32.const 0", 20, NULL, 1);
     emitInstruction("local.get $I1", 20, NULL, 1);
     emitInstruction("i32.sub", 20, NULL, 1);
     emitInstruction("local.set $I1", 20, NULL, 1);
     emitInstruction(")", 16, NULL, 1);
     emitInstruction("local.get $I1", 16, NULL, 1);
     emitInstruction("i32.const 10", 16, NULL, 1);
     emitInstruction("i32.rem_u", 16, NULL, 1);
     emitInstruction("i32.const 48", 16, NULL, 1);
     emitInstruction("i32.add", 16, NULL, 1);
     emitInstruction("call $printc", 16, NULL, 1);
     emitInstruction("local.get $I0", 16, NULL, 1);
     emitInstruction("i32.const 10", 16, NULL, 1);
     emitInstruction("i32.div_s", 16, NULL, 1);
     emitInstruction("local.set $I0", 16, NULL, 1);
     emitInstruction("br $L1", 16, NULL, 1);
     emitInstruction(")", 12, NULL, 1);
     emitInstruction(")", 8, NULL, 1); 
     emitInstruction(")", 4, NULL, 1); 
   }

   emitComment("End of standard prelude.", 0);

   //  /* generate code for program */
    cGen_globalvars(syntaxTree, 1);
    cGen(syntaxTree, 1);
   //  /* finish */

   // Call main
  if(main_replacement_counter == 1 && count_main == 0)
  {
    char * s = (char *) malloc(strlen(functionDeclarations[main_replacement_index].function_name)+10);
    strcpy(s,"(start $");
    strcat(s, functionDeclarations[main_replacement_index].function_name);
    strcat(s, ")");
    emitInstruction(s, 4, NULL, 1);
  }
  else
  {
    emitInstruction("(start $main)", 4, NULL, 1);
  }

  // Output string data
  char * trueString = "\"true\"";
  emitData(trueString, 0, NULL);

  char * falseString = "\"false\"";
  emitData(falseString, 5, NULL);

  outputStringData(syntaxTree, 0);

  // Output memory required
  memorySize += dataSize / 65536;
   
  emitMemory(memorySize, NULL);

  emitInstruction(")", 0, NULL, 1);
}

