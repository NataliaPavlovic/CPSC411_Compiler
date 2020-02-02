#include <stdio.h>
#include <ctype.h>

int line = 1;
char * yytext;

struct {
  int TokenType;
  char* TokenStart;
  int TokenLength;
}

// Linked List

int scanner ()
{
	char ch;
	FILE *fp;
	while((ch = getchar() != EOF) && !isspace(ch))
	{
		switch((char) ch)
		{
			case EOF: return 0;
			case '\n': line++;
			case '=': return '=';
			case '>':
				ch = getc(fp);
				// if(ch == "=")
				// {
				// 	return ">=";
				// }
				// else
				// {
				// 	ungetc(ch, fp);
				// 	return ">";
				// }
			default:
				if (isalpha(ch))
				{
					do ch = getc(fp);
					while(isalnum(ch));
					{
						ungetc(ch, fp);
						// return 'ID';
					}
				}
				else
				{
					printf("error");
					// Throw exception and exit
				}
		}
	}
}

int main (){
	// FILE *fp;
	// Open file
}