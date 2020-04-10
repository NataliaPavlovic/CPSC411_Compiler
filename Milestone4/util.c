// Natalia Pavlovic
// CPSC 411
// Milestone 3
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
      fprintf(listing,
         "%d: Reserved Word: %s\n", lineno, tokenString);
      break;
    //Operation/Special Symbols 
    case LE: fprintf(listing, "%d: Special Symbol: <=\n", lineno); break;
    case GT: fprintf(listing, "%d: Special Symbol: >\n", lineno); break;
    case GE: fprintf(listing, "%d: Special Symbol: >=\n", lineno); break;
    case EQ: fprintf(listing,"%d: Special Symbol: ==\n", lineno); break;
    case NQ: fprintf(listing,"%d: Special Symbol: !=\n", lineno); break;
    case AND: fprintf(listing,"%d: Special Symbol: &&\n", lineno); break;
    case OR: fprintf(listing,"%d: Special Symbol: ||\n", lineno); break;
    case ';': fprintf(listing,"%d: Special Symbol: ;\n", lineno); break;
    case ',': fprintf(listing,"%d: Special Symbol: ,\n", lineno); break;
    case '(': fprintf(listing,"%d: Special Symbol: (\n", lineno); break;
    case ')': fprintf(listing,"%d: Special symbl: )\n", lineno); break;
    case '{': fprintf(listing,"%d: Special Symbol: {\n", lineno); break;
    case '}': fprintf(listing,"%d: Special Symbol: }\n", lineno); break;
    case '+': fprintf(listing,"%d: Special Symbol: +\n", lineno); break;
    case '-': fprintf(listing,"%d: Special Symbol: -\n", lineno); break;
    case '*': fprintf(listing,"%d: Special Symbol: *\n", lineno); break;
    case '/': fprintf(listing,"%d: Special Symbol: /\n", lineno); break;
    case '%': fprintf(listing,"%d: Special Symbol: %%\n", lineno); break;
    case '<': fprintf(listing,"%d: Special Symbol: <\n", lineno); break;
    case '>': fprintf(listing,"%d: Special Symbol: >\n", lineno); break;
    case '=': fprintf(listing,"%d: Special Symbol: =\n", lineno); break;
    case '!': fprintf(listing,"%d: Special Symbol: !\n", lineno); break;

    //EOF
    case ENDFILE: fprintf(listing,"%d: End Of File\n", lineno); break;
    
    //Numbers
    case NUMBER:
      fprintf(listing,
          "%d: NUMBER, val= %s\n", lineno, tokenString);
      break;
    
    //Identifiers    
    case ID:
      fprintf(listing,
          "%d: ID, name= %s\n", lineno, tokenString);
      break;
    //Error  
    case ERROR:
      fprintf(listing,
          "%d: ERROR: %s\n", lineno, tokenString);
      break;
      
    default:
      fprintf(listing,"%d: Unknown token: %c\n", lineno, token);
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
      fprintf(listing,
         "%d: Reserved Word: %s\n", tree->lineno, tokenString);
      break;
    //Operation/Special Symbols 
    case LE: fprintf(listing, "<= at line %d", tree->lineno); break;
    case GT: fprintf(listing, "> at line %d", tree->lineno); break;
    case GE: fprintf(listing, ">= at line %d", tree->lineno); break;
    case EQ: fprintf(listing,"== at line %d", tree->lineno); break;
    case NQ: fprintf(listing,"!= at line %d", tree->lineno); break;
    case AND: fprintf(listing,"&& at line %d", tree->lineno); break;
    case OR: fprintf(listing,"|| at line %d", tree->lineno); break;
    case ';': fprintf(listing,"; at line %d", tree->lineno); break;
    case ',': fprintf(listing,", at line %d", tree->lineno); break;
    case '(': fprintf(listing,"( at line %d", tree->lineno); break;
    case ')': fprintf(listing,") at line %d", tree->lineno); break;
    case '{': fprintf(listing,"{ at line %d", tree->lineno); break;
    case '}': fprintf(listing,"} at line %d", tree->lineno); break;
    case '+': fprintf(listing,"+ at line %d", tree->lineno); break;
    case '-': fprintf(listing,"- at line %d", tree->lineno); break;
    case '*': fprintf(listing,"* at line %d", tree->lineno); break;
    case '/': fprintf(listing,"/ at line %d", tree->lineno); break;
    case '%': fprintf(listing,"%% at line %d", tree->lineno); break;
    case '<': fprintf(listing,"< at line %d", tree->lineno); break;
    case '>': fprintf(listing,"> at line %d", tree->lineno); break;
    case '=': fprintf(listing,"= at line %d", tree->lineno); break;
    case '!': fprintf(listing,"! at line %d", tree->lineno); break;

    //EOF
    case ENDFILE: fprintf(listing,"%d: End Of File\n", tree->lineno); break;
    
    //Numbers
    case NUMBER:
      fprintf(listing,
          "%d: NUMBER, val= %s\n", tree->lineno, tokenString);
      break;
    
    //Identifiers    
    case ID:
      fprintf(listing,
          "%d: ID, name= %s\n", tree->lineno, tokenString);
      break;
    //Error  
    case ERROR:
      fprintf(listing,
          "%d: ERROR: %s\n", tree->lineno, tokenString);
      break;
      
    default:
      fprintf(listing,"%d: Unknown token: %c\n", tree->lineno, token);
  }
}

