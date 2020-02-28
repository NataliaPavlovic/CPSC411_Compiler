/****************************************************/
/* File: main.c                                     */
/* Main program for EX Compiler                     */
/****************************************************/

#include "globals.h"
#include "util.h"
#include "scan.h"
#include "parse.h"

/* allocate global variables */
int lineno = 0;
FILE * source;
FILE * output;

/* allocate and set tracing flags */
int TraceScan = TRUE;
int TraceParse = TRUE;
int Error = FALSE;

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
  output = stdout;
  fprintf(output,"\nCompiler: %s\n", fname);
  
  //Set first run to true (Used for scanner)
  int firstTime = 1;
  
  //Enable if you need to debug parser
  //yydebug = 1;
  
  //Call Parser
  syntaxTree = parse();
  //Print Syntax Tree from parser if TraceParse is True
  if (TraceParse) {
    fprintf(output, "\nSyntax tree:\n");
    printTree(syntaxTree);
  }

  //Close Source File
  fclose(source);
  return 0;
}
