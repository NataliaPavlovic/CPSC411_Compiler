%{
#include <stdio.h>
int line = 1;	
int string_index = 0;
int flag = 0;
%}

%x	STRING
%%

[ \t\r]+	;
\n	line++;

"//".*		ECHO;
"//".*\n	ECHO;

\"	{BEGIN STRING;}
<STRING>\" {yytext[string_index] = '\0'; BEGIN 0; string_index=0; return STRING;}
<STRING>e {}
<STRING>\n {printf("Error, new line in string\n");}
<STRING>. {yymore(); string_index++;}

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