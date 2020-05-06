// Natalia Pavlovic
// CPSC 411
// Milestone 2
// March 2020
// Code modified from EX Compiler from tutorial
// Code Extracts From: Kenneth C. Louden

#include "globals.h"
#include "util.h"

//Prints tokens and lexeme to output
void printToken( TokenType token, const char* tokenString ) {
  switch (token) {
    //Reserved Words
    case INT:
    case BOOLEAN:
    case VOID:
    case IF:
    case ELSE:
    case WHILE:
    case RETURN:
    case BREAK:
    case TRUE:
    case FALSE:
      //Carries Over for all Reserved Words
      fprintf(output,
         "%d: Reserved Word: %s\n", lineno, tokenString);
      break;
    //Operation/Special Symbols 
    case LE: fprintf(output, "%d: Special Symbol: <=\n", lineno); break;
    case GT: fprintf(output, "%d: Special Symbol: >\n", lineno); break;
    case GE: fprintf(output, "%d: Special Symbol: >=\n", lineno); break;
    case EQ: fprintf(output,"%d: Special Symbol: ==\n", lineno); break;
    case NE: fprintf(output,"%d: Special Symbol: !=\n", lineno); break;
    case AND: fprintf(output,"%d: Special Symbol: &&\n", lineno); break;
    case OR: fprintf(output,"%d: Special Symbol: ||\n", lineno); break;
    case ';': fprintf(output,"%d: Special Symbol: ;\n", lineno); break;
    case ',': fprintf(output,"%d: Special Symbol: ,\n", lineno); break;
    case '(': fprintf(output,"%d: Special Symbol: (\n", lineno); break;
    case ')': fprintf(output,"%d: Special symbl: )\n", lineno); break;
    case '{': fprintf(output,"%d: Special Symbol: {\n", lineno); break;
    case '}': fprintf(output,"%d: Special Symbol: }\n", lineno); break;
    case '+': fprintf(output,"%d: Special Symbol: +\n", lineno); break;
    case '-': fprintf(output,"%d: Special Symbol: -\n", lineno); break;
    case '*': fprintf(output,"%d: Special Symbol: *\n", lineno); break;
    case '/': fprintf(output,"%d: Special Symbol: /\n", lineno); break;
    case '%': fprintf(output,"%d: Special Symbol: %%\n", lineno); break;
    case '<': fprintf(output,"%d: Special Symbol: <\n", lineno); break;
    case '>': fprintf(output,"%d: Special Symbol: >\n", lineno); break;
    case '=': fprintf(output,"%d: Special Symbol: =\n", lineno); break;
    case '!': fprintf(output,"%d: Special Symbol: !\n", lineno); break;

    //EOF
    case ENDFILE: fprintf(output,"%d: End Of File\n", lineno); break;
    
    //Numbers
    case NUMBER:
      fprintf(output,
          "%d: NUMBER, val= %s\n", lineno, tokenString);
      break;
    
    //Identifiers    
    case ID:
      fprintf(output,
          "%d: ID, name= %s\n", lineno, tokenString);
      break;
    //Error  
    case ERROR:
      fprintf(output,
          "%d: ERROR: %s\n", lineno, tokenString);
      break;
      
    default:
      fprintf(output,"%d: Unknown token: %c\n", lineno, token);
  }
}

