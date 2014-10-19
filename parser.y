%{
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"

extern int yylex ();
extern int yyparse ();
extern FILE *yyin;

void yyerror(const char *s);

double stack[1024]; // A stack for number operations
double *stack_ptr = stack - 1;
int stack_size = 0;
void stack_binop (char *string);
void stack_unop (char *string);
void stack_action (char *string);
void stack_push (double num);
void print_float (double num, char *format)
{
	char buffer[64];
	snprintf(buffer, 64, "%f", num);
	for (int i=strlen(buffer)-1; i > 0; i--)
	{
		if (buffer[i] != '0')
		{
			if (buffer[i] == '.')
				buffer[i] = '\0';
			break;
		}
		buffer[i] = '\0';
	}
	printf(format, buffer);
}

%}

%union {
    char *v_string;
	double v_float;
}

%token <v_string> BINOP ACTION UNOP
%token <v_float> NUM

%start rpcalc

%%

rpcalc:
	  	lines
	 	;

lines:
	 	lines line
		| line
		;

line:
		statments '\n' { print_float(stack_ptr[0], "%s\n> "); }

statments:
		statments stack_manipulation
		| stack_manipulation
		;

stack_manipulation:
		BINOP { stack_binop(yylval.v_string); }
		| NUM { stack_push(yylval.v_float); }
		| ACTION { stack_action(yylval.v_string); }
		| UNOP { stack_unop(yylval.v_string); }
		;

%%

void dumpstack ()
{
	if (stack_size < 1)
		return;

	double *i = stack;
	while(i != stack_ptr)
	{
		print_float(i[0], "%s, ");
		i++;
	}
	print_float(i[0], "%s\n");
}

void stack_binop (char *string)
{
	if (stack_size < 2)
		return;
	stack_ptr --;
	stack_size--;

	if (strcmp(string, "+") == 0)
		stack_ptr[0] = stack_ptr[0] + stack_ptr[1];
	else if (strcmp(string, "-") == 0)
		stack_ptr[0] = stack_ptr[0] - stack_ptr[1];
	else if (strcmp(string, "*") == 0)
		stack_ptr[0] = stack_ptr[0] * stack_ptr[1];
	else if (strcmp(string, "/") == 0)
		stack_ptr[0] = stack_ptr[0] / stack_ptr[1];
	else if (strcmp(string, "%") == 0)
		stack_ptr[0] = fmod(stack_ptr[0], stack_ptr[1]);
	else if (strcmp(string, "^") == 0)
		stack_ptr[0] = pow(stack_ptr[0], stack_ptr[1]);
}

void stack_unop (char *string)
{
	if (stack_size < 1)
		return;

	if (strcmp(string, "sin") == 0)
		stack_ptr[0] = sin(stack_ptr[0]);
	else if (strcmp(string, "cos") == 0)
		stack_ptr[0] = cos(stack_ptr[0]);
	else if (strcmp(string, "tan") == 0)
		stack_ptr[0] = tan(stack_ptr[0]);
}

void stack_action (char *string)
{
	if (strcmp(string, "dump") == 0)
		dumpstack();
	else if (strcmp(string, "exit") == 0)
		exit(0);
}

// increase the stack size and push number to the top
void stack_push (double num)
{
	stack_ptr++;
	stack_ptr[0] = num;

	stack_size++;
}

int main (int argc, char **argv)
{
	printf("> ");
	yyparse();
}

void yyerror (const char *s)
{
	printf("Parse error:\n\t%s\n", s);
	//exit(-1);
}
