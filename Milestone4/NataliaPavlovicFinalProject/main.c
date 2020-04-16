// Natalia Pavlovic
// CPSC 411
// Milestone 4
// April 2020
// Code modified from EX Compiler from tutorial

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
FILE * source;
FILE * listing;
FILE * code;

/* allocate and set tracing flags */
int EchoSource = 0;
int TraceScan = 0;
int TraceParse = 1;
int TraceAnalyze = 0;
int TraceCode = 1;

int Error = 0;

int main( int argc, char * argv[] ) { 
  
  TreeNode * syntaxTree;
  
  //Source File
  char fname[120];
  
  //Error handling for source file
  if (argc != 2)
    { fprintf(stderr,"Usage: %s <filename>\n", argv[0]);
      exit(1);
    }
  
  //Copy source filename onto var  
  strcpy(fname,argv[1]);
  //Open Source File 
  source = fopen(fname, "r");
  
  //File Not Found Handler
  if (source == NULL) {
    fprintf(stderr,"File %s not found\n", fname);
    exit(1);
  }
  
  //Send output to terminal screen
  listing = stdout;
  fprintf(listing,"\nCompiler: %s\n", fname);
  
  //Set first run to true (Used for scanner)
  int firstTime = 1;
  
  //Enable if you need to debug parser
  //yydebug = 1;
  
  //Call Parser
  syntaxTree = parse();
  //Print Syntax Tree from parser if TraceParse is True
  if (TraceParse) {
    fprintf(listing, "\nSyntax tree:\n");
    printTree(syntaxTree);
  }

  #if !NO_ANALYZE
  if (! Error)
  { if (TraceAnalyze) fprintf(listing,"\nBuilding Symbol Table...\n");
    buildSymtab(syntaxTree);
    if (TraceAnalyze) fprintf(listing,"\nChecking Types...\n");
    typeCheck(syntaxTree);
    if (TraceAnalyze) fprintf(listing,"\nType Checking Finished\n");
  }

  // Print Annotated AST if there are no errors
  if(! Error)
  {
    if (TraceAnalyze) {
      fprintf(listing, "\nAnnotated Syntax tree:\n");
      printAnnotatedTree(syntaxTree);
    }
  }
  
  #if !NO_CODE
  if (! Error)
  { 
    char * codefile;
    int fnlen = strcspn(fname,".");
    if(fname[fnlen+1] == 'j')
    {
      codefile = (char *) calloc(fnlen+4+1, sizeof(char));
      strncpy(codefile,fname,fnlen+2);
      codefile[fnlen] = '_';
    }
    else
    {
      codefile = (char *) calloc(fnlen+4+3, sizeof(char));
      strncpy(codefile,fname,fnlen+4);
      codefile[fnlen] = '_';
    }

    strncpy(codefile,fname,fnlen);
    strcat(codefile,".wat");
    code = fopen(codefile,"w");
    if (code == NULL)
    { 
      printf("Unable to open %s\n",codefile);
      exit(1);
    }
    codeGen(syntaxTree,codefile);
    fclose(code);
  }
  #endif
  #endif

  //Close Source File
  fclose(source);
  return 0;
}
