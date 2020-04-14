%{
// Natalia Pavlovic
// CPSC 411
// Milestone 3
// March 2020
#define YYPARSER
#define YYINITDEPTH 1000

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
//Stores number of arguments for a function call
int numberArgs = 0;
int numberArgsFunk = 0;

%}

%start    start

%token    ENDFILE ERROR
%token    INT BOOLEAN VOID IF ELSE WHILE RETURN BREAK TRUE FALSE
%token    ID NUMBER STRING
%token    EQ NQ LE GE AND OR 
%%

start           : /* empty */
                | globaldeclarations {savedTree = $1;}
                ;

globaldeclarations      : globaldeclaration {$$ = $1;}
                        | globaldeclarations globaldeclaration
                        {
                            YYSTYPE t = $1;
                            if (t != NULL) {
                              while (t -> sibling != NULL)
                                t = t -> sibling;
                                
                              t -> sibling = $2;
                              $$ = $1;
                            }
                            else $$ = $2;
                        }
                        ;

globaldeclaration       : variabledeclaration {$$ = $1;}
                        | functiondeclaration {$$ = $1;}
                        | mainfunctiondeclaration {$$ = $1;}
                        ;

variabledeclaration     : BOOLEAN ID ';'
                        {
                            char * str = (char *)malloc(MAXTOKENLEN+1);
                            strcpy(str, previousTokenString);
                            $$ = newDecNode(VarK);
                            $$ -> type = Boolean;
                            $$ -> attr.name = str;
                            $$ -> lineno = lineno;
                        }
                        | INT ID ';'
                        {
                            char * str = (char *)malloc(MAXTOKENLEN+1);
                            strcpy(str, previousTokenString);
                            $$ = newDecNode(VarK);
                            $$ -> type = Integer;
                            $$ -> attr.name = str;
                            $$ -> lineno = lineno;
                        }
                        ;


functiondeclaration     : BOOLEAN functiondeclarator block
                        {
                            $$ = $2;
                            $$ -> child[1] = $3;
                        }
                        | INT functiondeclarator block
                        {
                            $$ = $2;
                            $$ -> child[1] = $3;
                        }
                        | VOID functiondeclarator block
                        {
                            $$ = $2;
                            $$ -> child[1] = $3;
                        }
                        ;

functiondeclarator      : ID '(' formalparameterlist ')'
                        {
                            $$ = newDecNode(FunK);
                            char * str = (char *)malloc(MAXTOKENLEN+1);

                            int i;
                            for(i = currentIndex; i >= 0; i--)
                            {
                                if(fullLine[i][0]=='(')
                                {
                                    break;
                                }   
                            }

                            strcpy(str, fullLine[i-1]);

                            if(strcmp("boolean", fullLine[i-2])==0)
                            {
                                $$ -> type = Boolean;
                            }
                            else if(strcmp("int", fullLine[i-2])==0) 
                            {
                                $$ -> type = Integer;
                            }
                            else if(strcmp("void", fullLine[i-2])==0) 
                            {
                                $$ -> type = Void;
                            }

                            $$ -> attr.name = str;
                            $$ -> child[0] = newLabelNode(FctnParamsK);
                            $$ -> child[0] -> child[0] = $3;
                            $$ -> lineno = lineno;    
                            $$ -> param_size = numberArgsFunk;
                            numberArgsFunk = 0;
                        }
                        | ID '(' ')'
                        {
                            $$ = newDecNode(FunK);
                            char * str = (char *)malloc(MAXTOKENLEN+1);

                            int i;
                            for(i = currentIndex; i >= 0; i--)
                            {
                                if(fullLine[i][0]=='(')
                                {
                                    break;
                                }   
                            }

                            strcpy(str, fullLine[i-1]);

                            if(strcmp("boolean", fullLine[i-2])==0)
                            {
                                $$ -> type = Boolean;
                            }
                            else if(strcmp("int", fullLine[i-2])==0) 
                            {
                                $$ -> type = Integer;
                            }
                            else if(strcmp("void", fullLine[i-2])==0) 
                            {
                                $$ -> type = Void;
                            }

                            $$ -> attr.name = str;
                            $$ -> lineno = lineno;
                            $$ -> param_size = 0;
                        }

