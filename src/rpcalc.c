#include "rpcalc.h"
#include "math.h"
#include "output.h"
#include "stdio.h"
#include "string.h"

// Reverse polish notation calculator programmed in C
double stack[1024];
double *head = stack-1; // The head of the stack
double *top = 0; // The largest value the stack has ever reached

void stack_push()
{
	head++;
	if (head > top)
		top = head;
}

void stack_pop()
{
	head--;
}

// push a number onto the stack
void rpPush (double num)
{
	stack_push();
	head[0] = num;
}

// add the top two numbers on the stack
void rpAdd ()
{
	stack_pop();
	head[0] = head[0] + head[1];
}

// subtract the top two numbers from the stack
void rpSub ()
{
	stack_pop();
	head[0] = head[0] - head[1];
}

// multiply the top two numbers on the stack
void rpMul ()
{
	stack_pop();
	head[0] = head[0] * head[1];
}

// divide the top two numbers on the stack
void rpDiv ()
{
	stack_pop();
	head[0] = head[0] / head[1];
}

// round the top number on the stack (required for factorial among others)
void rpRound ()
{
	head[0] = round(head[0]);
}

// square root the top element of the stack
void rpSqrt ()
{
	head[0] = sqrt(head[0]);
}

void rpPow ()
{
	stack_pop();
	head[0] = pow(head[0], head[1]);
}

// get the factorial of the top element on the stack
void rpFactorial ()
{
	int factorial = 1;
	for (int i = 2; i <= head[0]; i++) {
		factorial *= i;
	}
	head[0] = factorial;
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
	while (ptr < head)
	{
		//print_float(*ptr);
		print_double(*ptr, COLOR_BLUE);
		printf(", ");
		ptr++;
	}

	//print_float(*ptr);
	print_double(*ptr, COLOR_GREEN);
	ptr++;

	while (ptr <= top)
	{
		printf(", ");
		print_double(*ptr, COLOR_YELLOW);
		ptr++;
	}

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
	stack_push();
	head[0] = head[-1];
}

void rpDrop()
{
	stack_pop();
}

void rpCatch()
{
	stack_push();
}
