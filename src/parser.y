%{
#include "interpreter.h"
#include "rpcalc.h"
#include "stdio.h"
#include "stdlib.h"
#include "input_handler.h"
#include "output.h"

extern int yylex ();
extern int yyparse ();
extern FILE *yyin;

void yyerror(const char *s);

int rpcalc_input (char *buffer, int *num_bytes_read, int max_bytes_to_read);

%}

%union {
    char *string;
	double number;
	int integer;
}

%token <string> OPERATION IDENTIFIER FILENAME
%token <number> NUMBER
%token <integer> LOOP

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
	   manipulations '\n' { rpPrint(); print_line_start(); }
	   | definition '\n' { print_line_start(); }
	   | FILENAME { read_file($1); }
	   | '\n' { print_line_start(); }
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
		| LOOP { interpret_loop($1, 1); }
		;

declaration:
		OPERATION { interpret_operation($1, 0); }
		| NUMBER { interpret_number($1, 0); }
		| IDENTIFIER { interpret_func_call($1, 0); }
		| '\n' { print_line_start(); }
		| LOOP { interpret_loop($1, 0); }
		;

%%

int main (int argc, char **argv)
{
	init_input_handler();
	print_line_start();
	read_file("rpc_lib/config.rpc");
	yyparse();
	end_input_handler();
	print_newline();
}

void yyerror (const char *s)
{
	printf("Parse error:\n\r\t%s\n\r", s);
	exit(-1);
}