formalparameterlist     : BOOLEAN ID
                        {
                            char * str = (char *)malloc(MAXTOKENLEN+1);
                            strcpy(str, tokenString);
                            $$ = newDecNode(ParameterK);
                            $$ -> type = Boolean;
                            $$ -> attr.name = str;
                            $$ -> lineno = lineno; 
                            numberArgsFunk++; 
                        }
                        | INT ID
                        {
                            char * str = (char *)malloc(MAXTOKENLEN+1);
                            strcpy(str, tokenString);
                            $$ = newDecNode(ParameterK);
                            $$ -> type = Integer;
                            $$ -> attr.name = str;
                            $$ -> lineno = lineno; 
                            numberArgsFunk++;  
                        }
                        | formalparameterlist ',' BOOLEAN ID
                        {
                            YYSTYPE t = $1;
                            if (t != NULL) {
                              while (t -> sibling != NULL)
                                t = t -> sibling;
                                
                              char * str = (char *)malloc(MAXTOKENLEN+1);
                              strcpy(str, tokenString);
                              t -> sibling = newDecNode(ParameterK);
                              t -> sibling -> type = Boolean;
                              t -> sibling -> attr.name = str;
                              t -> sibling -> lineno = lineno;
                              numberArgsFunk++;
                              $$ = $1;
                            }
                            else
                            {
                                char * str = (char *)malloc(MAXTOKENLEN+1);
                                strcpy(str, tokenString);
                                $$ = newDecNode(ParameterK);
                                $$ -> type = Boolean;
                                $$ -> attr.name = str;
                                $$ -> lineno = lineno;
                                numberArgsFunk++; 
                            }                       
                        }
                        | formalparameterlist ',' INT ID
                        {
                            YYSTYPE t = $1;
                            if (t != NULL) {
                              while (t -> sibling != NULL)
                                t = t -> sibling;
                                
                              char * str = (char *)malloc(MAXTOKENLEN+1);
                              strcpy(str, tokenString);
                              t -> sibling = newDecNode(ParameterK);
                              t -> sibling -> type = Integer;
                              t -> sibling -> attr.name = str;
                              t -> sibling -> lineno = lineno;
                              numberArgsFunk++;
                              $$ = $1;
                            }
                            else
                            {
                                char * str = (char *)malloc(MAXTOKENLEN+1);
                                strcpy(str, tokenString);
                                $$ = newDecNode(ParameterK);
                                $$ -> type = Integer;
                                $$ -> attr.name = str;
                                numberArgsFunk++;
                            }                       
                        }
                        ;


mainfunctiondeclaration : functiondeclarator block
                        {
                            $$ = $1;
                            $$ -> type = Void;
                            $$ -> child[1] = $2;
                        }
                        ;

block                   : '{' blockstatements '}' 
                        {
                            $$ = newLabelNode(BlockK);
                            $$ -> child[0] = $2;
                        }
                        | '{' '}'
                        {
                            $$ = newStmtNode(EmptyK);
                        }
                        ;

blockstatements         : blockstatement {$$ = $1;}
                        | blockstatements blockstatement
                        {
                            YYSTYPE t = $1;
                            if (t != NULL) {
                              while (t -> sibling != NULL)
                                t = t -> sibling;
                                
                              t -> sibling = $2;
                              $$ = $1;

                            }
                            else $$ = $2;   
                        }
                        ;

blockstatement          : variabledeclaration {$$ = $1;}
                        | statement {$$ = $1;}
                        ;

