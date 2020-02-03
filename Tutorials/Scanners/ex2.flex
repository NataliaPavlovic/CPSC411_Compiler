%{
#include <stdio.h>
int line = 1;	
%}

%x	STRING
%%

[ \t\r]+	;
\n	line++;

"//".*		ECHO;
"//".*\n	ECHO;

\"	{yymore(); BEGIN STRING;}
<STRING>\" {BEGIN 0; return STRING;}
<STRING>\n {printf("Error, new line in string\n");}
<STRING>. {yymore();}

.	{printf("Bad Char\n");}

%%

int main () {
	yyin = fopen("test2.txt", "r");

	int t;
	while((t=yylex()) != 0)
	{
		printf("Found %s at line %d\n", yytext, line);
	}
	return 0;
}