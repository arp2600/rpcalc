%{
#include "interpreter.h"
#include "rpcalc.h"
#include "stdio.h"
#include "stdlib.h"

extern int yylex ();
extern int yyparse ();
extern FILE *yyin;

void yyerror(const char *s);
%}

%union {
    char *string;
	double number;
}

%token <string> OPERATION IDENTIFIER
%token <number> NUMBER

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
		statements '\n' { rpPrint(); printf("> "); }
		| '\n' { printf("> "); }

statements:
		statements statement
		| statement 
		;

statement:
		OPERATION  { interpret_operation($1); }
		| NUMBER  { interpret_number($1); }
		| IDENTIFIER { interpret_func_call($1); }
		| ':' IDENTIFIER { interpret_func_definition($2); }
		| ';' { interpret_end_of_func(); }
		;

%%

int main (int argc, char **argv)
{
	printf("> ");
	yyparse();
}

void yyerror (const char *s)
{
	printf("Parse error:\n\t%s\n", s);
	exit(-1);
}
