%{
#include <stdio.h>
int line = 1;  
int character = 1;

int string_index = 0;

int token = 0;
int warnings = 0;

enum types{
    number = 1,
    id = 2,
    string = 3,
    reserved = 4,
    operator = 5,
    special = 6
};
%}

letter       [a-zA-Z_]
digit        [0-9]

id           ({letter})({letter}|{digit})*

number       ({digit})*

reserved     "int"|"boolean"|"void"|"if"|"else"|"while"|"return"|"break"|"true"|"false"
operator     "+"|"-"|"*"|"/"|"%"|"<"|">"|"<="|">="|"="|"=="|"!="|"!"|"||"|"&&"
special      ";"|","|"("|")"|"{"|"}"

comment      "//"([^("\r"|"\n")]*)?

%x  STRING
%x  NULL_CHARACTER
%%

[ \t\r\b\f\']+      ;
\n                  line++; warnings = 0;

{comment}           {printf("Comment %s found at line %d\n", yytext, line);}

{reserved}          {token=reserved; return yytext[0];}
{operator}          {token=operator; return yytext[0];}
{special}           {token=special; return yytext[0];}

{number}            {token=number; return yytext[0];}
{id}                {token=id; return yytext[0];}

\"                  {BEGIN STRING;}
<STRING>\\(\"|\\)   {string_index+=2; yymore();}
<STRING>\"          {yytext[string_index]='\0'; BEGIN 0; token = string; return STRING;}
<STRING><<EOF>>     {printf("error: string missing closing quote at or near line %d\n", line); exit(1);}
<STRING>\n          {printf("error: string missing closing quote at or near line %d\n", line); exit(1);}
<STRING>.           {string_index++; yymore();}

<<EOF>>             {printf("EOF found at line %d\n", line); exit(1);}

.                   {
                        warnings++; 
                        if(warnings >= 12)
                        {
                            printf("error: too many warnings at or near line %d\n", line);
                            exit(1);
                        }
                        else
                        {
                            printf("warning: ignoring bad character at or near line %d\n", line);
                        }
                    }

%%

int main(int argc, char *argv[]) {
    yyin = fopen(argv[1], "r");

    int t;
    while((t=yylex()) != 0)
    {
        switch(token){
            case number:
            {
                printf("Token(number, %d, %s)\n", line, yytext);
                token = 0;
                break;
            }
            case id:
            {
                printf("Token(id, %d, %s)\n", line, yytext);
                token = 0;
                break;
            }
            case string:
            {
                char string[string_index];
                // Only for string
                int i = 0, j = 0;
                for(int i = 0; i < string_index; i++)
                {
                    if(yytext[i]!='\0')
                    {
                        string[j] = yytext[i];
                        j++;
                    }
                }
                string[j] = '\0';
                printf("Token(string, %d, %s)\n", line, string);
                string_index = 0;
                token = 0;
                break;
            }
            case reserved:
                // Fallthrough
            case operator:
                // Fallthrough
            case special:
            {
                printf("Token(%s, %d, None)\n", yytext, line);
                token = 0;
                break;          
            }
            default:
                // Should never reach this case
                printf("Error unkown token type\n");
                break;
        }
    }
    return 0;
}