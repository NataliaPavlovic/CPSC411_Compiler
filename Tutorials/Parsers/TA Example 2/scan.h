/****************************************************/
/* File: scan.h                                     */
/* The scanner interface for EX Compiler            */
/****************************************************/

#ifndef _SCAN_H_
#define _SCAN_H_

#include "globals.h"
//Max size of a token
#define MAXTOKENLEN 40

//Store lexeme of each token
extern char tokenString[MAXTOKENLEN+1];

/* Note: the below vars are used in 
   scanner.flex and parser.y files        */

//Store lexeme of previous tokens
extern char previousTokenString[MAXTOKENLEN+1];
//Store entire current line of tokens
extern char fullLine[10][MAXTOKENLEN+1];

//Return next token in source file
TokenType getToken(int firstTime);

#endif
