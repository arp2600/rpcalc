%{
#include "interpreter.h"
#include "rpcalc.h"
#include "stdio.h"
#include "stdlib.h"
#include "input_handler.h"

extern int yylex ();
extern int yyparse ();
extern FILE *yyin;

void yyerror(const char *s);

int rpcalc_input (char *buffer, int *num_bytes_read, int max_bytes_to_read);

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
	  	segments	
	 	;

segments:
		segments segment
		| segment
		;

segment:
	   manipulations '\n' { rpPrint(); }
	   | definition '\n'
	   ;

definition:
		':' IDENTIFIER { interpret_func_definition($2); } declarations ';' { interpret_end_of_func(); }
		;

declarations:
		declarations declaration
		| declaration
		;

manipulations:
		manipulations manipulation
		| manipulation
		;

manipulation:
		OPERATION { interpret_operation($1, 1); }
		| NUMBER { interpret_number($1, 1); }
		| IDENTIFIER { interpret_func_call($1, 1); }
		;

declaration:
		OPERATION { interpret_operation($1, 0); }
		| NUMBER { interpret_number($1, 0); }
		| IDENTIFIER { interpret_func_call($1, 0); }
		| '\n'
		;

%%

int main (int argc, char **argv)
{
	init_input_handler();
	yyparse();
	end_input_handler();
}

void yyerror (const char *s)
{
	printf("Parse error:\n\r\t%s\n\r", s);
	exit(-1);
}
