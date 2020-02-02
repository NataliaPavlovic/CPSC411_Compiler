%{
#include <stdio.h>
int line = 1;   
%}

digit           [0-9]
bindigit        [0-1]
octdigit        [0-7]
hexdigit        ({digit}|[a-fA-F])
nonzerodigit    [1-9]
hexinteger      "0"("x"|"X")("_"?{hexdigit})+
octinteger      "0"("o"|"O")("_"?{octdigit})+
bininteger      "0"("b"|"B")("_"?{bindigit})+
decinteger      {nonzerodigit}("_"?{digit})*
zero            "0"
integer         ({decinteger}|{bininteger}|{octinteger}|{hexinteger}|{zero})

digitpart       {digit}+("_"{digit}+)*
fraction        "."{digitpart}*
pointfloat      {digitpart}*({fraction}|{digitpart})(".")?
exponent        ("e"|"E")("+"|"-")?{digitpart}
exponentfloat   ({pointfloat}|{digitpart}){exponent}
floatnumber     ({pointfloat}|{exponentfloat})

comment         "#".*(^("\n"|EOF))?

%%

[ \t\r]+ ;
\n line++;

<<EOF>>       {printf("EOF found at line %d\n", line); exit(1);}

{comment}     {printf("Comment %s found at line %d\n", yytext, line);}

{integer}     {printf("Integer %s found at line %d\n", yytext, line);}

{floatnumber} {printf("Floatnumber %s found at line %d\n", yytext, line);}

.             {printf("Bad Char %s at line %d\n", yytext, line);}

%%

int main() {
    yyin = fopen("pythontest.txt", "r");

    int t;
    while((t=yylex()) != 0)
    {
        printf("Found %s at line %d", yytext, line);
    }
    return 0;
}