%{
#include <stdio.h>
int line = 1;   
%}

letter  [a-zA-Z_]
digit   [0-9]

num     {digit}{digit}*
id      ({letter})({letter}|{digit})*

nonzerodigit [1-9]
decinteger   {nonzerodigit}("_"?{digit})*
zero         "0"
integer      ({decinteger}|{zero})

reserved     "int"|"boolean"|"void"|"if"|"else"|"while"|"return"|"break"|"true"|"false"
operator     "+"|"-"|"*"|"/"|"%"|"<"|">"|"<="|">="|"="|"=="|"!="|"!"|"||"|"&&"
special      ";"|","|"."|"("|")"|"{"|"}"|"["|"]"

comment      "//"([^("\r"|\n"|EOF)]*)?

%x  STRING
%%

[ \t\r\b\f\']+ ;
\n line++;

<<EOF>>      {exit(1);}

{comment}    ;

{reserved}   {printf("Reserved %s found at line %d\n", yytext, line);}
{operator}   {printf("Operator %s found at line %d\n", yytext, line);}
{special}    {printf("Special %s found at line %d\n", yytext, line);}

{num}        {printf("Number %s found at line %d\n", yytext, line);}
{id}         {printf("Identifier %s found at line %d\n", yytext, line);}


\"  {yymore(); BEGIN STRING;}
<STRING>\" {BEGIN 0; return STRING;}
<STRING>. {yymore();}
<STRING>\n {printf("Error, new line in string\n");}

.            {printf("Bad Char %s at line %d\n", yytext, line);}

%%

int main() {
    yyin = fopen("TestFiles/comment-term-eof.t11", "r");

    int t;
    while((t=yylex()) != 0)
    {
        printf("Found %s at line %d\n", yytext, line);
    }
    return 0;
}