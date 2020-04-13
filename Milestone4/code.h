/****************************************************/
/* File: code.h                                     */
/* Code emitting utilities for the C- compiler      */
/* and interface to the TM machine                  */
/*                                                  */
/*                                                  */
/****************************************************/

#ifndef _CODE_H_
#define _CODE_H_

/* pc = program counter  */
#define  pc 7

/* mp = "memory pointer" points
 * to bottom of memory (for temp storage)
 */
#define  gp 6

/* gp = "global pointer" points
 * to maximum address (global
 * variable storage)
 */
#define bp 5

/*fp="frame pointer" points
 *points to current frame in the stack
 */
#define sp 4
 
/* accumulator */
#define  bx 2

/* 2nd accumulator */
#define  ax 1

#define  zero 0

/* code emitting utilities */

/* Procedure emitComment prints a comment line 
 * with comment c in the code file
 */
void emitComment( char * c, int r );

/* Procedure emitRO emits a register-only
 * TM instruction
 * op = the opcode
 * r = target register
 * s = 1st source register
 * t = 2nd source register
 * c = a comment to be printed if TraceCode is TRUE
 */
void emitData( char *op, int offset, char *c);

void emitMemory( int memorySize, char *c);

void emitNumberedLabel( char * op, int r, int number, char *c, int newline);

/* Procedure emitRM emits a register-to-memory
 * TM instruction
 * op = the opcode
 * r = target register
 * d = the offset
 * s = the base register
 * c = a comment to be printed if TraceCode is TRUE
 */
void emitRM( char * op, int r, char *c, int newline);

/* Function emitSkip skips "howMany" code
 * locations for later backpatch. It also
 * returns the current code position
 */
int emitSkip( int howMany);

/* Procedure emitBackup backs up to 
 * loc = a previously skipped location
 */
void emitBackup( int loc);

/* Procedure emitRestore restores the current 
 * code position to the highest previously
 * unemitted position
 */
void emitRestore(void);

/* Procedure emitRM_Abs converts an absolute reference 
 * to a pc-relative reference when emitting a
 * register-to-memory TM instruction
 * op = the opcode
 * r = target register
 * a = the absolute location in memory
 * c = a comment to be printed if TraceCode is TRUE
 */
void emitRM_Abs( char *op, int r, int a, char * c);

#endif

