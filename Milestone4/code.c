/****************************************************/
/* File: code.c                                     */
/* Code emitting utilities implementation           */
/****************************************************/

#include "globals.h"
#include "code.h"

/* location number for current instruction emission */
static int emitLoc = 0 ;

/* Highest location emitted so far
   For use in conjunction with emitSkip,
   emitBackup, and emitRestore */
static int highEmitLoc = 0;

/* Procedure emitComment prints a comment line 
 * with comment c in the code file
 */
void emitComment( char * c, int r )
{ 
  if (TraceCode) 
    fprintf(code,"%*.*s;; %s\n", r, r, " ", c);
}
//extern FILE* code;  code text file in globals.h

/* Procedure emitRO emits a register-only
 * instruction
 * op = the opcode
 * r = target register
 * s = 1st source register
 * t = 2nd source register
 * c = a comment to be printed if TraceCode is TRUE
 */
void emitData( char *op, int offset, char *c)
{ 
  fprintf(code,"%*.*s(data 0 (i32.const %d) %s)",4,4, " ", offset, op);
  if (TraceCode && c!=NULL) fprintf(code,"\t%s",c) ;
  fprintf(code,"\n") ;
  if (highEmitLoc < emitLoc) highEmitLoc = emitLoc ;
} /* emitRO */


void emitMemory( int memorySize, char *c)
{ 
  fprintf(code,"%*.*s(memory %d)",4,4, " ", memorySize);
  if (TraceCode && c!=NULL) fprintf(code,"\t%s",c) ;
  fprintf(code,"\n") ;
  if (highEmitLoc < emitLoc) highEmitLoc = emitLoc ;
} /* emitRO */

void emitNumberedLabel( char * op, int r, int number, char *c)
{
  fprintf(code,"%*.*s%s%d",r,r, " ", op, number);
  if (TraceCode && c!=NULL) fprintf(code,"\t%s",c) ;
  fprintf(code,"\n") ;
  if (highEmitLoc < emitLoc)  highEmitLoc = emitLoc ;
}

/* Procedure emitRM emits a register-to-memory
 * op = the opcode
 * r = target register
 * d = the offset
 * s = the base register
 * c = a comment to be printed if TraceCode is TRUE
 */
void emitRM( char * op, int r, char *c, int newline)
{ 
  //fprintf(code,"%3d:  %5s  %d,%d(%d) ",emitLoc++,op,r,d,s);
  //printf("[%*.*s%s]", padLen, padLen, padding, myString);  // LEFT Padding 
  fprintf(code,"%*.*s%s",r,r, " ", op);
  if (newline)
  {
    if (TraceCode && c!=NULL) fprintf(code,"\t;; %s",c) ;
    fprintf(code,"\n") ;
  }
  if (highEmitLoc < emitLoc)  highEmitLoc = emitLoc ;
} /* emitRM */

/* Function emitSkip skips "howMany" code
 * locations for later backpatch. It also
 * returns the current code position
 */
int emitSkip( int howMany)
{  int i = emitLoc;
   emitLoc += howMany ;
   if (highEmitLoc < emitLoc)  highEmitLoc = emitLoc ;
   return i;
} /* emitSkip */

/* Procedure emitBackup backs up to 
 * loc = a previously skipped location
 */
void emitBackup( int loc)
{ if (loc > highEmitLoc) emitComment("BUG in emitBackup", 0);
  emitLoc = loc ;
} /* emitBackup */

/* Procedure emitRestore restores the current 
 * code position to the highest previously
 * unemitted position
 */
void emitRestore(void)
{ emitLoc = highEmitLoc;}

/* Procedure emitRM_Abs converts an absolute reference 
 * to a pc-relative reference when emitting a
 * register-to-memory instruction
 * op = the opcode
 * r = target register
 * a = the absolute location in memory
 * c = a comment to be printed if TraceCode is TRUE
 */
void emitRM_Abs( char *op, int r, int a, char * c)
{ fprintf(code,"%3d:  %5s  %d,%d(%d) ",
               emitLoc,op,r,a-(emitLoc+1),pc);
  ++emitLoc ;
  if (TraceCode) fprintf(code,"\t%s",c) ;
  fprintf(code,"\n") ;
  if (highEmitLoc < emitLoc) highEmitLoc = emitLoc ;
} /* emitRM_Abs */

