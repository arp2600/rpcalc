#ifndef _RPCALC_H_
#define _RPCALC_H_

void rpPush (double num);	// push a number onto the stack
void rpAdd ();	// add the top two numbers on the stack
void rpSub ();	// subtract the top two numbers from the stack
void rpMul ();	// multiply the top two numbers on the stack
void rpDiv ();	// divide the top two numbers on the stack
void rpRound ();	// round the top number on the stack (required for factorial among others)
void rpSqrt ();	// square root the top element of the stack
void rpPow ();
// trig operations
void rpSin ();
void rpCos ();
void rpTan ();
void rpSinh ();
void rpCosh ();
void rpTanh ();

void rpPrint ();
void rpDump ();
void rpSwap ();
void rpDup ();

void rpDrop();
void rpCatch();

#endif
