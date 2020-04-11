/****************************************************/
/* File: cgen.c                                     */
/* The code generator implementation                */
/* for the EX compiler                              */
/* You must edit this to generate code in           */
/* WAT format                                       */
/*                                                  */
/****************************************************/

#include "globals.h"
#include "symtab.h"
#include "code.h"
#include "cgen.h"

/* to store local var of main 
*/
static int main_locals = 0;

/* getValue:
 * 1 - store value in ax
 * 0 - store address in bx
 */
static int getValue=1;

/* prototype for internal recursive code generator */
static void cGen (TreeNode * tree);


static int tmp;

/* isRecursive:
 * 1 - cGen will recurse on sibling
 * 0 - cGen won't recurse on sibling
 */
static int isRecursive = 1;

static int dataSize = 0;
static int memorySize = 1;

static int indentation = 4;

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

/* emit one instruction to get the address of a var,
 * store the address in bx,
 * we can access the var by bx[0]
 * Might help you understand what steps to take when generating code for each case
 * Edit to generate code for WAT instead
 */
void emitGetAddr(TreeNode *var)
{
  switch(var->scope){
    case 0:
        // char * s = (char *) malloc(strlen(tree->attr.name)+13);
        // strcpy(s,"local.set $");
        // strcat(s, tree->attr.name);
        // (st_lookup(var->attr.name,0))
        // emitRM();
        //emitRM("LDA",bx,-1-(st_lookup(var->attr.name,0)),gp,"get global address");
        break;
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    {
      char * s = (char *) malloc(strlen(var->attr.name)+13);
      strcpy(s,"local.set $");
      strcat(s, var->attr.name);
      emitRM(s, indentation, NULL, 1);
      break;
    }
  }
}

/* Procedure genDec generates code at an declaration node */
static void genDec( TreeNode * tree)
{ /* Complete this function */
  switch (tree->kind.dec)
  { 
    case VarK:
    {
      char * s = (char *) malloc(strlen(tree->attr.name)+14);
      strcpy(s, "(local $");
      strcat(s, tree->attr.name);
      strcat(s," i32)");
      emitRM(s, indentation, NULL, 1);
      break;
    }
    case ParameterK:
    {
      char * s = (char *) malloc(strlen(tree->attr.name)+15);
      strcpy(s," (param $");
      strcat(s, tree->attr.name);
      strcat(s, " i32)");
      emitRM(s, 1, NULL, 0);

      cGen(tree->child[0]);
      break;
    }
    case FunK:
    {
      char * s = (char *) malloc(strlen(tree->attr.name)+8);
      strcpy(s,"(func $");
      strcat(s, tree->attr.name);
      emitRM(s, indentation, NULL, 0);
      int i;
      cGen(tree->child[0]);
      indentation += 4;
      emitRM("\n", indentation, NULL, 0);
      cGen(tree->child[1]);
      indentation -= 4;
      emitRM(")", indentation, NULL, 1);

      cGen(tree->sibling);
      break;
    }
  }
} /* genDec */

/* Procedure genStmt generates code at a statement node */
static void genStmt( TreeNode * tree)
{/* Complete this function */
  switch (tree->kind.stmt)
  {
    case CallK:
    {
      cGen(tree->child[0]);
      char * s = (char *) malloc(strlen(tree->attr.name)+7);
      strcpy(s,"call $");
      strcat(s, tree->attr.name);
      emitRM(s, indentation, NULL, 1);
      break;
    }
    case ReturnK:
      break;
    case WhileK:
    {
      cGen(tree->child[0]);
      break;
    }
    case IfK:
    {
      cGen(tree->child[0]);
      break;
    }
    case IfElseK:
    {
      cGen(tree->child[0]);
      break;
    }
    case BreakK:
      break;
    case CompoundK:
    {
      cGen(tree->child[0]);
      break;
    }
    default:
      break;
  }

} /* genStmt */

/* Procedure genExp generates code at an expression node */
static void genExp( TreeNode * tree)
{ /* Complete this function */
  switch (tree->kind.exp)
  {
    case OpK:
    {
      switch(tree -> attr.op)
      {
        case '+':
          cGen(tree->child[0]);
          cGen(tree->child[1]);
          emitRM("i32.add", indentation, NULL, 1);          
          break;
        case '-':
          if(tree->child[1] == NULL)
          {
            emitRM("i32.const 0", indentation, NULL, 1);
            cGen(tree->child[0]);  
          }
          else
          {
            cGen(tree->child[0]);
            cGen(tree->child[1]);
          }
          emitRM("i32.sub", indentation, NULL, 1);  
          break;
        case '*':
          cGen(tree->child[0]);
          cGen(tree->child[1]);
          emitRM("i32.mut", indentation, NULL, 1); 
          break;
        case '/':
          cGen(tree->child[0]);
          cGen(tree->child[1]);
          emitRM("i32.div_s", indentation, NULL, 1); 
          break;
        case '%':
          cGen(tree->child[0]);
          cGen(tree->child[1]);
          emitRM("i32.mod_u", indentation, NULL, 1); 
          break;
        // case '!':
        //   break;
      }
      break;
    }
    case IdK:
    {
      char * s = (char *) malloc(strlen(tree->attr.name)+12);
      strcpy(s,"local.get $");
      strcat(s, tree->attr.name);
      emitRM(s, indentation, NULL, 1);
      break;
    }
    case ConstK:
    {
      char * s = (char *) malloc(strlen(tree->attr.val)+11);
      strcpy(s,"i32.const ");
      strcat(s, tree->attr.val);
      emitRM(s, indentation, NULL, 1);
      break;
    }
    case AssignK:
    {
      cGen(tree->child[0]);
      emitGetAddr(tree);      
      break;   
    }
  }
} /* genExp */

