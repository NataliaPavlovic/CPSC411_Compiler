/****************************************************/
/* File: parser_incomplete.y                        */
/* Parser Specification for EX Compiler             */
/* Note: This parser is missing some functionality  */
/* that would let it get values of previously read  */
/* token lexemes.                                   */
/* Actual parser.y will be uploaded later           */
/****************************************************/
%{
#define YYPARSER

#include "globals.h"
#include "util.h"
#include "scan.h"
#include "parse.h"

//Return Type set to AST
#define YYSTYPE TreeNode *

static char * savedNUM;
static int global_size = 0;

//Store AST to be returned later
static TreeNode * savedTree;
//Store name of ID to be returned later
static char * savedName;

//Function Declarations
static int yylex();
int yyerror(char * s);

static int firstTime = 1;

%}

%token    ENDFILE ERROR
%token    IF ELSE WHILE RETURN VOID BOOL TRUE FALSE INT NOT
%token    ID NUM
%token    ASSIGN EQ NQ LT GT LE GE PLUS MINUS TIMES DIV LPAREN RPAREN SEMI COMMA LBRACK RBRACK LCBRACK RCBRACK AND OR
%%
program   : dec-list  {savedTree = $1;}
          ;

dec-list  : dec-list dec  {
                            YYSTYPE t = $1;
                            if (t != NULL) {
                              while (t -> sibling != NULL)
                                t = t -> sibling;
                                
                              t -> sibling = $2;
                              $$ = $1;
                            }
                            else $$ = $2;
                          }
          | dec           {$$ = $1;}
          ;

dec       : var_dec {$$ = $1;}
          ;

var_dec   : INT ID SEMI {
                          char * str = (char *)malloc(MAXTOKENLEN+1);
                          strcpy(str, previousTokenString);
                          $$ = newDecNode(VarK);
                          $$->attr.name = str;
                          $$->type = Integer;
                          $$->lineno = lineno;
                        }
          | VOID ID SEMI {
                          char * str = (char *)malloc(MAXTOKENLEN+1);
                          strcpy(str, previousTokenString);
                          $$ = newDecNode(VarK);
                          $$->attr.name = str;
                          $$->type = Void;
                          $$->lineno = lineno;
                         }
          | INT ID LBRACK NUM RBRACK SEMI {
                                            char * str1 = (char *)malloc(MAXTOKENLEN+1);
                                            char * str2 = (char *)malloc(MAXTOKENLEN+1);
                                            strcpy(str1, fullLine[1]);
                                            strcpy(str2, fullLine[3]);
                                            $$ = newDecNode(ArrayK);
                                            $$->attr.name = str1;
                                            $$->type = Integer;
                                            $$->value = atoi(str2);
                                            $$->isArray = 1;
                                            $$->lineno = lineno;
                                          }
          ;



%%

int yyerror(char * message) {
  fprintf(output, "Syntax error at line %d: %s\n", lineno, message);
  fprintf(output, "Current token: ");
  printToken(yychar, tokenString);
  Error = TRUE;
  return 0;
}

static int yylex(void) {
 
 TokenType t = getToken(firstTime);
 firstTime = 0;
 if(t != EOF) {
    return t;
 }
 return 0;
}

TreeNode * parse(void)
{ 
  yyparse();
  return savedTree;
}
