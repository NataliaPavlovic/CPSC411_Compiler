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

comment      "//"([^("\r"|"\n")]*)?

%x  STRING
%%

[ \t\r\b\f]+ ;
\n line++;

{comment}    {printf("Debug comment %s found at line %d\n", yytext, line);}

{reserved}   {printf("Reserved %s found at line %d\n", yytext, line);}
{operator}   {printf("Operator %s found at line %d\n", yytext, line);}
{special}    {printf("Special %s found at line %d\n", yytext, line);}

{num}        {printf("Number %s found at line %d\n", yytext, line);}
{id}         {printf("Identifier %s found at line %d\n", yytext, line);}


\"  {yymore(); BEGIN STRING;}
<STRING>\\\" {yymore();}
<STRING>\\\n {yymore();}
<STRING>\" {BEGIN 0; return STRING;}
<STRING><<EOF>> {printf("Error, EOF line in string\n"); exit(1);}
<STRING>\n {line++; printf("Error, new line in string\n"); exit(1);}
<STRING>.^(NULL) {yymore();}

<<EOF>>    {printf("Debug EOF found at line %d\n", line); exit(1);}

.            {printf("Bad Char %s at line %d\n", yytext, line);}

%%

int main(int argc, char *argv[]) {
    yyin = fopen(argv[1], "r");

    int t;
    while((t=yylex()) != 0)
    {
        printf("%s %d\n", yytext, line);
    }
    return 0;
}