//Prints tokens, lexeme and line numbers to for operators
void printOperators( TokenType token, const char* tokenString, TreeNode *tree ) {
  switch (token) {
    //Reserved Words
    case INT:
    case BOOLEAN:
    case VOID:
    case IF:
    case ELSE:
    case WHILE:
    case RETURN:
    case BREAK:
    case TRUE:
    case FALSE:
      //Carries Over for all Reserved Words
      fprintf(output,
         "%d: Reserved Word: %s\n", tree->lineno, tokenString);
      break;
    //Operation/Special Symbols 
    case LE: fprintf(output, "<= at line %d", tree->lineno); break;
    case GT: fprintf(output, "> at line %d", tree->lineno); break;
    case GE: fprintf(output, ">= at line %d", tree->lineno); break;
    case EQ: fprintf(output,"== at line %d", tree->lineno); break;
    case NE: fprintf(output,"!= at line %d", tree->lineno); break;
    case AND: fprintf(output,"&& at line %d", tree->lineno); break;
    case OR: fprintf(output,"|| at line %d", tree->lineno); break;
    case ';': fprintf(output,"; at line %d", tree->lineno); break;
    case ',': fprintf(output,", at line %d", tree->lineno); break;
    case '(': fprintf(output,"( at line %d", tree->lineno); break;
    case ')': fprintf(output,") at line %d", tree->lineno); break;
    case '{': fprintf(output,"{ at line %d", tree->lineno); break;
    case '}': fprintf(output,"} at line %d", tree->lineno); break;
    case '+': fprintf(output,"+ at line %d", tree->lineno); break;
    case '-': fprintf(output,"- at line %d", tree->lineno); break;
    case '*': fprintf(output,"* at line %d", tree->lineno); break;
    case '/': fprintf(output,"/ at line %d", tree->lineno); break;
    case '%': fprintf(output,"%% at line %d", tree->lineno); break;
    case '<': fprintf(output,"< at line %d", tree->lineno); break;
    case '>': fprintf(output,"> at line %d", tree->lineno); break;
    case '=': fprintf(output,"= at line %d", tree->lineno); break;
    case '!': fprintf(output,"! at line %d", tree->lineno); break;

    //EOF
    case ENDFILE: fprintf(output,"%d: End Of File\n", tree->lineno); break;
    
    //Numbers
    case NUMBER:
      fprintf(output,
          "%d: NUMBER, val= %s\n", tree->lineno, tokenString);
      break;
    
    //Identifiers    
    case ID:
      fprintf(output,
          "%d: ID, name= %s\n", tree->lineno, tokenString);
      break;
    //Error  
    case ERROR:
      fprintf(output,
          "%d: ERROR: %s\n", tree->lineno, tokenString);
      break;
      
    default:
      fprintf(output,"%d: Unknown token: %c\n", tree->lineno, token);
  }
}

//Creates a new Statement Node for AST
TreeNode * newStmtNode(StmtKind kind) {
  TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
  
  int i;
  
  if (t == NULL)
    fprintf(output,"Out of memory error at line %d\n", lineno);
  
  else {
    for (i=0;i<MAXCHILDREN;i++) 
      t->child[i] = NULL;
    t->sibling = NULL;
    t->nodekind = StmtK;
    t->kind.stmt = kind;
    t->lineno = lineno;
  }
  return t;
}

//Creates a new Expression Node for AST
TreeNode * newExpNode(ExpKind kind) {
  TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
  
  int i;
  
  if (t == NULL)
    fprintf(output,"Out of memory error at line %d\n", lineno);
  
  else {
    for (i=0;i<MAXCHILDREN;i++)
      t->child[i] = NULL;
    t->sibling = NULL;
    t->nodekind = ExpK;
    t->kind.exp = kind;
    t->lineno = lineno;
    t->type = Void;
  }
  return t;
}

//Creates a new Declaration Node for AST
TreeNode * newDecNode(DecKind kind) {
  TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
  
  int i;
  
  if (t == NULL)
    fprintf(output,"Out of memory error at line %d\n", lineno);
  
  else {
    for (i=0;i<MAXCHILDREN;i++)
      t->child[i] = NULL;
    t->sibling = NULL;
    t->nodekind = DecK;
    t->kind.dec = kind;
    t->lineno = lineno;
    t->type = Void;
  }
  return t;
}

//Creates a new Label Node for AST
TreeNode * newLabelNode(LabelKind kind) {
  TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
  
  int i;
  
  if (t == NULL)
    fprintf(output,"Out of memory error at line %d\n", lineno);
  
  else {
    for (i=0;i<MAXCHILDREN;i++)
      t->child[i] = NULL;
    t->sibling = NULL;
    t->nodekind = LabelK;
    t->kind.dec = kind;
    t->lineno = lineno;
    t->type = Void;
  }
  return t;
}

//Makes a copy of a String
char * copyString(char * s) {
  int n;
  char * t;
  if (s==NULL) return NULL;
  n = strlen(s)+1;
  t = malloc(n);
  if (t==NULL)
    fprintf(output,"Out of memory error at line %d\n", lineno);
  else strcpy(t,s);
  return t;
}

//Stores Current Num of spaces for AST
static int indentno = 0;

//Increase/Cecrease Indentation
#define INDENT indentno+=2
#define UNINDENT indentno-=2

//Increases Indetation by printing spaces
static void printSpaces(void) {
  int i;
  for (i=0;i<indentno;i++)
    fprintf(output," ");
}

