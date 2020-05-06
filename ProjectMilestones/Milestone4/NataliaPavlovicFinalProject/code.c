// Natalia Pavlovic
// CPSC 411
// Milestone 4
// April 2020
// Code modified from EX Compiler from tutorial

#include "globals.h"
#include "code.h"

/* Procedure emitComment prints a comment line 
 * with comment c in the code file
 */
void emitComment( char * c, int r )
{ 
  if (TraceCode) 
    fprintf(code,"%*.*s;; %s\n", r, r, " ", c);
}

// Outputs global variables
void emitData( char *op, int offset, char *c)
{ 
  fprintf(code,"%*.*s(data 0 (i32.const %d) %s)",4,4, " ", offset, op);
  if (TraceCode && c!=NULL) fprintf(code,"\t%s",c) ;
  fprintf(code,"\n") ;
}

// Outputs memory required
void emitMemory( int memorySize, char *c)
{ 
  fprintf(code,"%*.*s(memory %d)",4,4, " ", memorySize);
  if (TraceCode && c!=NULL) fprintf(code,"\t%s",c) ;
  fprintf(code,"\n") ;
}

// Outputs the WAT code for an instruction string and number combination
void emitNumberedLabel( char * op, int r, int number, char *c, int newline)
{
  fprintf(code,"%*.*s%s%d",r,r, " ", op, number);
  if (newline)
  {
    if (TraceCode && c!=NULL) fprintf(code,"\t;; %s",c) ;
    fprintf(code,"\n") ;
  }
}

// Outputs the WAT code for an instruction string
void emitInstruction( char * op, int r, char *c, int newline)
{ 
  fprintf(code,"%*.*s%s",r,r, " ", op);
  if (newline)
  {
    if (TraceCode && c!=NULL) fprintf(code,"\t;; %s",c) ;
    fprintf(code,"\n") ;
  }
}
