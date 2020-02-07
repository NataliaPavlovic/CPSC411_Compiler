%{
// Natalia Pavlovic
// CPSC 411
// Milestone 1
// Feb. 2020

#include <stdio.h>

int line = 1; // Source file line number 

int string_index = 0; // String indexes used to determine the length of string

int warnings = 0; // Number of warnings per source file line

int tokenType = 0; // Type of token

enum tokentypes{
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
%%

[ \t\r\b\f\']+      ;
\n                  line++; warnings = 0;

{comment}           {printf("Comment %s found at line %d\n", yytext, line);}

{reserved}          {tokenType=reserved; return yytext[0];}
{operator}          {tokenType=operator; return yytext[0];}
{special}           {tokenType=special; return yytext[0];}

{number}            {tokenType=number; return yytext[0];}
{id}                {tokenType=id; return yytext[0];}

\"                  {BEGIN STRING;}
<STRING>\\(\"|\\)   {
                        string_index+=2; // Add 2 because these string literals show up as 2 separate characters in a string
                        yymore();
                    }
<STRING>\"          {   
                        yytext[string_index]='\0'; // Place terminating character at end of string
                        BEGIN 0; 
                        tokenType = string; 
                        return STRING;
                    }
<STRING><<EOF>>     {fprintf(stderr, "Error: string missing closing quote at or near line %d\n", line); exit(1);}
<STRING>\n          {fprintf(stderr, "Error: string missing closing quote at or near line %d\n", line); exit(1);}
<STRING>.           {string_index++; yymore();}

<<EOF>>             {printf("EOF found at line %d\n", line); exit(0);}

.                   {
                        warnings++; 
                        if(warnings >= 12)
                        {
                            fprintf(stderr, "Error: too many warnings at or near line %d\n", line);
                            exit(1);
                        }
                        else
                        {
                            fprintf(stderr, "Warning: ignoring bad character at or near line %d\n", line);
                        }
                    }

%%

int main(int argc, char *argv[]) {
    if(argc!=2)
    {
        fprintf(stderr, "Error: Wrong number of arguments. Format should be ./scanner <testfile>\n");
        exit(1);
    }

    yyin = fopen(argv[1], "r");

    if (yyin==NULL)
    {
        fprintf(stderr, "Error: Cannot open file for reading\n");
        exit(1);
    }

    int t;
    while((t=yylex()) != 0)
    {
        // Format tokens for printing
        switch(tokenType){
            case number:
            {
                printf("Token(number, %d, %s)\n", line, yytext);
                tokenType = 0;
                break;
            }
            case id:
            {
                printf("Token(id, %d, %s)\n", line, yytext);
                tokenType = 0;
                break;
            }
            case string:
            {
                // Copy contents of yytext to a new string in order to remove NUL characters

                char string[string_index];
                // Only for string
                int j = 0;
                for(int i = 0; i < string_index; i++)
                {
                    if(yytext[i]!='\0')
                    {
                        string[j] = yytext[i];
                        j++;
                    }
                    else
                    {
                        printf("Removed NUL character at character position %d in line %d\n", i, line);
                    }
                }
                string[j] = '\0'; // Place terminating character as end of string
                printf("Token(string, %d, %s)\n", line, string);

                string_index = 0;
                tokenType = 0;
                break;
            }
            case reserved:
                // Fallthrough because reserved print in same format as special
            case operator:
                // Fallthrough because operator print in same format as special
            case special:
            {
                printf("Token(%s, %d, None)\n", yytext, line);
                tokenType = 0;
                break;          
            }
            default:
                // Should never reach this case
                fprintf(stderr, "Error: unkown token type\n");
                exit(1);
                break;
        }
    }
    fclose(yyin);

    return 0;
}
