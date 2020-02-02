%{
#include <stdio.h>
int line = 1;	
%}

letter	[a-zA-Z]
digit	[0-9]

num		{digit}{digit}*
id 		{letter}{letter}*

reserved	"true"|"false"|"boolean"|"int"|"void"|"if"|"else"|"while"|"break"|"return"
operators	"||"|"&&"|"+"|"-"|"*"|"/"
special		";"|"."|"("|")"|"{"|"}"
%%

[ \t\r]		;
\n 		line++;

{reserved}	{printf("Reserved %s found at line %d\n", yytext, line);}
{operators}	{printf("Operators %s found at line %d\n", yytext, line);}
{special}	{printf("Special %s found at line %d\n", yytext, line);}

{num}		{printf("Number %s found at line %d\n", yytext, line);}
{id}		{printf("Identifier %s found at line %d\n", yytext, line);}

.	{printf("Bad Char %s at line %s", yytext, line);}

%%

int main() {
	yyin = fopen("test.txt", "r");

	int t;
	while((t=yylex()) != 0)
	{
		printf("Found %s at line %d", yytext, line);
	}
	return 0;
}