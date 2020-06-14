// Natalia Pavlovic
// CPSC 411
// Milestone 4
// April 2020
// Code modified from EX Compiler from tutorial

#ifndef _CODE_H_
#define _CODE_H_

/* code emitting utilities */

/* Procedure emitComment prints a comment line 
 * with comment c in the code file
 */
void emitComment( char * c, int r );

void emitData( char *op, int offset, char *c);

void emitMemory( int memorySize, char *c);

void emitNumberedLabel( char * op, int r, int number, char *c, int newline);

void emitInstruction( char * op, int r, char *c, int newline);

#endif

