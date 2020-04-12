/****************************************************/
/* File: main.c                                     */
/* Main program for EX compiler                     */                             */
/****************************************************/

#include "globals.h"

/* set NO_PARSE to TRUE to get a scanner-only compiler */
#define NO_PARSE 0
/* set NO_ANALYZE to TRUE to get a parser-only compiler */
#define NO_ANALYZE 0

/* set NO_CODE to TRUE to get a compiler that does not
 * generate code
 */
#define NO_CODE 0

#include "util.h"
#if NO_PARSE
#include "scan.h"
#else
#include "parse.h"
#if !NO_ANALYZE
#include "analyze.h"
#if !NO_CODE
#include "cgen.h"
#endif
#endif
#endif

/* allocate global variables */
int lineno = 0;
int HighScope = 0;
FILE * source;
FILE * listing;
FILE * code;

/* allocate and set tracing flags */
int EchoSource = TRUE;
int TraceScan = TRUE;
int TraceParse = TRUE;
int TraceAnalyze = TRUE;
int TraceCode = FALSE;

int Error = FALSE;

int main( int argc, char * argv[] )
{ TreeNode * syntaxTree;
  char pgm[120]; /* source code file name */
  if (argc != 2)
    { fprintf(stderr,"usage: %s <filename>\n",argv[0]);
      exit(1);
    }
  strcpy(pgm,argv[1]) ;
  if (strchr (pgm, '.') == NULL)
     strcat(pgm,".CM");
  source = fopen(pgm,"r");
  if (source==NULL)
  { fprintf(stderr,"File %s not found\n",pgm);
    exit(1);
  }
  listing = stdout; /* send listing to screen */
  fprintf(listing,"\nEX COMPILATION: %s\n",pgm);
  
  int firstTime = 1;
  
  if (NO_PARSE)
  {
    fprintf(listing,"Lexing started\n");
    getToken(firstTime);
    firstTime = 0;    
    while (getToken(firstTime)!=ENDFILE);
  }
  else{
    syntaxTree = parse();
    if (TraceParse) {
    fprintf(listing,"\nSyntax tree:\n");
    printTree(syntaxTree);
    }
  }

  if (!NO_ANALYZE){
   // if (! Error)
   // {
      printf("Start Analyzing\n");

      if (TraceAnalyze) fprintf(listing,"\nBuilding Symbol Table...\n");
      buildSymtab(syntaxTree);
      if (TraceAnalyze) fprintf(listing,"\nChecking Types...\n");
      typeCheck(syntaxTree);
      if (TraceAnalyze) fprintf(listing,"\nType Checking Finished\n");
   // }
  }

#if !NO_CODE
  if (Error)
  { 
    char * codefile;
    int fnlen = strcspn(pgm,".");
    codefile = (char *) calloc(fnlen+4, sizeof(char));
    strncpy(codefile,pgm,fnlen);
    strcat(codefile,".tm"); // This generates code file with .tm extension. Yours must be .wat
    code = fopen(codefile,"w");
    if (code == NULL)
    { printf("Unable to open %s\n",codefile);
      exit(1);
    }
    codeGen(syntaxTree,codefile);
    if (TraceCode) 
    fprintf(listing,"\nCode generated in file %s\n",codefile);
    fclose(code);
  }
#endif

  fclose(source);
  return 0;
}