statement               : '{' blockstatements '}' 
                        {
                            $$ = newStmtNode(CompoundK);
                            $$ -> lineno = lineno;
                            $$ -> child[0] = $2;
                        }
                        | '{' '}'
                        {
                            $$ = newStmtNode(EmptyK);
                            $$ -> lineno = lineno;
                        }
                        | ';'
                        {
                            $$ = newStmtNode(SemicolonK);
                            $$ -> lineno = lineno;
                        }
                        | statementexpression ';' 
                        {
                            $$ = newStmtNode(CompoundK);
                            $$ -> lineno = lineno;
                            $$ -> child[0] = $1;
                        }
                        | BREAK ';'
                        {
                            $$ = newStmtNode(BreakK);
                            $$ -> lineno = lineno;
                        }
                        | RETURN expression ';'
                        {                            
                            $$ = newStmtNode(ReturnK);
                            $$ -> child[0] = $2;
                            $$ -> lineno = lineno;
                        }
                        | RETURN ';' 
                        {                            
                            $$ = newStmtNode(ReturnK);
                            $$ -> lineno = lineno;
                        }
                        | IF '(' expression ')' statement
                        {
                            $$ = newStmtNode(IfK);
                            $$ -> child[0] = $3;
                            $$ -> child[1] = $5;
                            $$-> lineno = $$ -> child[1] -> lineno;
                        }
                        | IF '(' expression ')' statement ELSE statement
                        {
                            $$ = newStmtNode(IfElseK);
                            $$ -> child[0] = $3;
                            $$ -> child[1] = $5;
                            $$ -> child[2] = $7;
                            $$-> lineno = lineno;
                        }
                        | WHILE '(' expression ')' statement
                        {
                            $$ = newStmtNode(WhileK);
                            $$ -> child[0] = $3;
                            $$ -> child[1] = $5;
                            $$ -> lineno = lineno;
                        }
                        ;

statementexpression     : assignment {$$ = $1;}
                        | functioninvocation {$$ = $1;}
                        ;

primary                 : NUMBER
                        {   
                            char * str = (char *)malloc(MAXTOKENLEN+1);
                            strcpy(str, tokenString);
                            $$ = newExpNode(ConstK);
                            $$->type = Integer;
                            $$->attr.val = str;
                            $$ -> lineno = lineno;
                        }
                        | STRING
                        {
                            char * str = (char *)malloc(MAXTOKENLEN+1);
                            strcpy(str, tokenString);
                            $$ = newExpNode(ConstK);
                            $$ -> attr.val = str;
                            $$ -> lineno = lineno;
                        }
                        | TRUE
                        {
                            char * str = (char *)malloc(MAXTOKENLEN+1);
                            strcpy(str, tokenString);
                            $$ = newExpNode(ConstK);
                            $$ -> type = Boolean;
                            $$ -> attr.val = str;
                            $$ -> lineno = lineno;
                        }
                        | FALSE
                        {
                            char * str = (char *)malloc(MAXTOKENLEN+1);
                            strcpy(str, tokenString);
                            $$ = newExpNode(ConstK);
                            $$ -> type = Boolean;
                            $$ -> attr.val = str;
                            $$ -> lineno = lineno;
                        }
                        | '(' expression ')' {$$ = $2;}
                        | functioninvocation {$$ = $1;}
                        ;

argumentlist            : expression {$$ = $1; numberArgs++;printf("num args %d\n", $$ -> param_size);}
                        | argumentlist ',' expression
                        {
                            YYSTYPE t = $1;
                            if (t != NULL) {
                              while (t -> sibling != NULL)
                              {
                                t = t -> sibling;
                              }
                                
                              t -> sibling = $3;
                              $$ = $1;
                            }
                            else $$ = $3;
                            {
                                $$ -> param_size = $$ -> param_size + 1;
                            }
                            $$ -> lineno = lineno;
                            printf("num args %d\n", $$ -> param_size);
                        }
                        ;

