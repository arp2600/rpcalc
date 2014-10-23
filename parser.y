%{
#include "interpreter.h"
#include "rpcalc.h"
#include "stdio.h"
#include "stdlib.h"

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
	   manipulations
	   | definition
	   ;

definition:
		':' IDENTIFIER declarations ';' { printf("End of definition %s\n", $2); }
		;

declarations:
		declarations declaration
		| declarations declaration '\n'
		| declaration '\n'
		| declaration
		| '\n'
		;

manipulations:
		manipulations manipulation
		| manipulations manipulation '\n' { printf("Result from a series of manipulations\n"); }
		| manipulation '\n' { printf("Result from a single manipulation\n"); }
		| manipulation
		| '\n' { printf("Blank line\n"); }
		;

manipulation:
		OPERATION 
		| NUMBER 
		| IDENTIFIER 
		;

declaration:
		OPERATION 
		| NUMBER 
		| IDENTIFIER 
		;

%%

int main (int argc, char **argv)
{
	yyparse();
}

void yyerror (const char *s)
{
	printf("Parse error:\n\t%s\n", s);
	exit(-1);
}
