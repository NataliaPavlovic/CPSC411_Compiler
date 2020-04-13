%{
// Natalia Pavlovic
// CPSC 411
// Milestone 3
// March 2020
#include "globals.h"
#include "util.h"
#include "scan.h"

char tokenString[MAXTOKENLEN+1];
int string_index = 0; 
char previousTokenString[MAXTOKENLEN+1];
char fullLine[10][MAXTOKENLEN+1];
int characterNumber = 0;
int currentIndex = 0;

%}

%option noyywrap

letter       [a-zA-Z_]
digit        [0-9]
newline      \n

id           ({letter})({letter}|{digit})*

number       ({digit})*

comment      "//"(["("|")"|^("\r"|"\n")]*)?

operator     "+"|"-"|"*"|"/"|"%"|"="|"!"
special      ";"|","|"("|")"|"{"|"}"

%x  STRING_TOKEN
%%

[ \t\r\b\f\']+              ;
{newline}                   {
                                lineno++; characterNumber=0;string_index=0;     
                                for(int i = 0; i < 10; i++)
                                {   
                                    for(int j = 0; j < MAXTOKENLEN+1; j++)
                                    {
                                        fullLine[i][j] = '\0';
                                    }
                                }
                            }

{comment}                   {;}

"int"                       {return INT;}
"boolean"                   {return BOOLEAN;}
"void"                      {return VOID;}
"if"                        {return IF;}
"else"                      {return ELSE;}
"while"                     {return WHILE;}
"return"                    {return RETURN;}
"break"                     {return BREAK;}
"true"                      {return TRUE;}
"false"                     {return FALSE;}

"!="                        {return NQ;}
"=="                        {return EQ;}
"<"                         {return yytext[0];}
">"                         {return yytext[0];}
"<="                        {return LE;}
">="                        {return GE;}
"&&"                        {return AND;}
"||"                        {return OR;}

{operator}                  {return yytext[0];}
{special}                   {return yytext[0];}

{number}                    {return NUMBER;}
{id}                        {return ID;}

\"                          {BEGIN STRING_TOKEN;}
<STRING_TOKEN>\\(\"|\\)     {
                            string_index+=2; // Add 2 because these string literals show up as 2 separate characters in a string
                            yymore();
                            }
<STRING_TOKEN>\"            {   
                            yytext[string_index]='\0'; // Place terminating character at end of string
                            BEGIN 0; 
                            return STRING;
                            }
<STRING_TOKEN><<EOF>>       {fprintf(stderr, "Error: string missing closing quote at or near line %d\n", lineno); return ERROR;}
<STRING_TOKEN>\n            {fprintf(stderr, "Error: string missing closing quote at or near line %d\n", lineno); return ERROR;}
<STRING_TOKEN>.             {string_index++; yymore();}

<<EOF>>                     {return ENDFILE;}

.                           {return ERROR;}

%%

//Return current token - use in main.c
TokenType getToken(int firstTime) 
{  
    TokenType currentToken;

    if (firstTime) {
    firstTime = FALSE;
    lineno++;
    yyin = source;
    yyout = listing;
    }

    strcpy(previousTokenString, tokenString);

    currentToken = yylex();  

    // Remove NULL characters in a string
    if (string_index != 0)
    {
        for(int i = 0; i < string_index; i++)
        {
            if(yytext[i]=='\0')
            {
                yytext[i] = ' ';
                printf("Removed NUL character at character position %d in line %d\n", i, lineno);
            }
        }
        string_index = 0;
    }

    strncpy(tokenString, yytext, MAXTOKENLEN+1);

    strcpy(fullLine[characterNumber], tokenString);
    //Set currentIndex to its index in fullLine
    currentIndex = characterNumber;
    characterNumber++;

    if (TraceScan)
    {
        printToken(currentToken,tokenString);
    }

    return currentToken;
}