functioninvocation      : ID '(' argumentlist ')'
                        {
                            char * str = (char *)malloc(MAXTOKENLEN+1);
                            printf("%d %d %d\n", startIndex, currentIndex, lineno);

                            int i;
                            int j = 0;
                            for(i = currentIndex; i >= 0; i--)
                                {
                                    if(fullLine[i][0]=='(')
                                    {
                                        j++;
                                    } 
                                    else if (fullLine[i][0]==')')
                                    {
                                        j--;
                                    }
                                }
                                if(startIndex == 0)
                                {
                                    for(i = currentIndex; i >= 0; i--)
                                    {
                                        if(fullLine[i][0]=='(' && (isalpha(fullLine[i-1][0])) || fullLine[i-1][0] == '_')
                                        {
                                            break;
                                        }   
                                    }
                                    startIndex = i-1;
                                }
                                else
                                {
                                    //Nested
                                    for(i = startIndex; i >= 0; i--)
                                    {
                                        if(fullLine[i][0]=='(' && (isalpha(fullLine[i-1][0])) || fullLine[i-1][0] == '_')
                                        {
                                            break;
                                        }   
                                    }
                                    if(i == -1)
                                    {
                                        for(i = currentIndex; i >=startIndex; i--)
                                        {
                                            if(fullLine[i][0]=='(' && (isalpha(fullLine[i-1][0])) || fullLine[i-1][0] == '_')
                                            {
                                                break;
                                            }   
                                        }
                                        startIndex = i-1;
                                    }
                                    else
                                    {
                                        startIndex = i-1;  
                                    }
                                }

                                strcpy(str, fullLine[i-1]);
                                printf("%d %d %d %s\n", startIndex, currentIndex, lineno, str);

                                $$ = newStmtNode(CallK);
                                $$ -> attr.name = str;
                                $$ -> child[0] = newLabelNode(FctnArgsK);
                                $$ -> child[0] -> child[0] = $3;
                                $3 -> param_size = $3 -> param_size + 1;
                                $$ -> child[0] -> param_size = $3 -> param_size ;
                                $$ -> lineno = lineno;
                        }
                        | ID '(' ')'
                        {
                            char * str = (char *)malloc(MAXTOKENLEN+1);
                            int i;

                            if(startIndex == 0)
                            {
                                for(i = currentIndex; i >= 0; i--)
                                {
                                    if(fullLine[i][0]=='(' && (isalpha(fullLine[i-1][0])) || fullLine[i-1][0] == '_')
                                    {
                                        break;
                                    }   
                                }
                                startIndex = i-1;
                            }
                            else
                            {
                                for(i = currentIndex; i >=startIndex; i--)
                                {
                                    if(fullLine[i][0]=='(' && (isalpha(fullLine[i-1][0])) || fullLine[i-1][0] == '_')
                                    {
                                        break;
                                    }   
                                }
                                startIndex = i-1;
                            }

                            strcpy(str, fullLine[i-1]);
                            $$ = newStmtNode(CallK);
                            $$->attr.name = str;
                            $$ -> lineno = lineno;
                        }
                        ;

unaryexpression         : '-' unaryexpression
                        {
                            $$ = newExpNode(OpK);
                            $$ -> attr.op = '-';
                            $$ -> child[0] = $2;
                            $$ -> lineno = lineno;
                        }
                        | '!' unaryexpression
                        {
                            $$ = newExpNode(OpK);
                            $$->attr.op = '!';
                            $$ -> child[0] = $2;
                            $$ -> lineno = lineno;
                        }   
                        | primary {$$ = $1;}
                        | ID
                        {
                            char * str = (char *)malloc(MAXTOKENLEN+1);
                            strcpy(str, previousTokenString);
                            $$ = newExpNode(IdK);
                            $$->attr.name = str;
                            $$ -> lineno = lineno;
                        }
                        ;

multiplicativeexpression: unaryexpression {$$ = $1;}
                        | multiplicativeexpression '*' unaryexpression
                        {
                            $$ = newExpNode(OpK);
                            $$ -> attr.op = '*';
                            $$ -> child[0] = $1;
                            $$ -> child[1] = $3;
                            $$ -> lineno = lineno;
                        }
                        | multiplicativeexpression '/' unaryexpression
                        {
                            $$ = newExpNode(OpK);
                            $$ -> attr.op = '/';
                            $$ -> child[0] = $1;
                            $$ -> child[1] = $3;
                            $$ -> lineno = lineno;
                        }
                        | multiplicativeexpression '%' unaryexpression
                        {
                            $$ = newExpNode(OpK);
                            $$ -> attr.op = '%';
                            $$ -> child[0] = $1;
                            $$ -> child[1] = $3;
                            $$ -> lineno = lineno;
                        }
                        ;