//Creates a new Statement Node for AST
TreeNode * newStmtNode(StmtKind kind) {
  TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
  
  int i;
  
  if (t == NULL)
    fprintf(listing,"Out of memory error at line %d\n", lineno);
  
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
    fprintf(listing,"Out of memory error at line %d\n", lineno);
  
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
    fprintf(listing,"Out of memory error at line %d\n", lineno);
  
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
    fprintf(listing,"Out of memory error at line %d\n", lineno);
  
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
    fprintf(listing,"Out of memory error at line %d\n", lineno);
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
    fprintf(listing," ");
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
            fprintf(listing,"[Variable declaration \"%s\" of type \"%s\" at line %d and scope %d]\n"
                   , tree->attr.name, tree->type==Integer?"Integer": (tree->type==Boolean?"Boolean":"Void"), tree->lineno, tree->scope);
            break;
            
          case FunK:
            fprintf(listing, "[Function declaration \"%s()\""
                    " of return type \"%s\" with \"%d\" arguments at line %d]\n", 
                    tree->attr.name, tree->type==Integer?"Integer": (tree->type==Boolean?"Boolean":"Void"), tree->param_size, tree->lineno);
            break;

          case ParameterK:
            fprintf(listing, "[Parameter \"%s\""
                    " of type \"%s\" at line %d]\n", 
                    tree->attr.name, tree->type==Integer?"Integer": (tree->type==Boolean?"Boolean":"Void"), tree->lineno);
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
            fprintf(listing, "]\n");
            break;
                
          case IdK:
            fprintf(listing, "[Identifier \"%s\" at line %d]\n", tree->attr.name, tree->lineno);
            break;
                
          case ConstK:
            fprintf(listing, "[Literal constant \"%s\" at line %d]\n", tree->attr.val, tree->lineno);
            break;
                
          case AssignK:
            fprintf(listing, "[Assignment \"%s\" at line %d]\n", tree->attr.name, tree->lineno);
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
            fprintf(listing, "[RETURN statement at line %d]\n", tree->lineno);
            break;
                
          case CallK:
          fprintf(listing, "[Call to function \"%s()\" with \"%d\" argument(s) at line %d]\n",
                  tree->attr.name,(tree->child[0])!=NULL?(tree->child[0])->param_size:0, tree->lineno);
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
            fprintf(listing, "[Block ending at line %d and scope %d]\n", tree->lineno, tree->scope);
            break;

        default:
          fprintf(listing, "<<<unknown label type>>>\n");
          break;
        }
      }

      else
        fprintf(listing, "<<<unknown node kind>>>\n");

      for (i=0; i<MAXCHILDREN; ++i)
        printTree(tree->child[i]);
        
      tree = tree->sibling;
    }

    UNINDENT;
}

//Stores Current Num of spaces for Annotated AST
static int indentno_annotated = 0;

//Increase/Cecrease Indentation
#define INDENT_ANNOTATED indentno_annotated+=2
#define UNINDENT_ANNOTATED indentno_annotated-=2

//Increases Indetation by printing spaces
static void printSpacesAnnotated(void) {
  int i;
  for (i=0;i<indentno_annotated;i++)
    fprintf(listing," ");
}

//Print the Annotated AST
void printAnnotatedTree(TreeNode *tree)
{
    int i;
    
    //Macro to Indent
    INDENT_ANNOTATED;

    //Loop while tree is not null (No Children)
    while (tree != NULL) {

      printSpacesAnnotated();

      //Output based on Node Type
        
      if (tree->nodekind == DecK) {

        switch(tree->kind.dec) {
          case VarK:
            fprintf(listing,"[Variable declaration \"%s\" of type \"%s\" at line %d, scope %d and memory location %d]\n"
                   , tree->attr.name, tree->type==Integer?"Integer": (tree->type==Boolean?"Boolean":"Void"), tree->lineno, tree->scope, tree->loc);
            break;
            
          case FunK:
            fprintf(listing, "[Function declaration \"%s()\""
                    " of return type \"%s\" with \"%d\" arguments at line %d. ", 
                    tree->attr.name, tree->type==Integer?"Integer": (tree->type==Boolean?"Boolean":"Void"), tree->param_size, tree->lineno);
            
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
          fprintf(listing, "[Call to function \"%s()\" with \"%d\" argument(s) at line %d and scope %d]\n",
                  tree->attr.name,(tree->child[0])!=NULL?(tree->child[0])->param_size:0, tree->lineno, tree->scope);
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

    UNINDENT_ANNOTATED;
}
