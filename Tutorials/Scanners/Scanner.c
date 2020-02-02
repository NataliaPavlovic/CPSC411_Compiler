// tokens are what the scanner sends to the parser. Anything you want to catch
// Lex matches the longest pattern it can in the rules
// 

%{ //Declarations
	#include <stdio.h>
	enum{
		T-GT=1, 
		T_GE,
		T_EE, 
		T_Being
		T_End, 
		T_ID	// identifiers
	}

	int line = 1;
%}

% //Definitions
alpha [a-zA-Z]
an[a-zA-Z0-9]
%x STRING	// x used because it is not used for anything in C, like s and d are

%% 
//Rules
"\"" { 
		yymore(); // Looking for a quote
		Begin STRING;
	 }

"<STRING\">" Begin 0	// Whatever you were beginning before, it has ended now

<STRING> . yymore(); //
// <STRING>/n

// [" "\t\r] // do nothing
// "\n" line++:
// ">" return T_GT;
// ">=" return T_GE;
// "==" return T_EE;
// "begin" return T_Begin;
// "end" return T_End;
// ({alpha}{an}*) return T_ID
//. return error or print bad character... // catch anything else, invalid token
// .|\n echo;
%%

int main() 
{
	int n;
	while((n=input()!=EOF && n!= "\n"))
	{
		// do nothing
	}

	int t;

	//min = fopen("input.txt", "r");
	//Error handling

	// yytext()
	// yymore()

	//anything you match will return from yylex
	while((t=yylex()))
	{
		printf("Found token %d at line %d", t, line);
	}

	return 0;
}

//yylex - tells main to start reading file and going through your rules -> Will use this
//yylval - Will use it for parser (not scanner)
//yystype - Will not need it
//yytext - what you read?

// -lvl