additiveexpression      : multiplicativeexpression {$$ = $1;}
                        | additiveexpression '+' multiplicativeexpression
                        {
                            $$ = newExpNode(OpK);
                            $$ -> attr.op = '+';
                            $$ -> child[0] = $1;
                            $$ -> child[1] = $3;
                            $$ -> lineno = lineno;
                        }
                        | additiveexpression '-' multiplicativeexpression
                        {
                            $$ = newExpNode(OpK);
                            $$ -> attr.op = '-';
                            $$ -> child[0] = $1;
                            $$ -> child[1] = $3;
                            $$ -> lineno = lineno;
                        }
                        ;

relationalexpression    : additiveexpression {$$ = $1;}
                        | relationalexpression '<' additiveexpression
                        {
                            $$ = newExpNode(OpK);
                            $$ -> attr.op = '<';
                            $$ -> child[0] = $1;
                            $$ -> child[1] = $3;
                            $$ -> lineno = lineno;
                        }
                        | relationalexpression '>' additiveexpression
                        {
                            $$ = newExpNode(OpK);
                            $$ -> attr.op = '>';
                            $$ -> child[0] = $1;
                            $$ -> child[1] = $3;
                            $$ -> lineno = lineno;
                        }
                        | relationalexpression LE additiveexpression
                        {
                            $$ = newExpNode(OpK);
                            $$ -> attr.op = LE;
                            $$ -> child[0] = $1;
                            $$ -> child[1] = $3;
                            $$ -> lineno = lineno;
                        }
                        | relationalexpression GE additiveexpression
                        {
                            $$ = newExpNode(OpK);
                            $$ -> attr.op = GE;
                            $$ -> child[0] = $1;
                            $$ -> child[1] = $3;
                            $$ -> lineno = lineno;
                        }
                        ;

equalityexpression      : relationalexpression {$$ = $1;}
                        | equalityexpression EQ relationalexpression
                        {
                            $$ = newExpNode(OpK);
                            $$ -> attr.op = EQ;
                            $$ -> child[0] = $1;
                            $$ -> child[1] = $3;
                            $$ -> lineno = lineno;
                        }
                        | equalityexpression NQ relationalexpression
                        {
                            $$ = newExpNode(OpK);
                            $$ -> attr.op = NQ;
                            $$ -> child[0] = $1;
                            $$ -> child[1] = $3;
                            $$ -> lineno = lineno;
                        }
                        ;

conditionalandexpression: equalityexpression {$$ = $1;}
                        | conditionalandexpression AND equalityexpression
                        {
                            $$ = newExpNode(OpK);
                            $$ -> attr.op = AND;
                            $$ -> child[0] = $1;
                            $$ -> child[1] = $3;
                            $$ -> lineno = lineno;
                        }
                        ;

conditionalorexpression : conditionalandexpression {$$ = $1;}
                        | conditionalorexpression OR conditionalandexpression
                        {
                            $$ = newExpNode(OpK);
                            $$ -> attr.op = OR;
                            $$ -> child[0] = $1;
                            $$ -> child[1] = $3;
                            $$ -> lineno = lineno;
                        }
                        ;

assignmentexpression    : conditionalorexpression {$$ = $1;}
                        | assignment {$$ = $1;}
                        ;

assignment              : ID '=' assignmentexpression
                        {
                            $$ = newExpNode(AssignK);
                            char * str = (char *)malloc(MAXTOKENLEN+1);

                            int i;
                            for(i = startIndexAssign; i >= 0; i--)
                            {
                                if(fullLine[i][0]=='=')
                                {
                                    break;
                                }   
                            }
                            startIndexAssign = i-1;

                            strcpy(str, fullLine[i-1]);
                            $$ -> attr.name = str;
                            $$ -> child[0] = $3;
                            $$ -> lineno = lineno;
                        }
                        ;

expression              : assignmentexpression {$$ = $1;}
                        ;



%%

int yyerror(char * message) {
  fprintf(listing, "Syntax error at line %d: %s\n", lineno, message);
  fprintf(listing, "Current token: ");
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
