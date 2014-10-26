#include "rpcalc.h"
#include "math.h"
#include "output.h"
#include "stdio.h"
#include "string.h"

// Reverse polish notation calculator programmed in C
double stack[1024];
double *head = stack-1;

// push a number onto the stack
void rpPush (double num)
{
	head++;
	head[0] = num;
}

// add the top two numbers on the stack
void rpAdd ()
{
	head--;
	head[0] = head[0] + head[1];
}

// subtract the top two numbers from the stack
void rpSub ()
{
	head--;
	head[0] = head[0] - head[1];
}

// multiply the top two numbers on the stack
void rpMul ()
{
	head--;
	head[0] = head[0] * head[1];
}

// divide the top two numbers on the stack
void rpDiv ()
{
	head--;
	head[0] = head[0] / head[1];
}

// round the top number on the stack (required for factorial among others)
void rpRound ()
{
}

// square root the top element of the stack
void rpSqrt ()
{
	head[0] = sqrt(head[0]);
}

void rpPow ()
{
	head--;
	head[0] = pow(head[0], head[1]);
}

// trig operations
void rpSin ()
{
	head[0] = sin(head[0]);
}
void rpCos ()
{
	head[0] = cos(head[0]);
}
void rpTan ()
{
	head[0] = tan(head[0]);
}
void rpSinh ()
{
	head[0] = sinh(head[0]);
}
void rpCosh ()
{
	head[0] = cosh(head[0]);
}
void rpTanh ()
{
	head[0] = tanh(head[0]);
}

void rpPrint ()
{
	print_double(*head, COLOR_GREEN);
	print_newline();
}

void rpDump ()
{
	if (head == stack-1)
		return;

	double *ptr = stack;
	while (ptr != head)
	{
		//print_float(*ptr);
		print_double(*ptr, COLOR_RED);
		printf(", ");
		ptr++;
	}
	//print_float(*ptr);
	print_double(*ptr, COLOR_RED);
	print_newline();
}

void rpSwap ()
{
	double t = head[0];
	head[0] = head[-1];
	head[-1] = t;
}

void rpDup ()
{
	head++;
	head[0] = head[-1];
}

void rpDrop()
{
	head--;
}

void rpCatch()
{
	head++;
}