//Print the AST
void printTree(TreeNode *tree)
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
            fprintf(output,"[Variable declaration \"%s\" of type \"%s\" at line %d]\n"
                   , tree->attr.name, tree->type==Integer?"Integer": (tree->type==Boolean?"Boolean":"Void"), tree->lineno);
            break;
            
          case ArrayK:
            fprintf(output, "[Array declaration \"%s\" of size %d"
                    " and type \"%s\" at line %d]\n",
                    tree->attr.name, tree->value, tree->type==Integer?"Integer": (tree->type==Boolean?"Boolean":"Void"), tree->lineno);
            break;
            
          case FunK:
            fprintf(output, "[Function declaration \"%s()\""
                    " of return type \"%s\" at line %d]\n", 
                    tree->attr.name, tree->type==Integer?"Integer": (tree->type==Boolean?"Boolean":"Void"), tree->lineno);
            break;

          case ParameterK:
            fprintf(output, "[Parameter \"%s\""
                    " of type \"%s\" at line %d]\n", 
                    tree->attr.name, tree->type==Integer?"Integer": (tree->type==Boolean?"Boolean":"Void"), tree->lineno);
            break;
            
          default:
            fprintf(output, "<<<unknown declaration type>>>\n");
            break;
        }
      }
      
      else if (tree->nodekind == ExpK) {

        switch(tree->kind.exp) {
          case OpK:
            fprintf(output, "[Operator ");
            printOperators(tree->attr.op, "", tree);
            fprintf(output, "]\n");
            break;
                
          case IdK:
            fprintf(output, "[Identifier \"%s", tree->attr.name);
            //Array Indexing
            if (tree->value != 0)
              fprintf(output, "[%d]", tree->value);
            fprintf(output, "\" at line %d]\n", tree->lineno);
            break;
                
          case ConstK:
            fprintf(output, "[Literal constant \"%s\" at line %d]\n", tree->attr.val, tree->lineno);
            break;
                
          case AssignK:
            fprintf(output, "[Assignment \"%s\" at line %d]\n", tree->attr.name, tree->lineno);
            break;       
                
          default:
            fprintf(output, "<<<unknown expression type>>>\n");
            break;
        }
      }
    
      else if (tree->nodekind == StmtK) {

        switch(tree->kind.stmt) {
          case CompoundK:
            fprintf(output, "[Compound statement at line %d]\n", tree->lineno);
            break;
      
          case IfK:
            fprintf(output, "[IF statement ending at line %d]\n", tree->lineno);
            break;

          case ElseK:
            fprintf(output, "[ELSE statement ending at line %d]\n", tree->lineno);
            break;

          case BreakK:
            fprintf(output, "[BREAK statement at line %d]\n", tree->lineno);
            break;
                
          case WhileK:
            fprintf(output, "[WHILE statement ending at line %d]\n", tree->lineno);
            break;
                
          case ReturnK:
            fprintf(output, "[RETURN statement at line %d]\n", tree->lineno);
            break;
                
          case CallK:
          fprintf(output, "[Call to function \"%s()\" with \"%d\" argument(s) at line %d]\n",
                  tree->attr.name,(tree->child[0])!=NULL?(tree->child[0])->param_size:0, tree->lineno);
          break;

          case EmptyK:
            fprintf(output, "[EMPTY statement at line %d]\n", tree->lineno);
            break;

          case SemicolonK:
            fprintf(output, "[Semicolon statement at line %d]\n", tree->lineno);
            break;
       
        default:
          fprintf(output, "<<<unknown statement type>>>\n");
          break;
        }
      }
      else if (tree->nodekind == LabelK) {
        switch(tree->kind.stmt) {
          case FctnParamsK:
            fprintf(output, "[Function Parameters List at line %d]\n", tree->lineno);
            break;  
          
          case FctnArgsK:
            fprintf(output, "[Function Declaration List at line %d]\n", tree->lineno);
            break;      
          
          case BlockK:
            fprintf(output, "[Block ending at line %d]\n", tree->lineno);
            break;

        default:
          fprintf(output, "<<<unknown label type>>>\n");
          break;
        }
      }

      else
        fprintf(output, "<<<unknown node kind>>>\n");

      for (i=0; i<MAXCHILDREN; ++i)
        printTree(tree->child[i]);
        
      tree = tree->sibling;
    }

    UNINDENT;
}
