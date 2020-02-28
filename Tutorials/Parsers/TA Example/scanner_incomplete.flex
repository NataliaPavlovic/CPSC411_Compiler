/****************************************************/
/* File: scanner_incomplete.flex                    */
/* The lex specification for EX Compiler            */
/* Note: This is the incomlete scanner and therefore*/
/* is missing some code that the parser uses        */
/* Specifically to get previous tokens.             */
/* Actual scanner.flex will be uploaded later       */
/****************************************************/

%x COMMENT_MULTI_LINE
%{
#include "globals.h"
#include "util.h"
#include "scan.h"

%}

digit       [0-9]
number      {digit}+
letter      [a-zA-Z]
identifier  {letter}+
newline     \n
whitespace  [ \t\r]+

%%

"bool"          {return BOOL;}
"if"            {return IF;}
"else"          {return ELSE;}
"while"         {return WHILE;}
"return"        {return RETURN;}
"true"          {return TRUE;}
"false"         {return FALSE;}
"void"          {return VOID;}
"int"           {return INT;}
"not"           {return NOT;}

"="             {return ASSIGN;}
"!="            {return NQ;}
"=="            {return EQ;}
"<"             {return LT;}
">"             {return GT;}
"<="            { return LE;}
">="            {return GE;}
"&&"            {return AND;}
"||"            {return OR;}
"+"             {return PLUS;}
"-"             {return MINUS;}
"*"             {return TIMES;}
"/"             {return DIV;}
"("             {return LPAREN;}
")"             {return RPAREN;}
";"             {return SEMI;}
","             {return COMMA;}
"["             {return LBRACK;}
"]"             {return RBRACK;}
"{"             {return LCBRACK;}
"}"             {return RCBRACK;}

{number}        {return NUM;}
{identifier}    {return ID;}

{newline}       {lineno++;}
{whitespace}    {}

<INITIAL>"/*"               {BEGIN(COMMENT_MULTI_LINE);}
<COMMENT_MULTI_LINE>"*/"    {BEGIN(INITIAL);}
<COMMENT_MULTI_LINE><<EOF>> {printToken(ERROR,"EOF in comment"); yyterminate();}
<COMMENT_MULTI_LINE>.       {}
<COMMENT_MULTI_LINE>\n      {}

.       {return ERROR;}

%%
//Return current token - use in main.c
TokenType getToken(int firstTime) {
  
  TokenType currentToken;
  
  if (firstTime) {
    firstTime = FALSE;
    lineno++;
    yyin = source;
    yyout = output;
  }
  
  strcpy(previousTokenString, tokenString);

  currentToken = yylex();  
  strncpy(tokenString, yytext, MAXTOKENLEN);
  
  if (TraceScan)
    printToken(currentToken,tokenString);
  

  
  return currentToken;
}
