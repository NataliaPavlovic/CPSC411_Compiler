%{
// Natalia Pavlovic
// CPSC 411
// Milestone 4
// April 2020
#include "globals.h"
#include "util.h"
#include "scan.h"

char tokenString[MAXTOKENLEN+1];
int string_index = 0; 
char previousTokenString[MAXTOKENLEN+1];
char fullLine[50][MAXTOKENLEN+1];
int characterNumber = 0;
int currentIndex = 0;
int startIndex = 0;
int startIndexAssign = 0;

int replace_char = 0;

%}

%option noyywrap

letter       [a-zA-Z_]
digit        [0-9]
newline      \n

comment      "//"

id           ({letter})({letter}|{digit})*

number       ({digit})*

operator     "+"|"-"|"*"|"/"|"%"|"="|"!"
special      ";"|","|"("|")"|"{"|"}"

%x  STRING_TOKEN
%x  COMMENT_TOKEN
%x  DOUBLE_SLASH
%%

[ \t\r\b\f\']+              ;
{newline}                   {
                                lineno++; characterNumber=0;string_index=0; 
                                startIndex = 0;    
                                for(int i = 0; i < 10; i++)
                                {   
                                    for(int j = 0; j < MAXTOKENLEN+1; j++)
                                    {
                                        fullLine[i][j] = '\0';
                                    }
                                }
                            }

"int"                       {return INT;}
"boolean"                   {return BOOLEAN;}
"void"                      {return VOID;}
"if"                        {return IF;}
"else"                      {return ELSE;}
"else if"                   {return ELSEIF;}
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

{comment}                   {BEGIN COMMENT_TOKEN;}
<COMMENT_TOKEN>\n           {BEGIN 0;}
<COMMENT_TOKEN>\r           {BEGIN 0;}
<COMMENT_TOKEN>.            {;}

{operator}                  {return yytext[0];}
{special}                   {return yytext[0];}

{number}                    {return NUMBER;}
{id}                        {return ID;}

\"                          {BEGIN STRING_TOKEN;}
<STRING_TOKEN>\\\"          {
                            string_index+=2; // Add 2 because these string literals show up as 2 separate characters in a string
                            yymore();
                            }

<STRING_TOKEN>\\\'          {
                            string_index+=2; // Add 2 because these string literals show up as 2 separate characters in a string
                            yymore();
                            }

<STRING_TOKEN>\\\\          {
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
<STRING_TOKEN>\\(b|f)       {replace_char++; string_index+=2; yymore();}
<STRING_TOKEN>\0            {replace_char+=2; string_index++; yymore();}
<STRING_TOKEN>\1            {replace_char+=2; string_index++; yymore();}
<STRING_TOKEN>\1a           {replace_char+=2; string_index++; yymore();}
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
        char new_string[string_index + replace_char];
        int j = 0;
        for(int i = 0; i < string_index; i++)
        {
            if(i < string_index - 1 && yytext[i]=='\\' && yytext[i+1]=='b')
            {
                new_string[j] = '\\';
                j++;
                new_string[j] = '0';
                j++;
                new_string[j] = '8';
                j++;
                i++;
            }
            else if(i < string_index - 1 && yytext[i]=='\\' && yytext[i+1]=='f')
            {
                new_string[j] = '\\';
                j++;
                new_string[j] = '0';
                j++;
                new_string[j] = 'c';
                j++;
                i++;
            }
            else if(yytext[i]=='\0')
            {
                new_string[j] = '\\';
                j++;
                new_string[j] = '0';
                j++;
                new_string[j] = '0';
                j++;
            }
            else if(yytext[i]=='\1')
            {
                new_string[j] = '\\';
                j++;
                new_string[j] = '0';
                j++;
                new_string[j] = '1';
                j++;
            }
            else if(yytext[i]==0x1a)
            {
                new_string[j] = '\\';
                j++;
                new_string[j] = '1';
                j++;
                new_string[j] = 'a';
                j++;
            }
            else
            {
                new_string[j] = yytext[i];
                j++;
            }
        }
        new_string[j] = '\0';
        string_index = 0;
        strncpy(tokenString, new_string, MAXTOKENLEN+1);
    }
    else
    {
        strncpy(tokenString, yytext, MAXTOKENLEN+1);
    }

    strcpy(fullLine[characterNumber], tokenString);
    //Set currentIndex to its index in fullLine
    currentIndex = characterNumber;
    startIndexAssign = currentIndex;
    characterNumber++;

    if (TraceScan)
    {
        printToken(currentToken,tokenString);
    }

    return currentToken;
}