static void genLabel( TreeNode * tree )
{
  TreeNode * temp = tree;
  if( tree->kind.stmt == BlockK && tree->child[0] != NULL)
  {
    tree=tree->child[0];
    if(tree->nodekind == DecK && tree->kind.dec == VarK)
    {
      cGen(tree);
    }
    while(tree->sibling != NULL)
    {
      tree = tree->sibling;
      if(tree->nodekind == DecK && tree->kind.dec == VarK)
      {
        cGen(tree);
      }
    }
  }
  tree = temp;
  if( tree->child[0] != NULL)
  {
    tree=tree->child[0];
    if(tree->nodekind == DecK && tree->kind.dec == VarK)
    {
      ;
    }
    else
    {
      cGen(tree);
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
        cGen(tree);
      }
    }
  }
}

/* Procedure cGen recursively generates code by
 * tree traversal
 */
static void cGen( TreeNode * tree)
{ 
  if (tree != NULL)
  { switch (tree->nodekind) {
      case StmtK:
        printf("StmtK %s\n", tree->attr.name);
        genStmt(tree);
        break;
      case ExpK:
        if (tree->attr.name != NULL)
          printf("ExpK %s\n", tree->attr.name);
        else
          printf("ExpK %s\n", tree->attr.val);
        genExp(tree);
        break;
      case DecK:
        printf("DecK %s\n", tree->attr.name);
        genDec(tree);
        break;
      case LabelK:
        printf("LabelK\n");
        genLabel(tree);
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
   emitRM("(module", 0, NULL, 1);
   emitRM("(import \"host\" \"exit\" (func $exit))", 4, NULL, 1);
   emitRM("(import \"host\" \"getchar\" (func $getchar (result i32)))", 4, NULL, 1);

   // putchar
   emitRM("(import \"host\" \"putchar\" (func $putchar (param i32)))", 4, NULL, 1);

   // halt
   emitRM("(func $halt", 4, NULL, 1);
   emitRM("call $exit", 8, NULL, 1);
   emitRM(")", 4, NULL, 1);

   // printc
   emitRM("(func $printc (param $char i32)", 4, NULL, 1);
   emitRM("local.get $char", 8, NULL, 1); 
   emitRM("call $putchar", 8, NULL, 1); 
   emitRM(")", 4, NULL, 1);

   // prints
   emitRM("(func $prints (param $offset i32) (param $length i32)", 4, NULL, 1);
   emitRM("(local $I0 i32)", 8, NULL, 1);
   emitRM("i32.const 0", 8, NULL, 1);
   emitRM("local.set $I0", 8, NULL, 1);
   emitRM("(block $B1", 8, NULL, 1);
   emitRM("(loop $L1", 12, NULL, 1);
   emitRM("local.get $length", 16, NULL, 1);
   emitRM("local.get $I0", 16, NULL, 1);
   emitRM("i32.le_s", 16, NULL, 1);
   emitRM("br_if $B1", 16, NULL, 1);
   emitRM("local.get $offset", 16, NULL, 1);
   emitRM("local.get $I0", 16, NULL, 1);
   emitRM("i32.add", 16, NULL, 1);
   emitRM("i32.load", 16, NULL, 1);
   emitRM("call $printc", 16, NULL, 1);
   emitRM("local.get $I0", 16, NULL, 1);
   emitRM("i32.const 1", 16, NULL, 1);
   emitRM("i32.add", 16, NULL, 1);
   emitRM("local.set $I0", 16, NULL, 1);
   emitRM("br $L1", 16, NULL, 1);
   emitRM(")", 12, NULL, 1);
   emitRM(")", 8, NULL, 1);
   emitRM(")", 4, NULL, 1);

   // print b
   emitRM("(func $printb (param $b i32)", 4, NULL, 1);
   emitComment("select with 3rd operand 0 selects 2nd operand", 4);
   emitComment("select with 3rd operand 1 selects 1st operand", 4);
   emitRM("(local $I0 i32)", 8, NULL, 1);
   emitRM("i32.const 5", 8, NULL, 1);
   emitRM("i32.const 6", 8, NULL, 1);
   emitRM("local.get $b", 8, NULL, 1);
   emitRM("select", 8, NULL, 1);
   emitRM("local.set $I0", 8, NULL, 1);
   emitRM("i32.const 0", 8, NULL, 1);
   emitRM("i32.const 5", 8, NULL, 1);
   emitRM("local.get $b", 8, NULL, 1);
   emitRM("select", 8, NULL, 1);
   emitRM("local.get $I0", 8, NULL, 1);
   emitRM("call $prints", 8, NULL, 1);
   emitRM(")", 4, NULL, 1);

   // printi
   emitRM("(func $printi (param $n i32) (param $pow i32)", 4, NULL, 1); 
   emitRM("(block $B2", 8, NULL, 1); 
   emitRM("(loop $L2", 12, NULL, 1);
   emitRM("local.get $n", 16, NULL, 1);
   emitRM("i32.const 0", 16, NULL, 1);
   emitRM("i32.ge_s", 16, NULL, 1); 
   emitRM("br_if $B2", 16, NULL, 1);
   emitRM("local.get $n", 16, NULL, 1);
   emitRM("i32.const -1", 16, NULL, 1);
   emitRM("i32.mul", 16, NULL, 1);
   emitRM("local.set $n", 16, NULL, 1);
   emitRM("i32.const 45", 16, NULL, 1);
   emitRM("call $printc", 16, NULL, 1);
   emitRM(")", 12, NULL, 1);
   emitRM(")", 8, NULL, 1);
   emitRM("(block $B1", 8, NULL, 1);
   emitRM("(loop $L1", 12, NULL, 1);
   emitRM("i32.const 0", 16, NULL, 1);
   emitRM("local.get $pow", 16, NULL, 1);
   emitRM("i32.ge_s", 16, NULL, 1);
   emitRM("br_if $B1", 16, NULL, 1);
   emitRM("local.get $n", 16, NULL, 1);
   emitRM("local.get $pow", 16, NULL, 1);
   emitRM("i32.div_u", 16, NULL, 1);
   emitRM("i32.const 10", 16, NULL, 1);
   emitRM("i32.rem_u", 16, NULL, 1);
   emitRM("i32.const 48", 16, NULL, 1);
   emitRM("i32.add", 16, NULL, 1);
   emitRM("call $printc", 16, NULL, 1);
   emitRM("local.get $pow", 16, NULL, 1);
   emitRM("i32.const 10", 16, NULL, 1);
   emitRM("i32.div_u", 16, NULL, 1);
   emitRM("local.set $pow", 16, NULL, 1);
   emitRM("br $L1", 16, NULL, 1);
   emitRM(")", 12, NULL, 1);
   emitRM(")", 8, NULL, 1); 
   emitRM("i32.const 10", 8, "print newline character", 1);
   emitRM("call $printc", 8, NULL, 1); 
   emitRM(")", 4, NULL, 1); 

   emitComment("End of standard prelude.", 0);

   // Global Declarations
   // Function Declarations

   // Call main
   emitRM("(start $main)", 4, NULL, 1);

   // /*defining Input & output fuction as if they were in-built(global) */
   // /* if only necessary  i,e. if they are used in program */ 
   // fun = fun_lookup("input",0);
   // if(fun!=NULL){
   // if (TraceCode) emitComment("Begin input()");
   // fun->fun_start = emitSkip(0);
   // emitRO("IN",ax,0,0,"read input into ax");
   // emitRM("LDA",sp,1,sp,"pop prepare");
   // emitRM("LD",pc,-1,sp,"pop return addr");
   // if (TraceCode) emitComment("End input()");
   // }
   
   // fun = fun_lookup("output",0);
   // if(fun!=NULL){
   // if (TraceCode) emitComment("Begin output()");
   // fun->fun_start = emitSkip(0);
   // emitRM("LD",ax,1,sp,"load param into ax");
   // emitRO("OUT",ax,0,0,"output using ax");
   // emitRM("LDA",sp,1,sp,"pop prepare");
   // emitRM("LD",pc,-1,sp,"pop return addr");
   // if (TraceCode) emitComment("End output()");
   // }
   
  //  /* generate code for program */
   cGen(syntaxTree);
  //  /* finish */
   
  //   /* Fill up jump-to-main code */
  //  emitBackup(loc);
  //  fun = fun_lookup("main",0);
  //  if(fun==NULL)
  //  {
  //  	fprintf(stderr,"main not found\n");
  //  }
   
  // emitRM("LDA",ax,3,pc,"store returned PC");
  // emitRM("LDA",sp,-1,sp,"push prepare");
  // emitRM("ST",ax,0,sp,"push returned PC");
  // emitRM("LDC",pc,fun->fun_start,0,"jump to function");
  // emitRM("LDA",sp,main_locals,sp,"release local var");

  char * trueString = "\"true\\n\"";
  emitData(trueString, dataSize, NULL);
  dataSize += originalStringLength(trueString);

  char * falseString = "\"false\\n\"";
  emitData(falseString, dataSize, NULL);
  dataSize += originalStringLength(falseString);
   
  memorySize += dataSize / 65536;
   
  emitMemory(memorySize, NULL);

  emitRM(")", 0, NULL, 1);
      
  //emitComment("End of execution.", 0);
  //emitRO("HALT",0,0,0,"");
}

