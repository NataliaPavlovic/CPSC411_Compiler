/****************************************************/
/* File: util.c                                     */
/* Utility Functions for EX Compile                 */
/* Code Extracts From: Kenneth C. Louden            */
/****************************************************/

#include "globals.h"
#include "util.h"

//Prints tokens and lexeme to output
void printToken( TokenType token, const char* tokenString ) {
  switch (token) {
    //Reserved Words
    case IF:
    case WHILE:
    case ELSE:
    case INT:
    case BOOL:
    case NOT:
    case RETURN:
    case TRUE:
    case FALSE:
    case VOID:
      //Carries Over for all Reserved Words
      fprintf(output,
         "%d: Reserved Word: %s\n", lineno, tokenString);
      break;
    
    //Operation/Special Symbols    
    case ASSIGN: fprintf(output,"%d: Special Symbol: =\n", lineno); break;
    case LT: fprintf(output,"%d: Special Symbol: <\n", lineno); break;
    case LE: fprintf(output, "%d: Special Symbol: <=\n", lineno); break;
    case GT: fprintf(output, "%d: Special Symbol: >\n", lineno); break;
    case GE: fprintf(output, "%d: Special Symbol: >=\n", lineno); break;
    case EQ: fprintf(output,"%d: Special Symbol: ==\n", lineno); break;
    case NQ: fprintf(output,"%d: Special Symbol: !=\n", lineno); break;
    case AND: fprintf(output,"%d: Special Symbol: &&\n", lineno); break;
    case OR: fprintf(output,"%d: Special Symbol: ||\n", lineno); break;
    case COMMA: fprintf(output,"%d: Special Symbol: ,\n", lineno); break;
    case LPAREN: fprintf(output,"%d: Special Symbol: (\n", lineno); break;
    case RPAREN: fprintf(output,"%d: Special symbl: )\n", lineno); break;
    case LBRACK: fprintf(output,"%d: Special Symbol: [\n", lineno); break;
    case RBRACK: fprintf(output,"%d: Special Symbol: ]\n", lineno); break;
    case LCBRACK: fprintf(output,"%d: Special Symbol: {\n", lineno); break;
    case RCBRACK: fprintf(output,"%d: Special Symbol: }\n", lineno); break;
    case SEMI: fprintf(output,"%d: Special Symbol: ;\n", lineno); break;
    case PLUS: fprintf(output,"%d: Special Symbol: +\n", lineno); break;
    case MINUS: fprintf(output,"%d: Special Symbol: -\n", lineno); break;
    case TIMES: fprintf(output,"%d: Special Symbol: *\n", lineno); break;
    case DIV: fprintf(output,"%d: Special Symbol: /\n", lineno); break;
    
    //EOF
    case ENDFILE: fprintf(output,"%d: End Of File\n", lineno); break;
    
    //Numbers
    case NUM:
      fprintf(output,
          "%d: NUM, val= %s\n", lineno, tokenString);
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
      fprintf(output,"%d: Unknown token: %d\n", lineno, token);
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
                   , tree->attr.name, tree->type==Integer?"Integer":"Void", tree->lineno);
            break;
            
          case ArrayK:
            fprintf(output, "[Array declaration \"%s\" of size %d"
                    " and type \"%s\"]\n",
                    tree->attr.name, tree->value, tree->type==Integer?"Integer":"Void");
            break;
            
          case FunK:
            fprintf(output, "[Function declaration \"%s()\""
                    " of return type \"%s\"]\n", 
                    tree->attr.name, tree->type==Integer?"Integer":"Void");
            break;
            
          default:
            fprintf(output, "<<<unknown declaration type>>>\n");
            break;
        }
      }
      
      else if (tree->nodekind == ExpK) {

        switch(tree->kind.exp) {
          case OpK:
            fprintf(output, "[Operator \"");
            printToken(tree->attr.op, "");
            break;
                
          case IdK:
            fprintf(output, "[Identifier \"%s", tree->attr.name);
            //Array Indexing
            if (tree->value != 0)
              fprintf(output, "[%d]", tree->value);
            fprintf(output, "\"]\n");
            break;
                
          case ConstK:
            fprintf(output, "[Literal constant \"%d\"]\n", tree->attr.val);
            break;
                
          case AssignK:
            fprintf(output, "[Assignment]\n");
            break;
                
          default:
            fprintf(output, "<<<unknown expression type>>>\n");
            break;
        }
      }
    
      else if (tree->nodekind == StmtK) {

        switch(tree->kind.stmt) {
          case CompoundK:
            fprintf(output, "[Compound statement]\n");
            break;
      
          case IfK:
            fprintf(output, "[IF statement]\n");
            break;
                
          case WhileK:
            fprintf(output, "[WHILE statement]\n");
            break;
                
          case ReturnK:
            fprintf(output, "[RETURN statement]\n");
            break;
                
          case CallK:
          fprintf(output, "[Call to function \"%s() %d\"]\n",
                  tree->attr.name,(tree->child[0])!=NULL?(tree->child[0])->param_size:0);
          break;
       
        default:
          fprintf(output, "<<<unknown statement type>>>\n");
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
