%option noyywrap
%{

#include "parser.tab.h"
#include "input_handler.h"
#define RETURN_OP { yylval.string = str_duplicate(yytext); return OPERATION; }

int get_input (char *buf, int max_size);
char *str_duplicate(char *string);

#define YY_INPUT(buf,result,max_size) result = get_input(buf,max_size)

%}

%%

 /* Operations */
"+"|"-"|"*"|"/"|"%"|"^"				RETURN_OP
(sin|cos|tan)(h)?					RETURN_OP
rnd|sqrt|dup|swap					RETURN_OP
"dump"|"exit" 						RETURN_OP
drop|catch							RETURN_OP

 /* Identifiers */
([a-zA-Z0-9_]+"/")?[a-zA-Z0-9_]+"."rpc					{ yylval.string = str_duplicate(yytext); return FILENAME; }
[a-zA-Z_][a-zA-Z0-9_]*				{ yylval.string = str_duplicate(yytext); return IDENTIFIER; }

 /* Numbers */
"-"?[0-9]+"."?						{ yylval.number = atof(yytext); return NUMBER; } /* Integers with an optional dot on the end */
"-"?[0-9]*"."[0-9]+					{ yylval.number = atof(yytext); return NUMBER; } /* Floats */
"-"?[0-9]e"-"?[0-9]+				{ yylval.number = atof(yytext); return NUMBER; } /* Integers with exponent */
"-"?[0-9]*"."[0-9]+e"-"?[0-9]+		{ yylval.number = atof(yytext); return NUMBER; } /* Floats with exponent */

`[0-9]+								{ yylval.integer = atof(yytext+1); return LOOP; }

"//".*$								; /* Single line comments */

":"									{ return ':'; }
";"									{ return ';'; }
\n									{ return '\n'; }

 /* Ignore whitespace */
[ \t]								;

 /* Ignore unknown characters */
 .									{ printf("Unrecognized token '%s'\n\r", yytext); }

%%

int get_input (char *buf, int max_size)
{
	//int c = getchar();
	int c = getch();
	return (c == EOF) ? YY_NULL : (buf[0] = c, 1);
}

char *str_duplicate(char *string)
{
	int length = strlen(string);
	char *out = (char*)malloc(length+1);
	strcpy(out, string);
	return out;
}
