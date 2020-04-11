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
        if(var->isArray){
          emitRM("LDA",bx,-(st_lookup(var->attr.name,0)),gp,"get global array address");
        }
        else{
          emitRM("LDA",bx,-1-(st_lookup(var->attr.name,0)),gp,"get global address");
        }
        break;
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        if(var_lookup(var->attr.name,var->scope)->isParam)
        {
        	 if(var->isArray){
          		emitRM("LD",bx,2+(st_lookup(var->attr.name,var->scope)),bp,"get param array address");
       		 }
        	else
        	{
          		emitRM("LDA",bx,2+(st_lookup(var->attr.name,var->scope)),bp,"get param variable address");
        	}
        }
        else
        {
        	if(var->isArray ){
         		 emitRM("LDA",bx,-(st_lookup(var->attr.name,var->scope)),bp,"get local array address");
        	}
        	else{
          		emitRM("LDA",bx,-1-(st_lookup(var->attr.name,var->scope)),bp,"get local address");
        	}
        }
        break;

  }
}


/* Procedure genDec generates code at an declaration node */
static void genDec( TreeNode * tree)
{ /* Complete this function */

} /* genDec */




/* Procedure genStmt generates code at a statement node */
static void genStmt( TreeNode * tree)
{/* Complete this function */

} /* genStmt */

/* Procedure genExp generates code at an expression node */
static void genExp( TreeNode * tree)
{ /* Complete this function */
  
} /* genExp */

/* Procedure cGen recursively generates code by
 * tree traversal
 */
static void cGen( TreeNode * tree)
{ if (tree != NULL)
  { switch (tree->nodekind) {
      case StmtK:
        genStmt(tree);
        break;
      case ExpK:
        genExp(tree);
        break;
      case DecK:
        genDec(tree);  
      default:
        break;
    }
    if(isRecursive)
    cGen(tree->sibling);
  }
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
{  char * s = malloc(strlen(codefile)+7);
   BucketList fun;  /*function bucket */


   strcpy(s,"File: ");
   strcat(s,codefile);
   emitComment("C- Compilation to TM Code");
   emitComment(s);
   
   /* generate standard prelude */
   emitComment("Standard prelude:");
   emitRM("LD",gp,0,zero,"load maxaddress from location 0");
   emitRM("LDA",sp,syntaxTree->kind.dec!=FunK?-(syntaxTree->param_size):0,gp,"copy gp to sp &allocating global variables(if any)");
   emitRM("ST",zero,0,zero,"clear location 0");
   emitComment("End of standard prelude.");
   
   /*jump to main */
      if (TraceCode) emitComment("Jump to main()");
   int loc = emitSkip(6); /*A call consumes 5 instructions, change this as needed*/

   /*defining Input & output fuction as if they were in-built(global) */
   /* if only necessary  i,e. if they are used in program */ 
   fun = fun_lookup("input",0);
   if(fun!=NULL){
   if (TraceCode) emitComment("Begin input()");
   fun->fun_start = emitSkip(0);
   emitRO("IN",ax,0,0,"read input into ax");
   emitRM("LDA",sp,1,sp,"pop prepare");
   emitRM("LD",pc,-1,sp,"pop return addr");
   if (TraceCode) emitComment("End input()");
   }
   
   fun = fun_lookup("output",0);
   if(fun!=NULL){
   if (TraceCode) emitComment("Begin output()");
   fun->fun_start = emitSkip(0);
   emitRM("LD",ax,1,sp,"load param into ax");
   emitRO("OUT",ax,0,0,"output using ax");
   emitRM("LDA",sp,1,sp,"pop prepare");
   emitRM("LD",pc,-1,sp,"pop return addr");
   if (TraceCode) emitComment("End output()");
   }
   
   
   
   /* generate code for program */
   cGen(syntaxTree);
   /* finish */
   
    /* Fill up jump-to-main code */
   emitBackup(loc);
   fun = fun_lookup("main",0);
   if(fun==NULL)
   {
   	fprintf(stderr,"main not found\n");
   }
   
  emitRM("LDA",ax,3,pc,"store returned PC");
  emitRM("LDA",sp,-1,sp,"push prepare");
  emitRM("ST",ax,0,sp,"push returned PC");
  emitRM("LDC",pc,fun->fun_start,0,"jump to function");
  emitRM("LDA",sp,main_locals,sp,"release local var");
   
   
   emitComment("End of execution.");
   emitRO("HALT",0,0,0,"");
}

